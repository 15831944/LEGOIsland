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

using namespace Tgl;

struct D3DRM
{
    typedef IDirect3DRM*            RendererDataType;
    typedef IDirect3DRMDevice*      DeviceDataType;
    typedef IDirect3DRMViewport*    ViewDataType;
    typedef IDirect3DRMFrame*	    CameraDataType;
    typedef IDirect3DRMFrame*       GroupDataType;
    typedef IDirect3DRMFrame*	    LightDataType;
    typedef IDirect3DRMMeshBuilder* MeshDataType;
    typedef IDirect3DRMTexture*     TextureDataType;

    // Renderer
    static Result   RendererCreate(RendererDataType&);
    static void     RendererDestroy(RendererDataType);
    static Result   RendererCreateDevice(RendererDataType,
                                         const DeviceDirectDrawCreateData&,
                                         DeviceDataType&);
    static Result   RendererCreateDevice(RendererDataType,
                                         const DeviceDirect3DCreateData&,
                                         DeviceDataType&);
    static Result   RendererCreateView(RendererDataType,
                                       const DeviceDataType,
                                       const CameraDataType pCamera,
                                       unsigned long x,
                                       unsigned long y,
                                       unsigned long width,
                                       unsigned long height,
                                       ViewDataType&);
    static Result   RendererCreateCamera(RendererDataType, CameraDataType&);
    static Result   RendererCreateLight(RendererDataType,
                                        LightType,
                                        double r, double g, double b,
                                        LightDataType&);
    static Result   RendererCreateGroup(RendererDataType,
                                        const GroupDataType pParentGroup,
                                        GroupDataType&);
    static Result   RendererCreateMesh(RendererDataType,
                                       unsigned long vertexCount,
                                       const float (*pVertices)[3],
                                       const float (*pTextureCoordinates)[2],
                                       unsigned long faceCount,
                                       unsigned long vertexPerFaceCount,
                                       unsigned long* pFaceData,
                                       MeshDataType&);
    static Result   RendererCreateMesh(RendererDataType,
                                       unsigned long vertexCount,
                                       const float (*pVertices)[3],
                                       const float (*pTextureCoordinates)[2],
                                       unsigned long* pFaceData,
                                       MeshDataType&);
    static Result   RendererCreateTexture(RendererDataType,
                                          TextureDataType&);
    static Result   RendererCreateTexture(RendererDataType,
                                          int width, int height,
                                          int bitsPerTexel,
                                          const void* pTexels,
                                          int pTexelsArePersistent,
                                          int paletteEntryCount,
                                          const PaletteEntry*,
                                          TextureDataType&);
    static Result   RendererSetTextureDefaultShadeCount(RendererDataType,
                                                        unsigned long);
    static Result   RendererSetTextureDefaultColorCount(RendererDataType,
                                                        unsigned long);

    // Device
    static void             DeviceDestroy(DeviceDataType);
    static Result           DeviceSetColorModel(DeviceDataType, ColorModel);
    static Result           DeviceSetShadingModel(DeviceDataType, ShadingModel);
    static Result           DeviceSetShadeCount(DeviceDataType, unsigned long);
    static Result           DeviceSetDither(DeviceDataType, int);
    static unsigned long    DeviceGetWidth(DeviceDataType);
    static unsigned long    DeviceGetHeight(DeviceDataType);
    static void             DeviceHandleActivate(DeviceDataType, int);
    static void             DeviceHandlePaint(DeviceDataType, void* pData);
    static Result           DeviceUpdate(DeviceDataType);
#ifdef _DEBUG
    static unsigned long    DeviceGetDrawnTriangleCount(DeviceDataType); 
#endif

