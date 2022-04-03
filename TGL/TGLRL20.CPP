// ??? someone must initialize the IRL GUIDs
#define INITGUID

#include "tglRL20.h"

namespace RL20Impl
{

static int              g_refCount = 0;
RL20::RendererDataType  RL20::g_theRenderer = &g_refCount;

RL20::ViewportAppData::ViewportAppData()
{
    Result  result;

    m_lightFrame            = RLCreateFrame(0);
    m_camera                = 0;
    m_lastRenderedFrame     = 0;
    m_backgroundColorRed    = 0;
    m_backgroundColorGreen  = 0;
    m_backgroundColorBlue   = 0;

    assert(m_lightFrame);
    // NOTE: ref count of m_lightFrame is now 0
    assert(RLObjectGetReferenceCount(m_lightFrame) == 0);

    // ??? will inserting then removing a light cause this light group
    // to get destroyed - if so, we must bump the ref count here...
    result = ResultVal(RLObjectReference(m_lightFrame));
    assert(Succeeded(result));

}

RL20::ViewportAppData::~ViewportAppData()
{
    Result  result;

    // ??? RL bug (?): if we don't remove the child light frames here, before
    // m_lightFrame is destroyed,  RLFrameGetParent() of a child light frame
    // after m_lightFrame is destroyed will crash in RL.
    {
        int         childFramesCount;
        int         i;
        RLFrame*    pChildFrames;

        result = ResultVal(RLFrameGetChildren(m_lightFrame,
                                              &childFramesCount,
                                              &pChildFrames));
        assert(Succeeded(result));

        for (i = 0; i < childFramesCount; i++)
        {
            assert(RLFrameGetParent(pChildFrames[i]) == m_lightFrame);
            assert(RLObjectGetReferenceCount(pChildFrames[i]) > 0);
            RLFrameRemoveChild(m_lightFrame, pChildFrames[i]);
        }
        RLFree(pChildFrames);
    }

    result = ResultVal(RLObjectDestroy(m_lightFrame));
    assert(Succeeded(result));
}

Result
RL20::ViewportCreateAppData(ViewDataType view,
                            CameraDataType camera)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = new ViewportAppData();
    assert(pViewportAppData);
    pViewportAppData->m_camera = camera;

    assert(!RLObjectGetAppData(view));
    assert(sizeof(pViewportAppData) <= sizeof(unsigned long));
    result = ResultVal(RLObjectSetAppData(view, reinterpret_cast<unsigned long>(pViewportAppData)));
    assert(Succeeded(result));
    assert(reinterpret_cast<ViewportAppData*>(RLObjectGetAppData(view)) == pViewportAppData);

    if (Succeeded(result))
    {
        // pass ViewportAppData as argument to destroy callback to avoid the problem
        // of accessing view while it is being destroyed
        result = ResultVal(RLObjectAddDestroyCallback(view,
                                                      ViewportDestroyCallback,
                                                      pViewportAppData));
        assert(Succeeded(result));
    }

    if (!Succeeded(result))
    {
        delete pViewportAppData;
        RLObjectSetAppData(view, 0);
    }

    return result;
}

