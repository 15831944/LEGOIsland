#ifndef _tglRL20_h
#define _tglRL20_h

#include "tglImpl.h"    // TGL Implementation template
#include "rl.h"	        // Reality Lab 2.0
#define  DDRAW          // rlwin.h needs this to include Direct Draw support
#include "rlwin.h"      // Reality Lab 2.0 Windows
#include "math.h"       // tan()
#include <limits.h>     // INT_MAX

//////////////////////////////////////////////////////////////////////////////
//
// RL20 meta definition
//

namespace RL20Impl
{

using namespace Tgl;

struct RL20
{
    typedef int*        RendererDataType;
    typedef RLDevice    DeviceDataType;
    typedef RLViewport  ViewDataType;
    typedef RLFrame	CameraDataType;
    typedef RLFrame     LightDataType;
    typedef RLFrame	GroupDataType;
    typedef RLMesh      MeshDataType;
    typedef RLTexture   TextureDataType;

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
                                       DeviceDataType,
                                       CameraDataType camera,
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
                                        GroupDataType parentGroup,
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

    static Result   RendererSetTextureDefaultShadeCount(RendererDataType, unsigned long);
    static Result   RendererSetTextureDefaultColorCount(RendererDataType, unsigned long);

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
    static Result   ViewSetCamera(ViewDataType, CameraDataType);
    static Result   ViewAddLight(ViewDataType, LightDataType);
    static Result   ViewRemoveLight(ViewDataType, LightDataType);
    static Result   ViewRender(ViewDataType, GroupDataType);
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
    static Result   ViewPick(ViewDataType,
                             unsigned long x,
                             unsigned long y,
                             const TglImpl::GroupImpl<RL20>** ppGroupsToPickFrom,
                             int groupsToPickFromCount,
                             const Group**& rppPickedGroups,
                             int& rPickedGroupCount);
    static Result   ViewTransformWorldToScreen(ViewDataType,
                                               const double world[3],
                                               double screen[4]);

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
    static Result   GroupAddGroup(GroupDataType, GroupDataType childGroup);
    static Result   GroupAddMesh(GroupDataType, MeshDataType);
    static Result   GroupRemoveGroup(GroupDataType, GroupDataType childGroup);
    static Result   GroupRemoveMesh(GroupDataType, MeshDataType);
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
    static Result   MeshSetShadingModel(MeshDataType, ShadingModel);
#ifdef _DEBUG
    static Result           MeshGetBoundingBox(MeshDataType, float[3], float[3]);
    static unsigned long    MeshGetFaceCount(MeshDataType);
    static unsigned long    MeshGetVertexCount(MeshDataType);
#endif

    // Texture
    static void     TextureDestroy(TextureDataType);
    static Result   TextureSetTexels(TextureDataType,
                                     int width, int height,
                                     int bitsPerTexel,
                                     const void* pTexels,
                                     int pixelsArePersistent);
    static Result   TextureSetPalette(TextureDataType,
                                      int entryCount,
                                      const PaletteEntry*);
private:
    // Helper
    class Image : public RLImage
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
        ViewportAppData();
        ~ViewportAppData();

        // 'light frame' that is the parent frame of all lights
        RLFrame m_lightFrame;
        RLFrame m_camera;
        RLFrame m_lastRenderedFrame;

        double              m_backgroundColorRed;
        double              m_backgroundColorGreen;
        double              m_backgroundColorBlue;
    };

    friend ViewportAppData;

    static Result       ResultVal(RLError result)
    {
        return ((result == RLNoError) ? Success : Error); 
    }

    static Result   RendererCreateMesh(RendererDataType,
                                       unsigned long vertexCount,
                                       const float (*pVertices)[3],
                                       const float (*pTextureCoordinates)[2],
                                       int* pFaceData,
                                       MeshDataType&);

    static RLMatrix4d*      Translate(const DoubleMatrix4&, RLMatrix4d&);
    static RLVector*        Translate(const double[3], RLVector&);
    static int              Translate(TextureMappingMode);
    static RLRenderQuality  Translate(ShadingModel);

