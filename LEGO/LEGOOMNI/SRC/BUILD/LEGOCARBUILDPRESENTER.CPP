/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"
#include "LegoBuild.h"
#include "LegoCarBuildPresenter.h"


//---------------------------------------------------------------------------

void LegoCarBuildPresenter::ReadyTickle()
{
	if(m_entity)
		delete m_entity;
	m_entity = new LegoCarBuild();
	if(m_entity)
	{
		((LegoCarBuild*)m_entity)->Create(m_action->GetObjectName());
		LegoOmni::GetInstance()->AddWorld((LegoCarBuild*)m_entity);
		((LegoCarBuild*)m_entity)->ProcessPresenterTree(this);
		
		// Get scripted location, direction and up vectors.
		SetWorldTransform(m_action->GetLocation(), m_action->GetDirection(), m_action->GetUp());
	}

	m_state = e_starting;
}
