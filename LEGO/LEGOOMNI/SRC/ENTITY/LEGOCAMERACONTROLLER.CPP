/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxNotificationManager.h"
#include "LegoOmni.h"
#include "LegoROI.h"
#include "LegoVideoManager.h"
#include "Lego3DManager.h"
#include "LegoNotify.h"
#include "LegoInputManager.h"
#include "Lego3DView.h"
#include "LegoCameraController.h"

LegoCameraController::LegoCameraController()
{
	Init();
}

void LegoCameraController::Init()
{
}

LegoCameraController::~LegoCameraController()
{
	Destroy(TRUE);
}

MxResult
LegoCameraController::Create()
{
    MxResult result = FAILURE;
    if (!LegoOmni::GetInstance()->GetInputManager()) {
        goto done;
    }
    if(!LegoOmni::GetInstance()->GetVideoManager()) {
		goto done;
	}
	if(!((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()) {
		goto done;
	}
	if(!((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->GetLego3DView()) {
		goto done;
	}

	LegoOmni::GetInstance()->GetInputManager()->BeginCaptureMouse(this);
	LegoPointOfViewController::Create(((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->GetLego3DView());

	result = SUCCESS;

done:
    return result;
}

void
LegoCameraController::Destroy(MxBool p_fromDestructor)
{
	if(LegoOmni::GetInstance()->GetInputManager()) {
	    if(LegoOmni::GetInstance()->GetInputManager()->GetMouseCapture() == this)
			LegoOmni::GetInstance()->GetInputManager()->EndCaptureMouse();
	}
	Init();
    if (!p_fromDestructor) {
    }
	LegoPointOfViewController::Destroy();
}

void
LegoCameraController::Destroy()
{
	Destroy(FALSE);
}

MxResult
LegoCameraController::Notify(MxParam& p_param)
{
	switch (((MxNotificationParam&) p_param).GetNotification()) {
		// mouse input events
		case c_notificationDragEnd:
		{
			if(LegoEventNotificationParam::c_lButtonState != ((LegoEventNotificationParam&) p_param).GetModifier())
				OnLButtonUp(MxPoint32(((LegoEventNotificationParam&) p_param).GetX(),
									  ((LegoEventNotificationParam&) p_param).GetY()));
			else if(LegoEventNotificationParam::c_rButtonState != ((LegoEventNotificationParam&) p_param).GetModifier())
				OnRButtonUp(MxPoint32(((LegoEventNotificationParam&) p_param).GetX(),
									  ((LegoEventNotificationParam&) p_param).GetY()));
		}
		break;
		case c_notificationDragStart:
		{
			if(LegoEventNotificationParam::c_lButtonState == ((LegoEventNotificationParam&) p_param).GetModifier())
				OnLButtonDown(MxPoint32(((LegoEventNotificationParam&) p_param).GetX(),
									    ((LegoEventNotificationParam&) p_param).GetY()));
			else if(LegoEventNotificationParam::c_rButtonState == ((LegoEventNotificationParam&) p_param).GetModifier())
				OnRButtonDown(MxPoint32(((LegoEventNotificationParam&) p_param).GetX(),
									    ((LegoEventNotificationParam&) p_param).GetY()));
		}
		break;
		case c_notificationDrag:
		{
				OnMouseMove(((LegoEventNotificationParam&) p_param).GetModifier(),
							MxPoint32(((LegoEventNotificationParam&) p_param).GetX(),
									  ((LegoEventNotificationParam&) p_param).GetY()));
		}
		break;
	}
	return SUCCESS;
}

void
LegoCameraController::OnLButtonDown(MxPoint32 p_point)
{
    LeftDown(p_point.GetX(), p_point.GetY());
}

void
LegoCameraController::OnLButtonUp(MxPoint32 p_point)
{
    LeftUp(p_point.GetX(), p_point.GetY());
}

void
LegoCameraController::OnRButtonDown(MxPoint32 p_point)
{
    RightDown(p_point.GetX(), p_point.GetY());
}

void
LegoCameraController::OnRButtonUp(MxPoint32 p_point)
{
   RightUp(p_point.GetX(), p_point.GetY());
}

void
LegoCameraController::OnMouseMove(MxU8 p_modifier, MxPoint32 p_point) 
{
    if(LegoEventNotificationParam::c_lButtonState == p_modifier)
		LeftDrag(p_point.GetX(), p_point.GetY());
    else if(LegoEventNotificationParam::c_rButtonState == p_modifier)
		RightDrag(p_point.GetX(), p_point.GetY());
}


void
LegoCameraController::SetWorldTransform(const Mx3DPointDouble & p_location, const Mx3DPointDouble & p_direction, const Mx3DPointDouble & p_up)
{
	if(m_lego3DView)
	{
		ViewROI* pPointOfView = m_lego3DView->GetPointOfView();

		if(pPointOfView)
		{
			::Vector3 position(p_location.GetX(), p_location.GetY()+m_entityOffsetUp, p_location.GetZ());
			::Vector3 direction(p_direction.GetX(), p_direction.GetY(), p_direction.GetZ());
			::Vector3 up(p_up.GetX(), p_up.GetY(), p_up.GetZ());
			::Matrix4 mat;

			CalcLocalTransform(	position, direction, up, mat);
			pPointOfView->SetLocalTransform(mat);
			m_lego3DView->Moved(*pPointOfView);

		}
	}
}

Mx3DPointDouble
LegoCameraController::GetWorldUp()
{
	if(m_lego3DView && m_lego3DView->GetPointOfView())
	{
		::Vector3 up = m_lego3DView->GetPointOfView()->GetWorldUp();
		return(Mx3DPointDouble(up[0],up[1],up[2]));
	}
	else
		return (Mx3DPointDouble(0,0,0));
}

Mx3DPointDouble
LegoCameraController::GetWorldLocation()
{
	if(m_lego3DView && m_lego3DView->GetPointOfView())
	{
		::Vector3 position = m_lego3DView->GetPointOfView()->GetWorldPosition();
		return(Mx3DPointDouble(position[0],position[1]-m_entityOffsetUp,position[2]));
	}
	else
		return(Mx3DPointDouble(0,0,0));
}

Mx3DPointDouble
LegoCameraController::GetWorldDirection()
{
	if(m_lego3DView && m_lego3DView->GetPointOfView())
	{
		::Vector3 direction = m_lego3DView->GetPointOfView()->GetWorldDirection();
		return(Mx3DPointDouble(direction[0],direction[1],direction[2]));
	}
	else
		return (Mx3DPointDouble(0,0,0));
}

