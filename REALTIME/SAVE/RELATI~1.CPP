
#include "realtime.h"
#include "vec.h"
#include "float.h"  // FLT_EPSILON

//???
#if 0
extern void AfxTrace(const char*, ...);
#define TRACEX AfxTrace
#else
void foo(const char*, ...) {}
#define TRACEX foo
#endif

using namespace std;

inline void build_parent2world(const Matrix4& local2world,
							   const Matrix4& local2parent,
							   Matrix4& parent2world)
{
    // given current local->world transform and current
    // local->parent, calculate what parent->world must be
    Matrix4 local_inverse;

    INVERTMAT4d(local_inverse, local2parent);
    MXM4(parent2world, local_inverse, local2world);
}


RelativeROI::RelativeROI(LODListBase* lodList)
: ROI(lodList)
{
	IDENTMAT4(local2parent);
	IDENTMAT4(local2world);
	FILLVEC3(world_bounding_box.Min(), HUGE_VAL);
	FILLVEC3(world_bounding_box.Max(), -HUGE_VAL);
	FILLVEC3(world_bounding_sphere.Center(), 0);
			 world_bounding_sphere.Radius() = 0.0;
	FILLVEC3(world_velocity, 0);
}

void RelativeROI::SetLocalTransform(const Matrix4& local_transform)
{
    Matrix4 parent2world;

    // figure out current parent2world transform using local2parent
    // *before* modifying local2parent
    build_parent2world(local2world, local2parent, parent2world);

	set_local_transform(local_transform);

    update_world_data(parent2world);
}

void RelativeROI::SetLocalTransformTree(const TransformTreeNode& tree)
{
    Matrix4 parent2world;

    // figure out current parent2world transform using local2parent
    // *before* modifying local2parent
    build_parent2world(local2world, local2parent, parent2world);

    set_local_transform_tree(tree);

    // update position, up, direction and update geometry
    update_world_data(parent2world);
}

void RelativeROI::set_local_transform(const Matrix4& local_transform)
{
	// sets local2parent transform for this roi
	// NOTE: only local2parent is updated (no world data), and only
	//       this roi's local2parent transform is updated
	// NOTE: caller must call update_world_data() after calling this member

#if 0
    // make sure axis are perpendicular
    assert(fabs(DOT3(local_transform[0], local_transform[1])) <= 4 * FLT_EPSILON);
    assert(fabs(DOT3(local_transform[0], local_transform[2])) <= 4 * FLT_EPSILON);
    assert(fabs(DOT3(local_transform[1], local_transform[2])) <= 4 * FLT_EPSILON);
#endif

    SETMAT4(local2parent, local_transform);

    // maintain local2parent in an affine state
    NORMALIZE_VEC3(local2parent[0], local2parent[0]);
    NORMALIZE_VEC3(local2parent[1], local2parent[1]);
    NORMALIZE_VEC3(local2parent[2], local2parent[2]);

    TRACEX("RelativeROI::set_local_transform():\n");
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(local2parent[0]));
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(local2parent[1]));
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(local2parent[2]));
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|\n", EXPAND4(local2parent[3]));
}

void RelativeROI::set_local_transform_tree(const TransformTreeNode& tree)
{
	// sets local2parent transforms for this roi and comps
	// NOTE: only local2parent transforms are updated (no world data)
    // NOTE: caller must call update_world_data() after calling this member,
    //       but it is sufficient to call update_world_data() on this roi
    //       since update_world_data() recurses

    if(tree.use_this_matrix)
		set_local_transform(tree.local2parent);
	
	const TransformTreeNodeList *kid_anim = tree.child_nodes; 
    if(kid_anim)
		WALK_STL_OBJECT(*kid_anim, TransformTreeNodeList, ci)
		{
			int which_comp = (*ci).child_index;
			RelativeROI* child;

			// ??? for now
#if 0
			child = (RelativeROI*) comp[which_comp];
#else
			CompoundObject::iterator iterator = comp->begin();
			for (int j = 0; j < which_comp; j++, ++iterator) 
			{
			}
			child = (RelativeROI*) *iterator;
#endif

			child->set_local_transform_tree(*ci);
		}
}