    static Result       ViewPrepareFrameForRender(RLFrame frame,
                                                  RLFrame camera,
                                                  RLFrame lightFrame,
                                                  double backgroundRed,
                                                  double backgroundGreen,
                                                  double backgroundBlue);
    static Result       ViewRestoreFrameAfterRender(RLFrame frame,
                                                    RLFrame camera,
                                                    RLFrame lightFrame);
    static Result       ViewportCreateAppData(ViewDataType, CameraDataType camera);
    static void         ViewportDestroyCallback(RLObject, void*);
    static RLFrame      ViewportGetLightFrame(ViewDataType);
    static void         RLTextureDestroyCallback(RLObject, void*);
    static Image*       TextureGetImage(TextureDataType);
    static Result       TextureSetImage(TextureDataType, Image*);

private:
    static RendererDataType         g_theRenderer;
};

//////////////////////////////////////////////////////////////////////////////

inline
Result
RL20::RendererCreate(RendererDataType& rRenderer)
{
    rRenderer = g_theRenderer;
    (*rRenderer)++;

    return Success;
}

inline
void
RL20::RendererDestroy(RendererDataType renderer)
{
    assert(renderer == g_theRenderer);
    assert(*renderer > 0);

    (*renderer)--;
}

inline
Result
RL20::RendererCreateDevice(RendererDataType,
                           const DeviceDirectDrawCreateData& rCreateData,
                           DeviceDataType& rDevice)
{
	rDevice = RLWinDDrawCreateDevice(reinterpret_cast<char*>(const_cast<GUID*>(rCreateData.m_driverGUID)),
                                      rCreateData.m_hWnd,
                                      rCreateData.m_pDirectDraw,
                                      rCreateData.m_pFrontBuffer,
                                      rCreateData.m_pBackBuffer,
                                      rCreateData.m_pPalette,
                                      rCreateData.m_isFullScreen ? RLDDRAW_FLIP : RLDDRAW_BLIT);

    if (rDevice)
    {
        RLObjectReference(rDevice);
        return Success;
    }
    else
    {
        return Error;
    }
}

inline
Result
RL20::RendererCreateDevice(RendererDataType,
                           const DeviceDirect3DCreateData&,
                           DeviceDataType&)
{
    return Error;
}

inline
Result
RL20::RendererCreateView(RendererDataType,
                         DeviceDataType device,
                         CameraDataType camera,
                         unsigned long x,
                         unsigned long y,
                         unsigned long width,
                         unsigned long height,
                         ViewDataType& rView)
{
    rView = RLCreateViewport(device, camera, x, y, width, height);

    if (rView)
    {
        Result  result;

        result = ViewportCreateAppData(rView, camera);

        if (!Succeeded(result))
        {
            RLObjectDestroy(rView);
            rView = 0;
        }
    }

    return (rView ? Success : Error);
}

inline
Result
RL20::RendererCreateCamera(RendererDataType, CameraDataType& rCamera)
{
    // camera is added to the scene when it is rendered

    rCamera	= RLCreateFrame(0);

    if (rCamera)
    {
        RLObjectReference(rCamera);
        return Success;
    }
    else
    {
        return Error;
    }
}

inline
Result
RL20::RendererCreateLight(RendererDataType,
                          LightType type,
                          double r, double g, double b,
                          LightDataType& rLight)
{
    // ??? translate type
    RLLightType	lightType = (RLLightType) type;
    RLFrame     lightFrame;
    RLLight     light;
    Result      result;

    lightFrame	= RLCreateFrame(0);

    if (!lightFrame)
    {
        assert(0);
        return Error;
    }

    assert(RLObjectGetReferenceCount(lightFrame) == 0);

    light = RLCreateLightRGB(lightType, RLVal(r), RLVal(g), RLVal(b));
    if (!light)
    {
        assert(0);
        RLObjectDestroy(lightFrame);
        return Error;
    }

    assert(RLObjectGetReferenceCount(light) == 0);

    result = ResultVal(RLFrameAddLight(lightFrame, light));
    if (!Succeeded(result))
    {
        assert(0);
        RLObjectDestroy(light);
        RLObjectDestroy(lightFrame);
        return result;
    }

    assert(RLObjectGetReferenceCount(light) == 1);
    assert(RLObjectGetReferenceCount(lightFrame) == 0);

    RLObjectReference(lightFrame);
    rLight = lightFrame;

    return result;
}

#define GROUP_PARENTCHILD 0

