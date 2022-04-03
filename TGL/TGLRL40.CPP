#define INITGUID
#include "tglRL40.h"

namespace D3DRMImpl
{

D3DRM::RendererDataType    D3DRM::g_pTheRenderer = 0;

D3DRM::ViewportAppData::ViewportAppData(RendererDataType pD3DRM)
{
    Result  result;

    result = ResultVal(pD3DRM->CreateFrame(0, &m_pLightFrame));
    assert(Succeeded(result));

    m_pCamera               = 0;
    m_pLastRenderedFrame    = 0;
    m_backgroundColorRed    = 0;
    m_backgroundColorGreen  = 0;
    m_backgroundColorBlue   = 0;
}

D3DRM::ViewportAppData::~ViewportAppData()
{
    int     refCount;
    Result  result;

     // ??? D3DRM bug: if we don't remove the child light frames here, before
    // m_pLightFrame is destroyed,  GetParent() of a child light frame
    // after m_pLightFrame is destroyed will crash in D3DRM.
    // this can be demonstarted e.g. using the Lego demo app when resizing the window;
    // then, the view is destroyed, and thus the light frame, while the lights are
    // still kept "alive", then a new view is created and the lights are inserted
    // in the new view's light frame - that causes a crash
#define AVOID_BUG 1
#define TEST_IF_BUG_HAS_BEEN_FIXED 0

#if AVOID_BUG
    IDirect3DRMFrameArray*  pChildFrames;
    IDirect3DRMFrame*       pChildFrame = 0;
    int                     i;

    result = ResultVal(m_pLightFrame->GetChildren(&pChildFrames));
    assert(Succeeded(result));

    for (i = 0; i < (int) pChildFrames->GetSize(); i++)
    {
        result = ResultVal(pChildFrames->GetElement(i, &pChildFrame));
        assert(Succeeded(result));

#if !TEST_IF_BUG_HAS_BEEN_FIXED
        result = ResultVal(m_pLightFrame->DeleteChild(pChildFrame));
        assert(Succeeded(result));
#endif /* !TEST_IF_BUG_HAS_BEEN_FIXED */

        refCount = pChildFrame->Release();  // GetElement() does AddRef()

        // if light is deleted, but not removed from view
        // then refCount will be 0 here...
        assert(refCount >= 1);
    }
    refCount = pChildFrames->Release();
    assert(refCount == 0);
#endif /* AVOID_BUG */

    refCount = m_pLightFrame->Release();
    assert(refCount == 0);

    // execute the following lines to test if bug has been fixed
#if TEST_IF_BUG_HAS_BEEN_FIXED
    IDirect3DRMFrame*   pParentFrame;

    assert(pChildFrame);

    // the following line crashes if bug has not been fixed
    result = ResultVal(pChildFrame->GetParent(&pParentFrame));
    assert(Succeeded(result));

    // if we reach this point the bug has been fixed
    assert(0);
#endif /* TEST_IF_BUG_HAS_BEEN_FIXED */
}

Result
D3DRM::ViewportCreateAppData(RendererDataType pD3DRM,
                             ViewDataType pViewport,
                             CameraDataType pCamera)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = new ViewportAppData(pD3DRM);
    assert(pViewportAppData);
    pViewportAppData->m_pCamera = pCamera;

    assert(!pViewport->GetAppData());
    assert(sizeof(pViewportAppData) <= sizeof(unsigned long));
    result = ResultVal(pViewport->SetAppData(reinterpret_cast<unsigned long>(pViewportAppData)));
    assert(Succeeded(result));
    assert(reinterpret_cast<ViewportAppData*>(pViewport->GetAppData()) == pViewportAppData);

    if (Succeeded(result))
    {
        // pass ViewportAppData as argument to destroy callback to avoid the problem
        // of accessing view while it is being destroyed
        result = ResultVal(pViewport->AddDestroyCallback(ViewportDestroyCallback,
                                                         pViewportAppData));
        assert(Succeeded(result));
    }

    if (!Succeeded(result))
    {
        delete pViewportAppData;
        pViewport->SetAppData(0);
    }

    return result;
}

void
D3DRM::ViewportDestroyCallback(IDirect3DRMObject* pObject, void* pArg)
{
    ViewportAppData*    pViewportAppData = reinterpret_cast<ViewportAppData*>(pArg);
    Result              result;

    assert(static_cast<ViewDataType>(pObject));
    assert(pViewportAppData);
    

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_pLastRenderedFrame,
                                         pViewportAppData->m_pCamera,
                                         pViewportAppData->m_pLightFrame);
    assert(Succeeded(result));

    delete pViewportAppData;
}

