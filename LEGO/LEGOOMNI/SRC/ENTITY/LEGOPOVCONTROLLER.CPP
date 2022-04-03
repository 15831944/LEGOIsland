/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoPOVController.h"
#include "TGL.h"
#include "Lego3DView.h"
#include "ViewManager.h" 
#include "vec.h"
#include "LEntity.h"
#include "LegoNavController.h"
#include "MxTickleManager.h"
#include "LegoOmni.h"

//////////////////////////////////////////////////////////////////////

LegoMouseController::LegoMouseController()
{
    m_isButtonDown  = 0;
}

LegoMouseController::~LegoMouseController()
{
}

void LegoMouseController::LeftDown(int x, int y)
{
    m_isButtonDown = 1;
    m_buttonX = x;
    m_buttonY = y;
}

void LegoMouseController::LeftUp(int x, int y)
{
    m_isButtonDown = 0;
    m_buttonX = x;
    m_buttonY = y;
}

void LegoMouseController::LeftDrag(int x, int y)
{
    m_buttonX = x;
    m_buttonY = y;
}

void LegoMouseController::RightDown(int x, int y)
{
    m_isButtonDown = 1;
    m_buttonX = x;
    m_buttonY = y;
}

void LegoMouseController::RightUp(int x, int y)
{
    m_isButtonDown = 0;
    m_buttonX = x;
    m_buttonY = y;
}

void LegoMouseController::RightDrag(int x, int y)
{
    m_buttonX = x;
    m_buttonY = y;
}


//////////////////////////////////////////////////////////////////////

LegoPointOfViewController::LegoPointOfViewController() 
{
	m_lego3DView = NULL; 
	m_entity = NULL; 
	m_nav = NULL;
	// m_entityOffsetUp is a temporary kludge.  It should be replaced
	// by 3D camera offset and position stored in the entity since each
	// entity may have a different best viewpoint.
	m_entityOffsetUp = 0.0;
}

MxResult
LegoPointOfViewController::Create(Lego3DView* p_lego3DView) 
{
	m_lego3DView = p_lego3DView;
	m_nav = new LegoNavController();
	m_nav->SetTrackDefaultParams(TRUE);
	LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 50);
	return SUCCESS;
}

void
LegoPointOfViewController::Destroy() 
{
	LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);
	if(m_nav)
		delete m_nav;
}

void LegoPointOfViewController::OnViewSize(int width, int height)
{
	m_nav->SetControlMax(width, height);
}

void LegoPointOfViewController::LeftDown(int x, int y)
{ 
    LegoMouseController::LeftDown(x, y); 
    AffectPointOfView(); 
}

void LegoPointOfViewController::LeftDrag(int x, int y)
{ 
    LegoMouseController::LeftDrag(x, y); 
    AffectPointOfView(); 
}

void LegoPointOfViewController::AffectPointOfView()
{
	m_nav->SetTargets(ButtonX(), ButtonY(), IsButtonDown());
	if (m_entity)
	{
		double new_speed = m_nav->CalculateNewSpeed(m_entity->GetWorldSpeed());
		m_entity->SetWorldSpeed(new_speed);
	}
}

MxResult
LegoPointOfViewController::Tickle()
{
	ViewROI* pPointOfView = m_lego3DView->GetPointOfView();

	if(pPointOfView && m_nav && !m_entity)
	{
		Vector3     new_dir, new_pos;

		const Vector3     cur_pos(pPointOfView->GetWorldPosition());
		const Vector3     cur_dir(pPointOfView->GetWorldDirection());

		if (m_nav->CalculateNewPosDir(cur_pos, cur_dir, new_pos, new_dir))
		{
			Matrix4 new_mat;

			CalcLocalTransform(new_pos, new_dir, pPointOfView->GetWorldUp(), new_mat);
			pPointOfView->SetLocalTransform(new_mat);
			m_lego3DView->Moved(*pPointOfView);
		}
	}
	return SUCCESS;
}



void LegoPointOfViewController::SetEntity(LegoEntity* p_entity)
{
	LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);
	m_entity = p_entity;
    ViewROI*    pointOfView = m_lego3DView->GetPointOfView();
	if(m_entity && pointOfView)
	{
		Matrix4 mat;
		CalcLocalTransform(	Vector3(m_entity->GetWorldLocation().GetX(),
									m_entity->GetWorldLocation().GetY() + m_entityOffsetUp,
									m_entity->GetWorldLocation().GetZ()),
							Vector3(m_entity->GetWorldDirection().GetX(),
									m_entity->GetWorldDirection().GetY(),
									m_entity->GetWorldDirection().GetZ()),
							Vector3(m_entity->GetWorldUp().GetX(),
									m_entity->GetWorldUp().GetY(),
									m_entity->GetWorldUp().GetZ()),
							mat
									);
		pointOfView->SetLocalTransform(mat);
	}
	else
		LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 50);
}