inline
Result
RL20::RendererCreateGroup(RendererDataType, GroupDataType parentGroup, GroupDataType& rGroup)
{
#if GROUP_PARENTCHILD
    rGroup = RLCreateFrame(parentGroup);
#else
    rGroup = RLCreateFrame(0);
    if ((rGroup != 0) && parentGroup)
    {
        RLFrameAddVisual(parentGroup, rGroup);
    }
#endif

    if (rGroup)
    {
        RLObjectReference(rGroup);
        return Success;
    }
    else
    {
        return Error;
    }
}

inline
Result
RL20::RendererCreateMesh(RendererDataType renderer,
                         unsigned long vertexCount,
                         const float (*pVertices)[3],
                         const float (*pTextureCoordinates)[2],
                         unsigned long faceCount,
                         unsigned long vertexPerFaceCount,
                         unsigned long* pFaceData,
                         MeshDataType&  rMesh)
{
    // Face data is faceCount tuples, each of format
    //  [vertex1index, ... vertexNindex], where N = vertexPerFaceCount

    int*    pRLFaceData;
    Result  result;

    // Face data needs to be in:
    //  [face1VertexCount face1Vertex1index, ... face1VertexMindex
    //   face2VertexCount face2Vertex1index, ... face2VertexNindex
    //   ...
    //   0]

    pRLFaceData = new int[(faceCount * (vertexPerFaceCount + 1)) + 1];

    for (unsigned long i = 0; i < faceCount; i++)
    {
        pRLFaceData[i * (vertexPerFaceCount + 1)] = vertexPerFaceCount;

        for (unsigned long j = 0; j < vertexPerFaceCount; j++)
        {
            // make sure unsigned long is representable as an int
            assert(pFaceData[(i * vertexPerFaceCount) + j] <= (unsigned long) INT_MAX);
            // make sure unsigned long does not end up being negative 
            assert(((int) pFaceData[(i * vertexPerFaceCount) + j]) >= 0);

            pRLFaceData[(i * (vertexPerFaceCount + 1)) + 1 + j] = 
              pFaceData[(i * vertexPerFaceCount) + j];
        }
    }

    pRLFaceData[faceCount * (vertexPerFaceCount + 1)] = 0;

    result = RendererCreateMesh(renderer,
                                vertexCount,
                                pVertices,
                                pTextureCoordinates,
                                pRLFaceData,
                                rMesh);

    delete [] pRLFaceData;

    return result;
}

inline
Result
RL20::RendererCreateMesh(RendererDataType renderer,
                         unsigned long vertexCount,
                         const float (*pVertices)[3],
                         const float (*pTextureCoordinates)[2],
                         unsigned long* pFaceData,
                         MeshDataType&  rMesh)
{
    // Face data is:
    //  [face1VertexCount face1Vertex1index, ... face1VertexMindex
    //   face2VertexCount face2Vertex1index, ... face2VertexNindex
    //   ...
    //   0]

    Result  result;

    if (sizeof(*pFaceData) == sizeof(int))
    {
        // verify assumptions that face data is representable as ints
#ifdef _DEBUG
        unsigned long*  pFaceVertexData;
        unsigned long   faceVertexCount;

        pFaceVertexData = pFaceData;
        faceVertexCount = *pFaceVertexData;
        while (faceVertexCount != 0)
        {
            pFaceVertexData += 1;
            for (unsigned long i = 0; i < faceVertexCount; i++)
            {
                // make sure unsigned long is representable as an int
                assert(pFaceVertexData[i] <= (unsigned long) INT_MAX);
                // make sure unsigned long does not end up being negative 
                assert(((int) pFaceVertexData[i]) > 0);
            }
            pFaceVertexData += faceVertexCount;
            faceVertexCount = *pFaceVertexData;
        }
#endif

        result = RendererCreateMesh(renderer,
                                    vertexCount, pVertices,
                                    pTextureCoordinates,
                                    reinterpret_cast<int*>(pFaceData),
                                    rMesh);
    }
    else
    {
        int*            pRLFaceData;
        int             faceDataSize;
        unsigned long*  pFaceVertexData;
        unsigned long   faceVertexCount;

        pFaceVertexData = pFaceData;
        faceVertexCount = *pFaceVertexData;
        faceDataSize = 0;
        while (faceVertexCount != 0)
        {
            faceDataSize    += (faceVertexCount + 1); // 1 because of vertex count itself
            pFaceVertexData += (faceVertexCount + 1);
            faceVertexCount = *pFaceVertexData;
        }
        faceDataSize    += 1;   // the last vertex count (which is 0)

        pRLFaceData = new int[faceDataSize];
        
        for (int i = 0; i < faceDataSize; i++)
        {
            // make sure unsigned long is representable as an int
            assert(pFaceVertexData[i] <= (unsigned long) INT_MAX);
            // make sure unsigned long does not end up being negative 
            assert(((int) pFaceVertexData[i]) > 0);
            pRLFaceData[i] = (int) pFaceData[i];
        }

        result = RendererCreateMesh(renderer,
                                    vertexCount, pVertices,
                                    pTextureCoordinates,
                                    pRLFaceData,
                                    rMesh);

        delete [] pRLFaceData;
    }

    return result;
}


