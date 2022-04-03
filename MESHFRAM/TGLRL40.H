#ifndef _tglD3DRM_h
#define _tglD3DRM_h

#include "tglImpl.h"    // TGL Implementation template
#include "d3drm.h"	    // Direct3D Retained Mode
#include "d3drmwin.h"
#include "limits.h"     // UCHAR_MAX
#include "math.h"       // tan()

//////////////////////////////////////////////////////////////////////////////
//
// D3DRM meta definition
//

namespace D3DRMImpl
{

struct MeshData
{
	IDirect3DRMMesh*   mesh;
	IDirect3DRMFrame*  frame;
};

using namespace Tgl;

struct D3DRM
{
    typedef IDirect3DRM*            RendererDataType;
    typedef IDirect3DRMDevice*      DeviceDataType;
    typedef IDirect3DRMViewport*    ViewDataType;
    typedef IDirect3DRMFrame*	    CameraDataType;
    typedef IDirect3DRMFrame*       GroupDataType;
    typedef IDirect3DRMFrame*	    LightDataType;
    typedef MeshData*        MeshDataType;
    typedef IDirect3DRMTexture*     TextureDataType;

    // Renderer
    static Result   RendererCreate(IDirect3DRM*&);
    static void     RendererDestroy(IDirect3DRM*);
    static Result   RendererCreateDevice(IDirect3DRM*,
                                         const DeviceDirectDrawCreateData&,
                                         IDirect3DRMDevice*&);
    static Result   RendererCreateDevice(IDirect3DRM*,
                                         const DeviceDirect3DCreateData&,
                                         IDirect3DRMDevice*&);
    static Result   RendererCreateView(IDirect3DRM*,
                                       const IDirect3DRMDevice*,
                                       const IDirect3DRMFrame* pCamera,
                                       unsigned long x,
                                       unsigned long y,
                                       unsigned long width,
                                       unsigned long height,
                                       IDirect3DRMViewport*&);
    static Result   RendererCreateCamera(IDirect3DRM*, IDirect3DRMFrame*&);
    static Result   RendererCreateLight(IDirect3DRM*,
                                        LightType,
                                        double r, double g, double b,
                                        IDirect3DRMFrame*&);
    static Result   RendererCreateGroup(IDirect3DRM*,
                                        const IDirect3DRMFrame* pParentGroup,
                                        IDirect3DRMFrame*&);
    static Result   RendererCreateMesh(IDirect3DRM*,
                                       unsigned long vertexCount,
                                       const float (*pVertices)[3],
                                       const float (*pTextureCoordinates)[2],
                                       unsigned long faceCount,
                                       unsigned long vertexPerFaceCount,
                                       unsigned long* pFaceData,
                                       MeshData*&);
    static Result   RendererCreateMesh(IDirect3DRM*,
                                       unsigned long vertexCount,
                                       const float (*pVertices)[3],
                                       const float (*pTextureCoordinates)[2],
                                       unsigned long* pFaceData,
                                       MeshData*&);
    static Result   RendererCreateTexture(IDirect3DRM*,
                                          IDirect3DRMTexture*&);
    static Result   RendererCreateTexture(IDirect3DRM*,
                                          int width, int height,
                                          int bitsPerTexel,
                                          const void* pTexels,
                                          int pTexelsArePersistent,
                                          int paletteEntryCount,
                                          const PaletteEntry*,
                                          IDirect3DRMTexture*&);
    static Result   RendererSetTextureDefaultShadeCount(IDirect3DRM*,
                                                        unsigned long);
    static Result   RendererSetTextureDefaultColorCount(IDirect3DRM*,
                                                        unsigned long);

    // Device
    static void             DeviceDestroy(IDirect3DRMDevice*);
    static Result           DeviceSetColorModel(IDirect3DRMDevice*, ColorModel);
    static Result           DeviceSetShadingModel(IDirect3DRMDevice*, ShadingModel);
    static Result           DeviceSetShadeCount(IDirect3DRMDevice*, unsigned long);
    static Result           DeviceSetDither(IDirect3DRMDevice*, int);
    static unsigned long    DeviceGetWidth(IDirect3DRMDevice*);
    static unsigned long    DeviceGetHeight(IDirect3DRMDevice*);
    static void             DeviceHandleActivate(IDirect3DRMDevice*, int);
    static void             DeviceHandlePaint(IDirect3DRMDevice*, void* pData);
    static Result           DeviceUpdate(IDirect3DRMDevice*);
#ifdef _DEBUG
    static unsigned long    DeviceGetDrawnTriangleCount(IDirect3DRMDevice*); 
#endif

    // View
    static void     ViewDestroy(IDirect3DRMViewport*);
    static Result   ViewClear(IDirect3DRMViewport*);
    static Result   ViewSetCamera(IDirect3DRMViewport*, const IDirect3DRMFrame*);
    static Result   ViewAddLight(IDirect3DRMViewport*, const IDirect3DRMFrame*);
    static Result   ViewRemoveLight(IDirect3DRMViewport*, const IDirect3DRMFrame*);
    static Result   ViewRender(IDirect3DRMViewport*, const IDirect3DRMFrame*);
    static Result   ViewForceUpdate(IDirect3DRMViewport*,
                                    unsigned long x,
                                    unsigned long y,
                                    unsigned long width,
                                    unsigned long height);
    static Result   ViewSetBackgroundColor(IDirect3DRMViewport*,
                                           double r, double g, double b);
    static Result   ViewSetProjection(IDirect3DRMViewport*, ProjectionType);
    static Result   ViewSetFrontClippingPlane(IDirect3DRMViewport*, double distance);
    static Result   ViewSetBackClippingPlane(IDirect3DRMViewport*, double distance);
    static Result   ViewSetFrustrum(IDirect3DRMViewport*,
                                    double frontClippingDistance,
                                    double backClippingDistance,
                                    double degrees);
    static Result   ViewTransformWorldToScreen(IDirect3DRMViewport*,
                                               const double world[3],
                                               double screen[4]);
    static Result   ViewPick(IDirect3DRMViewport*,
                             unsigned long x,
                             unsigned long y,
                             const TglImpl::GroupImpl<D3DRM>** ppGroupsToPickFrom,
                             int groupsToPickFromCount,
                             const Group**& rppPickedGroups,
                             int& rPickedGroupCount);

    // Camera
    static void     CameraDestroy(IDirect3DRMFrame*);
    static Result   CameraSetTransformation(IDirect3DRMFrame*, const DoubleMatrix4&);

    // Light
    static void     LightDestroy(IDirect3DRMFrame*);
    static Result   LightSetTransformation(IDirect3DRMFrame*, const DoubleMatrix4&);

