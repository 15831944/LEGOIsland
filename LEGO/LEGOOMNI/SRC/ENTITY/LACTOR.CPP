/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxTickleManager.h"
#include "LegoOmni.h"
#include "LActor.h"
#include "LWorld.h"
#include "LegoActorPresenter.h"
#include "PathCtrl.h"

// ----------------------------------------------------------------
// LegoActor Class

LegoActor::LegoActor()
{
	m_stateFlags = 0;
	m_proximityCount = 0;
}

LegoActor::~LegoActor()
{
	Destroy(TRUE);
}

MxResult 
LegoActor::Create(const MxChar* p_name, LegoWorld* p_world)
{
	MxResult result = FAILURE;
	
    if (!LegoOmni::GetInstance()->GetTickleManager()) {
        goto done;
    }
    if (LegoEntity::Create(p_name, p_world) != SUCCESS) {
        goto done;
    }
	if( NULL == (m_spacePresenter = new LegoSpacePresenter())) {
		goto done;
	}
	if(m_spacePresenter->Create(this) != SUCCESS) {
		goto done;
	}

	LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 100);

	result = SUCCESS;

done:
	if(result != SUCCESS)
	{
		delete m_spacePresenter;
		m_spacePresenter = NULL;
	}
	return result;
}

void LegoActor::Destroy(MxBool p_fromDestructor)
{
	if (LegoOmni::GetInstance()->GetTickleManager()) {
	    LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);
    }
	if(!p_fromDestructor)
		LegoEntity::Destroy();
}

void LegoActor::Destroy()
{
	Destroy(FALSE);
}

MxResult LegoActor::Tickle()
{
	// Update state variables
	if(m_stateFlags & ACTOR_PROXIMITY_EVENT_FLAG)
	{
		if(m_proximityCount++ > 2)
		{
			m_stateFlags &= ~ACTOR_PROXIMITY_EVENT_FLAG;
			m_proximityCount = 0;
		}
	}
    if(GetWorldSpeed())
	    ((LegoSpacePresenter*)m_spacePresenter)->Move();

	return SUCCESS;
}

void LegoActor::OnActorProximityEvent(LegoActor* p_otherActor)
{
	// Just set the collision event state flag
	m_stateFlags |= ACTOR_PROXIMITY_EVENT_FLAG;
	m_proximityCount = 0;
}

void LegoActor::OnNodeProximityEvent(MxS32 p_nodeId)
{
	// Just set the collision event state flag
	m_stateFlags |= NODE_PROXIMITY_EVENT_FLAG;
}