Result
RL20::RendererCreateTexture(RendererDataType renderer, TextureDataType& rTexture)
{
    return RendererCreateTexture(renderer, 0, 0, 0, 0, 0, 0, 0, rTexture);
}

inline
Result
RL20::RendererCreateTexture(RendererDataType,
                            int width, int height, int bitsPerTexel,
                            const void* pTexels,
                            int pTexelsArePersistent,
                            int paletteEntryCount,
                            const PaletteEntry* pEntries,
                            TextureDataType& rTexture)
{
    Image*  pImage;
    Result  result;
    
    pImage = new Image(width, height, bitsPerTexel,
                       pTexels, pTexelsArePersistent,
                       paletteEntryCount, pEntries);
    assert(pImage);

    rTexture = RLCreateTexture(pImage);
    assert(rTexture);
    assert(RLObjectGetReferenceCount(rTexture) == 0);

    if (rTexture)
    {
        RLObjectReference(rTexture);

        result = TextureSetImage(rTexture, pImage);
        assert(Succeeded(result));

        if (!Succeeded(result))
        {
            RLObjectDestroy(rTexture);
            rTexture = 0;
        }
    }
    else
    {
        result = Error;
    }

    return result;
}

inline
Result
RL20::RendererSetTextureDefaultShadeCount(RendererDataType,
                                          unsigned long count)
{
    RLTextureSetDefaultShades((int) count);
    return ResultVal(RLNoError);
}

inline
Result
RL20::RendererSetTextureDefaultColorCount(RendererDataType,
                                          unsigned long count)
{
    RLTextureSetDefaultColours((int) count);
    return ResultVal(RLNoError);
}

inline
void
RL20::DeviceDestroy(DeviceDataType device)
{
    RLObjectDestroy(device);
}

inline
Result
RL20::DeviceSetColorModel(DeviceDataType device,
                          ColorModel colorModel)
{
    // ??? translate color model
    RLColourModel	rlColorModel = (RLColourModel) colorModel;

    return ResultVal(RLDeviceSetColourModel(device, rlColorModel));
}

inline
Result
RL20::DeviceSetShadingModel(DeviceDataType device,
                            ShadingModel shadingModel)
{
    RLRenderQuality	rlRenderQuality = Translate(shadingModel);

    return ResultVal(RLDeviceSetQuality(device, rlRenderQuality));
}

inline
Result
RL20::DeviceSetShadeCount(DeviceDataType device,
                          unsigned long shadeCount)
{
    return ResultVal(RLDeviceSetShades(device, shadeCount));
}

inline
Result
RL20::DeviceSetDither(DeviceDataType device,
                      int dither)
{
    return ResultVal(RLDeviceSetDither(device, dither));
}

inline
unsigned long
RL20::DeviceGetWidth(DeviceDataType device)
{
    return RLDeviceGetWidth(device);
}

inline
unsigned long
RL20::DeviceGetHeight(DeviceDataType device)
{
    return RLDeviceGetHeight(device);
}

#ifdef _DEBUG
inline
unsigned long
RL20::DeviceGetDrawnTriangleCount(DeviceDataType device)
{
    return RLDeviceGetPolygonsDrawn(device);
}
#endif

inline
void
RL20::DeviceHandleActivate(DeviceDataType device, int activate)
{
    // ???

    // this is incorrect/unneccessary for a memory device
    // this may be unneccessary for a ddraw device

    RLWinHandleActivate(device, activate); 
}

inline
void
RL20::DeviceHandlePaint(DeviceDataType device, void* pData)
{
    // ??? pData

    // ???
    // this is incorrect/unneccessary for a memory device
    // this may be unneccessary for a ddraw device

    HDC     hDC = (HDC) pData;

    RLWinHandlePaint(device, hDC);
}