    // Group
    static void     GroupDestroy(IDirect3DRMFrame*);
    static Result   GroupSetTransformation(IDirect3DRMFrame*, const DoubleMatrix4&);
    static Result   GroupSetColor(IDirect3DRMFrame*, double r, double g, double b);
    static Result   GroupSetTexture(IDirect3DRMFrame*, IDirect3DRMTexture*);
    static Result   GroupAddGroup(IDirect3DRMFrame*, const IDirect3DRMFrame* pChildGroup);
    static Result   GroupAddMesh(IDirect3DRMFrame*, const MeshData*);
    static Result   GroupRemoveGroup(IDirect3DRMFrame*, const IDirect3DRMFrame* pChildGroup);
    static Result   GroupRemoveMesh(IDirect3DRMFrame*, const MeshData*);
    static Result   GroupRemoveAll(IDirect3DRMFrame*);
    static Result   GroupTransformLocalToWorld(IDirect3DRMFrame*,
                                               const double local[3],
                                               double world[3]);

    // Mesh
    static void     MeshDestroy(MeshData*);
    static Result   MeshSetColor(MeshData*, double r, double g, double b);
    static Result   MeshSetTexture(MeshData*, IDirect3DRMTexture*);
    static Result   MeshSetTextureMappingMode(MeshData*,
                                              TextureMappingMode);
    static Result   MeshSetShadingModel(MeshData*,
                                               ShadingModel);

#ifdef _DEBUG
    static Result           MeshGetBoundingBox(MeshData*,
                                               float [3], float[3]);
    static unsigned long    MeshGetFaceCount(MeshData*);
    static unsigned long    MeshGetVertexCount(MeshData*);
#endif

    // Texture
    static void     TextureDestroy(IDirect3DRMTexture*);
    static Result   TextureSetTexels(IDirect3DRMTexture*,
                                     int width, int height, int bitsPerTexel,
                                     const void* pTexels, int texelsArePersistent);
    static Result   TextureSetPalette(IDirect3DRMTexture*,
                                      int entryCount,
                                      const PaletteEntry* pEntries);

private:
    // Helper
    class Image : public D3DRMIMAGE
    {
    public:
        Image(int width, int height, int bitsPerTexel,
              const void* pTexels, int pTexelsArePersistent,
              int paletteEntryCount, const PaletteEntry* pEntries);
        ~Image();

        Result      SetTexels(int width, int height, int bitsPerTexel,
                               const void* pTexels, int texelsArePersistent);
        Result      SetPalette(int entryCount, const PaletteEntry* pEntries);

    private:
        int         m_texels_allocated_by_client;
    };

    struct ViewportAppData
    {
        ViewportAppData(IDirect3DRM*);
        ~ViewportAppData();

        // 'light frame' that is the parent frame of all lights
        IDirect3DRMFrame*   m_pLightFrame;
        IDirect3DRMFrame*   m_pCamera;
        IDirect3DRMFrame*   m_pLastRenderedFrame;

        double              m_backgroundColorRed;
        double              m_backgroundColorGreen;
        double              m_backgroundColorBlue;

        // ??? beta3 bug
        // D3DRMViewport::ForceUpdate() crashes if Render() has not been called
        // ??? each Tgl::View needs this... set to FALSE on creation, set to TRUE when
        //     rendered first time
        BOOL                m_canCallForceUpdate;
    };

    friend ViewportAppData;

    static Result   ResultVal(HRESULT result)
    {
        // Facility Code: 0x999
        // AfxTrace("ResultVal(0x%lx): Facility: 0x%lx, Code: 0x%lx\n",
        //          (long) result,
        //          (long) HRESULT_FACILITY(result),
        //          (long) HRESULT_CODE(result));
        return SUCCEEDED(result) ? Success : Error;
    }

    static D3DRMMATRIX4D*       Translate(const DoubleMatrix4&, D3DRMMATRIX4D&);
    static D3DVECTOR*           Translate(const double[3], D3DVECTOR&);
    static D3DRMRENDERQUALITY	Translate(ShadingModel);
    static D3DRMLIGHTTYPE	    Translate(LightType);
    static D3DRMPROJECTIONTYPE  Translate(ProjectionType);
    static D3DRMMAPPINGFLAG     Translate(TextureMappingMode);