Result
D3DRM::ViewPick(ViewDataType pViewport,
                unsigned long x,
                unsigned long y,
                const TglImpl::GroupImpl<D3DRM>** ppGroupsToPickFrom,
                int groupsToPickFromCount,
                const Group**& rppPickedGroups,
                int& rPickedGroupCount)
{
    IDirect3DRMPickedArray* pTopLevelFrameHierarchies;
    Result                  result;

    rppPickedGroups = 0;
    rPickedGroupCount = 0;
    result = ResultVal(pViewport->Pick(x, y, &pTopLevelFrameHierarchies));
    assert(Succeeded(result));
    
    if (Succeeded(result) && pTopLevelFrameHierarchies)
    {
        // pTopLevelFrameHierarchies is a sequence of "toplevel frame hierarchies",
        // each which is under the point <x, y>, in foreground-to-background order

        if (pTopLevelFrameHierarchies->GetSize() > 0)
        {
            IDirect3DRMVisual*      pVisual;
            IDirect3DRMFrameArray*  pFrameHierarchy;
            D3DRMPICKDESC           pickDesc;

            // foreground-to-background order - we want the foreground-most hierarchy
            result = ResultVal(pTopLevelFrameHierarchies->GetPick(0,
                                                                  &pVisual,
                                                                  &pFrameHierarchy,
                                                                  &pickDesc));
            assert(Succeeded(result));

            if (Succeeded(result) && pFrameHierarchy)
            {
                int hierarchyDepth = pFrameHierarchy->GetSize();

                if (hierarchyDepth > 0)
                {
                    // top-down order
                    // i.e. scene at index 0, toplevel-roi's group at index 1, etc.
   
                    // NOTE: the returned array represents how the structure was
                    //       at last render time

                    rppPickedGroups = new const Group*[hierarchyDepth];
                    rPickedGroupCount = hierarchyDepth;

                    for (int i = 0; i < hierarchyDepth; i++)
                    {
                        IDirect3DRMFrame*   pFrame;

                        result = ResultVal(pFrameHierarchy->GetElement(i, &pFrame));
                        assert(Succeeded(result));

                        // map from pFrame to pGroup given passed in data structure
                        // of Groups
                        rppPickedGroups[i] = 0;
                        for (int j = 0; j < groupsToPickFromCount; j++)
                        {
                            if (*ppGroupsToPickFrom[j] == pFrame)
                            {
                                // ??? should we increase ref count or not when we
                                //     insert a group into this array
                                rppPickedGroups[i] = ppGroupsToPickFrom[j];
                                break;
                            }
                        }
                        pFrame->Release(); // GetElement()
                    }
                }

                pVisual->Release();
                pFrameHierarchy->Release();
            }
        }

        pTopLevelFrameHierarchies->Release();
    }

    return result;
}

Result
D3DRM::TextureSetImage(TextureDataType pTexture,
                       Image* pImage)
{
    unsigned long   appData;
    Result          result;

    assert(sizeof(pImage) <= sizeof(appData));
    appData = reinterpret_cast<unsigned long>(pImage);
    assert(reinterpret_cast<Image*>(appData) == pImage);

    if (TextureGetImage(pTexture))
    {
        // ??? not handled yet
        assert(0);
    }

    result = ResultVal(pTexture->SetAppData(appData));
    assert(Succeeded(result));

    if (Succeeded(result) && pImage)
    {
        result = ResultVal(pTexture->AddDestroyCallback(TextureDestroyCallback,
                                                             pImage));
        assert(Succeeded(result));

        if (!Succeeded(result))
        {
            pTexture->SetAppData(0);
        }
    }

    return result;
}

void
D3DRM::TextureDestroyCallback(IDirect3DRMObject* pObject, void* pArg)
{
    Image* pImage = reinterpret_cast<Image*>(pArg);

    assert(pImage);
    delete pImage;
}

D3DRM::Image::Image(int width, int height, int bitsPerTexel,
                    const void* pTexels, int pTexelsArePersistent,
                    int paletteEntryCount, const PaletteEntry* pEntries)
{
    Result  result;

    D3DRMIMAGE::width               = 0;
    D3DRMIMAGE::height              = 0;
    D3DRMIMAGE::aspectx             = 1;
    D3DRMIMAGE::aspecty             = 1;
    D3DRMIMAGE::depth               = 0;
    D3DRMIMAGE::rgb                 = FALSE;
    D3DRMIMAGE::bytes_per_line      = 0;
    D3DRMIMAGE::buffer1             = 0;
    D3DRMIMAGE::buffer2             = 0;
    D3DRMIMAGE::red_mask            = 0xff;  // ???
    D3DRMIMAGE::green_mask          = 0xff;  // ???
    D3DRMIMAGE::blue_mask           = 0xff;  // ???
    D3DRMIMAGE::alpha_mask          = 0xff;  // ???
    D3DRMIMAGE::palette_size        = 0;
    D3DRMIMAGE::palette             = 0;
    m_texels_allocated_by_client    = FALSE;

    if (pTexels)
    {
        result = SetTexels(width, height, bitsPerTexel, pTexels, pTexelsArePersistent);
        assert(Succeeded(result));
    }

    if (pEntries)
    {
        result = SetPalette(paletteEntryCount, pEntries);
        assert(Succeeded(result));
    }
}