    // View
    static void     ViewDestroy(ViewDataType);
    static Result   ViewClear(ViewDataType);
    static Result   ViewSetCamera(ViewDataType, const CameraDataType);
    static Result   ViewAddLight(ViewDataType, const LightDataType);
    static Result   ViewRemoveLight(ViewDataType, const LightDataType);
    static Result   ViewRender(ViewDataType, const GroupDataType);
    static Result   ViewForceUpdate(ViewDataType,
                                    unsigned long x,
                                    unsigned long y,
                                    unsigned long width,
                                    unsigned long height);
    static Result   ViewSetBackgroundColor(ViewDataType,
                                           double r, double g, double b);
    static Result   ViewSetProjection(ViewDataType, ProjectionType);
    static Result   ViewSetFrontClippingPlane(ViewDataType, double distance);
    static Result   ViewSetBackClippingPlane(ViewDataType, double distance);
    static Result   ViewSetFrustrum(ViewDataType,
                                    double frontClippingDistance,
                                    double backClippingDistance,
                                    double degrees);
    static Result   ViewTransformWorldToScreen(ViewDataType,
                                               const double world[3],
                                               double screen[4]);
    static Result   ViewPick(ViewDataType,
                             unsigned long x,
                             unsigned long y,
                             const TglImpl::GroupImpl<D3DRM>** ppGroupsToPickFrom,
                             int groupsToPickFromCount,
                             const Group**& rppPickedGroups,
                             int& rPickedGroupCount);

    // Camera
    static void     CameraDestroy(CameraDataType);
    static Result   CameraSetTransformation(CameraDataType, const DoubleMatrix4&);

    // Light
    static void     LightDestroy(LightDataType);
    static Result   LightSetTransformation(LightDataType, const DoubleMatrix4&);

    // Group
    static void     GroupDestroy(GroupDataType);
    static Result   GroupSetTransformation(GroupDataType, const DoubleMatrix4&);
    static Result   GroupSetColor(GroupDataType, double r, double g, double b);
    static Result   GroupSetTexture(GroupDataType, TextureDataType);
    static Result   GroupAddGroup(GroupDataType, const GroupDataType pChildGroup);
    static Result   GroupAddMesh(GroupDataType, const MeshDataType);
    static Result   GroupRemoveGroup(GroupDataType, const GroupDataType pChildGroup);
    static Result   GroupRemoveMesh(GroupDataType, const MeshDataType);
    static Result   GroupRemoveAll(GroupDataType);
    static Result   GroupTransformLocalToWorld(GroupDataType,
                                               const double local[3],
                                               double world[3]);

    // Mesh
    static void     MeshDestroy(MeshDataType);
    static Result   MeshSetColor(MeshDataType, double r, double g, double b);
    static Result   MeshSetTexture(MeshDataType, TextureDataType);
    static Result   MeshSetTextureMappingMode(MeshDataType,
                                              TextureMappingMode);
    static Result   MeshSetShadingModel(MeshDataType,
                                        ShadingModel);

#ifdef _DEBUG
    static Result           MeshGetBoundingBox(MeshDataType,
                                               float [3], float[3]);
    static unsigned long    MeshGetFaceCount(MeshDataType);
    static unsigned long    MeshGetVertexCount(MeshDataType);
#endif