    static Result               ViewPrepareFrameForRender(IDirect3DRMFrame* pFrame,
                                                          IDirect3DRMFrame* pCamera,
                                                          IDirect3DRMFrame* pLightFrame,
                                                          double backgroundRed,
                                                          double backgroundGreen,
                                                          double backgroundBlue);
    static Result               ViewRestoreFrameAfterRender(IDirect3DRMFrame* pFrame,
                                                            IDirect3DRMFrame* pCamera,
                                                            IDirect3DRMFrame* pLightFrame);
    static Result               ViewportCreateAppData(IDirect3DRM*,
                                                      IDirect3DRMViewport*,
                                                      IDirect3DRMFrame* pCamera);
    static void                 ViewportDestroyCallback(IDirect3DRMObject*,
                                                        void*);
    static IDirect3DRMFrame*    ViewportGetLightFrame(IDirect3DRMViewport*);
    static void                 TextureDestroyCallback(IDirect3DRMObject*,
                                                       void*);
    static Image*               TextureGetImage(IDirect3DRMTexture*);
    static Result               TextureSetImage(IDirect3DRMTexture*, Image*);

private:
    static IDirect3DRM*  g_pTheRenderer;
};

// ???
//extern void __cdecl AfxTrace(LPCTSTR lpszFormat, ...);

//////////////////////////////////////////////////////////////////////////////

inline
Result
D3DRM::RendererCreate(IDirect3DRM*& rpD3DRM)
{
    if (g_pTheRenderer)
    {
        g_pTheRenderer->AddRef();
    }
    else
    {
        Result  result;

        result = ResultVal(Direct3DRMCreate(&g_pTheRenderer));
        assert(Succeeded(result));
        assert((g_pTheRenderer->AddRef(), g_pTheRenderer->Release()) == 1);
    }

    rpD3DRM = g_pTheRenderer;

    return (rpD3DRM != 0) ? Success : Error;
}

inline
void
D3DRM::RendererDestroy(IDirect3DRM* pD3DRM)
{
    int refCount;

    refCount = pD3DRM->Release();
    if (refCount <= 0)
    {
        assert(refCount == 0);
        g_pTheRenderer = 0;
    }
}

inline
Result
D3DRM::RendererCreateDevice(IDirect3DRM* pD3DRM,
                            const DeviceDirectDrawCreateData& rCreateData,
                            IDirect3DRMDevice*& rpDevice)
{
    Result  result;

    result = ResultVal(pD3DRM->CreateDeviceFromSurface(const_cast<GUID*>(rCreateData.m_driverGUID),
                                                       rCreateData.m_pDirectDraw,
                                                       rCreateData.m_pBackBuffer,
                                                       &rpDevice));

    if (Succeeded(result))
    {
        if (rCreateData.m_pBackBuffer)
        {
            // ???
            static int gSetBufferCount = 1;
            if (gSetBufferCount)
            {
            Result  result2;

            result2 = ResultVal(rpDevice->SetBufferCount(2));
            assert(Succeeded(result));
            }
        }
    }

    return result;
}

inline
Result
D3DRM::RendererCreateDevice(IDirect3DRM* pD3DRM,
                            const DeviceDirect3DCreateData& rCreateData,
                            IDirect3DRMDevice*& rpDevice)
{
    Result  result;

#if 0
    result = ResultVal(pD3DRM->CreateDeviceFromD3D(rCreateData.m_pDirect3D,
                                                   rCreateData.m_pDirect3DDevice,
                                                   &rpDevice));
#else
    // deal with buffer count
    result = Error;
#endif

    return result;
}

inline
Result
D3DRM::RendererCreateView(IDirect3DRM* pD3DRM,
                          const IDirect3DRMDevice* pDevice,
                          const IDirect3DRMFrame* pCamera,
                          unsigned long x, unsigned long y,
                          unsigned long width, unsigned long height,
                          IDirect3DRMViewport*& rpViewport)
{
    Result  result;

    result = ResultVal(pD3DRM->CreateViewport(const_cast<IDirect3DRMDevice*>(pDevice),
                                              const_cast<IDirect3DRMFrame*>(pCamera),
                                              x, y, width, height,
                                              &rpViewport));

    if (Succeeded(result))
    {
        result = ViewportCreateAppData(pD3DRM,
                                       rpViewport,
                                       const_cast<IDirect3DRMFrame*>(pCamera));

        if (!Succeeded(result))
        {
            rpViewport->Release();
            rpViewport = 0;
        }
    }

    return result;
}

inline
Result
D3DRM::RendererCreateCamera(IDirect3DRM* pD3DRM, IDirect3DRMFrame*& rpCamera)
{
    // camera is added to the scene when it is rendered
    return ResultVal(pD3DRM->CreateFrame(0, &rpCamera));
}

inline
Result
D3DRM::RendererCreateLight(IDirect3DRM* pD3DRM, LightType type,
                          double r, double g, double b,
                          IDirect3DRMFrame*& rpLight)
{
    D3DRMLIGHTTYPE	    lightType = Translate(type);
    IDirect3DRMFrame*   pLightFrame;
    IDirect3DRMLight*   pLight;
    Result      result;

    result = ResultVal(pD3DRM->CreateFrame(0, &pLightFrame));
    assert(Succeeded(result));
    if (!Succeeded(result))
    {
        return result;
    }
    // pLightFrame ref count is now 1
    assert((pLightFrame->AddRef(), pLightFrame->Release()) == 1);

    result = ResultVal(pD3DRM->CreateLightRGB(lightType,
                                              D3DVAL(r), D3DVAL(g), D3DVAL(b),
                                              &pLight));
    assert(Succeeded(result));
    if (!Succeeded(result))
    {
        pLightFrame->Release();
        return result;
    }
    // pLight ref count is now 1
    assert((pLight->AddRef(), pLight->Release()) == 1);

    result = ResultVal(pLightFrame->AddLight(pLight));
    assert(Succeeded(result));
    if (!Succeeded(result))
    {
        pLightFrame->Release();
        pLight->Release();
        return result;
    }
    // pLightFrame ref count is still 1
    assert((pLightFrame->AddRef(), pLightFrame->Release()) == 1);

    // pLight ref count is now 2
    assert((pLight->AddRef(), pLight->Release()) == 2);

    // Release() pLight so it gets deleted when pLightFrame is Release()
    pLight->Release();

    rpLight = pLightFrame;

    return result;
}

#define GROUP_PARENTCHILD 0

inline
Result
D3DRM::RendererCreateGroup(IDirect3DRM* pD3DRM,
                           const IDirect3DRMFrame* pParentGroup,
                           IDirect3DRMFrame*& rpFrame)
{
    Result  result;

#if GROUP_PARENTCHILD
    result = ResultVal(pD3DRM->CreateFrame(const_cast<IDirect3DRMFrame*>(pParentGroup),
                                           &rpFrame));
#else

    result = ResultVal(pD3DRM->CreateFrame(0, &rpFrame));
    if (Succeeded(result) && pParentGroup)
    {
        result = ResultVal(const_cast<IDirect3DRMFrame*>(pParentGroup)->AddVisual(rpFrame));
        if (!Succeeded(result))
        {
            rpFrame->Release();
            rpFrame = 0;
        }
    }
#endif

    // ???
#if 0
    if (Succeeded(result))
    {
        result = ResultVal(rpFrame->SetMaterialMode(D3DRMMATERIAL_FROMPARENT));
        assert(Succeeded(result));
        if (!Succeeded(result))
        {
            rpFrame->Release();
            rpFrame = 0;
        }
    }
#endif

    return result;
}

// NOTE: ??? when normals are specified later...
//       we no longer need to go through MeshBuilder, but can create a mesh
//       and AddGroup() + SetVertices()

inline
Result
D3DRM::RendererCreateMesh(IDirect3DRM* pD3DRM,
                          unsigned long vertexCount,
                          const float (*pVertices)[3],
                          const float (*pTextureCoordinates)[2],
                          unsigned long faceCount,
                          unsigned long vertexPerFaceCount,
                          unsigned long* pFaceData,
                          MeshData*& rpMesh)
{
    // Face data is faceCount tuples, each of format
    //  [vertex1index, ... vertexNindex], where N = vertexPerFaceCount

    unsigned long*  pD3DRMFaceData;
    unsigned long   i;
    Result          result;

    // Face data needs to be:
    //  [face1VertexCount face1Vertex1index, ... face1VertexMindex
    //   face2VertexCount face2Vertex1index, ... face2VertexNindex
    //   ...
    //   0]
    pD3DRMFaceData = new unsigned long[(faceCount * (vertexPerFaceCount + 1)) + 1];
    for (i = 0; i < faceCount; i++)
    {
        unsigned long j;

        pD3DRMFaceData[i * (vertexPerFaceCount + 1)] = vertexPerFaceCount;
        for (j = 0; j < vertexPerFaceCount; j++)
        {
            pD3DRMFaceData[(i * (vertexPerFaceCount + 1)) + 1 + j] = 
              pFaceData[(i * vertexPerFaceCount) + j];
        }
    }
    pD3DRMFaceData[faceCount * (vertexPerFaceCount + 1)] = 0;

    result = RendererCreateMesh(pD3DRM,
                                vertexCount, pVertices,
                                pTextureCoordinates,
                                pD3DRMFaceData,
                                rpMesh);

    delete [] pD3DRMFaceData;


    return result;
}

inline
Result
D3DRM::RendererCreateMesh(IDirect3DRM* pD3DRM,
                          unsigned long vertexCount,
                          const float (*pVertices)[3],
                          const float (*pTextureCoordinates)[2],
                          unsigned long* pFaceData,
                          MeshData*& data)
{
    // Face data is:
    //  [face1VertexCount face1Vertex1index, ... face1VertexMindex
    //   face2VertexCount face2Vertex1index, ... face2VertexNindex
    //   ...
    //   0]

    IDirect3DRMMeshBuilder* pMeshBuilder;
    Result          result;

	data = new MeshData;
    IDirect3DRMMesh*& rpMesh = data->mesh;
	result = ResultVal(pD3DRM->CreateFrame(0, &data->frame));
	assert(result);
		
	result = ResultVal(pD3DRM->CreateMeshBuilder(&pMeshBuilder));
    if (Succeeded(result))
    {
        D3DVECTOR*  pD3DRMVertices;

        // verify assumption about D3DVECTOR and float arrays
        assert(sizeof(D3DVECTOR) == (3 * sizeof(float)));       // structure member alignment
        assert(sizeof(D3DVECTOR[2]) == (2 * 3 * sizeof(float)));// structure alignment
        assert(sizeof(D3DVECTOR*) == sizeof(pVertices));        // pointers
        assert(sizeof(((D3DVECTOR*) 0)->x) == sizeof(pVertices[0][0]));
        assert(sizeof(((D3DVECTOR*) 0)->y) == sizeof(pVertices[0][1]));
        assert(sizeof(((D3DVECTOR*) 0)->z) == sizeof(pVertices[0][2]));
        assert(offsetof(D3DVECTOR, x) == ((&pVertices[0][0] - &pVertices[0][0]) * sizeof(pVertices[0][0])));
        assert(offsetof(D3DVECTOR, y) == ((&pVertices[0][1] - &pVertices[0][0]) * sizeof(pVertices[0][0])));
        assert(offsetof(D3DVECTOR, z) == ((&pVertices[0][2] - &pVertices[0][0]) * sizeof(pVertices[0][0])));

        pD3DRMVertices = reinterpret_cast<D3DVECTOR*>(const_cast<float(*)[3]>(pVertices));

        // ???
        // result = ResultVal(pMeshBuilder->ReserveSpace(vertexCount, 0, faceCount);

        result = ResultVal(pMeshBuilder->AddFaces(vertexCount, pD3DRMVertices,
                                                  0, 0,
                                                  pFaceData, 0));

        if (Succeeded(result) && pTextureCoordinates)
        {
            unsigned long   i;

            for (i = 0; (i < vertexCount) && Succeeded(result); i++)
            {
                result = ResultVal(pMeshBuilder->SetTextureCoordinates(i,
                                                                       pTextureCoordinates[i][0],
                                                                       pTextureCoordinates[i][1]));
            }
        }

        if (Succeeded(result))
        {
pMeshBuilder->SetQuality(D3DRMRENDER_FLAT); 
            result = ResultVal(pMeshBuilder->CreateMesh(&rpMesh));
			data->frame->AddVisual(rpMesh);

            // ???
#if 0
            if (Succeeded(result))
            {
                Result  result2;

                result2 = MeshSetTextureMappingMode(rpMesh, Linear);
                assert(Succeeded(result2));
            }
#endif
        }

        pMeshBuilder->Release();
    }

    return result;
}

inline
Result
D3DRM::RendererCreateTexture(IDirect3DRM* pD3DRM,
                             IDirect3DRMTexture*& rpTexture)
{
    return RendererCreateTexture(pD3DRM, 0, 0, 0, 0, 0, 0, 0, rpTexture);
}

inline
Result
D3DRM::RendererCreateTexture(IDirect3DRM* pD3DRM,
                             int width, int height, int bitsPerTexel,
                             const void* pTexels,
                             int pTexelsArePersistent,
                             int paletteEntryCount,
                             const PaletteEntry* pEntries,
                             IDirect3DRMTexture*& rpTexture)
{
    Image*  pImage;
    Result  result;
    
    pImage = new Image(width, height, bitsPerTexel,
                       pTexels, pTexelsArePersistent,
                       paletteEntryCount, pEntries);
    assert(pImage);

    result = ResultVal(pD3DRM->CreateTexture(pImage, &rpTexture));
    assert(Succeeded(result));
    assert((rpTexture->AddRef(), rpTexture->Release()) == 1);

    if (Succeeded(result))
    {
        result = TextureSetImage(rpTexture, pImage);
        assert(Succeeded(result));

        if (!Succeeded(result))
        {
            rpTexture->Release();
            rpTexture = 0;
            delete pImage;
        }
    }
    else
    {
        delete pImage;
    }

    return result;
}

inline
Result
D3DRM::RendererSetTextureDefaultShadeCount(IDirect3DRM* pD3DRM,
                                           unsigned long count)
{
    return ResultVal(pD3DRM->SetDefaultTextureShades(count));
}

inline
Result
D3DRM::RendererSetTextureDefaultColorCount(IDirect3DRM* pD3DRM,
                                           unsigned long count)
{
    return ResultVal(pD3DRM->SetDefaultTextureColors(count));
}

//////////////////////////////////////////////////////////////////////////////
//
// Device
//

inline
void
D3DRM::DeviceDestroy(IDirect3DRMDevice* pDevice)
{
    pDevice->Release();
}

inline
Result
D3DRM::DeviceSetColorModel(IDirect3DRMDevice* pDevice,
                           ColorModel colorModel)
{
    // ??? beta2
    // No longer part of D3DRM
#if 0
    D3DRMCOLORMODEL	d3drmColorModel = Translate(colorModel);

    return ResultVal(pDevice->SetColorModel(d3drmColorModel));
#else
    return Success;
#endif
}

inline
Result
D3DRM::DeviceSetShadingModel(IDirect3DRMDevice* pDevice,
                            ShadingModel shadingModel)
{
    D3DRMRENDERQUALITY	renderQuality = Translate(shadingModel);

    return ResultVal(pDevice->SetQuality(renderQuality));
}

inline
Result
D3DRM::DeviceSetShadeCount(IDirect3DRMDevice* pDevice,
                          unsigned long shadeCount)
{
    return ResultVal(pDevice->SetShades(shadeCount));
}

inline
Result
D3DRM::DeviceSetDither(IDirect3DRMDevice* pDevice,
                      int dither)
{
    return ResultVal(pDevice->SetDither(dither));
}

inline
unsigned long
D3DRM::DeviceGetWidth(IDirect3DRMDevice* pDevice)
{
    return pDevice->GetWidth();
}

inline
unsigned long
D3DRM::DeviceGetHeight(IDirect3DRMDevice* pDevice)
{
    return pDevice->GetHeight();
}

#ifdef _DEBUG
inline
unsigned long
D3DRM::DeviceGetDrawnTriangleCount(IDirect3DRMDevice* pDevice)
{
    IDirect3DDevice*    pD3DDevice;
    D3DSTATS            stats;
    Result              result;

    result = ResultVal(pDevice->GetDirect3DDevice(&pD3DDevice));
    assert(Succeeded(result));

    memset(&stats, 0, sizeof(stats));
    stats.dwSize = sizeof(stats);
    result = ResultVal(pD3DDevice->GetStats(&stats));
    assert(Succeeded(result));

    pD3DDevice->Release();

    return stats.dwTrianglesDrawn;
}
#endif

inline
void
D3DRM::DeviceHandleActivate(IDirect3DRMDevice* pDevice, int activate)
{
    IDirect3DRMWinDevice*   pD3DRMWinDevice;
    Result                  result;

    result = ResultVal(pDevice->QueryInterface(IID_IDirect3DRMWinDevice,
                                                    (void **) &pD3DRMWinDevice));
    if (Succeeded(result))
    {
        int refCount;

        pD3DRMWinDevice->HandleActivate(activate);

        refCount = pD3DRMWinDevice->Release();
        assert(refCount == 1);
    }
}

inline
void
D3DRM::DeviceHandlePaint(IDirect3DRMDevice* pDevice, void* pData)
{
    IDirect3DRMWinDevice*   pD3DRMWinDevice;
    Result                  result;

    result = ResultVal(pDevice->QueryInterface(IID_IDirect3DRMWinDevice,
                                                    (void **) &pD3DRMWinDevice));
    if (Succeeded(result))
    {
        HDC hDC = (HDC) pData;
        int refCount;

        pD3DRMWinDevice->HandlePaint(hDC);

        refCount = pD3DRMWinDevice->Release();
        assert(refCount == 1);
    }
}

inline
Result
D3DRM::DeviceUpdate(IDirect3DRMDevice* pDevice)
{
    return ResultVal(pDevice->Update()); 
}

//////////////////////////////////////////////////////////////////////////////
//
// View
//

inline
void
D3DRM::ViewDestroy(IDirect3DRMViewport* pViewport)
{
    pViewport->Release();
}

inline
Result
D3DRM::ViewSetProjection(IDirect3DRMViewport* pViewport, ProjectionType type)
{
    D3DRMPROJECTIONTYPE projectionType = Translate(type);

    return ResultVal(pViewport->SetProjection(projectionType));
}

inline
Result
D3DRM::ViewSetFrustrum(IDirect3DRMViewport* pViewport,
                      double frontClippingDistance,
                      double backClippingDistance,
                      double degrees)
{
    double  field = frontClippingDistance * tan(DegreesToRadians(degrees/2));
    Result  result;

    result = ResultVal(pViewport->SetFront(D3DVAL(frontClippingDistance)));
    if (Succeeded(result))
    {
        result = ResultVal(pViewport->SetBack(D3DVAL(backClippingDistance)));
    }
    if (Succeeded(result))
    {
        result = ResultVal(pViewport->SetField(D3DVAL(field)));
    }

    return result;
}

inline
Result
D3DRM::ViewSetBackgroundColor(IDirect3DRMViewport* pViewport,
                              double r, double g, double b)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
    assert(pViewportAppData);

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_pLastRenderedFrame,
                                         pViewportAppData->m_pCamera,
                                         pViewportAppData->m_pLightFrame);
    assert(Succeeded(result));
    pViewportAppData->m_backgroundColorRed      = r;
    pViewportAppData->m_backgroundColorGreen    = g;
    pViewportAppData->m_backgroundColorBlue     = b;
    pViewportAppData->m_pLastRenderedFrame      = 0;

    return result;
}

