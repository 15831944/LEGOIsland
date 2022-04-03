#ifndef __LEGOROI_H
#define __LEGOROI_H

#include "LegoTypes.h"
#include "LegoSphere.h"
#include "LegoMatrix.h"
#include "tgl.h"
#include "realtime.h"
#include "ViewManager.h"

class LegoMesh;
class LegoStorage;
class LegoAnim;
class LegoTreeNode;
class LegoAnimNodeData;

class LegoCostInfo {
public:
    LegoCostInfo() { m_pixelsCovered = 0.0F; m_cost = 0.0F; }
    LegoCostInfo(LegoFloat p_pixelsCovered, LegoFloat p_cost)
        { m_pixelsCovered = p_pixelsCovered; m_cost = p_cost; }
    LegoFloat GetPixelsCovered() { return m_pixelsCovered; }
    void SetPixelsCovered(LegoFloat p_pixelsCovered)
        { m_pixelsCovered = p_pixelsCovered; }
    LegoFloat GetCost() { return m_cost; }
    void SetCost(LegoFloat p_cost) { m_cost = p_cost; }
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
protected:
    LegoFloat m_pixelsCovered;
    LegoFloat m_cost;
};

class LegoLOD : public ViewLOD {
public:
    LegoLOD(Tgl::Renderer*);
    virtual ~LegoLOD();
    void SetMeshGroup(Tgl::Group* p_meshGroup) { m_meshGroup = p_meshGroup; }
    LegoU32 GetNumVertices() const { return m_numVertices; }
    void SetNumVertices(LegoU32 p_numVertices)
        { m_numVertices = p_numVertices; }
    LegoFloat GetAveragePolyArea() const { return m_averagePolyArea; }
    void SetAveragePolyArea(LegoFloat p_averagePolyArea)
        { m_averagePolyArea = p_averagePolyArea; }
    LegoU32 GetNumCosts() { return m_numCosts; }
    void SetNumCosts(LegoU32 p_numCosts) { m_numCosts = p_numCosts; }
    LegoCostInfo* GetCosts() { return m_costs; }
    void SetCosts(LegoCostInfo* p_costs) { m_costs = p_costs; }
    LegoCostInfo& GetCost(LegoU32 p_i) { return m_costs[p_i]; }
    void SetCost(LegoU32 p_i, LegoCostInfo& p_cost) { m_costs[p_i] = p_cost; }
    LegoResult Read(Tgl::Renderer*, LegoStorage* p_storage, LegoBool p_writable = FALSE);
    LegoResult Write(LegoStorage* p_storage);
    virtual double Cost(double pixelsCovered) const;
    virtual double AveragePolyArea() const { return m_averagePolyArea; }
    virtual int NVerts() const { return m_numVertices; }
protected:
    LegoU32 m_numMeshes;
    LegoMesh** m_meshes;
    LegoU32 m_numVertices;
    LegoFloat m_averagePolyArea;
    LegoU32 m_numCosts;
    LegoCostInfo* m_costs;
};

class LegoROI : public ViewROI {
public:
    LegoROI(Tgl::Renderer* p_renderer);
    LegoROI(Tgl::Renderer* p_renderer, ViewLODList* p_lodList);
	virtual ~LegoROI();
    LegoResult Read(Tgl::Renderer* p_renderer, ViewLODListManager* p_viewLODListManager, LegoStorage* p_storage, LegoBool p_writable = FALSE);
    LegoResult Write(LegoStorage* p_storage);
	virtual double IntrinsicImportance() const { return 0.5; }
    LegoResult SetFrame(LegoAnim* p_anim, LegoTime p_time);
    const LegoChar* GetName() const { return m_name; }
protected:
	// overidden virtual methods
    void update_world_bounding_volumes()
	{
		CalcWorldBoundingVolumes(m_sphere, local2world,
			world_bounding_box, world_bounding_sphere);
	}
    
	LegoResult CreateLocalTransformTree(LegoTreeNode* p_animNode, LegoTime p_time, TransformTreeNode* p_shadowTree, LegoMatrixF4x4 p_matrix);
	LegoResult CreateLocalTransform(LegoAnimNodeData* pAnimNodeData, LegoTime p_time, LegoMatrixF4x4& rLocalTransform);
	LegoChar* m_name;
    BoundingSphere m_sphere;
};


#endif // __LEGOROI_H



