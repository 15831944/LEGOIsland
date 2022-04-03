
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                     *
 *                       REALTIME CONTROL SYSTEM                       *
 *                       version 1.0                                   *
 *                       by Daniel Green                               *
 *                       Mindscape, Inc.                               *
 *                       December 1995                                 *
 *                                                                     *
 * DESCRIPTION                                                         *
 *    This header file contains the declarations for all the classes   *
 *    in the real-time control system as described in the proposal of  *
 *    of the same name.                                                *
 *                                                                     *
 * BUGS                                                                *
 *    Mostly untested                                                  *
 *                                                                     *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _REALTIME_H
#define _REALTIME_H

#include "std.h"    // vector, list, set, map
#include "LODList.h"

#pragma warning( disable : 4786)
#pragma warning( disable : 4244)

/*
 * A convienient macro for walking an STL container object.
 * It expands to a "for" statement with a loop control variable
 * of the given name iterating over the given container object
 * of the given type.
 * Note that to walk an object given a pointer to it, simply
 * dereference it first (i.e. WALK_STL_OBJECT(*pObj, ObjType, oi)).
 */
#define WALK_STL_OBJECT(container, type, iterator_name) \
		for( \
			type::const_iterator iterator_name = (container).begin(); \
			(iterator_name) != (container).end(); \
			++(iterator_name) \
			)

/*
 * A simple array of three doubles that can be indexed into.
 */
class Vector3 {
public:
	double elements[3]; // storage is public for easy access
	Vector3() {}
	Vector3(double x, double y, double z) {
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
	}
	Vector3(const double v[3]) {
		elements[0] = v[0];
		elements[1] = v[1];
		elements[2] = v[2];
	}
	const double &operator[](long i) const { return elements[i]; }
	      double &operator[](long i)       { return elements[i]; }
};


/*
 * A simple array of four doubles that can be indexed into.
 */
class Vector4 {
public:
	double elements[4]; // storage is public for easy access
	Vector4() {}
	Vector4(double x, double y, double z, double w) {
		elements[0] = x;
		elements[1] = y;
		elements[2] = z;
		elements[3] = w;
	}
	Vector4(const double v[4]) {
		elements[0] = v[0];
		elements[1] = v[1];
		elements[2] = v[2];
		elements[3] = v[3];
	}
	const double &operator[](long i) const { return elements[i]; }
	      double &operator[](long i)       { return elements[i]; }
};


/*
 * A simple array of four Vector4s that can be indexed into.
 */
class Matrix4 {
public:
	Vector4 rows[4]; // storage is public for easy access
	Matrix4() {}
	Matrix4(
		const Vector4& x_axis,
		const Vector4& y_axis,
		const Vector4& z_axis,
		const Vector4& position)
	{
		rows[0] = x_axis;
		rows[1] = y_axis;
		rows[2] = z_axis;
		rows[3] = position;
	}
	Matrix4(const double m[4][4]) {
		rows[0] = m[0];
		rows[1] = m[1];
		rows[2] = m[2];
		rows[3] = m[3];
	}
	const Vector4 &operator[](long i) const { return rows[i]; }
	      Vector4 &operator[](long i)       { return rows[i]; }
};


/*
 * A list of transformation nodes.
 */
typedef std::list<class TransformTreeNode> TransformTreeNodeList; 

/*
 * A TransformTreeNode contains a transformation matrix for an ROI and
 * possibly some of it's descendants.
 * If use_this_matrix is true, the contained matrix will replace the one
 * used by the RelativeROI to which this node is passed in it's
 * SetLocalTransformTree method.
 * If child_nodes is non-NULL, each TransformTreeNode in the list is
 * recursivly passed to an ROI's child as indexed by child_index.
 * Note that the use_this_matrix flag is useful when an animation tree
 * contains data for some low-level nodes, but some intermediate nodes
 * should be left unaffected. Leaving such a node unaffected is different
 * from applying an identity matrix since it might be desired for those
 * nodes to be animated separately.
 */
class TransformTreeNode {
public:
	int child_index; // i'th comp within parent which this node refers to
	Matrix4 local2parent; // new transformation within ROI parent
	bool use_this_matrix; // matrix ignored if false but kids still recursed
	TransformTreeNodeList *child_nodes; // branches to recurse if non-NULL
};


/*
 * A simple bounding box object with Min and Max accessor methods.
 */
