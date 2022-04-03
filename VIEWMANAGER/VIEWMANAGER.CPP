#include "ViewManager.h"

using namespace Tgl;


// Just some useful macros
//
#ifndef M_PI
#		define M_PI 3.1416
#endif
#ifdef DTOR
#       undef DTOR
#endif
#       define DTOR(angle) ((angle) * M_PI / 180.)
#ifdef ABS
#       undef ABS
#endif
#       define ABS(n) (((n) > 0) ? (n) : -(n))
#ifdef MAX
#       undef MAX
#endif
#       define MAX(a, b) ((a) > (b) ? (a) : (b))
#ifdef MIN
#       undef MIN
#endif
#       define MIN(a, b) ((a) < (b) ? (a) : (b))
#ifdef SQR
#       undef SQR
#endif
#       define SQR(n) ((n) * (n))
#ifdef M_SQRT2
#       undef M_SQRT2
#endif
#       define M_SQRT2 1.41421356237309504880


class PillarLOD : public ViewLOD
{
public:
	PillarLOD(Renderer*, int i);
	double Cost(double pixels_covered) const
		{ return  pixels_covered/(640*480)/10 + nsections*.03/80; }
	double AveragePolyArea() const { return 2 * M_PI * 2.5 / nsections; };
	int NVerts() const { return nsections * 8; }
private:
	int nsections;
};



static inline void box_to_sphere(const BoundingBox &box, BoundingSphere &sph)
{
	double sums[3];
	VPV3(sums, box.Max(), box.Min());
	VDS3(sph.Center(), sums, 2.0);
	double extents[3];
	VMV3(extents, box.Max(), box.Min());
	double max_dim = MAX(extents[0], extents[1]);
	max_dim = MAX(max_dim, extents[2]);
	sph.Radius() = max_dim / 2.0;
}


static void box_union(BoundingBox &into,
				const BoundingBox &a, const BoundingBox &b)
{
	into.Min()[0] = MIN(a.Min()[0], b.Min()[0]);
	into.Min()[1] = MIN(a.Min()[1], b.Min()[1]);
	into.Min()[2] = MIN(a.Min()[2], b.Min()[2]);
	into.Max()[0] = MAX(a.Max()[0], b.Max()[0]);
	into.Max()[1] = MAX(a.Max()[1], b.Max()[1]);
	into.Max()[2] = MAX(a.Max()[2], b.Max()[2]);
}

void TreeNode::Add(ViewROI &vroi)
{
	// node bounds = union of all vroi's bounds
	if(0 == comp->size())
		world_bounding_box = vroi.GetWorldBoundingBox();
	else
		box_union(world_bounding_box, world_bounding_box, vroi.GetWorldBoundingBox());
	box_to_sphere(world_bounding_box, world_bounding_sphere); // simple for now
	//comp->insert(&vroi);
	comp->push_back(&vroi);
	//m_pGeometry->Add(vroi->GetGeometry());
}

void TreeNode::Moved(ViewROI &vroi)
{
	// Readjust ROI bounds.
	// This is most easily done by simply removing and then
	// reinserting the given vroi
	//    
	Remove(vroi);
	Add(vroi);
}

void TreeNode::Remove(ViewROI &vroi)
{
	// Remove the given ViewROI from this node's compound list
	//
    
    // make sure vroi is already in this node's compound list
    assert(!(std::find(comp->begin(), comp->end(), &vroi) == comp->end()));

	//comp->erase(CompoundObject::const_iterator((const ROI*)&vroi));
	comp->remove(&vroi);

	// Rebuild this node's bounds in case the removed object's box was
	// contributing to part of this node's box which then needs to shrink.
	//
    FILLVEC3(world_bounding_box.Min(), 888888.);
    FILLVEC3(world_bounding_box.Max(), -888888.);

	for(CompoundObject::iterator ci = comp->begin(); !(ci == comp->end()); ++ci) {
		OrientableROI *child = (OrientableROI *)(*ci);
    	box_union(world_bounding_box, world_bounding_box, child->GetWorldBoundingBox());
	}

    box_to_sphere(world_bounding_box, world_bounding_sphere); // simple for now
}


ViewManager::ViewManager(Tgl::Group* s,
                         const OrientableROI* point_of_view)