D3DRM::Image::~Image()
{
    if (!m_texels_allocated_by_client)
    {
        // buffer was allocated by us before
        delete [] D3DRMIMAGE::buffer1;
    }
    delete [] D3DRMIMAGE::palette;
}

inline int IsPowerOfTwo(int n)
{
    int remainder = 0;

    // ??? better way: return (((~x) + 1) & x) == x;
    while ((n > 2) && !remainder)
    {
        remainder = n % 2;
        n /= 2;
    }

    return ((n == 2) && !remainder);
}

Result
D3DRM::Image::SetTexels(int width, int height, int bitsPerTexel,
                        const void* pTexels, int texelsArePersistent)
{
    // ??? assuming each Texel in pTexels occupies exactly
    //     bitsPerTexel bits in pTexels
    int     bytesPerScanline = width;

    assert(IsPowerOfTwo(width));            // width must be power of two
    assert(IsPowerOfTwo(height));           // height must be power of two
    assert((bytesPerScanline % 4) == 0);    // bytesPerScanline must be multiple of 4

    if (!IsPowerOfTwo(width) ||
        !IsPowerOfTwo(height) ||
        ((bytesPerScanline % 4) != 0))
    {
        return Error;
    }

    // ??? seems like system hangs if attempting to change buffer1...
    assert(!D3DRMIMAGE::buffer1 || (D3DRMIMAGE::buffer1 == pTexels));
    
    D3DRMIMAGE::width           = width;
    D3DRMIMAGE::height          = height;
    D3DRMIMAGE::depth           = bitsPerTexel;
    D3DRMIMAGE::bytes_per_line  = bytesPerScanline;

    if (!m_texels_allocated_by_client)
    {
        // buffer was allocated by us before
        delete [] D3DRMIMAGE::buffer1;
        D3DRMIMAGE::buffer1  = 0;
    }

    if (texelsArePersistent)
    {
        D3DRMIMAGE::buffer1  = const_cast<void*>(pTexels);
        m_texels_allocated_by_client = TRUE;
    }
    else
    {
        size_t  byteCount = bytesPerScanline * height;

        D3DRMIMAGE::buffer1  = new char[byteCount];
        memcpy(D3DRMIMAGE::buffer1, pTexels, byteCount);
        m_texels_allocated_by_client = FALSE;
    }

    return Success;
}

Result
D3DRM::Image::SetPalette(int entryCount,
                         const PaletteEntry* pEntries)
{
    int     i;

    if (D3DRMIMAGE::palette_size != entryCount)
    {
        if (D3DRMIMAGE::palette)
        {
            delete [] D3DRMIMAGE::palette;
            D3DRMIMAGE::palette         = 0;
            D3DRMIMAGE::palette_size    = 0;
        }
        if (entryCount > 0)
        {
            D3DRMIMAGE::palette         = new D3DRMPALETTEENTRY[entryCount];
            D3DRMIMAGE::palette_size    = entryCount;
        }
    }

    for (i = 0; i < entryCount; i++)
    {
        D3DRMIMAGE::palette[i].red      = (unsigned char) pEntries[i].m_red;
        D3DRMIMAGE::palette[i].green    = (unsigned char) pEntries[i].m_green;
        D3DRMIMAGE::palette[i].blue     = (unsigned char) pEntries[i].m_blue;
        D3DRMIMAGE::palette[i].flags    = D3DRMPALETTE_READONLY;
    }

    return Success;
}

}   // namespace D3DRMImpl


namespace Tgl
{
    
Renderer* CreateRenderer()
{
    TglImpl::RendererImpl<D3DRMImpl::D3DRM>* pRenderer;

    pRenderer = new TglImpl::RendererImpl<D3DRMImpl::D3DRM>;
    if (!pRenderer->Create())
    {
        delete pRenderer;
        pRenderer = 0;
    }

    assert(pRenderer);
    
    return pRenderer;
}

}   // namespace Tgl
