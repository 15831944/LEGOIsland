/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxTickleManager.h"
#include "LegoInputManager.h"
#include "LegoOmni.h"
#include "LegoBuild.h"


//---------------------------------------------------------------------------

void RotateArowndY(Mx3DPointDouble &p_point, MxDouble p_angle)
{
    MxDouble rot_mat[3][3];
	Vector3 curDir(p_point.GetX(), p_point.GetY(), p_point.GetZ()),
            newDir;

	IDENTMAT3(rot_mat);
	rot_mat[0][0] = rot_mat[2][2] = cos(p_angle);
	rot_mat[0][2] = rot_mat[2][0] = sin(p_angle);
	rot_mat[0][2] *= -1.0f;
	VXM3(newDir, curDir, rot_mat);
    p_point.SetX(newDir.elements[0]);
    p_point.SetY(newDir.elements[1]);
    p_point.SetZ(newDir.elements[2]);
}

void ChangeLocationAtXY(Mx3DPointDouble &p_point, MxS32 p_x, MxS32 p_y)
{
}


//===========================================================================
// LegoBuild Class

//---------------------------------------------------------------------------

LegoBuild::LegoBuild()
{
}


//---------------------------------------------------------------------------

LegoBuild::~LegoBuild()
{
	Destroy(TRUE);
}


//---------------------------------------------------------------------------

MxResult LegoBuild::Create(const MxChar* p_name)
{
	MxResult result = LegoWorld::Create(p_name);
    if(result != SUCCESS)
        return result;

	return SUCCESS;
}

//---------------------------------------------------------------------------


void LegoBuild::Destroy(MxBool p_fromDestructor)
{
    if(!p_fromDestructor)
		LegoWorld::Destroy();
}


//---------------------------------------------------------------------------

void LegoBuild::Destroy()
{
	Destroy(FALSE);
}


//===========================================================================
// LegoCarBuild Class

//---------------------------------------------------------------------------

LegoCarBuild::LegoCarBuild()
{
    m_selectedPart = NULL;
    m_state = e_idle;
}


//---------------------------------------------------------------------------

LegoCarBuild::~LegoCarBuild()
{
	Destroy(TRUE);
}


//---------------------------------------------------------------------------

MxResult LegoCarBuild::Create(const MxChar* p_name)
{
	MxResult result = LegoBuild::Create(p_name);
    if(result != SUCCESS)
        return result;

    assert(LegoOmni::GetInstance()->GetTickleManager());
    assert(LegoOmni::GetInstance()->GetInputManager());
    
    LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 50);
    LegoOmni::GetInstance()->GetInputManager()->BeginCaptureMouseRaw(this);

    m_state = e_select;

    return SUCCESS;
}


//---------------------------------------------------------------------------


void LegoCarBuild::Destroy(MxBool p_fromDestructor)
{
	m_selectedPart = NULL;
    m_state = e_idle;

    assert(LegoOmni::GetInstance()->GetTickleManager());
    LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);

    assert(LegoOmni::GetInstance()->GetInputManager());
    LegoOmni::GetInstance()->GetInputManager()->EndCaptureMouseRaw();

    if(!p_fromDestructor)
		LegoBuild::Destroy();
}


//---------------------------------------------------------------------------

void LegoCarBuild::Destroy()
{
	Destroy(FALSE);
}


//---------------------------------------------------------------------------

void LegoCarBuild::SelectPart()
{
    // For testing just peek up first element and rotate it
    if(m_entityList->GetNumElements())
    {
        LegoEntityListCursor cursor(m_entityList);
        cursor.Head(m_selectedPart);
        m_state = e_repeat;
    }
}


//---------------------------------------------------------------------------

void LegoCarBuild::RotateSelectedPart()
{
    if(m_selectedPart)
    {
	    Mx3DPointDouble location = m_selectedPart->GetWorldLocation();
	    Mx3DPointDouble direction = m_selectedPart->GetWorldDirection();
	    Mx3DPointDouble up = m_selectedPart->GetWorldUp();
        RotateArowndY(direction, 0.03);
        m_selectedPart->SetWorldTransform(location, direction, up);
    }
}


void LegoCarBuild::DragSelectedPart(MxS32 p_x, MxS32 p_y)
{
    if(m_selectedPart)
    {
	    Mx3DPointDouble location = m_selectedPart->GetWorldLocation();
	    Mx3DPointDouble direction = m_selectedPart->GetWorldDirection();
	    Mx3DPointDouble up = m_selectedPart->GetWorldUp();
        ChangeLocationAtXY(location, p_x, p_y);
        m_selectedPart->SetWorldTransform(location, direction, up);
    }
}


//---------------------------------------------------------------------------

MxResult LegoCarBuild::Tickle()
{
    switch(m_state)
    {
        case e_idle:
        case e_select:
            break;

        case e_repeat:
            RotateSelectedPart();
            break;
    }
    return SUCCESS;
}


//---------------------------------------------------------------------------

MxS32 LegoCarBuild::Notify(MxParam &p_event)
{
    LegoEventNotificationParam* event = (LegoEventNotificationParam*)&p_event;

    // Check object and select to rotate
    switch(event->GetNotification())
    {
        case c_notificationButtonDown:
            SelectPart();
            break;

        case c_notificationButtonUp:
            UnselectPart();
            break;

        case c_notificationMouseMove:
            DragSelectedPart(event->GetX(), event->GetY());
            break;
    }

    return TRUE; // do not give up!
}
