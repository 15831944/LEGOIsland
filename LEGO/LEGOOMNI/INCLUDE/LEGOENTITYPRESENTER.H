/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOENTITYPRESENTER_H
#define __LEGOENTITYPRESENTER_H

#include "MxPresenter.h"
#include "MxGeometry3D.h"

class LegoEntity;
class LegoWorld;

class LegoEntityPresenter : public MxCompositePresenter {
protected:
	LegoEntity* m_entity;  // the entity this is presenting
	                       // could be a world or actor in derived classes
	LegoWorld* m_world;	   // the world entity belongs to

    void Destroy(MxBool p_fromDestructor);
	virtual void Init();

    virtual void ReadyTickle();
    virtual void StartingTickle();
    virtual void StreamingTickle();
    virtual void RepeatingTickle();
	
public:
	LegoEntityPresenter();
	virtual ~LegoEntityPresenter();
    virtual MxResult Create(LegoEntity* p_entity);
    virtual void Destroy();
	virtual MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action);
//	virtual MxS32 Notify(MxParam& p_param);
	virtual void EndAction();
	virtual MxResult Tickle();
    virtual MxResult PutData();
    static const MxChar* HandlerClassName() { return "LegoEntityPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoEntityPresenter::ClassName())) || (MxCompositePresenter::IsA(p_str)) ; }

	void SetWorld(LegoWorld* p_world) {m_world = p_world;}
	LegoWorld* GetWorld() {return m_world;}
	
 	void SetEntity(LegoEntity* p_entity) {m_entity = p_entity;}
	LegoEntity* GetEntity() {return m_entity;}

#if CLEANUP	
	void SetWorldLocation(const Mx3DPointDouble & p_location);
	
	void SetWorldDirection(const Mx3DPointDouble & p_direction);

	void SetWorldUp(const Mx3DPointDouble & p_up);
#endif

	void SetWorldTransform(const Mx3DPointDouble & p_location,const Mx3DPointDouble & p_direction, const Mx3DPointDouble & p_up);
	Mx3DPointDouble GetWorldLocation();
	Mx3DPointDouble GetWorldDirection();
	Mx3DPointDouble GetWorldUp();
	Mx3DPointDouble GetWorldVelocity();

	void SetWorldSpeed(MxDouble p_speed);
	MxDouble GetWorldSpeed();

};

typedef LegoEntityPresenter * LegoEntityPresenterPtr;

class LegoEntityPresenterList : public MxPtrList<LegoEntityPresenter> {
protected:
	MxS8 Compare(LegoEntityPresenterPtr p_element1, LegoEntityPresenterPtr p_element2) 
				{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoEntityPresenterList(MxBool p_ownership=FALSE) : MxPtrList<LegoEntityPresenter>(p_ownership) {}
};

class LegoEntityPresenterListCursor : public MxPtrListCursor<LegoEntityPresenter> {
public:
    LegoEntityPresenterListCursor(LegoEntityPresenterList* p_list) : MxPtrListCursor<LegoEntityPresenter>(p_list) {}
};


#endif // __LEGOENTITYPRESENTER_H