Result
RL20::ViewPick(ViewDataType view,
               unsigned long x,
               unsigned long y,
               const TglImpl::GroupImpl<RL20>** ppGroupsToPickFrom,
               int groupsToPickFromCount,
               const Group**& rppPickedGroups,
               int& rPickedGroupCount)
{
    RLPickRecord*   pTopLevelFrameHierarchies;
    int             topLevelFrameHierarchyCount;
    Result          result;

    rppPickedGroups = 0;
    rPickedGroupCount = 0;
    result = ResultVal(RLViewportPick(view,
                                      x, y,
				                      &topLevelFrameHierarchyCount,
				                      &pTopLevelFrameHierarchies));
    assert(Succeeded(result));
    
    if (Succeeded(result) && pTopLevelFrameHierarchies)
    {
        // pTopLevelFrameHierarchies is a sequence of "toplevel frame hierarchies",
        // each which is under the point <x, y>, in foreground-to-background order

        if (topLevelFrameHierarchyCount > 0)
        {
            RLFrame*    pFrameHierarchy;
            int         frameHierarcyDepth;

            // foreground-to-background order - we want the foreground-most hierarchy
            pFrameHierarchy = pTopLevelFrameHierarchies[0].frames;
            frameHierarcyDepth = pTopLevelFrameHierarchies[0].frame_count;

            assert(pFrameHierarchy);

            if (pFrameHierarchy && (frameHierarcyDepth > 0))
            {
                // top-down order
                // i.e. scene at index 0, toplevel-roi's group at index 1, etc.

                // NOTE: the returned array represents how the structure was
                //       at last render time

                rppPickedGroups = new const Group*[frameHierarcyDepth];
                rPickedGroupCount = frameHierarcyDepth;

                for (int i = 0; i < frameHierarcyDepth; i++)
                {
                    RLFrame frame = pFrameHierarchy[i];

                    assert(frame);

                    // map from frame to pGroup given passed in data structure
                    // of Groups
                    rppPickedGroups[i] = 0;
                    for (int j = 0; j < groupsToPickFromCount; j++)
                    {
                        if (*ppGroupsToPickFrom[j] == frame)
                        {
                            // ??? should we increase ref count or not when we
                            //     insert a group into this array
                            rppPickedGroups[i] = ppGroupsToPickFrom[j];
                            break;
                        }
                    }
                }
            }
        }

        RLFreePickRecords(topLevelFrameHierarchyCount, pTopLevelFrameHierarchies);
    }

    return result;
}

void
RL20::ViewportDestroyCallback(RLObject object, void* pArg)
{
    ViewportAppData*    pViewportAppData = reinterpret_cast<ViewportAppData*>(pArg);
    Result              result;

    assert(static_cast<RLViewport>(object));
    assert(pViewportAppData);
    

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_lastRenderedFrame,
                                         pViewportAppData->m_camera,
                                         pViewportAppData->m_lightFrame);
    assert(Succeeded(result));

    delete pViewportAppData;

    result = ResultVal(RLObjectRemoveDestroyCallback(object,
						                             ViewportDestroyCallback,
                                                     pArg));

    assert(Succeeded(result));

    result = ResultVal(RLObjectSetAppData(object, 0));
    assert(Succeeded(result));
}

Result
RL20::RendererCreateMesh(RendererDataType,
                         unsigned long vertexCount,
                         const float (*pVertices)[3],
                         const float (*pTextureCoordinates)[2],
                         int* pFaceData,
                         MeshDataType& rMesh)
{
    // Face data is:
    //  [face1VertexCount face1Vertex1index, ... face1VertexMindex
    //   face2VertexCount face2Vertex1index, ... face2VertexNindex
    //   ...
    //   0]

    Result  result;

    rMesh = RLCreateMesh();

    result = (rMesh != 0) ? Success : Error;

    if (Succeeded(result))
    {
        RLVector*       pRLVertices;

        RLObjectReference(rMesh);

        // verify assumption about RLVector and float arrays
        assert(sizeof(RLVector) == (3 * sizeof(float)));       // structure member alignment
        assert(sizeof(RLVector[2]) == (2 * 3 * sizeof(float)));// structure alignment
        assert(sizeof(((RLVector*) 0)->x) == sizeof(pVertices[0][0]));
        assert(sizeof(((RLVector*) 0)->y) == sizeof(pVertices[0][1]));
        assert(sizeof(((RLVector*) 0)->z) == sizeof(pVertices[0][2]));
        assert(offsetof(RLVector, x) == ((&pVertices[0][0] - &pVertices[0][0]) * sizeof(pVertices[0][0])));
        assert(offsetof(RLVector, y) == ((&pVertices[0][1] - &pVertices[0][0]) * sizeof(pVertices[0][0])));
        assert(offsetof(RLVector, z) == ((&pVertices[0][2] - &pVertices[0][0]) * sizeof(pVertices[0][0])));

        pRLVertices = reinterpret_cast<RLVector*>(const_cast<float(*)[3]>(pVertices));

        // ??? ReserveSpace()
        result = ResultVal(RLMeshAddFaces(rMesh, vertexCount, pRLVertices,
			                              0, 0,
			                              pFaceData, 0, 0));

        if (Succeeded(result) && pTextureCoordinates)
        {
            unsigned long   i;

            for (i = 0; (i < vertexCount) && Succeeded(result); i++)
            {
                result = ResultVal(RLMeshSetTextureCoordinates(rMesh,
                                                               i,
                                                               pTextureCoordinates[i][0],
                                                               pTextureCoordinates[i][1]));
            }

            if (Succeeded(result))
            {
                Result  result2;

                result2 = MeshSetTextureMappingMode(rMesh, Linear);
                assert(Succeeded(result));
            }
        }
    }

    return result;
}

