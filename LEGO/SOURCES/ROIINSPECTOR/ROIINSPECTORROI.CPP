#include "stdafx.h"
#include "ROIInspectorROI.h"
#include "Tgl.h"
#include "std.h"    // min, max
#include "float.h"  // FLT_EPSILON

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//////////////////////////////////////////////////////////////////////////////
//
// ROIInspectorLOD

class ROIInspectorLOD : public LODObject
{
public:
	ROIInspectorLOD(Tgl::Renderer* pRenderer)
    {
        m_pGeometry = pRenderer->CreateGroup();
    }

	~ROIInspectorLOD()
    {
        delete m_pGeometry;
    }

    Tgl::Group* GetGeometry() const { return m_pGeometry; }

    double      Cost(double) const { return 0; }
    double      AveragePolyArea() const { return 0; }
    int         NVerts() const { return 0; }

private:
    Tgl::Group* m_pGeometry;
};

//////////////////////////////////////////////////////////////////////////////
//
//

ROIInspectorROI::ROIInspectorROI(Tgl::Renderer* pRenderer)
{
    LODList<ROIInspectorLOD>*   pLODList;
    Tgl::Result                 result;
    
    m_lodInfoCount  = 0;
    m_scale         = 1;
    ZEROVEC3(m_rotation);
    m_pGeometry     = pRenderer->CreateGroup();
    m_pLOD          = new ROIInspectorLOD(pRenderer);

    pLODList        = new LODList<ROIInspectorLOD>(1);
    pLODList->PushBack(m_pLOD);
    lods            = pLODList;

    result = m_pGeometry->Add(m_pLOD->GetGeometry());
    ASSERT(Tgl::Succeeded(result));
}

ROIInspectorROI::~ROIInspectorROI()
{
    const LODObject*    pLOD;
    Tgl::Result         result;

    result = m_pGeometry->Remove(m_pLOD->GetGeometry());
    ASSERT(Tgl::Succeeded(result));

    pLOD = static_cast<LODList<ROIInspectorLOD>*>(lods)->PopBack();
    ASSERT(pLOD == m_pLOD);

    delete m_pLOD;
    m_pLOD = 0;
    
    delete lods;
    lods = 0;

    delete m_pGeometry;
    m_pGeometry = 0;
}

const ViewLOD*  ROIInspectorROI::GetInspectedLOD(int i) const
{
    ASSERT(i < m_lodInfoCount);
    return m_lodInfos[i].m_pLOD;
}

void ROIInspectorROI::Add(const ViewROI* pROI,
                          const ViewLOD* pLOD,
                          unsigned long vertexCount)
{
    int         i;
    Tgl::Result result;

    ASSERT(m_lodInfoCount < g_maxLODInfos);
    ASSERT(m_pLOD->GetGeometry());
    ASSERT(pROI->GetGeometry());
    ASSERT(pLOD->GetGeometry());

    // we can only contain one LOD from the same ROI

    // if we already have an LOD from this ROI - reuse its lodInfo
    for (i = 0; i < m_lodInfoCount; i++)
    {
        if (m_lodInfos[i].m_pROI == pROI)
        {
            // remove ROI's geometry from ROIInspectorROI LOD's geometry
            result = const_cast<Tgl::Group*>(m_pLOD->GetGeometry())->Remove(pROI->GetGeometry());
            ASSERT(Tgl::Succeeded(result));
            break;
        }
    }

    if (i == m_lodInfoCount)
    {
        // there was no LOD from this ROI already
        m_lodInfoCount++;
    }

    m_lodInfos[i].m_pROI           = pROI;
    m_lodInfos[i].m_pLOD           = pLOD;
    m_lodInfos[i].m_vertexCount    = vertexCount;

    // remove any LOD geometry from ROI's geometry
    result = const_cast<Tgl::Group*>(pROI->GetGeometry())->RemoveAll();
    ASSERT(Tgl::Succeeded(result));

    // add LOD geometry to ROI's geometry
    result = const_cast<Tgl::Group*>(pROI->GetGeometry())->Add(pLOD->GetGeometry());
    ASSERT(Tgl::Succeeded(result));

    // add ROI's geometry to ROIInspectorROI LOD's geometry
    result = const_cast<Tgl::Group*>(m_pLOD->GetGeometry())->Add(pROI->GetGeometry());
    ASSERT(Tgl::Succeeded(result));

    update_world_bounding_volumes();
    UpdateWorldTransform();
}