: rt_view(roi_root), scene(s)
{
	// XXX Perhaps ROI's should be able to have NULL LODLists ??
    // ??? TreeNode's constructor already creates an LODList
    // ??? if TreeNode has LODList should those LODLists be managed by 
    //     LODListManager ?
	// roi_root.SetLODs(pViewLODListManager->Create("xxx", 0));
	rt_view.SetPOVSource(point_of_view);
    seconds_allowed         = 0.25;
#ifdef _DEBUG
    seconds_used_last_frame = 0.25;
#endif
}

ViewManager::~ViewManager()
{
	rt_view.SetPOVSource(0);
}

void ViewManager::SetPOVSource(const OrientableROI* point_of_view)
{
	rt_view.SetPOVSource(point_of_view);
}


void ViewManager::Add(ViewROI &vroi)
{
	// Insert into ROI R-tree
	//
	roi_root.Add(vroi);

	// Insert the vroi's group into the graphical scene tree.
	// Note that the groups of any child nodes of the given vroi are
	// assumed to be hierarchically below the vroi's group therefore
	// only the vroi's top-level group needs to be dealt with here.
	//
	if (vroi.GetGeometry())
		scene->Add(vroi.GetGeometry());
}


void ViewManager::Moved(ViewROI &vroi)
{
	// Update the ROI R-tree
	//
	roi_root.Moved(vroi);

	// Note: no change needed to graphical tree since it's
	// assumed that the caller has handled the transformations.
}

void ViewManager::Remove(ViewROI &vroi)
{
	// Remove the vroi from ROI R-tree
	//
	roi_root.Remove(vroi);

	// Remove the vroi's group from the graphical scene tree.
	// Note that the groups of any child nodes of the given vroi are
	// assumed to be hierarchically below the vroi's group therefore
	// only the vroi's top-level group needs to be dealt with here.
	//
	if (vroi.GetGeometry())
    {
        // in debug version make sure the roi's geometry is really in the scene
#if _DEBUG
        if (!(std::find(visible_rois.begin(), visible_rois.end(), &vroi) == visible_rois.end()))
            scene->Remove(vroi.GetGeometry());
#else
		scene->Remove(vroi.GetGeometry());
#endif
    }
}


void ViewManager::Update(double secondsUsedLastFrame)
{
#ifdef _DEBUG
    seconds_used_last_frame = secondsUsedLastFrame;
#endif

    visible_rois.erase(visible_rois.begin(), visible_rois.end());
    visible_lod_indices.erase(visible_lod_indices.begin(), visible_lod_indices.end());

	rt_view.SelectLODs(seconds_allowed, secondsUsedLastFrame, visible_rois, visible_lod_indices);

	int visible_count = visible_rois.size();
	int i;

    // remove previously selected ROIs, if any, geometry from scene
    scene->RemoveAll();

	// At this moment, there should be no geometry in the scene at all,
	// at least as far as the ViewManager is aware.
	
	// Now add the selected LOD choice for all objects to draw this time.
	//
	for(i=0; i<visible_count; i++)
	{
        Result result;
		ViewROI *vroi = (ViewROI*)(visible_rois[i]);
		Group* group = vroi->GetGeometry();
		assert(group);
        // remove previously used LOD's geometry, if any, from ROI
		group->RemoveAll();
        // insert selected LOD's geometry in ROI's geometry
		int new_lod_index = visible_lod_indices[i];
		const ViewLOD *new_lod = (const ViewLOD*)vroi->GetLOD(new_lod_index);
		const Group *new_geom = new_lod->GetGeometry();
		assert(new_geom);
		result = group->Add(new_geom); // insert new lod
        assert(Succeeded(result));
        // add ROI's geometry to scene
        result = scene->Add(group);
        assert(Succeeded(result));
	}
}


static const unsigned long pillar_sections[5] = {5, 8, 12, 20, 80};
static const double rainbow[5][3] = {
	{1,0,0},   // red
	{1,.5,0},  // orange
	{1,1,0},   // yellow
	{0,1,0},   // green
	{0,0,1},   // blue
};

