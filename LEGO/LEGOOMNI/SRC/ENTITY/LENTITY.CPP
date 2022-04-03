/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"

#include "LEntity.h"
#include "LegoVideoManager.h"
#include "Lego3DManager.h"
#include "LWorld.h"
#include "LegoCameraController.h"
#include "LegoEntityPresenter.h"
#include "LegoSpacePresenter.h"
#include "PathStruc.h"

// ----------------------------------------------------------------
// LegoEntity Class
LegoEntity::LegoEntity()
{
	Init();
}

LegoEntity::~LegoEntity()
{
	Destroy(TRUE);
}

void
LegoEntity::Init()
{
	m_world = NULL;
	m_spacePresenter = NULL;
	m_worldLocation.Fill(0);
	m_worldDirection.Fill(0);
	m_worldSpeed = 0;
	m_roi = NULL;
	m_cameraFlag = FALSE;
}

void LegoEntity::SetCameraFlag(MxBool p_flag)
{
	if(m_world && m_world->GetCameraController())
	{
		m_cameraFlag = p_flag;
		if(m_cameraFlag) 
		{   // attach this to camera controller
			if(m_spacePresenter)
				m_spacePresenter->SetPathTravelerType(PATH_PRIVILEGE_USER | m_spacePresenter->GetPathTravelerType());
			m_world->GetCameraController()->SetEntity(this);
		}
		else if(m_world->GetCameraController()->GetEntity() == this) 
		{
			if(m_spacePresenter)
				m_spacePresenter->SetPathTravelerType(~PATH_PRIVILEGE_USER & m_spacePresenter->GetPathTravelerType());
			m_world->GetCameraController()->SetEntity(NULL);
		}
	}
}

MxResult
LegoEntity::Create(const MxChar* p_name, LegoWorld* p_world)
{
	MxResult result = FAILURE;

	result = MxEntity::Create(p_name);
	SetWorld(p_world);

    return result;
}

void
LegoEntity::Destroy(MxBool p_fromDestructor)
{
	delete m_spacePresenter;
	if(m_roi) {
		((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->Remove(*m_roi);
		delete m_roi;
	}
	Init();
	if(!p_fromDestructor)
		MxEntity::Destroy();
}

void
LegoEntity::Destroy()
{
	Destroy(FALSE);
}

void 
LegoEntity::SetWorld(LegoWorld* p_world)
{
    m_world = p_world;
    
    // Do not include itself in the entity list
    if(p_world && (p_world != this))
        p_world->AddEntity(this);
}

void LegoEntity::SetROI(LegoROI* p_roi)
{
	m_roi = p_roi;
	if(m_roi)
	{
		Matrix4 mat;
		CalcLocalTransform(	Vector3(m_worldLocation.GetX(),m_worldLocation.GetY(),m_worldLocation.GetZ()),
							Vector3(m_worldDirection.GetX(),m_worldDirection.GetY(),m_worldDirection.GetZ()),
							Vector3(m_worldUp.GetX(),m_worldUp.GetY(),m_worldUp.GetZ()),
							mat);
		m_roi->SetLocalTransform(mat);

	    ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->Moved(*m_roi);
	}
}


void 
LegoEntity::SetWorldTransform(const Mx3DPointDouble & p_location,const Mx3DPointDouble & p_direction,const Mx3DPointDouble & p_up, MxBool p_setCamera)
{
	Mx3DPointDouble d = p_direction;
	d.Normalize();
	Mx3DPointDouble u = p_up;
	u.Normalize();

	m_worldLocation = p_location;
	m_worldDirection = d;
	m_worldUp = u;

	if(m_roi)
	{
		Matrix4 mat;
		CalcLocalTransform(	Vector3(p_location.GetX(), p_location.GetY(), p_location.GetZ()),
							Vector3(d.GetX(), d.GetY(), d.GetZ()),
							Vector3(u.GetX(), u.GetY(), u.GetZ()),
							mat);
		m_roi->SetLocalTransform(mat);
	    ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->Moved(*m_roi);
	}
	// Wouldn't have to do this if we just attached the camera directly to an entity roi.
	if(p_setCamera && GetCameraFlag() && m_world && m_world->GetCameraController()) {
		m_world->GetCameraController()->SetWorldTransform(p_location, d, u);
	}
}

Mx3DPointDouble
LegoEntity::GetWorldDirection()
{
	if(m_roi)
		m_worldDirection = Mx3DPointDouble(EXPAND3(m_roi->GetWorldDirection()));
	return m_worldDirection;
}

Mx3DPointDouble
LegoEntity::GetWorldUp()
{
	if(m_roi)
		m_worldUp = Mx3DPointDouble(EXPAND3(m_roi->GetWorldUp()));
	return m_worldUp;
}

Mx3DPointDouble
LegoEntity::GetWorldLocation()
{
	if(m_roi)
		m_worldLocation = Mx3DPointDouble(EXPAND3(m_roi->GetWorldPosition()));
	return m_worldLocation;
}

Mx3DPointDouble
LegoEntity::GetWorldVelocity()
{
	Mx3DPointDouble d = GetWorldDirection();
	d *= GetWorldSpeed();
	return d;
}

void 
LegoEntity::SetWorldSpeed(MxDouble p_speed)
{
	if(m_roi)
	{
		Mx3DPointDouble v = m_worldDirection;
		v.Normalize();
		v *= p_speed;

		::Vector3 v3(v.GetX(), v.GetY(), v.GetZ());
		#if CLEANUP
		m_roi->SetVelocity(v3);
		#endif
	    //((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->Moved(*m_roi);
	}
	m_worldSpeed = p_speed;
}

MxDouble 
LegoEntity::GetWorldSpeed()
{
	return m_worldSpeed;
}
