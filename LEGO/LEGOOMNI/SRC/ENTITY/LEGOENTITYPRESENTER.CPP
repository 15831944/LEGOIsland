/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxNotificationManager.h"
#include "MxDSAction.h"
#include "LegoOmni.h"
#include "LegoEntityPresenter.h"
#include "LEntity.h"
#include "LegoVideoManager.h"
#include "LegoNotify.h"

LegoEntityPresenter::LegoEntityPresenter()
{
	Init();
}

void LegoEntityPresenter::Init()
{
	m_entity = NULL;
	m_world = NULL;
}

LegoEntityPresenter::~LegoEntityPresenter()
{
	Destroy(TRUE);
}

MxResult
LegoEntityPresenter::Create(LegoEntity *p_entity)
{
    MxResult result = FAILURE;
    if (MxCompositePresenter::Create() != SUCCESS) {
        goto done;
    }
    
	SetEntity(p_entity);

	result = SUCCESS;

done:
    return result;
}

void
LegoEntityPresenter::Destroy(MxBool p_fromDestructor)
{
	if (LegoOmni::GetInstance()->GetVideoManager()) {
	    LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(this);
    }
	Init();
    if (!p_fromDestructor) {
        MxCompositePresenter::Destroy();
    }
}

void
LegoEntityPresenter::Destroy()
{
	Destroy(FALSE);
}

MxResult 
LegoEntityPresenter::StartAction(MxStreamController* p_controller, MxDSAction* p_action)
{
    MxResult result = FAILURE;

	result = MxCompositePresenter::StartAction(p_controller,p_action);

    if (!LegoOmni::GetInstance()->GetVideoManager()) {
        goto done;
    }
	LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(this);

done:
	return result;
}

void
LegoEntityPresenter::EndAction()
{
//	if (LegoOmni::GetInstance()->GetVideoManager()) {
//	    LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(this);
//    }
    MxCompositePresenter::EndAction();
}

/**
MxResult
LegoEntityPresenter::Notify(MxParam& p_param)
{
	switch (((MxNotificationParam&) p_param).GetNotification()) {
		case c_notificationEndAction:
		// subpresenter end-action notification
		{
			MxPresenter *presenter;
			presenter = (MxPresenter*)((MxEndActionNotificationParam&) p_param).GetSender();
			if(presenter)
			{
				MxPresenterListCursor cursor(m_presenterList);
				if(cursor.Find(presenter))
					cursor.Detach();
				delete presenter;
			}
			delete ((MxEndActionNotificationParam&) p_param).GetAction();
		}
		break;
	}
	return SUCCESS;
}
**/
void 
LegoEntityPresenter::ReadyTickle()
{
	if(m_world) // wait for this to be set (in m_world's Notify())
	{
		if(m_entity)
			delete m_entity;
		m_entity = NULL;
		m_entity = new LegoEntity();
		if(m_entity)
		{
			m_entity->Create(m_action->GetObjectName(), m_world);
			
			// Get scripted location, direction and up vectors.
			m_entity->SetWorldTransform(m_action->GetLocation(),m_action->GetDirection(),m_action->GetUp());
		}
		m_state = e_starting;
	}
}

void 
LegoEntityPresenter::StartingTickle()
{
	m_state = e_streaming;
}

void 
LegoEntityPresenter::StreamingTickle()
{
    m_state = e_repeating;
}

void 
LegoEntityPresenter::RepeatingTickle()
{
	if (m_presenterList->GetNumElements() == 0) {
		EndAction();
	}
}

MxResult 
LegoEntityPresenter::Tickle()
{
	    AUTOLOCK(m_criticalSection);

		switch (m_state) {
		case e_ready:
			ReadyTickle();
			if (m_state != e_starting) {
				break;
			}
			// fall through
		case e_starting:
			StartingTickle();
			if (m_state != e_streaming) {
				break;
			}
			// fall through
		case e_streaming:
			StreamingTickle();
			if (m_state != e_repeating) {
				break;
			}
			// fall through
		case e_repeating:
			RepeatingTickle();
			break;
		}
    return SUCCESS;
}

MxResult
LegoEntityPresenter::PutData()
{
//    AUTOLOCK(m_criticalSection);

    return SUCCESS;
}

void LegoEntityPresenter::SetWorldTransform(const Mx3DPointDouble & p_location,const Mx3DPointDouble & p_direction, const Mx3DPointDouble & p_up)
{
	if(m_entity)
		m_entity->SetWorldTransform(p_location, p_direction, p_up);
}

Mx3DPointDouble LegoEntityPresenter::GetWorldLocation()
{
	if(m_entity)
		return m_entity->GetWorldLocation();
	else
		return Mx3DPointDouble(0,0,0);
}

Mx3DPointDouble LegoEntityPresenter::GetWorldDirection()
{
	if(m_entity)
		return m_entity->GetWorldDirection();
	else
		return Mx3DPointDouble(1,0,0);
}

Mx3DPointDouble LegoEntityPresenter::GetWorldUp()
{
	if(m_entity)
		return m_entity->GetWorldUp();
	else
		return Mx3DPointDouble(0,1,0);
}

Mx3DPointDouble LegoEntityPresenter::GetWorldVelocity()
{
	if(m_entity)
		return m_entity->GetWorldVelocity();
	else
		return Mx3DPointDouble(0,0,0);
}
void 
LegoEntityPresenter::SetWorldSpeed(MxDouble p_speed)
{
	if(m_entity)
		m_entity->SetWorldSpeed(p_speed);
}

MxDouble 
LegoEntityPresenter::GetWorldSpeed()
{
	if(m_entity)
		return m_entity->GetWorldSpeed();
	else
		return 0;
}