PillarLOD::PillarLOD(Renderer* pRenderer, int i) : ViewLOD(pRenderer)
{
	nsections = pillar_sections[i];
	unsigned long   face_count = 2 * nsections;
	unsigned long   vert_count = 2 * face_count;
	float           (*verts)[3] = new float[vert_count][3];
	unsigned long * faces = new unsigned long[4*face_count*2];
	double          radians_per_face = DTOR(360) / nsections;

	for(int f=0; f<nsections; f++) {
		double cos_rads = cos(f * radians_per_face);
		double sin_rads = sin(f * radians_per_face);
		// bottom ring
		verts[f*2][0] = 2.5 * cos_rads;
		verts[f*2][1] = 0;
		verts[f*2][2] = 2.5 * sin_rads;
		verts[vert_count/2 + f*2][0] = verts[f*2][0];
		verts[vert_count/2 + f*2][1] = verts[f*2][1];
		verts[vert_count/2 + f*2][2] = verts[f*2][2];
		// top ring
		verts[f*2+1][0] = 2.5 * cos_rads;
		verts[f*2+1][1] = 5;
		verts[f*2+1][2] = 2.5 * sin_rads;
		verts[vert_count/2 + f*2+1][0] = verts[f*2+1][0];
		verts[vert_count/2 + f*2+1][1] = verts[f*2+1][1];
		verts[vert_count/2 + f*2+1][2] = verts[f*2+1][2];
		// face to next
		faces[f*4+0] = 2*f;
		faces[f*4+1] = 2*f + 1;
		faces[f*4+2] = 2*((f+1)%nsections) + 1;
		faces[f*4+3] = 2*((f+1)%nsections);
		// back face
		faces[(f+nsections)*4+0] = vert_count/2 +2*f;
		faces[(f+nsections)*4+1] = vert_count/2 +2*((f+1)%nsections); 
		faces[(f+nsections)*4+2] = vert_count/2 +2*((f+1)%nsections)+1; 
		faces[(f+nsections)*4+3] = vert_count/2 +2*f + 1; 
	}
    
    Mesh *mesh = pRenderer->CreateMesh(vert_count, (const float(*)[3]) verts,
                                       0, face_count, 4, faces);
	mesh->SetColor(EXPAND3(rainbow[i]));
    assert(m_meshGroup);
	m_meshGroup->Add(mesh);
    delete mesh;
	delete[] verts;
	delete[] faces;
	//lods->Append(new LegoLOD(6, mesh));
}

ViewLODList* g_pPillarLODList = 0;

static const Vector3
	pillar_min(-2.5, 0, -2.5),
	pillar_max(2.5, 5, 2.5),
	pillar_center_offset(0, 2.5, 0);

void MakePillarLODList(Renderer* pRenderer, ViewLODListManager* pViewLODListManager)
{
    if (!g_pPillarLODList)
    {
		g_pPillarLODList = pViewLODListManager->Create("Pillar", 5);
        assert(g_pPillarLODList);
        // now g_pPillarLODList's refCount = 1
        assert((g_pPillarLODList->AddRef(), g_pPillarLODList->Release()) == 1);
		for(int i=0; i<5; i++)
        {
            // ??? how to add LODs...
			g_pPillarLODList->PushBack(new PillarLOD(pRenderer, i));
        }
    }
}

class Pillar : public ViewROI
{
public:
	Pillar(Renderer* pRenderer, ViewLODListManager* pViewLODListManager)
    : ViewROI(pRenderer, (MakePillarLODList(pRenderer, pViewLODListManager), g_pPillarLODList))
	{
		world_bounding_sphere.Radius() = sqrt(2 * SQR(2.5));
	}
	void update_world_bounding_volumes()
	{
		VPV3(world_bounding_box.Min(), GetWorldPosition(), pillar_min);
		VPV3(world_bounding_box.Max(), GetWorldPosition(), pillar_max);
		VPV3(world_bounding_sphere.Center(), GetWorldPosition(), pillar_center_offset);
	}
};

#define PILLAR_ROWS    5
#define PILLAR_COLUMNS 4

void ViewManager::AddTestROIs(Renderer* pRenderer, ViewLODListManager* pViewLODListManager)
{
	for(int i=0; i<PILLAR_ROWS; i++)
		for(int j=0; j<PILLAR_COLUMNS; j++) {
			Pillar *pillar = new Pillar(pRenderer, pViewLODListManager);
			Matrix4 pos;
			IDENTMAT4(pos);
			pos[3][0] = 10 * (i - PILLAR_ROWS/2.0);
			pos[3][1] = 0.0;
			pos[3][2] = 10 * (j - PILLAR_COLUMNS/2.0);
			pillar->SetLocalTransform(pos);
			Add(*pillar); // must be added *after* position is set
		}
}