inline
Result
RL20::DeviceUpdate(DeviceDataType device)
{
    return ResultVal(RLDeviceUpdate(device)); 
}


inline
void
RL20::ViewDestroy(ViewDataType viewport)
{
    RLObjectDestroy(viewport);
}

inline
Result
RL20::ViewSetProjection(ViewDataType viewport, ProjectionType type)
{
    // ??? conversion of ProjectionType
    return ResultVal(RLViewportSetProjection(viewport,
                                             (RLProjectionType) type));
}

inline
Result
RL20::ViewSetFrustrum(ViewDataType viewport,
                      double frontClippingDistance,
                      double backClippingDistance,
                      double degrees)
{
    double   field = frontClippingDistance * tan(DegreesToRadians(degrees/2));
    Result  result;

    result = ResultVal(RLViewportSetFront(viewport,
                                          RLVal(frontClippingDistance)));
    if (Succeeded(result))
    {
        result = ResultVal(RLViewportSetBack(viewport,
                                             RLVal(backClippingDistance)));
    }
    if (Succeeded(result))
    {
        result = ResultVal(RLViewportSetField(viewport, RLVal(field)));
    }

    return result;
}

inline
Result
RL20::ViewSetBackgroundColor(ViewDataType viewport,
                             double r,
                             double g,
                             double b)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(RLObjectGetAppData(viewport));
    assert(pViewportAppData);

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_lastRenderedFrame,
                                         pViewportAppData->m_camera,
                                         pViewportAppData->m_lightFrame);
    assert(Succeeded(result));
    pViewportAppData->m_backgroundColorRed      = r;
    pViewportAppData->m_backgroundColorGreen    = g;
    pViewportAppData->m_backgroundColorBlue     = b;
    pViewportAppData->m_lastRenderedFrame       = 0;

    return result;
}

inline
Result
RL20::ViewClear(ViewDataType viewport)
{
    return ResultVal(RLViewportClear(viewport));
}

inline
Result
RL20::ViewSetCamera(ViewDataType viewport, CameraDataType camera)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(RLObjectGetAppData(viewport));
    assert(pViewportAppData);

    result = ViewRestoreFrameAfterRender(pViewportAppData->m_lastRenderedFrame,
                                         pViewportAppData->m_camera,
                                         pViewportAppData->m_lightFrame);
    assert(Succeeded(result));
    pViewportAppData->m_camera = camera;
    pViewportAppData->m_lastRenderedFrame = 0;

    return ResultVal(RLViewportSetCamera(viewport, camera));
}

inline
Result
RL20::ViewAddLight(ViewDataType viewport, LightDataType light)
{
    RLFrame lightFrame = ViewportGetLightFrame(viewport);

    assert(lightFrame);
    return ResultVal(RLFrameAddChild(lightFrame, light));
}

inline
Result
RL20::ViewRemoveLight(ViewDataType viewport, LightDataType light)
{
    RLFrame lightFrame = ViewportGetLightFrame(viewport);

    assert(lightFrame);
    return ResultVal(RLFrameRemoveChild(lightFrame, light));
}

inline
Result
RL20::ViewRender(ViewDataType viewport, GroupDataType group)
{
    ViewportAppData*    pViewportAppData;
    Result              result;

    pViewportAppData = reinterpret_cast<ViewportAppData*>(RLObjectGetAppData(viewport));
    assert(pViewportAppData);

    if (pViewportAppData->m_lastRenderedFrame != group)
    {
        result = ViewRestoreFrameAfterRender(pViewportAppData->m_lastRenderedFrame,
                                             pViewportAppData->m_camera,
                                             pViewportAppData->m_lightFrame);
        assert(Succeeded(result));

        pViewportAppData->m_lastRenderedFrame = group;

        result = ViewPrepareFrameForRender(pViewportAppData->m_lastRenderedFrame,
                                           pViewportAppData->m_camera,
                                           pViewportAppData->m_lightFrame,
                                           pViewportAppData->m_backgroundColorRed,
                                           pViewportAppData->m_backgroundColorGreen,
                                           pViewportAppData->m_backgroundColorBlue);
        assert(Succeeded(result));
    }

    result = ResultVal(RLViewportRender(viewport, group));

    return result;
}


inline
Result
RL20::ViewForceUpdate(ViewDataType viewport,
                      unsigned long x,
                      unsigned long y,
                      unsigned long width,
                      unsigned long height)
{
    return ResultVal(RLViewportForceUpdate(viewport,
                                           x, y,
                                           x + width, y + height)); 
}