inline
Result
D3DRM::ViewClear(IDirect3DRMViewport* pViewport)
{
    return ResultVal(pViewport->Clear());
}

inline
Result
D3DRM::ViewSetCamera(IDirect3DRMViewport* pViewport, const IDirect3DRMFrame* pCamera)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
    assert(pViewportAppData);

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_pLastRenderedFrame,
                                         pViewportAppData->m_pCamera,
                                         pViewportAppData->m_pLightFrame);
    assert(Succeeded(result));
    pViewportAppData->m_pCamera = const_cast<IDirect3DRMFrame*>(pCamera);
    pViewportAppData->m_pLastRenderedFrame = 0;

    return ResultVal(pViewport->SetCamera(const_cast<IDirect3DRMFrame*>(pCamera)));
}

inline
Result
D3DRM::ViewAddLight(IDirect3DRMViewport* pViewport, const IDirect3DRMFrame* pLight)
{
    IDirect3DRMFrame*   pLightFrame = ViewportGetLightFrame(pViewport);

    assert(pLightFrame);
    return ResultVal(pLightFrame->AddChild(const_cast<IDirect3DRMFrame*>(pLight)));
}

inline
Result
D3DRM::ViewRemoveLight(IDirect3DRMViewport* pViewport, const IDirect3DRMFrame* pLight)
{
    IDirect3DRMFrame*   pLightFrame = ViewportGetLightFrame(pViewport);

    assert(pLightFrame);
    return ResultVal(pLightFrame->DeleteChild(const_cast<IDirect3DRMFrame*>(pLight)));
}

