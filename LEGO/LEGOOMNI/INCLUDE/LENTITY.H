/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LENTITY_H
#define __LENTITY_H

#include "MxEntity.h"
#include "MxGeometry3D.h"
#include "LegoROI.h"

const MxDouble c_entitySpeedIncrement = 0.05;

class LegoWorld;
class LegoSpacePresenter;

class LegoEntity : public MxEntity
{
protected:
	LegoWorld*	m_world;
	LegoSpacePresenter* m_spacePresenter;
	MxU32		m_stateFlags;
	Mx3DPointDouble	m_worldLocation;
	Mx3DPointDouble	m_worldDirection;
	Mx3DPointDouble	m_worldUp;
	MxDouble	m_worldSpeed; // velocity = m_worldDirection*m_worldSpeed
    LegoROI* m_roi;
	MxBool m_cameraFlag;

	void Destroy(MxBool p_fromDestructor);
	void Init();

public:
	LegoEntity();
	virtual ~LegoEntity();
    virtual MxResult Create(const MxChar* p_name, LegoWorld* p_world);
    virtual void Destroy();
    virtual const MxChar* ClassName() { return "LegoEntity"; }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoEntity::ClassName())) || (MxEntity::IsA(p_str)) ; }

	virtual void SetPresenter(LegoSpacePresenter* p_presenter) { m_spacePresenter = p_presenter;}
	virtual LegoSpacePresenter* GetPresenter() { return m_spacePresenter;}


	void SetWorld(LegoWorld* p_world);
	LegoWorld* GetWorld() {return m_world;}
	
	void SetStateFlags(MxU32 p_val) {m_stateFlags = p_val;}
	MxU32 GetStateFlags() {return m_stateFlags;}	

	void SetROI(LegoROI* p_roi);
	LegoROI* GetROI() {return m_roi;}

	void SetCameraFlag(MxBool p_flag);
	MxBool GetCameraFlag() {return m_cameraFlag;}

	void SetWorldTransform(const Mx3DPointDouble & p_location,const Mx3DPointDouble & p_direction,const Mx3DPointDouble & p_up, MxBool p_setCamera=TRUE);
	Mx3DPointDouble GetWorldLocation();
	Mx3DPointDouble GetWorldDirection();
	Mx3DPointDouble GetWorldUp();

	Mx3DPointDouble GetWorldVelocity();

	void SetWorldSpeed(MxDouble p_speed);
	MxDouble GetWorldSpeed();
};

class LegoEntityList : public MxPtrList<LegoEntity> {
protected:
    virtual MxS8 Compare(LegoEntity* p_entity1, LegoEntity* p_entity2) 
			{ return p_entity1 == p_entity2 ? 0 : p_entity1 < p_entity2 ? -1 : 1; }
public:
    LegoEntityList(MxBool p_ownership = FALSE) : MxPtrList<LegoEntity>(p_ownership) {}
    static void Destroy(LegoEntity* p_entity) { delete p_entity; }
};

class LegoEntityListCursor : public MxPtrListCursor<LegoEntity> {
public:
    LegoEntityListCursor(LegoEntityList* p_list) : MxPtrListCursor<LegoEntity>(p_list) {}
};

#endif // __LENTITY_H