Result
RL20::TextureSetImage(TextureDataType texture, Image* pImage)
{
    unsigned long   appData;
    Result          result;

    assert(sizeof(pImage) <= sizeof(appData));
    appData = reinterpret_cast<unsigned long>(pImage);
    assert(reinterpret_cast<Image*>(appData) == pImage);

    if (TextureGetImage(texture))
    {
        // ??? not handled yet
        assert(0);
    }

    result = ResultVal(RLObjectSetAppData(texture, appData));
    assert(Succeeded(result));

    if (Succeeded(result) && pImage)
    {
        result = ResultVal(RLObjectAddDestroyCallback(texture,
                                                      RLTextureDestroyCallback,
                                                      pImage));
        assert(Succeeded(result));

        if (!Succeeded(result))
        {
            RLObjectSetAppData(texture, 0);
        }
    }

    return result;
}

void
RL20::RLTextureDestroyCallback(RLObject object, void* pArg)
{
    Image*  pImage = reinterpret_cast<Image*>(pArg);
    Result  result;

    assert(pImage);
    delete pImage;

    result = ResultVal(RLObjectRemoveDestroyCallback(object,
						                             RLTextureDestroyCallback,
                                                     pArg));
    assert(Succeeded(result));

    result = ResultVal(RLObjectSetAppData(object, 0));
    assert(Succeeded(result));
}

RL20::Image::Image(int width, int height, int bitsPerTexel,
                   const void* pTexels, int pTexelsArePersistent,
                   int paletteEntryCount, const PaletteEntry* pEntries)
{
    Result  result;

    RLImage::width                  = 0;
    RLImage::height                 = 0;
    RLImage::aspectx                = 1;
    RLImage::aspecty                = 1;
    RLImage::depth                  = 0;
    RLImage::rgb                    = FALSE;
    RLImage::bytes_per_line         = 0;
    RLImage::buffer1                = 0;
    RLImage::buffer2                = 0;
    RLImage::red_mask               = 0xff;  // ???
    RLImage::green_mask             = 0xff;  // ???
    RLImage::blue_mask              = 0xff;  // ???
    RLImage::alpha_mask             = 0xff;  // ???
    RLImage::palette_size           = 0;
    RLImage::palette                = 0;
    m_texels_allocated_by_client    = FALSE;

    if (pTexels)
    {
        result = SetTexels(width, height, bitsPerTexel, pTexels, pTexelsArePersistent);
        assert(Succeeded(result));
    }
    else
    {
        // ??? RL20 Bug/Issue:
        // cannot create a texture w/ an image w/ buffer1 non-NULL 
        int     width = 4;
        int     height = 4;
        int     bitsPerTexel = 8;
        char    texels[4 * 4];

        memset(texels, 0, sizeof(texels)/sizeof(texels[0]));
        result = SetTexels(width, height, bitsPerTexel, texels, FALSE);
        assert(Succeeded(result));
    }

    if (pEntries)
    {
        result = SetPalette(paletteEntryCount, pEntries);
        assert(Succeeded(result));
    }
    else
    {
        // ??? RL20 Bug/Issue:
        // cannot create a texture w/ an image w/ buffer1 non-NULL 
        PaletteEntry    entry = { 0, 0, 0 };
        int             noOfEntries = 1;
        
        result = SetPalette(noOfEntries, &entry);
        assert(Succeeded(result));
    }
}

