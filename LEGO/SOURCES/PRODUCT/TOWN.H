

/*
							TOWN.H
							by Daniel Green
							Mindscape, Inc.
							July - 1995

	This file describes the device independant database and UI classes.
	They are independant of the window system to facilitate porting.
	They are dependant however on RL. This could have also been abstracted,
	but the effort is probably not worth the effort at this time.
 */

#ifndef _TOWN_H
#define _TOWN_H

#include "tgl.h"
//#include "roi\roi.h"
#include "legoroi.h"


#pragma warning( disable : 4244)

#include "realtime.h"

#ifndef M_PI
#	define M_PI 3.1415926535
#endif

#include "std.h"

/*
	People, cars, etc.
	LegoMovable objects are objects with a Tickle method.
	That method is overrided to create derived behaviors.
	The default behavior is simply to drive in the current
	direction and velosity, and to rotate by the current
	rotation,
 */
class LegoMovable : public LegoROI
{
public:
    LegoMovable(Tgl::Renderer*, ViewLODList* lods);
	virtual void    Tickle();
};


/*
	A Lego citizen represents a resident of a town.
	Citizens have bodies, clothes, jobs, etc. which will
	need to be created and accessed via new methods.
	Each citizen's body	contains a head who's orientation
	can be controlled
 */
class LegoCitizen : public LegoMovable
{
public:
    LegoCitizen(Tgl::Renderer*, ViewLODList* lods);
	
	void SetHeadOrientation(const Vector3 dir) { SET3(head_dir, dir); }
	Tgl::Camera* GetHead() { return m_pHead; }
protected:
	void update_world_bounding_volumes() {}
	void update_world_data(const Matrix4& parent2world);

private:
	Tgl::Camera* m_pHead;
	Vector3  head_dir;
};


/*
	The Town class describes the complete state of a Lego town.
	Each Island will potentially have one town object.
	A town contains base plates, objects and other state.
	The objects are either immobile scenery or movable objects.
	The Town::Tickle method walks the town forward one time
	step by telling each movable object to take a step, and to
	mediate that motion by doing the collision dection and potentially
	disallowing impossible motions.
	All access to the internals of the town are via public methods.
 */

class Town {
public:
	Town();
	~Town();

    Tgl::Renderer*  GetRenderer()   { return m_pRenderer; }
	Tgl::Group* GetScene()          { return m_pScene; }
	Tgl::Group* GetKidsEye()        { return m_pKidsEye; }
	Tgl::Group* GetCityPlanner()    { return m_pCityPlanner; }

	// Advance town one time frame by calling Tickle method
	// of all movable objects in the town.
	//
	void Tickle();

private:
    Tgl::Renderer*  m_pRenderer;
	Tgl::Group*     m_pScene;
	Tgl::Group*     m_pKidsEye;
	Tgl::Group*     m_pCityPlanner;
	Tgl::Group*     m_pSun;
};


//////////////////////////////////////////////////////////////////////////////
//
// Controller
//
// A Controller knows how to affect the world (town).
// Particular controllers know how to affect the world in different ways.
// A controller's methods are invoked, typically, in response to UI events,
// and not automatically by a tickle manager.
//
//
// CitizenController
//
// A CitizenController affects the world (twon) by controlling one of
// the objects (citizens) in the world.
//
//
// EditorController
//
// An EditorController is a weird controller in that it ignores the objects
// in the world (town) and instead creates its own scene and a camera in that
// scene.
//

class Controller {
public:
    Controller() {}
	virtual ~Controller() = 0;
};

inline Controller::~Controller() {}


class MouseController : public Controller {
public:
    MouseController();
	virtual ~MouseController();

	virtual void LeftDown(int, int);
	virtual void LeftDrag(int, int);
	virtual void LeftUp(int, int);
	virtual void RightDown(int, int);
	virtual void RightDrag(int, int);
	virtual void RightUp(int, int);

	BOOL        IsButtonDown() const { return m_isButtonDown; }
	double      ButtonX() const { return m_buttonX; }
	double      ButtonY() const { return m_buttonY; }

private:
	BOOL        m_isButtonDown;
	double      m_buttonX;
	double      m_buttonY;
};

class EditorController : public MouseController
{
public:
	EditorController(Tgl::Group*);
	~EditorController();

	std::vector<Tgl::Group*>&   Objects() { return m_pObjects; }
	Tgl::Group* CurrentObject() { return m_pCurrentObject; }
	void        SetCurrentObject(Tgl::Group*);
	void        Remove(Tgl::Group*);
	void        RemoveAll();

	void        LeftDrag(int, int);
	void        RightDrag(int, int);

private:
	Tgl::Group* m_pScene;
   	Tgl::Group* m_pCurrentObject;	// object being Affectd
	std::vector<Tgl::Group*> m_pObjects;
};

class CitizenController : public MouseController
{
public:
	CitizenController(LegoCitizen*);
	~CitizenController();

	LegoCitizen*    Citizen() { return m_pCitizen; }

	void    LeftDown(int x, int y)
		{ MouseController::LeftDown(x, y);   AffectCitizen(); }
	void    LeftDrag(int x, int y)
		{ MouseController::LeftDrag(x, y);   AffectCitizen(); }
	void    LeftUp(int x, int y)
		{ MouseController::LeftUp(x, y);     AffectCitizen(); }
	void    RightDown(int x, int y)
		{ MouseController::RightDown(x, y);  AffectCitizen(); }
	void    RightDrag(int x, int y)
		{ MouseController::RightDrag(x, y);  AffectCitizen(); }
	void    RightUp(int x, int y)
		{ MouseController::RightUp(x, y);    AffectCitizen(); }

	void    OnViewSize(int width, int height);

protected:
	void    AffectCitizen();

private:
	LegoCitizen*        m_pCitizen;
	int                 dev_center_x, dev_center_y;
};


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

#endif // TOWN_H
