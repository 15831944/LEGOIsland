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
#include "LegoActorPresenter.h"
#include "LActor.h"
#include "LWorld.h"
#include "LegoROI.h"
#include "LegoVideoManager.h"
#include "LegoNotify.h"
#include "LegoModelPresenter.h"
//#include "PathStruc.h"
//#include "PathCtrl.h"
#include "LegoSpacePresenter.h"
#include "LegoAnimPresenter.h"

LegoActorPresenter::LegoActorPresenter()
{
}

LegoActorPresenter::~LegoActorPresenter()
{
}

void 
LegoActorPresenter::ReadyTickle()
{
	if(m_world) // wait for this to be set (in m_world's Notify())
	{
		if(m_entity)
			delete m_entity;
		m_entity = NULL;
		m_entity = new LegoActor();
		if(m_entity)
		{
			m_entity->Create(m_action->GetObjectName(), m_world);
			
			// Get scripted location, direction and up vectors.
			SetWorldTransform(m_action->GetLocation(), m_action->GetDirection(),m_action->GetUp());

			// kludge: mark one actor as the camera-carrier
			if(!strcmp("TestActor1",m_entity->GetEntityName()))
			{	// Attach camera to actor
				m_entity->SetCameraFlag(TRUE);
				SetWorldSpeed(0); // stop any auto movement
			}

            // kludge 2: start a walk cycle
            LegoOmni::GetInstance()->Start("D:\\Lego\\Media\\walk", "StartUp", this);

		}
		m_state = e_starting;
	}
}

MxResult 
LegoActorPresenter::Tickle()
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

MxS32 
LegoActorPresenter::Notify(MxParam& p_param)
{
	switch (((MxNotificationParam&) p_param).GetNotification()) {
	case c_notificationNewPresenter:
	    {
		    MxCompositePresenter* compositePresenter = (MxCompositePresenter*) (LegoAnimPresenter*)((MxNewPresenterNotificationParam&) p_param).GetPresenter();
            MxPresenterList* presenterList = compositePresenter->GetPresenterList();
            MxPresenterListCursor cursor(presenterList);
            MxPresenter* presenter;
            cursor.Head(presenter);
		    ((LegoAnimPresenter*) presenter)->SetEntity(m_entity);
	    }
	    break;
	}
	return SUCCESS;
}