inline
Result
D3DRM::ViewRender(IDirect3DRMViewport* pViewport, const IDirect3DRMFrame* pFrame)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
    assert(pViewportAppData);

    if (pViewportAppData->m_pLastRenderedFrame != pFrame)
    {
        result = ViewRestoreFrameAfterRender(pViewportAppData->m_pLastRenderedFrame,
                                             pViewportAppData->m_pCamera,
                                             pViewportAppData->m_pLightFrame);
        assert(Succeeded(result));

        pViewportAppData->m_pLastRenderedFrame = const_cast<IDirect3DRMFrame*>(pFrame);

        result = ViewPrepareFrameForRender(pViewportAppData->m_pLastRenderedFrame,
                                           pViewportAppData->m_pCamera,
                                           pViewportAppData->m_pLightFrame,
                                           pViewportAppData->m_backgroundColorRed,
                                           pViewportAppData->m_backgroundColorGreen,
                                           pViewportAppData->m_backgroundColorBlue);
        assert(Succeeded(result));
    }

    result = ResultVal(pViewport->Render(const_cast<IDirect3DRMFrame*>(pFrame)));
    assert(Succeeded(result));

    // ??? beta3
    // D3DRMViewport::ForceUpdate() crashes if Render() has not been called
    pViewportAppData->m_canCallForceUpdate = TRUE;

    return result;
}

inline
Result
D3DRM::ViewForceUpdate(IDirect3DRMViewport* pViewport,
                       unsigned long x,
                       unsigned long y,
                       unsigned long width,
                       unsigned long height)
{
    //??? beta3
    ViewportAppData*    pViewportAppData;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
    assert(pViewportAppData);

    if (pViewportAppData->m_canCallForceUpdate)
    {
        return ResultVal(pViewport->ForceUpdate(x, y, x + width, y + height));
    }
    else
    {
        return Success;
    }
}

