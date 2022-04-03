#ifndef _tglImpl_h
#define _tglImpl_h

#include "assert.h"

#include "tgl.h"

namespace TglImpl
{

using namespace Tgl;

//////////////////////////////////////////////////////////////////////////////
//  
// forward declaration

template <class T> class RendererImpl;
template <class T> class DeviceImpl;
template <class T> class ViewImpl;
template <class T> class CameraImpl;
template <class T> class LightImpl;
template <class T> class GroupImpl;
template <class T> class MeshImpl;
template <class T> class TextureImpl;

//////////////////////////////////////////////////////////////////////////////
//
// Renderer Implementation
//

template <class T>
class RendererImpl : public Renderer
{
public:
    // NOTE: a RendererImpl<T> is created in a two step process;
    //         first invoke the constructor, then call Create().
    RendererImpl() : m_data(0) { }
    RendererImpl(T::RendererDataType& data) : m_data(data)  {}
    ~RendererImpl();

private:
    RendererImpl(const RendererImpl<T>&);
    RendererImpl<T>& operator=(const RendererImpl<T>&);

public:
    // Abstract Data Type interface
    Device*     CreateDevice(const DeviceDirectDrawCreateData&);
    Device*     CreateDevice(const DeviceDirect3DCreateData&);
    View*       CreateView(const Device*, const Camera*,
                           unsigned long x, unsigned long y,
                           unsigned long width, unsigned long height);
    Group*      CreateGroup(const Group* pParentGroup = 0);
    Camera*     CreateCamera();
    Light*      CreateLight(LightType type, double r, double g, double b);
    Mesh*       CreateMesh(unsigned long vertexCount,
                           const float (*pVertices)[3],
                           const float (*pTextureCoordinates)[2],
                           unsigned long faceCount,
                           unsigned long vertexPerFaceCount,
                           unsigned long* pFaceData);
    Mesh*       CreateMesh(unsigned long vertexCount,
                           const float (*pVertices)[3],
                           const float (*pTextureCoordinates)[2],
                           unsigned long* pFaceData);
    Texture*    CreateTexture();
    Texture*    CreateTexture(int width, int height, int bitsPerTexel,
                              const void* pTexels,
                              int pTexelsArePersistent,
                              int paletteEntryCount,
                              const PaletteEntry* pEntries);

    Result      SetTextureDefaultShadeCount(unsigned long);
    Result      SetTextureDefaultColorCount(unsigned long);

    void*       ImplementationDataPtr();

    // Concrete Data Type interface
    Result      Create();
    void        Destroy();
    Result      CreateDevice(const DeviceDirectDrawCreateData&,
                             DeviceImpl<T>&);
    Result      CreateDevice(const DeviceDirect3DCreateData&, DeviceImpl<T>&);
    Result      CreateView(const DeviceImpl<T>&, const CameraImpl<T>&,
                           unsigned long x, unsigned long y,
                           unsigned long width, unsigned long height,
                           ViewImpl<T>&);
    Result      CreateGroup(const GroupImpl<T>* pParentGroup, GroupImpl<T>&);
    Result      CreateCamera(CameraImpl<T>&);
    Result      CreateLight(LightType type,
                            double r, double g, double b,
                            LightImpl<T>&);
    Result      CreateMesh(MeshImpl<T>&,
                           unsigned long vertexCount,
                           const float (*pVertices)[3],
                           const float (*pTextureCoordinates)[2],
                           unsigned long faceCount,
                           unsigned long vertexPerFaceCount,
                           unsigned long* pFaceData);
    Result      CreateMesh(MeshImpl<T>&,
                           unsigned long vertexCount,
                           const float (*pVertices)[3],
                           const float (*pTextureCoordinates)[2],
                           unsigned long* pFaceData);
    Result      CreateTexture(TextureImpl<T>&);
    Result      CreateTexture(TextureImpl<T>&,
                              int width, int height, int bitsPerTexel,
                              const void* pTexels,
                              int pTexelsArePersistent,
                              int paletteEntryCount,
                              const PaletteEntry* pEntries);