class BoundingBox {
public:
	const Vector3 &Min() const { return min; }
	      Vector3 &Min()       { return min; }
	const Vector3 &Max() const { return max; }
	      Vector3 &Max()       { return max; }
private:
	Vector3 min;
	Vector3 max;
};


/*
 * A simple bounding sphere object with center and radius accessor methods.
 */
class BoundingSphere {
public:
	const Vector3 &Center() const { return center; }
	      Vector3 &Center()       { return center; }
	const double &Radius()  const { return radius; }
	      double &Radius()        { return radius; }
private:
	Vector3 center;
	double radius;
};


#define NORMALIZE_VEC3(dst, src) { \
	double len = sqrt(NORMSQRD3(src)); \
	VDS3(dst, src, len); }


/*
 * Abstract base class representing a single LOD version of
 * a geometric object.
 */
class LODObject {
public:
	//LODObject();
	virtual ~LODObject() {}
    virtual double Cost(double pixels_covered) const = 0;
    virtual double AveragePolyArea() const = 0;
    virtual int NVerts() const = 0;
};

/*
 * A CompoundObject is simply a set of ROI objects which
 * all together represent a single object with sub-parts.
 */
class ROI;
//typedef std::set<ROI*, std::less<const ROI*> > CompoundObject;
typedef std::list<ROI*> CompoundObject;


/*
 * A ROIList is a list of ROI objects.
 */
typedef std::vector<const ROI*> ROIList;

/*
 * A simple list of integers.
 * Returned by RealtimeView::SelectLODs as indices into an ROIList.
 */
typedef std::vector<int> IntList;


/*
 * Abstract base class representing an object in a scene.
 * Application sub-classes must implement the IntrinsicImportance
 * method and must maintain it's current 3D data in the protected
 * data members. Note especially that the bounding box represents
 * the object in world space, therefore hierarchially transformed
 * objects will need to compute new world space bounding boxes
 * every time they move or are moved.
 */

class ROI {
public:
    ROI(LODListBase* lodList = 0) : lods(lodList)
    {
        comp = 0;
	}
	virtual ~ROI()
    {
        // derived class set the comp, so it should delete it
        assert(!comp);
    }
	virtual double					IntrinsicImportance() const = 0;
	virtual const Vector3			&GetWorldVelocity() const = 0;
	virtual const BoundingBox		&GetWorldBoundingBox() const = 0;
	virtual const BoundingSphere	&GetWorldBoundingSphere() const = 0;

	const LODListBase       *GetLODs() const { return lods; }
	const LODObject         *GetLOD(int i) const { assert(lods); return (*lods)[i]; }
	int                     GetLODCount() const { return lods ? lods->Size() : 0; }
	const CompoundObject    *GetComp() const { return comp; }

protected:
	CompoundObject  *comp;
	LODListBase     *lods;
};

class RelativeROI : public ROI {
public:
    RelativeROI(LODListBase* lodList = 0);

	const Vector3           &GetWorldVelocity()        const { return world_velocity; }
	const BoundingBox       &GetWorldBoundingBox()     const { return world_bounding_box; }
	const BoundingSphere    &GetWorldBoundingSphere()  const { return world_bounding_sphere; }

	void SetLocalTransform(const Matrix4&);
	void SetLocalTransformTree(const TransformTreeNode&);

	const double* GetWorldPosition() const { return local2world[3].elements; }
	const double* GetWorldDirection() const { return local2world[2].elements; }
	const double* GetWorldUp() const { return local2world[1].elements; }

protected:

	// update_world_data() is internally to update world data (local2world,
	// bounding volumes).  update_world_data() is implemented by calling
	// helper mebers update_local2world(), update_world_bounding_volumes() and
	// update_world_velocity() in sequence.
	// I.e., local2world is correct when update_world_bounding_volumes()
	// is called.
	virtual void update_world_data(const Matrix4& parent2world);
	virtual void update_local2world(const Matrix4& parent2world);
	virtual void update_world_bounding_volumes() = 0;
	virtual void update_world_velocity();

	void		 set_local_transform(const Matrix4&);
	void		 set_local_transform_tree(const TransformTreeNode&);

protected:
	Matrix4			local2parent;
	Matrix4			local2world;
	BoundingBox     world_bounding_box;
	BoundingSphere  world_bounding_sphere;
	Vector3         world_velocity;
};