RL20::Image::~Image()
{
    if (!m_texels_allocated_by_client)
    {
        // buffer was allocated by us before
        delete [] RLImage::buffer1;
    }
    delete [] RLImage::palette;
}

inline int IsPowerOfTwo(int n)
{
    int remainder = 0;

    // ??? better way: return ((~x + 1) & x) == x;
    while ((n > 2) && !remainder)
    {
        remainder = n % 2;
        n /= 2;
    }

    return ((n == 2) && !remainder);
}

Result
RL20::Image::SetTexels(int width, int height, int bitsPerTexel,
                       const void* pTexels, int texelsArePersistent)
{
    // ??? assuming each Texel in pPixels occupies exactly
    //     bitsPerTexel bits in pTexels
    int     bytesPerScanline = width;

    // width and height must be powers of two
    assert(IsPowerOfTwo(width));
    assert(IsPowerOfTwo(height));
    // bytesPerScanline must be multiple of 4
    assert((bytesPerScanline % 4) == 0);

    if (!IsPowerOfTwo(width) ||
        !IsPowerOfTwo(height) ||
        ((bytesPerScanline % 4) != 0))
    {
        return Error;
    }

    RLImage::width           = width;
    RLImage::height          = height;
    RLImage::depth           = bitsPerTexel;
    RLImage::bytes_per_line  = bytesPerScanline;

    if (!m_texels_allocated_by_client)
    {
        // buffer was allocated by us before
        delete [] RLImage::buffer1;
        RLImage::buffer1  = 0;
    }

    if (texelsArePersistent)
    {
        RLImage::buffer1  = const_cast<void*>(pTexels);
        m_texels_allocated_by_client = TRUE;
    }
    else
    {
        size_t  byteCount = bytesPerScanline * height;

        RLImage::buffer1  = new char[byteCount];
        memcpy(RLImage::buffer1, pTexels, byteCount);
        m_texels_allocated_by_client = FALSE;
    }

    return Success;
}

Result
RL20::Image::SetPalette(int entryCount, const PaletteEntry* pEntries)
{
    int     i;

    if (RLImage::palette_size != entryCount)
    {
        if (RLImage::palette)
        {
            delete [] RLImage::palette;
            RLImage::palette         = 0;
            RLImage::palette_size    = 0;
        }
        if (entryCount > 0)
        {
            RLImage::palette         = new RLPaletteEntry[entryCount];
            RLImage::palette_size    = entryCount;
        }
    }

    for (i = 0; i < entryCount; i++)
    {
        RLImage::palette[i].red      = (unsigned char) pEntries[i].m_red;
        RLImage::palette[i].green    = (unsigned char) pEntries[i].m_green;
        RLImage::palette[i].blue     = (unsigned char) pEntries[i].m_blue;
        RLImage::palette[i].flags    = RLPaletteReadOnly;
    }

    return Success;
}

}   // namespace RL20Impl


namespace Tgl
{

Renderer* 
CreateRenderer()
{
    TglImpl::RendererImpl<RL20Impl::RL20>* pRenderer;

    pRenderer = new TglImpl::RendererImpl<RL20Impl::RL20>;
    if (!pRenderer->Create())
    {
        delete pRenderer;
        pRenderer = 0;
    }

    assert(pRenderer);
    
    return pRenderer;
}

}   // namespace Tgl