    T::RendererDataType&        ImplementationData();
    const T::RendererDataType&  ImplementationData() const;

private:
    T::RendererDataType	m_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// Renderer Implementation

template <class T>
RendererImpl<T>::~RendererImpl()
{
    Destroy();
}

template <class T>
inline
Result
RendererImpl<T>::Create()
{
    assert(!m_data);
    return T::RendererCreate(m_data);
}

template <class T>
void
RendererImpl<T>::Destroy()
{
    if (m_data)
    {
         T::RendererDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
inline
Result
RendererImpl<T>::CreateDevice(const DeviceDirectDrawCreateData& rCreateData,
                              DeviceImpl<T>& rDevice)
{
    assert(m_data);
    assert(!rDevice.ImplementationData());

    return T::RendererCreateDevice(m_data, rCreateData, rDevice.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateDevice(const DeviceDirect3DCreateData& rCreateData,
                              DeviceImpl<T>& rDevice)
{
    assert(m_data);
    assert(!rDevice.ImplementationData());

    return T::RendererCreateDevice(m_data, rCreateData, rDevice.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateView(const DeviceImpl<T>& rDevice,
                            const CameraImpl<T>& rCamera,
                            unsigned long x,
                            unsigned long y,
                            unsigned long width,
                            unsigned long height,
                            ViewImpl<T>& rView)
{
    assert(m_data);
    assert(rDevice.ImplementationData());
    assert(rCamera.ImplementationData());
    assert(!rView.ImplementationData());

    return T::RendererCreateView(m_data,
                                 rDevice.ImplementationData(),
                                 rCamera.ImplementationData(),
                                 x, y, width, height,
                                 rView.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateGroup(const GroupImpl<T>* pParentGroup,
                             GroupImpl<T>& rGroup)
{
    assert(m_data);
    assert(!pParentGroup || pParentGroup->ImplementationData());
    assert(!rGroup.ImplementationData());

    return T::RendererCreateGroup(m_data,
                                  pParentGroup ? pParentGroup->ImplementationData() : 0,
                                  rGroup.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateCamera(CameraImpl<T>& rCamera)
{
    assert(m_data);
    assert(!rCamera.ImplementationData());

    return T::RendererCreateCamera(m_data, rCamera.ImplementationData()); 
}

template <class T>
inline
Result
RendererImpl<T>::CreateLight(LightType type,
                             double r, double g, double b,
                             LightImpl<T>& rLight)
{
    assert(m_data);
    assert(!rLight.ImplementationData());

    return T::RendererCreateLight(m_data, type, r, g, b, rLight.ImplementationData()); 
}

template <class T>
inline
Result
RendererImpl<T>::CreateMesh(MeshImpl<T>& rMesh,
                            unsigned long vertexCount,
                            const float (*pVertices)[3],
                            const float (*pTextureCoordinates)[2],
                            unsigned long faceCount,
                            unsigned long vertexPerFaceCount,
                            unsigned long* pFaceData)
{
    assert(m_data);
    assert(!rMesh.ImplementationData());

    return T::RendererCreateMesh(m_data, 
                                 vertexCount,
                                 pVertices,
                                 pTextureCoordinates,
                                 faceCount,
                                 vertexPerFaceCount,
                                 pFaceData,
                                 rMesh.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateMesh(MeshImpl<T>& rMesh,
                            unsigned long vertexCount,
                            const float (*pVertices)[3],
                            const float (*pTextureCoordinates)[2],
                            unsigned long* pFaceData)
{
    assert(m_data);
    assert(!rMesh.ImplementationData());

    return T::RendererCreateMesh(m_data, 
                                 vertexCount,
                                 pVertices,
                                 pTextureCoordinates,
                                 pFaceData,
                                 rMesh.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateTexture(TextureImpl<T>& rTexture)
{
    assert(m_data);
    assert(!rTexture.ImplementationData());

    return T::RendererCreateTexture(m_data, rTexture.ImplementationData());
}

template <class T>
inline
Result
RendererImpl<T>::CreateTexture(TextureImpl<T>& rTexture,
                               int width, int height, int bitsPerTexel,
                               const void* pTexels,
                               int pTexelsArePersistent,
                               int paletteEntryCount,
                               const PaletteEntry* pEntries)
{
    assert(m_data);
    assert(!rTexture.ImplementationData());

    return T::RendererCreateTexture(m_data,
                                    width, height, bitsPerTexel,
                                    pTexels, pTexelsArePersistent,
                                    paletteEntryCount, pEntries,
                                    rTexture.ImplementationData());
}


template <class T>
Device*
RendererImpl<T>::CreateDevice(const DeviceDirectDrawCreateData& rCreateData)
{
    assert(m_data);

    DeviceImpl<T>*	pDeviceImpl = new DeviceImpl<T>;

    if (!CreateDevice(rCreateData, *pDeviceImpl))
    {
         delete pDeviceImpl;
         pDeviceImpl = 0;
    }

    return pDeviceImpl;
}

template <class T>
Device*
RendererImpl<T>::CreateDevice(const DeviceDirect3DCreateData& rCreateData)
{
    assert(m_data);

    DeviceImpl<T>*	pDeviceImpl = new DeviceImpl<T>;

    if (!CreateDevice(rCreateData, *pDeviceImpl))
    {
         delete pDeviceImpl;
         pDeviceImpl = 0;
    }

    return pDeviceImpl;
}

template <class T>
View*
RendererImpl<T>::CreateView(const Device* pDevice,
                            const Camera* pCamera,
                            unsigned long x, unsigned long y,
                            unsigned long width, unsigned long height)
{
    assert(m_data);
    assert(pDevice);
    assert(pCamera);

    ViewImpl<T>*     pViewImpl = new ViewImpl<T>;

    if (!CreateView(*static_cast<const DeviceImpl<T>*>(pDevice),
#if 0               /* ??? compiler bug ... */
                    *static_cast<const CameraImpl<T>*>(pCamera),
#else
                    *reinterpret_cast<const CameraImpl<T>*>(pCamera),
#endif
                    x, y, width, height,
                    *pViewImpl))
    {
         delete pViewImpl;
         pViewImpl = 0;
    }

    return pViewImpl;
}

template <class T>
Camera*
RendererImpl<T>::CreateCamera()
{
    assert(m_data);

    CameraImpl<T>*	pCameraImpl = new CameraImpl<T>;

    if (!CreateCamera(*pCameraImpl))
    {
         delete pCameraImpl;
         pCameraImpl = 0;
    }

    return pCameraImpl;
}

template <class T>
Light*
RendererImpl<T>::CreateLight(LightType type, double r, double g, double b)
{
    assert(m_data);

    LightImpl<T>*	pLightImpl = new LightImpl<T>;

    if (!CreateLight(type, r, g, b, *pLightImpl))
    {
         delete pLightImpl;
         pLightImpl = 0;
    }

    return pLightImpl;
}

template <class T>
Group*
RendererImpl<T>::CreateGroup(const Group* pParentGroup)
{
    assert(m_data);

    GroupImpl<T>*	pGroupImpl = new GroupImpl<T>;

    if (!CreateGroup(static_cast<const GroupImpl<T>*>(pParentGroup), *pGroupImpl))
    {
         delete pGroupImpl;
         pGroupImpl = 0;
    }

    return pGroupImpl;
}

template <class T>
Mesh*
RendererImpl<T>::CreateMesh(unsigned long vertexCount,
                            const float (*pVertices)[3],
                            const float (*pTextureCoordinates)[2],
                            unsigned long faceCount,
                            unsigned long vertexPerFaceCount,
                            unsigned long* pFaceData)
{
    assert(m_data);

    MeshImpl<T>*     pMeshImpl = new MeshImpl<T>;

    if (!CreateMesh(*pMeshImpl,
                    vertexCount,
                    pVertices,
                    pTextureCoordinates,
                    faceCount,
                    vertexPerFaceCount,
                    pFaceData))
    {
         delete pMeshImpl;
         pMeshImpl = 0;
    }

    return pMeshImpl;
}

template <class T>
Mesh*
RendererImpl<T>::CreateMesh(unsigned long vertexCount,
                            const float (*pVertices)[3],
                            const float (*pTextureCoordinates)[2],
                            unsigned long* pFaceData)
{
    assert(m_data);

    MeshImpl<T>*     pMeshImpl = new MeshImpl<T>;

    if (!CreateMesh(*pMeshImpl,
                    vertexCount,
                    pVertices,
                    pTextureCoordinates,
                    pFaceData))
    {
         delete pMeshImpl;
         pMeshImpl = 0;
    }

    return pMeshImpl;
}

template <class T>
Texture*
RendererImpl<T>::CreateTexture()
{
    assert(m_data);

    TextureImpl<T>* pTextureImpl = new TextureImpl<T>;

    if (!CreateTexture(*pTextureImpl))
    {
         delete pTextureImpl;
         pTextureImpl = 0;
    }

    return pTextureImpl;
}

template <class T>
Texture*
RendererImpl<T>::CreateTexture(int width, int height, int bitsPerTexel,
                               const void* pTexels,
                               int pTexelsArePersistent,
                               int paletteEntryCount,
                               const PaletteEntry* pEntries)
{
    assert(m_data);

    TextureImpl<T>* pTextureImpl = new TextureImpl<T>;

    if (!CreateTexture(*pTextureImpl,
                       width, height, bitsPerTexel,
                       pTexels, pTexelsArePersistent,
                       paletteEntryCount, pEntries))
    {
         delete pTextureImpl;
         pTextureImpl = 0;
    }

    return pTextureImpl;
}

template <class T>
Result
RendererImpl<T>::SetTextureDefaultShadeCount(unsigned long count)
{
    assert(m_data);

    return T::RendererSetTextureDefaultShadeCount(m_data, count);
}

template <class T>
Result
RendererImpl<T>::SetTextureDefaultColorCount(unsigned long count)
{
    assert(m_data);

    return T::RendererSetTextureDefaultColorCount(m_data, count);
}

template <class T>
void*
RendererImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::RendererDataType&
RendererImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::RendererDataType&
RendererImpl<T>::ImplementationData() const
{
    return m_data; 
}


//////////////////////////////////////////////////////////////////////////////
//
// Device Implementation
//

template <class T>
class DeviceImpl : public Device
{
public:
    DeviceImpl() : m_data(0) {}
    DeviceImpl(T::DeviceDataType& data) : m_data(data)	{}
    ~DeviceImpl();

private:
    // not implemented
    DeviceImpl(const DeviceImpl<T>&);
    DeviceImpl<T>& operator=(const DeviceImpl<T>&);

public:
    // Abstract Data Type interface

    // Object members
    void*           ImplementationDataPtr();

    // Device members
    unsigned long   GetWidth();
    unsigned long   GetHeight();
    Result          SetColorModel(ColorModel);
    Result          SetShadingModel(ShadingModel);
    Result          SetShadeCount(unsigned long);
    Result          SetDither(int);

    void            HandleActivate(int);
    void            HandlePaint(void*);
    Result          Update();

#ifdef _DEBUG
    unsigned long   GetDrawnTriangleCount();
#endif

    // Concrete Data Type interface
    void            Destroy();
    T::DeviceDataType&          ImplementationData();
    const T::DeviceDataType&    ImplementationData() const;

private:
    T::DeviceDataType	m_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// Device Implementation
//

template <class T>
DeviceImpl<T>::~DeviceImpl()
{
    Destroy();
}

template <class T>
void
DeviceImpl<T>::Destroy()
{
    if (m_data)
    {
         T::DeviceDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
Result
DeviceImpl<T>::SetColorModel(ColorModel colorModel)
{
    assert(m_data);

    return T::DeviceSetColorModel(m_data, colorModel);
}

template <class T>
Result
DeviceImpl<T>::SetShadingModel(ShadingModel shadingModel)
{
    assert(m_data);

    return T::DeviceSetShadingModel(m_data, shadingModel);
}

template <class T>
Result
DeviceImpl<T>::SetShadeCount(unsigned long count)
{
    assert(m_data);

    return T::DeviceSetShadeCount(m_data, count);
}

template <class T>
Result
DeviceImpl<T>::SetDither(int dither)
{
    assert(m_data);

    return T::DeviceSetDither(m_data, dither);
}

template <class T>
unsigned long
DeviceImpl<T>::GetWidth()
{
    assert(m_data);

    return T::DeviceGetWidth(m_data); 
}

template <class T>
unsigned long
DeviceImpl<T>::GetHeight()
{
    assert(m_data);

    return T::DeviceGetHeight(m_data); 
}

template <class T>
void
DeviceImpl<T>::HandleActivate(int activate)
{
    assert(m_data);

    T::DeviceHandleActivate(m_data, activate); 
}

template <class T>
void
DeviceImpl<T>::HandlePaint(void* pData)
{
    assert(m_data);

    T::DeviceHandlePaint(m_data, pData); 
}

template <class T>
Result
DeviceImpl<T>::Update()
{
    assert(m_data);

    return T::DeviceUpdate(m_data); 
}

#ifdef _DEBUG
template <class T>
unsigned long
DeviceImpl<T>::GetDrawnTriangleCount()
{
    assert(m_data);

    return T::DeviceGetDrawnTriangleCount(m_data); 
}
#endif

template <class T>
void*
DeviceImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::DeviceDataType&
DeviceImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::DeviceDataType&
DeviceImpl<T>::ImplementationData() const
{
    return m_data; 
}

//////////////////////////////////////////////////////////////////////////////
//
// View Implementation
//

template <class T>
class ViewImpl : public View
{
public:
    ViewImpl() : m_data(0) {}
    ViewImpl(T::ViewDataType& data) : m_data(data)  {}
    ~ViewImpl();

private:
    ViewImpl(const ViewImpl<T>&);
    ViewImpl<T>& operator=(const ViewImpl<T>&);

public:
    // Abstract Data Type interface

    // Object members
    void*   ImplementationDataPtr();

    // View members
    Result  Add(const Light*);
    Result  Remove(const Light*);
    Result  SetCamera(const Camera*);
    Result  SetProjection(ProjectionType);
    Result  SetFrontClippingPlane(double);
    Result  SetBackClippingPlane(double);
    Result  SetFrustrum(double, double, double);
    Result  SetBackgroundColor(double r, double g, double b);
    Result  Clear();
    Result  Render(const Group*);
    Result  ForceUpdate(unsigned long x, 
                        unsigned long y,
                        unsigned long width,
                        unsigned long height);
    Result  Pick(unsigned long x, 
                 unsigned long y,
                 const Group** ppGroupsToPickFrom,
                 int groupsToPickFromCount,
                 const Group**& rppPickedGroups,
                 int& rPickedGroupCount);

    Result  TransformWorldToScreen(const double world[3],
                                   double screen[4]);

    // Concrete Data Type interface
    void    Destroy();
    Result  Remove(const LightImpl<T>&);
    Result  Add(const LightImpl<T>&);
    Result  SetCamera(const CameraImpl<T>&);
    Result  Render(const GroupImpl<T>&);
    Result  Pick(unsigned long x, 
                 unsigned long y,
                 const GroupImpl<T>** ppGroupsToPickFrom,
                 int groupsToPickFromCount,
                 const Group**& rppPickedGroups,
                 int& rPickedGroupCount);
    T::ViewDataType&        ImplementationData();
    const T::ViewDataType&  ImplementationData() const;

private:
    T::ViewDataType	m_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// View Implementation
//

template <class T>
ViewImpl<T>::~ViewImpl()
{
    Destroy();
}

template <class T>
void
ViewImpl<T>::Destroy()
{
    if (m_data)
    {
         T::ViewDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
inline
Result
ViewImpl<T>::Add(const LightImpl<T>& rLight)
{
    assert(m_data);
    assert(rLight.ImplementationData());

    return T::ViewAddLight(m_data, rLight.ImplementationData());
}

template <class T>
inline
Result
ViewImpl<T>::Remove(const LightImpl<T>& rLight)
{
    assert(m_data);
    assert(rLight.ImplementationData());

    return T::ViewRemoveLight(m_data, rLight.ImplementationData());
}

template <class T>
inline
Result
ViewImpl<T>::SetCamera(const CameraImpl<T>& rCamera)
{
    assert(m_data);
    assert(rCamera.ImplementationData());

    return T::ViewSetCamera(m_data, rCamera.ImplementationData());
}

template <class T>
inline
Result
ViewImpl<T>::Render(const GroupImpl<T>& rScene)
{
    assert(m_data);
    assert(rScene.ImplementationData());

    return T::ViewRender(m_data, rScene.ImplementationData());
}

template <class T>
inline
Result
ViewImpl<T>::Pick(unsigned long x, 
                  unsigned long y,
                  const GroupImpl<T>** ppGroupsToPickFrom,
                  int groupsToPickFromCount,
                  const Group**& rppPickedGroups,
                  int& rPickedGroupCount)
{
    assert(m_data);

    return T::ViewPick(m_data,
                       x, y,
                       ppGroupsToPickFrom,
                       groupsToPickFromCount,
                       rppPickedGroups,
                       rPickedGroupCount);
}

template <class T>
Result
ViewImpl<T>::SetProjection(ProjectionType projectionType)
{
    assert(m_data);

    return T::ViewSetProjection(m_data, projectionType);
}

template <class T>
Result
ViewImpl<T>::SetFrustrum(double frontClippingDistance,
                         double backClippingDistance,
                         double degrees)
{
    assert(m_data);

    return T::ViewSetFrustrum(m_data,
                              frontClippingDistance, backClippingDistance,
                              degrees);
}

template <class T>
Result
ViewImpl<T>::SetBackgroundColor(double r, double g, double b)
{
    assert(m_data);

    return T::ViewSetBackgroundColor(m_data,r, g, b);
}

template <class T>
Result
ViewImpl<T>::Clear()
{
    assert(m_data);

    return T::ViewClear(m_data);
}

template <class T>
Result
ViewImpl<T>::Add(const Light* pLight)
{
    assert(m_data);
    assert(pLight);

    return Add(*static_cast<const LightImpl<T>*>(pLight));
}

template <class T>
Result
ViewImpl<T>::Remove(const Light* pLight)
{
    assert(m_data);
    assert(pLight);

    return Remove(*static_cast<const LightImpl<T>*>(pLight));
}

template <class T>
Result
ViewImpl<T>::SetCamera(const Camera* pCamera)
{
    assert(m_data);
    assert(pCamera);

    return SetCamera(*static_cast<const CameraImpl<T>*>(pCamera));
}

template <class T>
Result
ViewImpl<T>::Render(const Group* pGroup)
{
    assert(m_data);
    assert(pGroup);

    return Render(*static_cast<const GroupImpl<T>*>(pGroup));
}

template <class T>
Result
ViewImpl<T>::ForceUpdate(unsigned long x, 
                         unsigned long y,
                         unsigned long width,
                         unsigned long height)
{
    assert(m_data);

    return T::ViewForceUpdate(m_data, x, y, width, height); 
}

template <class T>
Result
ViewImpl<T>::Pick(unsigned long x, 
                  unsigned long y,
                  const Group** ppGroupsToPickFrom,
                  int groupsToPickFromCount,
                  const Group**& rppPickedGroups,
                  int& rPickedGroupCount)
{
    assert(m_data);

    return Pick(x, y,
                reinterpret_cast<const GroupImpl<T>**>(ppGroupsToPickFrom),
                groupsToPickFromCount,
                rppPickedGroups,
                rPickedGroupCount);
}

template <class T>
Result
ViewImpl<T>::TransformWorldToScreen(const double world[3],
                                    double screen[4])
{
    assert(m_data);

    return T::ViewTransformWorldToScreen(m_data, world, screen); 
}

template <class T>
void*
ViewImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::ViewDataType&
ViewImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::ViewDataType&
ViewImpl<T>::ImplementationData() const
{
    return m_data; 
}

//////////////////////////////////////////////////////////////////////////////
//
// Camera Implementation
//

template <class T>
class CameraImpl : public Camera
{
public:
    CameraImpl()	: m_data(0)	{}
    ~CameraImpl();

private:
    CameraImpl(const CameraImpl<T>&);
    CameraImpl<T>& operator=(const CameraImpl<T>&);

public:
    void*   ImplementationDataPtr();

    // Camera methods
    Result  SetTransformation(const DoubleMatrix4&);

    // Concrete Data Type
    void    Destroy();
    T::CameraDataType&          ImplementationData();
    const T::CameraDataType&    ImplementationData() const;

private:
    T::CameraDataType     m_data;
};


template <class T>
CameraImpl<T>::~CameraImpl()
{
    Destroy();
}

template <class T>
void
CameraImpl<T>::Destroy()
{
    if (m_data)
    {
         T::CameraDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
Result
CameraImpl<T>::SetTransformation(const DoubleMatrix4& transformation)
{
    assert(m_data);

    return T::CameraSetTransformation(m_data, transformation);
}

template <class T>
void*
CameraImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::CameraDataType&
CameraImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::CameraDataType&
CameraImpl<T>::ImplementationData() const
{
    return m_data; 
}

//////////////////////////////////////////////////////////////////////////////
//
// Light Implementation
//

template <class T>
class LightImpl : public Light
{
public:
    LightImpl()	: m_data(0)	{}
    ~LightImpl();

private:
    LightImpl(const LightImpl<T>&);
    LightImpl<T>& operator=(const LightImpl<T>&);

public:
    void*   ImplementationDataPtr();

    // Light methods
    Result  SetTransformation(const DoubleMatrix4&);

    // Concrete Data Type
    void    Destroy();
    T::LightDataType&       ImplementationData();
    const T::LightDataType& ImplementationData() const;

private:
    T::LightDataType     m_data;
};

template <class T>
LightImpl<T>::~LightImpl()
{
    Destroy();
}

template <class T>
void
LightImpl<T>::Destroy()
{
    if (m_data)
    {
         T::LightDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
Result
LightImpl<T>::SetTransformation(const DoubleMatrix4& transformation)
{
    assert(m_data);

    return T::LightSetTransformation(m_data, transformation);
}

template <class T>
void*
LightImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::LightDataType&
LightImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::LightDataType&
LightImpl<T>::ImplementationData() const
{
    return m_data; 
}

//////////////////////////////////////////////////////////////////////////////
//
// Group Implementation
//

template <class T>
class GroupImpl : public Group
{
public:
    GroupImpl() : m_data(0)	{}
    ~GroupImpl();

    int operator==(const T::GroupDataType&) const;

private:
    GroupImpl(const GroupImpl<T>&);
    GroupImpl<T>& operator=(const GroupImpl<T>&);

public:

    // Object members
    void*   ImplementationDataPtr();

    // Group members
    Result  SetTransformation(const DoubleMatrix4&);
    Result  SetColor(double, double, double);
    Result  SetTexture(const Texture*);

    Result  Add(const Mesh*);
    Result  Add(const Group*);

    Result  Remove(const Group*);
    Result  Remove(const Mesh*);

    Result  RemoveAll();

    Result  TransformLocalToWorld(const double[3], double[3]);

    // Concrete Data Type Interface
    void    Destroy();
    Result  SetTexture(const TextureImpl<T>*);
    Result  Add(const GroupImpl<T>&);
    Result  Add(const MeshImpl<T>&);
    Result  Remove(const GroupImpl<T>&);
    Result  Remove(const MeshImpl<T>&);
    T::GroupDataType&       ImplementationData();
    const T::GroupDataType& ImplementationData() const;

private:
    T::GroupDataType     m_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// Group Implementation
//

template <class T>
GroupImpl<T>::~GroupImpl()
{
    Destroy();
}

template <class T>
inline
int
GroupImpl<T>::operator==(const T::GroupDataType& rData) const
{
    return m_data == rData; 
}

template <class T>
void
GroupImpl<T>::Destroy()
{
    if (m_data)
    {
        T::GroupDestroy(m_data);
        m_data = 0;
    }
}

template <class T>
inline
Result
GroupImpl<T>::SetTexture(const TextureImpl<T>* pTexture)
{
    assert(m_data);
    assert(!pTexture || pTexture->ImplementationData());

    return T::GroupSetTexture(m_data, pTexture ? pTexture->ImplementationData() : 0);
}

template <class T>
inline
Result
GroupImpl<T>::Add(const GroupImpl<T>& rGroup)
{
    assert(m_data);
    assert(rGroup.ImplementationData());

    return T::GroupAddGroup(m_data, rGroup.ImplementationData());
}

template <class T>
inline
Result
GroupImpl<T>::Add(const MeshImpl<T>& rMesh)
{
    assert(m_data);
    assert(rMesh.ImplementationData());

    return T::GroupAddMesh(m_data, rMesh.ImplementationData());
}

template <class T>
inline
Result
GroupImpl<T>::Remove(const GroupImpl<T>& rGroup)
{
    assert(m_data);
    assert(rGroup.ImplementationData());

    return T::GroupRemoveGroup(m_data, rGroup.ImplementationData());
}

template <class T>
inline
Result
GroupImpl<T>::Remove(const MeshImpl<T>& rMesh)
{
    assert(m_data);
    assert(rMesh.ImplementationData());

    return T::GroupRemoveMesh(m_data, rMesh.ImplementationData());
}

template <class T>
inline
Result
GroupImpl<T>::RemoveAll()
{
    assert(m_data);

    return T::GroupRemoveAll(m_data);
}

template <class T>
Result
GroupImpl<T>::SetTransformation(const DoubleMatrix4& transformation)
{
    assert(m_data);

    return T::GroupSetTransformation(m_data, transformation);
}

template <class T>
inline
Result
GroupImpl<T>::TransformLocalToWorld(const double local[3], double world[3])
{
    assert(m_data);

    return T::GroupTransformLocalToWorld(m_data, local, world);
}

template <class T>
Result
GroupImpl<T>::SetColor(double r, double g, double b)
{
    assert(m_data);

    return T::GroupSetColor(m_data, r, g, b);
}

template <class T>
Result
GroupImpl<T>::SetTexture(const Texture* pTexture)
{
    assert(m_data);

#if 0               /* ??? compiler bug ... */
    return SetTexture(static_cast<const TextureImpl<T>*>(pTexture));
#else
    return SetTexture(reinterpret_cast<const TextureImpl<T>*>(pTexture));
#endif
}

template <class T>
Result
GroupImpl<T>::Add(const Group* pGroup)
{
    assert(m_data);
    assert(pGroup);

    return Add(*static_cast<const GroupImpl<T>*>(pGroup));
}

template <class T>
Result
GroupImpl<T>::Add(const Mesh* pMesh)
{
    assert(m_data);
    assert(pMesh);

#if 0               /* ??? compiler bug ... */
    return Add(*static_cast<const MeshImpl<T>*>(pMesh));
#else
    return Add(*reinterpret_cast<const MeshImpl<T>*>(pMesh));
#endif
}

template <class T>
Result
GroupImpl<T>::Remove(const Group* pGroup)
{
    assert(m_data);
    assert(pGroup);

    return Remove(*static_cast<const GroupImpl<T>*>(pGroup));
}

template <class T>
Result
GroupImpl<T>::Remove(const Mesh* pMesh)
{
    assert(m_data);
    assert(pMesh);

    return Remove(*static_cast<const MeshImpl<T>*>(pMesh));
}

template <class T>
void*
GroupImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::GroupDataType&
GroupImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::GroupDataType&
GroupImpl<T>::ImplementationData() const
{
    return m_data; 
}

//////////////////////////////////////////////////////////////////////////////
//
// Mesh Implementation
//

template <class T>
class MeshImpl : public Mesh
{
public:
    MeshImpl() : m_data(0)	{}
    ~MeshImpl();

private:
    MeshImpl(const MeshImpl<T>&);
    MeshImpl<T>& operator=(const MeshImpl<T>&);

public:
    // Object methods
    void*   ImplementationDataPtr();

    // Mesh methods
    Result  SetColor(double, double, double);
    Result  SetTexture(const Texture*);
    Result  SetTextureMappingMode(TextureMappingMode);
    Result  SetShadingModel(ShadingModel);

#ifdef _DEBUG
    Result  GetBoundingBox(float[3], float[3]);
    unsigned long   GetFaceCount();
    unsigned long   GetVertexCount();
#endif

    // Concrete Data Type
    void    Destroy();
    Result  SetTexture(const TextureImpl<T>*);
    T::MeshDataType&        ImplementationData();
    const T::MeshDataType&  ImplementationData() const;

private:
    T::MeshDataType	m_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// Mesh Implementation
//

template <class T>
MeshImpl<T>::~MeshImpl()
{
    Destroy();
}

template <class T>
void
MeshImpl<T>::Destroy()
{
    if (m_data)
    {
         T::MeshDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
inline
Result
MeshImpl<T>::SetTexture(const TextureImpl<T>* pTexture)
{
    assert(m_data);
    assert(!pTexture || pTexture->ImplementationData());

    return T::MeshSetTexture(m_data, pTexture ? pTexture->ImplementationData() : 0);
}

template <class T>
inline
Result
MeshImpl<T>::SetTextureMappingMode(TextureMappingMode mode)
{
    assert(m_data);

    return T::MeshSetTextureMappingMode(m_data, mode);
}

template <class T>
inline
Result
MeshImpl<T>::SetShadingModel(ShadingModel model)
{
    assert(m_data);

    return T::MeshSetShadingModel(m_data, model);
}

template <class T>
Result
MeshImpl<T>::SetColor(double r, double g, double b)
{
    assert(m_data);

    return T::MeshSetColor(m_data, r, g, b);
}

template <class T>
Result
MeshImpl<T>::SetTexture(const Texture* pTexture)
{
    assert(m_data);

    return SetTexture(static_cast<const TextureImpl<T>*>(pTexture));
}

#ifdef _DEBUG
template <class T>
Result
MeshImpl<T>::GetBoundingBox(float min[3], float max[3])
{
    assert(m_data);

    return T::MeshGetBoundingBox(m_data, min, max);
}

template <class T>
unsigned long
MeshImpl<T>::GetFaceCount()
{
    assert(m_data);

    return T::MeshGetFaceCount(m_data);
}

template <class T>
unsigned long
MeshImpl<T>::GetVertexCount()
{
    assert(m_data);

    return T::MeshGetVertexCount(m_data);
}
#endif

template <class T>
void*
MeshImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::MeshDataType&
MeshImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::MeshDataType&
MeshImpl<T>::ImplementationData() const
{
    return m_data; 
}

//////////////////////////////////////////////////////////////////////////////
//
// Texture Implementation
//

template <class T>
class TextureImpl : public Texture
{
public:
    TextureImpl() : m_data(0)	{}
    ~TextureImpl();

    Result  SetTexels(int width, int height, int bitsPerTexel,
                      const void* pTexels, int pTexelsArePersistent);
    Result  SetPalette(int entryCount, const PaletteEntry* pEntries);

private:
    TextureImpl(const TextureImpl<T>&);
    TextureImpl<T>& operator=(const TextureImpl<T>&);

public:
    // Object methods
    void*   ImplementationDataPtr();

    // Texture methods

    // Concrete Data Type
    void    Destroy();
    T::TextureDataType&         ImplementationData();
    const T::TextureDataType&   ImplementationData() const;

private:
    T::TextureDataType	m_data;
};

//////////////////////////////////////////////////////////////////////////////
//
// Texture Implementation
//

template <class T>
TextureImpl<T>::~TextureImpl()
{
    Destroy();
}

template <class T>
void
TextureImpl<T>::Destroy()
{
    if (m_data)
    {
         T::TextureDestroy(m_data);
         m_data = 0;
    }
}

template <class T>
Result
TextureImpl<T>::SetTexels(int width, int height, int bitsPerTexel,
                          const void* pTexels, int pTexelsArePersistent)
{
    assert(m_data);

    return T::TextureSetTexels(m_data, width, height, bitsPerTexel,
                               pTexels, pTexelsArePersistent);
}

template <class T>
Result
TextureImpl<T>::SetPalette(int entryCount, const PaletteEntry* pEntries)
{
    assert(m_data);

    return T::TextureSetPalette(m_data, entryCount, pEntries);
}

template <class T>
void*
TextureImpl<T>::ImplementationDataPtr()
{
    assert(m_data);

    return reinterpret_cast<void*>(&m_data); 
}

template <class T>
inline
T::TextureDataType&
TextureImpl<T>::ImplementationData()
{
    return m_data; 
}

template <class T>
inline
const T::TextureDataType&
TextureImpl<T>::ImplementationData() const
{
    return m_data; 
}

} // namespace TglImpl

#endif /* _tglImpl_h */