void ROIInspectorROI::Remove(const ViewROI* pROI, const ViewLOD* pLOD)
{
    int         i;
    Tgl::Result result;

    ASSERT(GetLODCount() == 1);
    ASSERT(GetLOD(0));
    ASSERT(static_cast<const ViewLOD*>(GetLOD(0))->GetGeometry());
    ASSERT(pROI->GetGeometry());

    // remove ROI's geometry from ROIInspectorROI LOD's geometry
    result = const_cast<Tgl::Group*>(m_pLOD->GetGeometry())->Remove(pROI->GetGeometry());
    ASSERT(Tgl::Succeeded(result));

    // shuffle LODInfos
    for (i = 0; (i < m_lodInfoCount) && (m_lodInfos[i].m_pLOD != pLOD); i++)
    {
        // empty
    }

    while ((i + 1) < m_lodInfoCount)
    {
        m_lodInfos[i]  = m_lodInfos[i + 1];
    }
    m_lodInfoCount--;

    update_world_bounding_volumes();
    UpdateWorldTransform();
}

void ROIInspectorROI::RemoveAll()
{
    Tgl::Result result;

    ASSERT(GetLODCount() == 1);
    ASSERT(GetLOD(0));
    ASSERT(static_cast<const ViewLOD*>(GetLOD(0))->GetGeometry());

    // remove ROI's geometry from ROIInspectorROI LOD's geometry
    result = const_cast<Tgl::Group*>(m_pLOD->GetGeometry())->RemoveAll();
    ASSERT(Tgl::Succeeded(result));

    m_lodInfoCount = 0;

    update_world_bounding_volumes();
    UpdateWorldTransform();
}

void ROIInspectorROI::Rotate(const Vector3& rotation)
{
    m_rotation[0]   = rotation[0];
    m_rotation[1]   = rotation[1];
    m_rotation[2]   = rotation[2];

    UpdateWorldTransform();
}

void ROIInspectorROI::Scale(double scale)
{
    m_scale = scale;

    UpdateWorldTransform();
}

void ROIInspectorROI::UpdateWorldTransform()
{
    Tgl::DoubleMatrix4  transformation;
    Tgl::Result         result;

    transformation  = Tgl::Translation(EXPAND3(m_offset));
    transformation *= Tgl::Scale(m_scale, m_scale, m_scale);
    transformation *= Tgl::RotationX(m_rotation[0]);
    transformation *= Tgl::RotationY(m_rotation[1]);
    // ??? transformation *= Tgl::RotationZ(m_rotation[2]);

    SETMAT4(local2world, transformation);

    // update Tgl
    ASSERT(m_pGeometry);
	result = m_pGeometry->SetTransformation(transformation);
	ASSERT(Tgl::Succeeded(result));
}

void ROIInspectorROI::update_world_bounding_volumes()
{
    unsigned long       vertexCount;

    // update world bounding box
    FILLVEC3(world_bounding_box.Min(), HUGE_VAL);
    FILLVEC3(world_bounding_box.Max(), -HUGE_VAL);
    vertexCount             = 0;

    for (int i = 0; i < m_lodInfoCount; i++)
    {
        const BoundingBox&  lodWorldBoundingBox = m_lodInfos[i].m_pROI->GetWorldBoundingBox();

        world_bounding_box.Min()[0] = std::min(world_bounding_box.Min()[0], lodWorldBoundingBox.Min()[0]);
        world_bounding_box.Min()[1] = std::min(world_bounding_box.Min()[1], lodWorldBoundingBox.Min()[1]);
        world_bounding_box.Min()[2] = std::min(world_bounding_box.Min()[2], lodWorldBoundingBox.Min()[2]);
        world_bounding_box.Max()[0] = std::max(world_bounding_box.Max()[0], lodWorldBoundingBox.Max()[0]);
        world_bounding_box.Max()[1] = std::max(world_bounding_box.Max()[1], lodWorldBoundingBox.Max()[1]);
        world_bounding_box.Max()[2] = std::max(world_bounding_box.Max()[2], lodWorldBoundingBox.Max()[2]);
        vertexCount += m_lodInfos[i].m_vertexCount;
    }

    // update world bounding sphere
    if (m_lodInfoCount > 0)
    {
        VPV3(world_bounding_sphere.Center(), world_bounding_box.Max(), world_bounding_box.Min());
        VXS3(world_bounding_sphere.Center(), world_bounding_sphere.Center(), 0.5);
        world_bounding_sphere.Radius() = sqrt(DISTSQRD3(world_bounding_box.Max(), world_bounding_box.Min())) / 2.0;
     }
    else
    {
        ZEROVEC3(world_bounding_sphere.Center());
        world_bounding_sphere.Radius()    = 0;
    }

    // re-position ourselves so bounding sphere center is at origin
    VXS3(m_offset, world_bounding_sphere.Center(), -1);

    // now offset bounding box and sphere
    VMV3(world_bounding_box.Min(), world_bounding_box.Min(), world_bounding_sphere.Center());
    VMV3(world_bounding_box.Max(), world_bounding_box.Max(), world_bounding_sphere.Center());
    ZEROVEC3(world_bounding_sphere.Center());

    // ??? update the sole LOD's m_numPolys w/ m_vertexCount...
}

