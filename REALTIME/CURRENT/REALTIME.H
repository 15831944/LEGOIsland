
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
		position[0] = 0; position[1] = 0; position[2] = 0;
		direction[0] = 0; direction[1] = 0; direction[2] = 1;
		up[0] = 0; up[1] = 1; up[2] = 0;  // positive Y is up by default
		velosity[0] = 0; velosity[1] = 0; velosity[2] = 0;
		bounding_box.Min()[0] =
		bounding_box.Min()[1] =
		bounding_box.Min()[2] =  888888.;
		bounding_box.Max()[0] =
		bounding_box.Max()[1] =
		bounding_box.Max()[2] = -888888.;
		bounding_sphere.Center()[0] =
		bounding_sphere.Center()[1] =
		bounding_sphere.Center()[2] = 0.0;
		bounding_sphere.Radius() = 0.0;
	}
	virtual ~ROI()
    {
        // derived class set the comp, so it should delete it
        assert(!comp);
    }
	virtual double          IntrinsicImportance() const = 0;
	const LODListBase       &GetLODs()            const { assert(lods); return *lods; }
	const LODObject         *GetLOD(int which)    const { assert(lods); return (*lods)[which]; }
	int                     GetLODCount()         const { assert(lods); return lods->Size(); }
	const CompoundObject    *GetComp()            const { return comp; }
	const Vector3           &GetPosition()        const { return position; }
	const Vector3           &GetDirection()       const { return direction; }
	const Vector3           &GetUp()              const { return up; }
	const Vector3           &GetVelosity()        const { return velosity; }
	const BoundingBox       &GetBoundingBox()     const { return bounding_box; }
	const BoundingSphere    &GetBoundingSphere()  const { return bounding_sphere; }

protected:
	CompoundObject  *comp;
	Vector3         position;
	Vector3         direction;
	Vector3         up;
	Vector3         velosity;
	BoundingBox     bounding_box;
	BoundingSphere  bounding_sphere;
	LODListBase     *lods;
};


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
	void SetPOVSource(const ROI *obj);
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
	const ROI *pov_source;
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