inline
Result
RL20::ViewTransformWorldToScreen(ViewDataType viewport,
                                 const double world[3],
                                 double screen[4])
{
    RLVector4d  rlScreen;
    RLVector    rlWorld;
    RLVector*   pRLWorld = Translate(world, rlWorld);
    Result      result;

    result = ResultVal(RLViewportTransform(viewport, &rlScreen, pRLWorld));

    if (Succeeded(result))
    {
        screen[0]  = rlScreen.x;
        screen[1]  = rlScreen.y;
        screen[2]  = rlScreen.z;
        screen[3]  = rlScreen.w;
    }

    return result;
}

//////////////////////////////////////////////////////////////////////////////
//
// View helper

inline
Result
RL20::ViewPrepareFrameForRender(RLFrame frame,
                                RLFrame camera,
                                RLFrame lightFrame,
                                double backgroundRed,
                                double backgroundGreen,
                                double backgroundBlue)
{
    Result  result = Success;

    if (frame)
    {
        // set background color
        result = ResultVal(RLSceneSetBackgroundRGB(frame,
                                                   RLVal(backgroundRed),
                                                   RLVal(backgroundGreen),
                                                   RLVal(backgroundBlue)));
        assert(Succeeded(result));

        // add camera to frame to be rendered
        result = ResultVal(RLFrameAddChild(frame, camera));
        assert(Succeeded(result));

        // add light frame to frame to be rendered
        result = ResultVal(RLFrameAddChild(frame, lightFrame));
        assert(Succeeded(result));

        // increase ref count of frame to ensure it does not get deleted underneath us
        RLObjectReference(frame);
    }

    return result;
}

inline
Result
RL20::ViewRestoreFrameAfterRender(RLFrame frame,
                                  RLFrame camera,
                                  RLFrame lightFrame)
{
    Result  result = Success;

    if (frame)
    {
        // remove camera and light frame from frame that was rendered

        // this doesn't destroy the camera as it is still the camera of the viewport...
        result = ResultVal(RLFrameRemoveChild(frame, camera));
        assert(Succeeded(result));
        assert(RLObjectGetReferenceCount(camera) > 0);

        result = ResultVal(RLFrameRemoveChild(frame, lightFrame));
        assert(Succeeded(result));
        assert(RLObjectGetReferenceCount(lightFrame) > 0);

        // decrease frame's ref count (it was increased in ViewPrepareFrameForRender())
        RLObjectDestroy(frame);
    }

    return result;
}

inline
RLFrame
RL20::ViewportGetLightFrame(ViewDataType viewport)
{
    assert(RLObjectGetAppData(viewport));
    return reinterpret_cast<ViewportAppData*>(RLObjectGetAppData(viewport))->m_lightFrame;
}

//////////////////////////////////////////////////////////////////////////////
//
// Camera

inline
void
RL20::CameraDestroy(CameraDataType camera)
{
    RLObjectDestroy(camera);
}

inline
Result
RL20::CameraSetTransformation(CameraDataType camera, const DoubleMatrix4& transformation)
{
    RLMatrix4d  rlTransformation;
    RLMatrix4d* pRLTransformation = Translate(transformation,
                                              rlTransformation);

    return ResultVal(RLFrameAddTransform(camera,
                                         RLCombineReplace,
                                         *pRLTransformation));
}

//////////////////////////////////////////////////////////////////////////////
//
// Light

inline
void
RL20::LightDestroy(LightDataType light)
{
    RLObjectDestroy(light);
}

inline
Result
RL20::LightSetTransformation(LightDataType light, const DoubleMatrix4& transformation)
{
    RLMatrix4d  rlTransformation;
    RLMatrix4d* pRLTransformation = Translate(transformation,
                                              rlTransformation);

    return ResultVal(RLFrameAddTransform(light,
                                         RLCombineReplace,
                                         *pRLTransformation));
}

//////////////////////////////////////////////////////////////////////////////
//
// Group

inline
void
RL20::GroupDestroy(GroupDataType group)
{
    RLObjectDestroy(group);
}

inline
Result
RL20::GroupSetTransformation(GroupDataType group, const DoubleMatrix4& transformation)
{
    RLMatrix4d  rlTransformation;
    RLMatrix4d* pRLTransformation = Translate(transformation,
                                              rlTransformation);

    return ResultVal(RLFrameAddTransform(group,
                                         RLCombineReplace,
                                         *pRLTransformation));
}