inline
Result
D3DRM::ViewTransformWorldToScreen(IDirect3DRMViewport* pViewport,
                                  const double world[3],
                                  double screen[4])
{
    D3DRMVECTOR4D   d3dRMScreen;
    D3DVECTOR       d3dRMWorld;
    D3DVECTOR*      pD3DRMWorld = Translate(world, d3dRMWorld);
    Result          result;

    result = ResultVal(pViewport->Transform(&d3dRMScreen, pD3DRMWorld));

    if (Succeeded(result))
    {
        screen[0]  = d3dRMScreen.x;
        screen[1]  = d3dRMScreen.y;
        screen[2]  = d3dRMScreen.z;
        screen[3]  = d3dRMScreen.w;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////
//
// View helper

inline
IDirect3DRMFrame*
D3DRM::ViewportGetLightFrame(IDirect3DRMViewport* pViewport)
{
    assert(pViewport->GetAppData());
    return reinterpret_cast<ViewportAppData*>(pViewport->GetAppData())->m_pLightFrame;
}

inline
Result
D3DRM::ViewPrepareFrameForRender(IDirect3DRMFrame* pFrame,
                                 IDirect3DRMFrame* pCamera,
                                 IDirect3DRMFrame* pLightFrame,
                                 double backgroundRed,
                                 double backgroundGreen,
                                 double backgroundBlue)
{
    Result  result = Success;

    if (pFrame)
    {
        // set background color
        result = ResultVal(pFrame->SetSceneBackgroundRGB(D3DVAL(backgroundRed),
                                                         D3DVAL(backgroundGreen),
                                                         D3DVAL(backgroundBlue)));
        assert(Succeeded(result));

        // add camera to frame to be rendered
        result = ResultVal(pFrame->AddChild(pCamera));
        assert(Succeeded(result));

        // add light frame to frame to be rendered
        // ??? use IDirect3DRMLight::SetEnableFrame() instead ???
        result = ResultVal(pFrame->AddChild(pLightFrame));
        assert(Succeeded(result));

        // increase ref count of frame to ensure it does not get deleted underneath us
        pFrame->AddRef();
    }

    return result;
}

inline
Result
D3DRM::ViewRestoreFrameAfterRender(IDirect3DRMFrame* pFrame,
                                   IDirect3DRMFrame* pCamera,
                                   IDirect3DRMFrame* pLightFrame)
{
    Result  result = Success;

    if (pFrame)
    {
        // remove camera and light frame from frame that was rendered

        // this doesn't destroy the camera as it is still the camera of the viewport...
        result = ResultVal(pFrame->DeleteChild(pCamera));
        assert(Succeeded(result));
        assert((pCamera->AddRef(), pCamera->Release()) > 0);

        result = ResultVal(pFrame->DeleteChild(pLightFrame));
        assert(Succeeded(result));

        // decrease frame's ref count (it was increased in ViewPrepareFrameForRender())
        pFrame->Release();
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////
//
// Camera

inline
void
D3DRM::CameraDestroy(IDirect3DRMFrame* pCamera)
{
    pCamera->Release();
}

inline
Result
D3DRM::CameraSetTransformation(IDirect3DRMFrame* pCamera, 
                               const DoubleMatrix4& transformation)
{
    D3DRMMATRIX4D  helper;
    D3DRMMATRIX4D* pTransformation = Translate(transformation, helper);

#if 0
    return ResultVal(pCamera->AddTransform(D3DRMCOMBINE_REPLACE,
                                           *pTransformation));
#else
    D3DVECTOR           position;
    Result              result;
    Result              result2;

    result2 = ResultVal(pCamera->GetPosition(0, &position));
    assert(Succeeded(result2));

    result = ResultVal(pCamera->AddTransform(D3DRMCOMBINE_REPLACE,
                                             *pTransformation));
    assert(Succeeded(result));

    result2 = ResultVal(pCamera->GetPosition(0, &position));
    assert(Succeeded(result2));

    return result;
#endif
}

//////////////////////////////////////////////////////////////////////////////
//
// Light
//

inline
void
D3DRM::LightDestroy(IDirect3DRMFrame* pLight)
{
    // pLight's refCount is == 1 if light has been removed from a view
    // pLight's refCount is > 1 if light is still in view
    // Client must call pView->Remove(pLight) AND delete pLight in order
    // for the light to "really" be deleted
    pLight->Release();
}

inline
Result
D3DRM::LightSetTransformation(IDirect3DRMFrame* pLight, 
                              const DoubleMatrix4& transformation)
{
    D3DRMMATRIX4D  helper;
    D3DRMMATRIX4D* pTransformation = Translate(transformation, helper);

    return ResultVal(pLight->AddTransform(D3DRMCOMBINE_REPLACE,
                                          *pTransformation));
}

//////////////////////////////////////////////////////////////////////////////
//
// Group

inline
void
D3DRM::GroupDestroy(IDirect3DRMFrame* pFrame)
{
    pFrame->Release();
}

inline
Result
D3DRM::GroupSetTransformation(IDirect3DRMFrame* pFrame, 
                             const DoubleMatrix4& transformation)
{
    D3DRMMATRIX4D  helper;
    D3DRMMATRIX4D* pTransformation = Translate(transformation, helper);

    return ResultVal(pFrame->AddTransform(D3DRMCOMBINE_REPLACE,
                                               *pTransformation));
}

inline
Result
D3DRM::GroupSetColor(IDirect3DRMFrame* pFrame, 
                     double r, double g, double b)
{
    return ResultVal(pFrame->SetColorRGB(D3DVAL(r),
                                              D3DVAL(g),
                                              D3DVAL(b)));
}

inline
Result
D3DRM::GroupSetTexture(IDirect3DRMFrame* pFrame,
                       IDirect3DRMTexture* pTexture)
{
    return ResultVal(pFrame->SetTexture(pTexture));
}

inline
Result
D3DRM::GroupAddGroup(IDirect3DRMFrame* pFrame, 
                     const IDirect3DRMFrame* pChildFrame)
{
#if GROUP_PARENTCHILD
    return ResultVal(pFrame->AddChild(const_cast<IDirect3DRMFrame*>(pChildFrame)));
#else
    return ResultVal(pFrame->AddVisual(const_cast<IDirect3DRMFrame*>(pChildFrame)));
#endif
}

inline
Result
D3DRM::GroupAddMesh(IDirect3DRMFrame* pFrame, 
                    const MeshData* pMesh)
{
    return ResultVal(pFrame->AddVisual(pMesh->frame));
}

inline
Result
D3DRM::GroupRemoveGroup(IDirect3DRMFrame* pFrame, const IDirect3DRMFrame* pChildFrame)
{
#if GROUP_PARENTCHILD
    return ResultVal(pFrame->DeleteChild(const_cast<IDirect3DRMFrame*>(pChildFrame)));
#else
    return ResultVal(pFrame->DeleteVisual(const_cast<IDirect3DRMFrame*>(pChildFrame)));
#endif
}

inline
Result
D3DRM::GroupRemoveMesh(IDirect3DRMFrame* pFrame, const MeshData* pMesh)
{
    return ResultVal(pFrame->DeleteVisual(pMesh->frame));
}

inline
Result
D3DRM::GroupRemoveAll(IDirect3DRMFrame* pFrame)
{
    IDirect3DRMVisualArray* pVisuals;
    Result                  result;

    result = ResultVal(pFrame->GetVisuals(&pVisuals));
    assert(Succeeded(result));

    if (Succeeded(result))
    {
        int refCount;
        int i;

        for (i = 0; i < (int) pVisuals->GetSize(); i++)
        {
            IDirect3DRMVisual*  pVisual;

            result = ResultVal(pVisuals->GetElement(i, &pVisual));
            assert(Succeeded(result));

            result = ResultVal(pFrame->DeleteVisual(pVisual));
            assert(Succeeded(result));

            refCount = pVisual->Release();  // GetElement() does AddRef()
        }

        refCount = pVisuals->Release(); // GetVisuals() does AddRef()
        assert(refCount == 0);
    }    

    return result;
}

inline
Result
D3DRM::GroupTransformLocalToWorld(IDirect3DRMFrame* pFrame,
                                  const double local[3],
                                  double world[3])
{
    Result      result;
    D3DVECTOR    rlWorld;
    D3DVECTOR    rlLocal;
    D3DVECTOR*   pD3DRMLocal = Translate(local, rlLocal);

    result = ResultVal(pFrame->Transform(&rlWorld, pD3DRMLocal));

    if (Succeeded(result))
    {
        world[0]   = rlWorld.x;
        world[1]   = rlWorld.y;
        world[2]   = rlWorld.z;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////
//
// Mesh
//

inline
void
D3DRM::MeshDestroy(MeshData* pMesh)
{
    pMesh->frame->Release();
	delete pMesh;
}

inline
Result
D3DRM::MeshSetColor(MeshData* pMesh, double r, double g, double b)
{
    // ??? maybe must specify color when creating the mesh
    return ResultVal(pMesh->mesh->SetGroupColorRGB(D3DRMGROUP_ALLGROUPS, 
                                                  D3DVAL(r),
                                                  D3DVAL(g),
                                                  D3DVAL(b)));
}

inline
Result
D3DRM::MeshSetTexture(MeshData* pMesh,
                      IDirect3DRMTexture* pTexture)
{
    Result  result;

    // ???
    //???
    //    D3DRMMAPPING    d3dMappingMode = pMesh->GetGroupMapping(0);
    //result = pMesh->GetGroupTexture(THIS_ D3DRMGROUPINDEX id, LPDIRECT3DRMTEXTURE *returnPtr) PURE;

    // ??? if using texture set color to white... otherwise
    // color shines through
    if (pTexture)
    {
        result = MeshSetColor(pMesh, 1, 1, 1);
        assert(Succeeded(result));
    }

    result = ResultVal(pMesh->mesh->SetGroupTexture(D3DRMGROUP_ALLGROUPS,
                                                   pTexture));

    return result;
}

inline
Result
D3DRM::MeshSetTextureMappingMode(MeshData* pMesh,
                                 TextureMappingMode mode)
{
    D3DRMMAPPINGFLAG    d3drmMode = Translate(mode);

    return ResultVal(pMesh->mesh->SetGroupMapping(D3DRMGROUP_ALLGROUPS,
                                                 d3drmMode));
}

inline
Result
D3DRM::MeshSetShadingModel(MeshData* pMesh,
                           ShadingModel shadingModel)
{
    D3DRMRENDERQUALITY  d3drmQuality = Translate(shadingModel);

    Result result = ResultVal(pMesh->mesh->SetGroupQuality(D3DRMGROUP_ALLGROUPS, d3drmQuality));
	pMesh->frame->SetMaterialMode(Inherit == shadingModel ?
		D3DRMMATERIAL_FROMPARENT : D3DRMMATERIAL_FROMMESH);
	return result;
}

#ifdef _DEBUG
inline
Result
D3DRM::MeshGetBoundingBox(MeshData* pMesh,
                          float min[3], float max[3])
{
    D3DRMBOX    meshBox;
    Result      result;

    result = ResultVal(pMesh->mesh->GetBox(&meshBox));
    if (Succeeded(result))
    {
        min[0] = meshBox.min.x;
        min[1] = meshBox.min.y;
        min[2] = meshBox.min.z;
        max[0] = meshBox.max.x;
        max[1] = meshBox.max.y;
        max[2] = meshBox.max.z;
    }
    return result;
}

inline
unsigned long
D3DRM::MeshGetFaceCount(MeshData* pMesh)
{
    unsigned int    faceCount = 0;

    // ???
    //assert(pMesh->GetGroupCount() == 1);

#if 0
    pMesh->GetGroup(0, 0, &faceCount, 0, 0);
#else
    int groupCount = pMesh->mesh->GetGroupCount();
    int i;

    for (i = 0; i < groupCount; i++)
    {
        unsigned int facesInGroup;

        if (Succeeded(ResultVal(pMesh->mesh->GetGroup(i,             // group id
                                                     0,             // vertex count
                                                     &facesInGroup, // face count
                                                     0,             // vertex per face
                                                     0,             // data size
                                                     0))))          // data
        {
            faceCount += facesInGroup;
        }
        else
        {
            faceCount = 0;
            break;
        }
    }
#endif

    return faceCount;
}

inline
unsigned long
D3DRM::MeshGetVertexCount(MeshData* pMesh)
{
    unsigned int    vertexCount = 0;

    // ???
    //assert(pMesh->GetGroupCount() == 1);

#if 0
    pMesh->mesh->GetGroup(0, &vertexCount, 0, 0, 0);
#else
    int groupCount = pMesh->mesh->GetGroupCount();
    int i;

    for (i = 0; i < groupCount; i++)
    {
        unsigned int verticesInGroup;

        if (Succeeded(ResultVal(pMesh->mesh->GetGroup(i,                 // group id
                                                     &verticesInGroup,  // vertex count
                                                     0,                 // face count
                                                     0,                 // vertex per face
                                                     0,                 // data size
                                                     0))))              // data
        {
            vertexCount += verticesInGroup;
        }
        else
        {
            vertexCount = 0;
            break;
        }
    }
#endif

    return vertexCount;
}

#endif

//////////////////////////////////////////////////////////////////////////////
//
// Texture
//

inline
void
D3DRM::TextureDestroy(IDirect3DRMTexture* pTexture)
{
    pTexture->Release();
}

inline
Result
D3DRM::TextureSetTexels(IDirect3DRMTexture* pTexture,
                        int width, int height, int bitsPerTexel,
                        const void* pTexels, int texelsArePersistent)
{
    Image*  pImage = TextureGetImage(pTexture);
    Result  result;

    assert(pImage);
    result = pImage->SetTexels(width, height, bitsPerTexel,
                               pTexels, texelsArePersistent);
    assert(Succeeded(result));

    if (Succeeded(result))
    {
        result = ResultVal(pTexture->Changed(TRUE, FALSE));
        assert(Succeeded(result));
    }

    return result;
}

inline
Result
D3DRM::TextureSetPalette(IDirect3DRMTexture* pTexture,
                         int entryCount, const PaletteEntry* pEntries)
{
    Image*  pImage = TextureGetImage(pTexture);
    Result  result;

    assert(pImage);
    pImage->SetPalette(entryCount, pEntries);

    result = ResultVal(pTexture->Changed(FALSE, TRUE));
    assert(Succeeded(result));

    return Success;
}

//////////////////////////////////////////////////////////////////////////////
//
// Texture helper

inline
D3DRM::Image*
D3DRM::TextureGetImage(IDirect3DRMTexture* pTexture)
{
    return reinterpret_cast<Image*>(pTexture->GetAppData());
}

/////////////////////////////////////////////////////////////////////
//
// Helper

inline
D3DRMMATRIX4D*
D3DRM::Translate(const DoubleMatrix4& tglMatrix4x4, D3DRMMATRIX4D& rD3DRMMatrix4x4)
{
    // ??? this is not correct...
    if ((sizeof(D3DRMMATRIX4D) == sizeof(DoubleMatrix4)) &&
        (sizeof((*((D3DRMMATRIX4D*) 0))[0]) == sizeof((*((DoubleMatrix4*) 0))[0])) &&
        (sizeof((*((D3DRMMATRIX4D*) 0))[0][0]) == sizeof((*((DoubleMatrix4*) 0))[0][0])))
    {
        return (D3DRMMATRIX4D*) (void*) &tglMatrix4x4;
    }
    else
    {
        int i;

        for (i = 0; i < (sizeof(rD3DRMMatrix4x4)/sizeof(rD3DRMMatrix4x4[0])); i++)
        {
            int j;

            for (j = 0; j < (sizeof(rD3DRMMatrix4x4[0])/sizeof(rD3DRMMatrix4x4[0][0])); j++)
            {
                rD3DRMMatrix4x4[i][j] = D3DVAL(tglMatrix4x4[i][j]);
            }
        }

        return &rD3DRMMatrix4x4;
    }
}

inline
D3DVECTOR*
D3DRM::Translate(const double tglVector[3], D3DVECTOR& rD3DVector)
{
    if ((sizeof(D3DVECTOR) == (3 * sizeof(double))) &&
        (sizeof(((D3DVECTOR*)0)->x) == sizeof(tglVector[0])) &&
        (offsetof(D3DVECTOR, x) == ((&tglVector[0] - &tglVector[0]) * sizeof(tglVector[0]))) &&
        (offsetof(D3DVECTOR, y) == ((&tglVector[1] - &tglVector[0]) * sizeof(tglVector[0]))) &&
        (offsetof(D3DVECTOR, z) == ((&tglVector[2] - &tglVector[0]) * sizeof(tglVector[0]))))
    {
        return (D3DVECTOR*) (void*) tglVector;
    }
    else
    {
        rD3DVector.x    = D3DVAL(tglVector[0]);
        rD3DVector.y    = D3DVAL(tglVector[1]);
        rD3DVector.z    = D3DVAL(tglVector[2]);

        return &rD3DVector;
    }
}

inline
D3DRMRENDERQUALITY
D3DRM::Translate(ShadingModel tglShadingModel)
{
    D3DRMRENDERQUALITY  renderQuality;

    // ??? use lookup table
    switch (tglShadingModel)
    {
    case Wireframe:
        renderQuality = D3DRMRENDER_WIREFRAME;
        break;
    case UnlitFlat:
        renderQuality = D3DRMRENDER_UNLITFLAT;
        break;
    case Flat:
        renderQuality = D3DRMRENDER_FLAT;
        break;
    case Gouraud:
        renderQuality = D3DRMRENDER_GOURAUD;
        break;
    case Phong:
        renderQuality = D3DRMRENDER_PHONG;
        break;
    default:
        renderQuality = D3DRMRENDER_FLAT;
        break;
    }

    return renderQuality;
}

inline
D3DRMLIGHTTYPE
D3DRM::Translate(LightType tglLightType)
{
    D3DRMLIGHTTYPE  lightType;

    // ??? use lookup table
    switch (tglLightType)
    {
    case Ambient:
        lightType = D3DRMLIGHT_AMBIENT;
        break;
    case Point:
        lightType = D3DRMLIGHT_POINT;
        break;
    case Spot:
        lightType = D3DRMLIGHT_SPOT;
        break;
    case Directional:
        lightType = D3DRMLIGHT_DIRECTIONAL;
        break;
    case ParallelPoint:
        lightType = D3DRMLIGHT_PARALLELPOINT;
        break;
    default:
        lightType = D3DRMLIGHT_AMBIENT;
        break;
    }

    return lightType;
}

inline
D3DRMPROJECTIONTYPE
D3DRM::Translate(ProjectionType tglProjectionType)
{
    D3DRMPROJECTIONTYPE  projectionType;

    // ??? use lookup table
    switch (tglProjectionType)
    {
    case Perspective:
        projectionType = D3DRMPROJECT_PERSPECTIVE;
        break;
    case Orthographic:
        projectionType = D3DRMPROJECT_ORTHOGRAPHIC;
        break;
    default:
        projectionType = D3DRMPROJECT_PERSPECTIVE;
        break;
    }

    return projectionType;
}

inline
D3DRMMAPPINGFLAG
D3DRM::Translate(TextureMappingMode mode)
{
    D3DRMMAPPINGFLAG  d3drmMode;

    switch (mode)
    {
    case Linear:
        d3drmMode = D3DRMMAP_WRAPU | D3DRMMAP_WRAPV;
        break;
    case PerspectiveCorrect:
        //???d3drmMode = D3DRMMAP_WRAPU | D3DRMMAP_WRAPV | D3DRMMAP_PERSPCORRECT;
        d3drmMode = D3DRMMAP_PERSPCORRECT;
        break;
    default:
        d3drmMode = D3DRMMAP_WRAPU | D3DRMMAP_WRAPV;
        break;
    }

    return d3drmMode;
}

} // namespace D3DRMImpl

#endif /* _tglD3DRM_h */
