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
#include "LegoWorldPresenter.h"
#include "LWorld.h"
#include "LegoVideoManager.h"
#include "LegoNotify.h"

LegoWorldPresenter::LegoWorldPresenter()
{
}

LegoWorldPresenter::~LegoWorldPresenter()
{
}

void 
LegoWorldPresenter::ReadyTickle()
{
	if(m_entity)
		delete m_entity;
	m_entity = NULL;
	m_entity = new LegoWorld();
	if(m_entity)
	{
		((LegoWorld*)m_entity)->Create(m_action->GetObjectName());
		LegoOmni::GetInstance()->AddWorld((LegoWorld*)m_entity);
		((LegoWorld*)m_entity)->ProcessPresenterTree(this);
		
		// Get scripted location, direction and up vectors.
		SetWorldTransform(m_action->GetLocation(), m_action->GetDirection(), m_action->GetUp());
	}
	m_state = e_starting;
}