inline
Result
RL20::GroupSetColor(GroupDataType group, double r, double g, double b)
{
    return ResultVal(RLFrameSetColourRGB(group,
                                         RLVal(r), RLVal(g), RLVal(b)));
}

// ??? mapping/perspective ???

inline
Result
RL20::GroupSetTexture(GroupDataType group, TextureDataType texture)
{
    return ResultVal(RLFrameSetTexture(group, texture));
}

inline
Result
RL20::GroupAddGroup(GroupDataType group, GroupDataType childFrame)
{
#if GROUP_PARENTCHILD
    return ResultVal(RLFrameAddChild(group, childFrame));
#else
    return ResultVal(RLFrameAddVisual(group, childFrame));
#endif
}

inline
Result
RL20::GroupAddMesh(GroupDataType group, MeshDataType mesh)
{
    return ResultVal(RLFrameAddVisual(group, mesh));
}

inline
Result
RL20::GroupRemoveGroup(GroupDataType group, GroupDataType childFrame)
{
#if GROUP_PARENTCHILD
    return ResultVal(RLFrameRemoveChild(group, childFrame));
#else
    return ResultVal(RLFrameRemoveVisual(group, childFrame));
#endif
}

inline
Result
RL20::GroupRemoveMesh(GroupDataType group, MeshDataType mesh)
{
    return ResultVal(RLFrameRemoveVisual(group, mesh));
}

inline
Result
RL20::GroupRemoveAll(GroupDataType group)
{
    RLFrame*    pVisuals;
    int         visualCount;
    Result      result;

    result = ResultVal(RLFrameGetVisuals(group, &visualCount, &pVisuals));
    assert(Succeeded(result));

    if (Succeeded(result))
    {
        int i;

        for (i = 0; i < visualCount; i++)
        {
            result = ResultVal(RLFrameRemoveVisual(group, pVisuals[i]));
            assert(Succeeded(result));
        }
        RLFree(pVisuals);
    }

    return result;
}