    // Texture
    static void     TextureDestroy(TextureDataType);
    static Result   TextureSetTexels(TextureDataType,
                                     int width, int height, int bitsPerTexel,
                                     const void* pTexels, int texelsArePersistent);
    static Result   TextureSetPalette(TextureDataType,
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
        ViewportAppData(RendererDataType);
        ~ViewportAppData();

        // 'light frame' that is the parent frame of all lights
        IDirect3DRMFrame*   m_pLightFrame;
        IDirect3DRMFrame*   m_pCamera;
        IDirect3DRMFrame*   m_pLastRenderedFrame;

        double              m_backgroundColorRed;
        double              m_backgroundColorGreen;
        double              m_backgroundColorBlue;
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
    static Result               ViewportCreateAppData(RendererDataType,
                                                      ViewDataType,
                                                      CameraDataType pCamera);
    static void                 ViewportDestroyCallback(IDirect3DRMObject*,
                                                        void*);
    static IDirect3DRMFrame*    ViewportGetLightFrame(ViewDataType);
    static void                 TextureDestroyCallback(IDirect3DRMObject*,
                                                       void*);
    static Image*               TextureGetImage(TextureDataType);
    static Result               TextureSetImage(TextureDataType, Image*);

private:
    static RendererDataType  g_pTheRenderer;
};

// ???
//extern void __cdecl AfxTrace(LPCTSTR lpszFormat, ...);

//////////////////////////////////////////////////////////////////////////////

inline
Result
D3DRM::RendererCreate(RendererDataType& rpD3DRM)
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
D3DRM::RendererDestroy(RendererDataType pD3DRM)
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
D3DRM::RendererCreateDevice(RendererDataType pD3DRM,
                            const DeviceDirectDrawCreateData& rCreateData,
                            DeviceDataType& rpDevice)
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
D3DRM::RendererCreateDevice(RendererDataType pD3DRM,
                            const DeviceDirect3DCreateData& rCreateData,
                            DeviceDataType& rpDevice)
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
D3DRM::RendererCreateView(RendererDataType pD3DRM,
                          const DeviceDataType pDevice,
                          const CameraDataType pCamera,
                          unsigned long x, unsigned long y,
                          unsigned long width, unsigned long height,
                          ViewDataType& rpViewport)
{
    Result  result;

    result = ResultVal(pD3DRM->CreateViewport(const_cast<DeviceDataType>(pDevice),
                                              const_cast<CameraDataType>(pCamera),
                                              x, y, width, height,
                                              &rpViewport));

    if (Succeeded(result))
    {
        result = ViewportCreateAppData(pD3DRM,
                                       rpViewport,
                                       const_cast<CameraDataType>(pCamera));

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
D3DRM::RendererCreateCamera(RendererDataType pD3DRM, CameraDataType& rpCamera)
{
    // camera is added to the scene when it is rendered
    return ResultVal(pD3DRM->CreateFrame(0, &rpCamera));
}

inline
Result
D3DRM::RendererCreateLight(RendererDataType pD3DRM, LightType type,
                          double r, double g, double b,
                          LightDataType& rpLight)
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
D3DRM::RendererCreateGroup(RendererDataType pD3DRM,
                           const GroupDataType pParentGroup,
                           GroupDataType& rpGroup)
{
    Result  result;

#if GROUP_PARENTCHILD
    result = ResultVal(pD3DRM->CreateFrame(const_cast<GroupDataType>(pParentGroup),
                                           &rpGroup));
#else

    result = ResultVal(pD3DRM->CreateFrame(0, &rpGroup));
    if (Succeeded(result) && pParentGroup)
    {
        result = ResultVal(const_cast<GroupDataType>(pParentGroup)->AddVisual(rpGroup));
        if (!Succeeded(result))
        {
            rpGroup->Release();
            rpGroup = 0;
        }
    }
#endif

    // ???
#if 0
    if (Succeeded(result))
    {
        result = ResultVal(rpGroup->SetMaterialMode(D3DRMMATERIAL_FROMPARENT));
        assert(Succeeded(result));
        if (!Succeeded(result))
        {
            rpGroup->Release();
            rpGroup = 0;
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
D3DRM::RendererCreateMesh(RendererDataType pD3DRM,
                          unsigned long vertexCount,
                          const float (*pVertices)[3],
                          const float (*pTextureCoordinates)[2],
                          unsigned long faceCount,
                          unsigned long vertexPerFaceCount,
                          unsigned long* pFaceData,
                          MeshDataType& rpMesh)
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
D3DRM::RendererCreateMesh(RendererDataType pD3DRM,
                          unsigned long vertexCount,
                          const float (*pVertices)[3],
                          const float (*pTextureCoordinates)[2],
                          unsigned long* pFaceData,
                          MeshDataType& rpMesh)
{
    // Face data is:
    //  [face1VertexCount face1Vertex1index, ... face1VertexMindex
    //   face2VertexCount face2Vertex1index, ... face2VertexNindex
    //   ...
    //   0]

    Result          result;

    result = ResultVal(pD3DRM->CreateMeshBuilder(&rpMesh));
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
        // result = ResultVal(rpMesh->ReserveSpace(vertexCount, 0, faceCount);

        result = ResultVal(rpMesh->AddFaces(vertexCount, pD3DRMVertices,
                                                  0, 0,
                                                  pFaceData, 0));

        if (Succeeded(result) && pTextureCoordinates)
        {
            unsigned long   i;

            for (i = 0; (i < vertexCount) && Succeeded(result); i++)
            {
                result = ResultVal(rpMesh->SetTextureCoordinates(i,
                                                                       pTextureCoordinates[i][0],
                                                                       pTextureCoordinates[i][1]));
            }
        }

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

    return result;
}

inline
Result
D3DRM::RendererCreateTexture(RendererDataType pD3DRM,
                             TextureDataType& rpTexture)
{
    return RendererCreateTexture(pD3DRM, 0, 0, 0, 0, 0, 0, 0, rpTexture);
}

inline
Result
D3DRM::RendererCreateTexture(RendererDataType pD3DRM,
                             int width, int height, int bitsPerTexel,
                             const void* pTexels,
                             int pTexelsArePersistent,
                             int paletteEntryCount,
                             const PaletteEntry* pEntries,
                             TextureDataType& rpTexture)
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
D3DRM::RendererSetTextureDefaultShadeCount(RendererDataType pD3DRM,
                                           unsigned long count)
{
    return ResultVal(pD3DRM->SetDefaultTextureShades(count));
}

inline
Result
D3DRM::RendererSetTextureDefaultColorCount(RendererDataType pD3DRM,
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
D3DRM::DeviceDestroy(DeviceDataType pDevice)
{
    pDevice->Release();
}

inline
Result
D3DRM::DeviceSetColorModel(DeviceDataType pDevice,
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
D3DRM::DeviceSetShadingModel(DeviceDataType pDevice,
                            ShadingModel shadingModel)
{
    D3DRMRENDERQUALITY	renderQuality = Translate(shadingModel);

    return ResultVal(pDevice->SetQuality(renderQuality));
}

inline
Result
D3DRM::DeviceSetShadeCount(DeviceDataType pDevice,
                          unsigned long shadeCount)
{
    return ResultVal(pDevice->SetShades(shadeCount));
}

inline
Result
D3DRM::DeviceSetDither(DeviceDataType pDevice,
                      int dither)
{
    return ResultVal(pDevice->SetDither(dither));
}

inline
unsigned long
D3DRM::DeviceGetWidth(DeviceDataType pDevice)
{
    return pDevice->GetWidth();
}

inline
unsigned long
D3DRM::DeviceGetHeight(DeviceDataType pDevice)
{
    return pDevice->GetHeight();
}

#ifdef _DEBUG
inline
unsigned long
D3DRM::DeviceGetDrawnTriangleCount(DeviceDataType pDevice)
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
D3DRM::DeviceHandleActivate(DeviceDataType pDevice, int activate)
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
D3DRM::DeviceHandlePaint(DeviceDataType pDevice, void* pData)
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
D3DRM::DeviceUpdate(DeviceDataType pDevice)
{
    return ResultVal(pDevice->Update()); 
}

//////////////////////////////////////////////////////////////////////////////
//
// View
//

inline
void
D3DRM::ViewDestroy(ViewDataType pViewport)
{
    pViewport->Release();
}

inline
Result
D3DRM::ViewSetProjection(ViewDataType pViewport, ProjectionType type)
{
    D3DRMPROJECTIONTYPE projectionType = Translate(type);

    return ResultVal(pViewport->SetProjection(projectionType));
}

inline
Result
D3DRM::ViewSetFrustrum(ViewDataType pViewport,
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
D3DRM::ViewSetBackgroundColor(ViewDataType pViewport,
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
D3DRM::ViewClear(ViewDataType pViewport)
{
    return ResultVal(pViewport->Clear());
}

inline
Result
D3DRM::ViewSetCamera(ViewDataType pViewport, const CameraDataType pCamera)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
    assert(pViewportAppData);

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_pLastRenderedFrame,
                                         pViewportAppData->m_pCamera,
                                         pViewportAppData->m_pLightFrame);
    assert(Succeeded(result));
    pViewportAppData->m_pCamera = const_cast<CameraDataType>(pCamera);
    pViewportAppData->m_pLastRenderedFrame = 0;

    return ResultVal(pViewport->SetCamera(const_cast<CameraDataType>(pCamera)));
}

inline
Result
D3DRM::ViewAddLight(ViewDataType pViewport, const LightDataType pLight)
{
    IDirect3DRMFrame*   pLightFrame = ViewportGetLightFrame(pViewport);

    assert(pLightFrame);
    return ResultVal(pLightFrame->AddChild(const_cast<LightDataType>(pLight)));
}

inline
Result
D3DRM::ViewRemoveLight(ViewDataType pViewport, const LightDataType pLight)
{
    IDirect3DRMFrame*   pLightFrame = ViewportGetLightFrame(pViewport);

    assert(pLightFrame);
    return ResultVal(pLightFrame->DeleteChild(const_cast<LightDataType>(pLight)));
}

inline
Result
D3DRM::ViewRender(ViewDataType pViewport, const GroupDataType pGroup)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(pViewport->GetAppData());
    assert(pViewportAppData);

    if (pViewportAppData->m_pLastRenderedFrame != pGroup)
    {
        result = ViewRestoreFrameAfterRender(pViewportAppData->m_pLastRenderedFrame,
                                             pViewportAppData->m_pCamera,
                                             pViewportAppData->m_pLightFrame);
        assert(Succeeded(result));

        pViewportAppData->m_pLastRenderedFrame = const_cast<IDirect3DRMFrame*>(pGroup);

        result = ViewPrepareFrameForRender(pViewportAppData->m_pLastRenderedFrame,
                                           pViewportAppData->m_pCamera,
                                           pViewportAppData->m_pLightFrame,
                                           pViewportAppData->m_backgroundColorRed,
                                           pViewportAppData->m_backgroundColorGreen,
                                           pViewportAppData->m_backgroundColorBlue);
        assert(Succeeded(result));
    }

    result = ResultVal(pViewport->Render(const_cast<GroupDataType>(pGroup)));
    assert(Succeeded(result));

    return result;
}

inline
Result
D3DRM::ViewForceUpdate(ViewDataType pViewport,
                       unsigned long x,
                       unsigned long y,
                       unsigned long width,
                       unsigned long height)
{
    return ResultVal(pViewport->ForceUpdate(x, y, x + width, y + height));
}

inline
Result
D3DRM::ViewTransformWorldToScreen(ViewDataType pViewport,
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
D3DRM::ViewportGetLightFrame(ViewDataType pViewport)
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
D3DRM::CameraDestroy(CameraDataType pCamera)
{
    pCamera->Release();
}

inline
Result
D3DRM::CameraSetTransformation(CameraDataType pCamera, 
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
D3DRM::LightDestroy(LightDataType pLight)
{
    // pLight's refCount is == 1 if light has been removed from a view
    // pLight's refCount is > 1 if light is still in view
    // Client must call pView->Remove(pLight) AND delete pLight in order
    // for the light to "really" be deleted
    pLight->Release();
}

inline
Result
D3DRM::LightSetTransformation(LightDataType pLight, 
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
D3DRM::GroupDestroy(GroupDataType pGroup)
{
    pGroup->Release();
}

inline
Result
D3DRM::GroupSetTransformation(GroupDataType pGroup, 
                             const DoubleMatrix4& transformation)
{
    D3DRMMATRIX4D  helper;
    D3DRMMATRIX4D* pTransformation = Translate(transformation, helper);

    return ResultVal(pGroup->AddTransform(D3DRMCOMBINE_REPLACE,
                                               *pTransformation));
}

inline
Result
D3DRM::GroupSetColor(GroupDataType pGroup, 
                     double r, double g, double b)
{
    return ResultVal(pGroup->SetColorRGB(D3DVAL(r), D3DVAL(g), D3DVAL(b)));
}

inline
Result
D3DRM::GroupSetTexture(GroupDataType pGroup,
                       TextureDataType pTexture)
{
    return ResultVal(pGroup->SetTexture(pTexture));
}

inline
Result
D3DRM::GroupAddGroup(GroupDataType pGroup, 
                     const GroupDataType pChildFrame)
{
#if GROUP_PARENTCHILD
    return ResultVal(pGroup->AddChild(const_cast<GroupDataType>(pChildFrame)));
#else
    return ResultVal(pGroup->AddVisual(const_cast<GroupDataType>(pChildFrame)));
#endif
}

inline
Result
D3DRM::GroupAddMesh(GroupDataType pGroup, 
                    const MeshDataType pMesh)
{
    return ResultVal(pGroup->AddVisual(const_cast<MeshDataType>(pMesh)));
}

inline
Result
D3DRM::GroupRemoveGroup(GroupDataType pGroup, const GroupDataType pChildFrame)
{
#if GROUP_PARENTCHILD
    return ResultVal(pGroup->DeleteChild(const_cast<GroupDataType>(pChildFrame)));
#else
    return ResultVal(pGroup->DeleteVisual(const_cast<GroupDataType>(pChildFrame)));
#endif
}

inline
Result
D3DRM::GroupRemoveMesh(GroupDataType pGroup, const MeshDataType pMesh)
{
    return ResultVal(pGroup->DeleteVisual(const_cast<MeshDataType>(pMesh)));
}

inline
Result
D3DRM::GroupRemoveAll(GroupDataType pGroup)
{
    IDirect3DRMVisualArray* pVisuals;
    Result                  result;

    result = ResultVal(pGroup->GetVisuals(&pVisuals));
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

            result = ResultVal(pGroup->DeleteVisual(pVisual));
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
D3DRM::GroupTransformLocalToWorld(GroupDataType pGroup,
                                  const double local[3],
                                  double world[3])
{
    Result      result;
    D3DVECTOR    rlWorld;
    D3DVECTOR    rlLocal;
    D3DVECTOR*   pD3DRMLocal = Translate(local, rlLocal);

    result = ResultVal(pGroup->Transform(&rlWorld, pD3DRMLocal));

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
D3DRM::MeshDestroy(MeshDataType pMesh)
{
    pMesh->Release();
}

inline
Result
D3DRM::MeshSetColor(MeshDataType pMesh, double r, double g, double b)
{
    return ResultVal(pMesh->SetColorRGB(D3DVAL(r), D3DVAL(g), D3DVAL(b)));
}

inline
Result
D3DRM::MeshSetTexture(MeshDataType pMesh,
                      TextureDataType pTexture)
{
    Result  result;

#if 0
    // ??? if using texture set color to white... otherwise
    // color shines through
    if (pTexture)
    {
        result = MeshSetColor(pMesh, 1, 1, 1);
        assert(Succeeded(result));
    }
#endif

    result = ResultVal(pMesh->SetTexture(pTexture));

    return result;
}

inline
Result
D3DRM::MeshSetTextureMappingMode(MeshDataType pMesh,
                                 TextureMappingMode mode)
{
    return ResultVal(pMesh->SetPerspective(mode == Perspective ? TRUE : FALSE));
}

inline
Result
D3DRM::MeshSetShadingModel(MeshDataType pMesh,
                           ShadingModel shadingModel)
{
    D3DRMRENDERQUALITY  d3drmQuality = Translate(shadingModel);

    return ResultVal(pMesh->SetQuality(d3drmQuality));
}

#ifdef _DEBUG
inline
Result
D3DRM::MeshGetBoundingBox(MeshDataType pMesh,
                          float min[3], float max[3])
{
    D3DRMBOX    meshBox;
    Result      result;

    result = ResultVal(pMesh->GetBox(&meshBox));
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
D3DRM::MeshGetFaceCount(MeshDataType pMesh)
{
    return pMesh->GetFaceCount();
}

inline
unsigned long
D3DRM::MeshGetVertexCount(MeshDataType pMesh)
{
    return pMesh->GetVertexCount();
}

#endif

//////////////////////////////////////////////////////////////////////////////
//
// Texture
//

inline
void
D3DRM::TextureDestroy(TextureDataType pTexture)
{
    pTexture->Release();
}

inline
Result
D3DRM::TextureSetTexels(TextureDataType pTexture,
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
D3DRM::TextureSetPalette(TextureDataType pTexture,
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
D3DRM::TextureGetImage(TextureDataType pTexture)
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
