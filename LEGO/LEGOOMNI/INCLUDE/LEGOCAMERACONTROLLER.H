/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOCAMERACONTROLLER_H
#define __LEGOCAMERACONTROLLER_H

#include "MxPresenter.h"
#include "MxGeometry3D.h"
#include "LegoPOVController.h"

class LegoCameraController : public LegoPointOfViewController {
protected:
    void Destroy(MxBool p_fromDestructor);
	void Init();

	void OnLButtonDown(MxPoint32 p_point);
	void OnLButtonUp(MxPoint32 p_point);
	void OnRButtonDown(MxPoint32 p_point);
	void OnRButtonUp(MxPoint32 p_point);
	void OnMouseMove(MxU8 p_modifier, MxPoint32 p_point);

public:
	LegoCameraController();
	virtual ~LegoCameraController();
    virtual MxResult Create();
    virtual void Destroy();
	virtual MxS32 Notify(MxParam& p_param);
    virtual const MxChar* ClassName() { return "LegoCameraController"; }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, ClassName())) || (MxCore::IsA(p_str)) ; }

	void SetWorldTransform(const Mx3DPointDouble & p_location,const Mx3DPointDouble & p_direction, const Mx3DPointDouble & p_up);
	Mx3DPointDouble GetWorldLocation();
	Mx3DPointDouble GetWorldDirection();
	Mx3DPointDouble GetWorldUp();
};

typedef LegoCameraController * LegoCameraControllerPtr;

class LegoCameraControllerList : public MxPtrList<LegoCameraController> {
protected:
	MxS8 Compare(LegoCameraControllerPtr p_element1, LegoCameraControllerPtr p_element2) 
				{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoCameraControllerList(MxBool p_ownership=FALSE) : MxPtrList<LegoCameraController>(p_ownership) {}
};

class LegoCameraControllerListCursor : public MxPtrListCursor<LegoCameraController> {
public:
    LegoCameraControllerListCursor(LegoCameraControllerList* p_list) : MxPtrListCursor<LegoCameraController>(p_list) {}
};


#endif // __LEGOCAMERACONTROLLER_H