// for convenience for a ROI derived class to implement
// update_world_bounding_volumes() using a modelling sphere
void CalcWorldBoundingVolumes(const BoundingSphere& modelling_sphere,
							 const Matrix4& local2world,
							 BoundingBox&,
							 BoundingSphere&);

typedef enum {
	BOX_OUTSIDE = 0,
	BOX_CONTAINED,
	BOX_INTERSECTS,
} BoxVisibility;


/*
 * These forward declarations are only for implementation purposes
 * and should *not* be assumed to be part of the public interface.
 */
struct LODChoice;
template <class T> class LODChoiceQueue;
struct LODChoiceLess;
//typedef std::map<const LODObject *, LODChoice, std::less<const LODObject *> > LOD2Choice;
typedef std::map< const ROI*, LODChoice, std::less<const ROI*> > ROI2Choice;
typedef LODChoiceQueue< LODChoiceLess > LittleChoiceFirst;
typedef std::map<unsigned long, LODChoice, std::less<unsigned long> > Pair2Choice;



/*
 * A RealtimeView represents a scene hierarchy plus a point-of-view
 * into that scene. The GetVisibleObjects method returns a list of
 * objects currently visible, and the SelectLODs method optionally calls
 * GetVisibleObjects and returns the indices of LODObjects from the
 * visible list that should give the most realistic rendering within
 * a given time constraint.	 Note that if SelectLODs is passed a non-
 * empty object list, the selection is done using that list. This
 * allows the caller to pass in the results of a previous call to
 * GetVisibleObjects which would otherwise be recalculated.
 */
class RealtimeView {
public:
	RealtimeView(const ROI &r);
	~RealtimeView();
	void SetPOVSource(const RelativeROI *obj);
	void SetFOV(double deg, double neer, double phar);
	void SetEyeSeparation(double sep) { eye_sep = sep; }
	void SetResolution(int w, int h);
	BoxVisibility BoxVisible(const BoundingBox &box) const;
	double ProjectedSize(const BoundingSphere &sphere) const;
	bool GetVisibleObjects(
				const ROI *from,
				ROIList &into,
				double size_threshold = 0.0, // 0 means get all vis
				bool known_totally_contained = false) const;
	void SelectLODs(
				double seconds_allowed, // total rendering budget
				double seconds_used_last_frame, // send 0.0 for new anim
				ROIList &draw, IntList &which_lods) const;
private:
	// private versions of some public methods which are called by them.
	// The difference is that the private versions assume all
	// casched data is up to date, while the public versions make sure
	// that's so.
	//
	BoxVisibility box_visible(const BoundingBox &box) const;
	double projected_size(const BoundingSphere &sphere) const;
	bool get_visible_objects(
				const ROI *from,
				ROIList &into,
				double size_threshold,
				bool known_totally_contained) const;
	void select_lods(double seconds_allowed, double seconds_used_last_frame,
				ROIList &draw, IntList &which_lods) const;
	
	// utility functions
	//
	void update_viewing_data();
	const LODChoice* get_choice(const ROI* roi, int which, int last_which,
				Pair2Choice &store, bool* new_choice=NULL) const;
	const LODChoice* add_choice(const ROI* roi, int which, int last_which,
				Pair2Choice& store) const;
	void calculate_values(LODChoice &choice) const;
	double apparent_speed(const ROI *roi) const;
	bool inside_roi(const ROI *roi) const;
	
	// private data
	//
	const ROI &scene;
	const RelativeROI *pov_source;
	double view_angle, front, back, eye_sep;
	int width, height;
	Vector3
		position,
		direction,
		up;

	// casched computed values
	//
	int view_pixels;          // width * height
	double view_box[8][3];    // coordinates of the 8 WCS corners of view frustum
	double
		cam_xfm[4][4],        // camera transformation matrix
		cam_inv[4][4],        // inverse of cam_xfm
		persp[4][4],          // perspective matrix
		wcs_to_npc[4][4];     // takes world coords to normalized projection coords
	double tan_half_angle;    // tangent of half the viewing angle
	double view_area_at_one;  // rough area of projection at Z == 1.0
	int persp_data_dirty;
	LittleChoiceFirst *s;
	ROI2Choice *last_s;
	double cost_adjustment;
	double seconds_expected_last_frame;
	bool maxed_last_frame;
};

#endif
