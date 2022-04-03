#ifndef _ROIInspectorROI_h
#define _ROIInspectorROI_h

#include "ViewManager.h"

namespace Tgl
{
    class Renderer;
    class Mesh;
}

class ROIInspectorLOD;

//////////////////////////////////////////////////////////////////////////////
//
// ROIInspectorROI
//

class ROIInspectorROI : public OrientableROI
{
public:
    ROIInspectorROI(Tgl::Renderer*);
    ~ROIInspectorROI();

    void            Add(const ViewROI*, const ViewLOD*, unsigned long vertexCount);
    void            Remove(const ViewROI*, const ViewLOD*);
    void            RemoveAll();

    int             GetInspectedLODCount() const { return m_lodInfoCount; }
    const ViewLOD*  GetInspectedLOD(int i) const;

    void            Scale(double);
    void            Rotate(const Vector3&);

    double          GetScale() const { return m_scale; }
    const Vector3&  GetRotation() const { return m_rotation; }

    Tgl::Group*     GetGeometry() const { return m_pGeometry; }

    double          IntrinsicImportance() const { return 0; }

protected:
    void            update_world_bounding_volumes();
    void            UpdateWorldTransform();

private:
    // LODInfo to keep track of LODs that are being viewed, i.e. LODs whose 
    // geometry has been added to this ROI LOD's geometry.  We need LODInfos
    // to figure out the bounding box and sphere of this ROI.
    struct LODInfo
    {
        const ViewROI*  m_pROI;
        const ViewLOD*  m_pLOD;
        unsigned long   m_vertexCount;
    };
    enum    { g_maxLODInfos = 50 };

private:
	Tgl::Group*         m_pGeometry;
    ROIInspectorLOD*    m_pLOD;
    Vector3             m_offset;
    double              m_scale;
    Vector3             m_rotation;
                
    LODInfo             m_lodInfos[g_maxLODInfos];
    int                 m_lodInfoCount;

};

#endif