void
RelativeROI::update_world_data(const Matrix4& parent2world)
{
    // called to update local2world and world bounding volumes for this ROI
	// and recursively for comps
    
	update_local2world(parent2world);
	update_world_bounding_volumes();
	update_world_velocity();

	// iterate over comps
	if (comp)
	{
		CompoundObject::iterator iter;

		for (iter = comp->begin(); !(iter == comp->end()); iter++)
		{
			ROI* child = *iter;
        
			static_cast<RelativeROI*>(child)->update_world_data(local2world);
		}
	}
}

void
RelativeROI::update_local2world(const Matrix4& parent2world)
{
    // called to update local2world
	// use parent's local2world and local2parent to calculate local2world

    // parent2world better be affine
#if 0
    assert(fabs(NORMSQRD3(parent2world[0]) - 1.0f) <= (4 * FLT_EPSILON));
    assert(fabs(NORMSQRD3(parent2world[1]) - 1.0f) <= (4 * FLT_EPSILON));
    assert(fabs(NORMSQRD3(parent2world[2]) - 1.0f) <= (4 * FLT_EPSILON));
#endif

    MXM4(local2world, local2parent, parent2world);

    TRACEX("RelativeROI::update_local2world(): \n");
    TRACEX("   local2parent * parent2world = local2world\n");
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|   |% .4f, % .4f, % .4f, % .4f|   |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2parent[0]), EXPAND4(parent2world[0]), EXPAND4(local2world[0]));
    TRACEX("   |% .4f, % .4f, % .4f, % .4f| * |% .4f, % .4f, % .4f, % .4f| = |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2parent[1]), EXPAND4(parent2world[1]), EXPAND4(local2world[1]));
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|   |% .4f, % .4f, % .4f, % .4f|   |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2parent[2]), EXPAND4(parent2world[2]), EXPAND4(local2world[2]));
    TRACEX("   |% .4f, % .4f, % .4f, % .4f|   |% .4f, % .4f, % .4f, % .4f|   |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2parent[3]), EXPAND4(parent2world[3]), EXPAND4(local2world[3]));

}

void
RelativeROI::update_world_velocity()
{
	// nyi
}

void CalcWorldBoundingVolumes(const BoundingSphere& modelling_sphere,
							  const Matrix4& local2world,
							  BoundingBox& world_bounding_box,
							  BoundingSphere& world_bounding_sphere)
{
    // calculate world bounding volumes given a bounding sphere in modelling
	// space and local2world transform

    // ??? we need to transform the radius too... if scaling...

    V3XM4(world_bounding_sphere.Center(),
		  modelling_sphere.Center(),
		  local2world);

    world_bounding_sphere.Radius() = modelling_sphere.Radius();

    // update world_bounding_box
    world_bounding_box.Min()[0] = world_bounding_sphere.Center()[0] - world_bounding_sphere.Radius();
    world_bounding_box.Min()[1] = world_bounding_sphere.Center()[1] - world_bounding_sphere.Radius();
    world_bounding_box.Min()[2] = world_bounding_sphere.Center()[2] - world_bounding_sphere.Radius();
    world_bounding_box.Max()[0] = world_bounding_sphere.Center()[0] + world_bounding_sphere.Radius();
    world_bounding_box.Max()[1] = world_bounding_sphere.Center()[1] + world_bounding_sphere.Radius();
    world_bounding_box.Max()[2] = world_bounding_sphere.Center()[2] + world_bounding_sphere.Radius();

    TRACEX("CalcWorldBoundingVolumes:\n");
    TRACEX("   modelling_sphere.Center * local2world = bounding sphere center()\n");
    TRACEX("                                 |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2world[0]));
    TRACEX("   |% .4f, % .4f, % .4f| * |% .4f, % .4f, % .4f, % .4f| = |% .4f, % .4f, % .4f|\n",
            EXPAND3(world_bounding_sphere.Center()), EXPAND4(local2world[1]), EXPAND3(world_bounding_sphere.Center()));
    TRACEX("                                 |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2world[2]));
    TRACEX("                                 |% .4f, % .4f, % .4f, % .4f|\n",
            EXPAND4(local2world[3]));

    TRACEX("   bounding box    = [[% .4f, % .4f, % .4f][% .4f, % .4f, % .4f]]\n", EXPAND3(world_bounding_box.Min()), EXPAND3(world_bounding_box.Max()));
}