inline
Result
RL20::GroupTransformLocalToWorld(GroupDataType group,
                                 const double local[3],
                                 double world[3])
{
    Result      result;
    RLVector    rlWorld;
    RLVector    rlLocal;
    RLVector*   pRLLocal = Translate(local, rlLocal);

    result = ResultVal(RLFrameTransform(group, &rlWorld, pRLLocal));

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
RL20::MeshDestroy(MeshDataType mesh)
{
    RLObjectDestroy(mesh);
}

inline
Result
RL20::MeshSetColor(MeshDataType mesh, double r, double g, double b)
{
    return ResultVal(RLMeshSetColourRGB(mesh,
                                        RLVal(r), RLVal(g), RLVal(b)));
}

// ??? mapping/perspective ???

inline
Result
RL20::MeshSetTexture(MeshDataType mesh, TextureDataType texture)
{
    Result  result;

    result = ResultVal(RLMeshSetTexture(mesh, texture));

    // ???
    RLMeshSetPerspective(mesh, TRUE);

    return result;
}

inline
Result
RL20::MeshSetTextureMappingMode(MeshDataType mesh,
                                TextureMappingMode mode)
{
    int rlMode = Translate(mode);

    return ResultVal(RLMeshSetPerspective(mesh, rlMode));
}

inline
Result
RL20::MeshSetShadingModel(MeshDataType mesh,
                                 ShadingModel shadingModel)
{
    RLRenderQuality	rlRenderQuality = Translate(shadingModel);

    return ResultVal(RLMeshSetQuality(mesh, rlRenderQuality));
}

#ifdef _DEBUG
inline
Result
RL20::MeshGetBoundingBox(MeshDataType mesh, float min[3], float max[3])
{
    // ??? translate box
    RLBox   meshBox;
    Result  result;

    result = ResultVal(RLMeshGetBox(mesh, &meshBox));

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
RL20::MeshGetFaceCount(MeshDataType mesh)
{
    return RLMeshGetFaceCount(mesh);
}

inline
unsigned long
RL20::MeshGetVertexCount(MeshDataType mesh)
{
    return RLMeshGetVertexCount(mesh);
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Texture
//

inline
void
RL20::TextureDestroy(TextureDataType texture)
{
    RLObjectDestroy(texture);
}

inline
Result
RL20::TextureSetTexels(TextureDataType texture,
                       int width, int height, int bitsPerTexel,
                       const void* pTexels, int texelsArePersistent)
{
    Image*  pImage = TextureGetImage(texture);
    Result  result;

    assert(pImage);
    pImage->SetTexels(width, height, bitsPerTexel,
                      pTexels, texelsArePersistent);

    result = ResultVal(RLTextureChanged(texture, TRUE, FALSE));
    assert(Succeeded(result));

    return Success;
}

inline
Result
RL20::TextureSetPalette(TextureDataType texture,
                        int entryCount, const PaletteEntry* pEntries)
{
    Image*  pImage = TextureGetImage(texture);
    Result  result;

    assert(pImage);
    pImage->SetPalette(entryCount, pEntries);

    result = ResultVal(RLTextureChanged(texture, FALSE, TRUE));
    assert(Succeeded(result));

    return Success;
}

//////////////////////////////////////////////////////////////////////////////
//
// Texture helper

inline
RL20::Image*
RL20::TextureGetImage(TextureDataType texture)
{
    return reinterpret_cast<Image*>(RLObjectGetAppData(texture));
}

/////////////////////////////////////////////////////////////////////
//
// Helper

inline
RLMatrix4d*
RL20::Translate(const DoubleMatrix4& tglMatrix4x4, RLMatrix4d& rlMatrix4x4)
{
    if ((sizeof(RLMatrix4d) == sizeof(DoubleMatrix4)) &&
        (sizeof((*((RLMatrix4d*) 0))[0]) == sizeof((*((DoubleMatrix4*) 0))[0])) &&
        (sizeof((*((RLMatrix4d*) 0))[0][0]) == sizeof((*((DoubleMatrix4*) 0))[0][0])))
    {
        return (RLMatrix4d*) (void*) &tglMatrix4x4;
    }
    else
    {
        int i;

        for (i = 0; i < (sizeof(rlMatrix4x4)/sizeof(rlMatrix4x4[0])); i++)
        {
            int j;

            for (j = 0; j < (sizeof(rlMatrix4x4[0])/sizeof(rlMatrix4x4[0][0])); j++)
            {
                rlMatrix4x4[i][j] = RLVal(tglMatrix4x4[i][j]);
            }
        }

        return &rlMatrix4x4;
    }
}

inline
RLVector*
RL20::Translate(const double tglVector[3], RLVector& rlVector)
{
    if ((sizeof(RLVector) == (3 * sizeof(double))) &&
        (sizeof(((RLVector*)0)->x) == sizeof(tglVector[0])) &&
        (offsetof(RLVector, x) == ((&tglVector[0] - &tglVector[0]) * sizeof(tglVector[0]))) &&
        (offsetof(RLVector, y) == ((&tglVector[1] - &tglVector[0]) * sizeof(tglVector[0]))) &&
        (offsetof(RLVector, z) == ((&tglVector[2] - &tglVector[0]) * sizeof(tglVector[0]))))
    {
        return (RLVector*) (void*) tglVector;
    }
    else
    {
        rlVector.x  = RLVal(tglVector[0]);
        rlVector.y  = RLVal(tglVector[1]);
        rlVector.z  = RLVal(tglVector[2]);

        return &rlVector;
    }
}

inline
int
RL20::Translate(TextureMappingMode mode)
{
    int  rlMode;

    switch (mode)
    {
    case Linear:
        rlMode = FALSE;
        break;
    case PerspectiveCorrect:
        rlMode = TRUE;
        break;
    default:
        rlMode = FALSE;
        break;
    }

    return rlMode;
}

RLRenderQuality
RL20::Translate(ShadingModel tglShadingModel)
{
    RLRenderQuality  renderQuality;

    // ??? use lookup table
    switch (tglShadingModel)
    {
    case Wireframe:
        renderQuality = RLRenderWireframe;
        break;
    case UnlitFlat:
        renderQuality = RLRenderUnlitFlat;
        break;
    case Flat:
        renderQuality = RLRenderFlat;
        break;
    case Gouraud:
        renderQuality = RLRenderGouraud;
        break;
    case Phong:
        renderQuality = RLRenderPhong;
        break;
    default:
        renderQuality = RLRenderFlat;
        break;
    }

    return renderQuality;
}

} // namespace RL20Impl

#endif /* _tglRL20_h */
