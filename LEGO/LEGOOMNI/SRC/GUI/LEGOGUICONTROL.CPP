/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#include "StdLego.h"
#include "MxString.h"
#include "MxStreamer.h"
#include "MxVariableTable.h"
#include "LegoOmni.h"
#include "LegoGuiControl.h"
#include "LegoGui.h"
#include "LegoGuiCtrlPresenter.h"
#include "LegoNotify.h"

LegoGuiControl::LegoGuiControl()
{
	m_controlId = 0;
	m_objectName = NULL;
	m_sysVar = NULL;
	m_controlType = e_pushbutton;
	m_eventMask = 0;
	m_gui = 0;
	m_presenter = 0;
}

LegoGuiControl::~LegoGuiControl()
{
	if (m_presenter)
		delete m_presenter;
}

MxResult
LegoGuiControl::Create(
//	MxU32 p_controlId,
	MxCharString p_controlName,
	MxCharString p_objectName,
	MxCharString p_sysVar,
	MxU8 p_type,
	MxU8 p_eventMask,
	MxU8 p_keyLow,
	MxU8 p_keyHigh,
	LegoGuiPtr p_gui,
	MxU8Ptr p_data)
{
//	m_controlId = p_controlId;
	m_controlName = p_controlName;
	m_objectName = p_objectName;
	m_sysVar = p_sysVar;
	m_controlType = p_type;
	m_eventMask = p_eventMask;
	m_keyRangeLow = p_keyLow;
	m_keyRangeHigh = p_keyHigh;
	m_gui = p_gui;
	MxResult result = ParseControlData(p_data);
	if (result == SUCCESS)
		InitFromSystemVariable();

	return result;
}

void
LegoGuiControl::SendActionMessages(LegoGuiActionPtr p_action)
{
	LegoGuiMessagePtr message;
	LegoGuiMessageListCursor cursor (&(p_action->messageList));
	while (cursor.Next(message))
	{
		LegoGuiBase *target = m_gui->FindControl(message->GetTarget());
		if (target)
		{
			// build the message object
 			LegoMessageNotificationParam actionMessage(c_notificationCtrlMsg,
									this, message->GetType(), message->GetValue());

			// send message now
			target->Notify(actionMessage);
		}
	}
}


void
LegoGuiControl::StartActionSound(LegoGuiActionPtr p_action)
{
	//play omni sound
	if (p_action->soundActionIdx >= 0)
	{
		MxCharString name = m_gui->GetSoundActionName(p_action->soundActionIdx);
		if (name)
		{
			LegoOmni::GetInstance()->Start(m_gui->GetSourceId(), name, NULL);
		}
	}
}


MxS32
LegoGuiControl::Notify(MxParam& p_param)
{
	MxS32 result = FALSE;

	switch (((MxNotificationParam&) p_param).GetNotification())
	{
		case c_notificationCtrlMsg:
		{
			switch (((LegoMessageNotificationParam&)p_param).GetType())
			{
				case e_boolMsg:
					m_presenter->SetValue(
						((LegoMessageNotificationParam&)p_param).GetBoolValue());
					result = TRUE;
					break;
				case e_intMsg:
					m_presenter->SetValue(
						((LegoMessageNotificationParam&)p_param).GetIntValue());
					result = TRUE;
					break;
				case e_stringMsg:
					m_presenter->SetValue(
						((LegoMessageNotificationParam&)p_param).GetStringValue());
					result = TRUE;
					break;
				case e_sysVarMsg:
					// XXX temp we must get system variable
					// value and type to set this control's
					// new state!!!
					result = TRUE;
					break;
				default:
					break;
			}
			break;
		}
		default:
			result = LegoGuiBase::Notify(p_param);
			break;
	}
	return result;
}



void
LegoGuiControl::GetActionLoc(LegoGuiActionPtr p_action, MxU8 p_idx, MxPoint32 *p_loc)
{
	p_loc->SetX(p_action->offsetArray[p_idx].x);
	p_loc->SetY(p_action->offsetArray[p_idx].y);
}

void
LegoGuiControl::GetGuiAction(LegoGuiActionPtr p_action, MxU8Ptr *p_data, MxResult *p_result)
{
	if (*p_result == SUCCESS && p_action)
	{
		p_action->looping = GetBool(p_data);
		p_action->frameTime = GetTime(p_data);
		p_action->numFrames = GetU8(p_data);
		p_action->offsetArray = (LegoGuiScreenCoordPtr)*p_data;
		*p_data += sizeof(LegoGuiScreenCoord) * p_action->numFrames;
		p_action->bitmapArray = (MxS16Ptr)*p_data;
		*p_data += sizeof(MxS16) * p_action->numFrames;
		p_action->soundActionIdx = GetS16(p_data);
		p_action->actionNameIdx = GetS16(p_data);
		p_action->bitmapNoBlt = GetBool(p_data);


		MxU8 numMsgs = GetU8(p_data);
		while (numMsgs--)
		{
			LegoGuiMessagePtr message = new LegoGuiMessage;
			MxCharString target = GetString(p_data);
			message->SetTarget(target);
			LegoGuiMessageType type = (LegoGuiMessageType)GetU8(p_data);
			message->SetType(type);
			switch (type)
			{
				case e_boolMsg:
					message->SetValue(GetBool(p_data));
					break;
				case e_intMsg:
					message->SetValue(GetS32(p_data));
					break;
				case e_stringMsg:
				case e_sysVarMsg:
					MxCharString msg = GetString(p_data);
					message->SetValue(msg);
					m_gui->CheckForExitMessage(target, msg);
					break;
			}
			p_action->messageList.Append(message);
		}
	}
}

void
LegoGuiControl::SetValue(MxBool p_value)
{
	m_presenter->SetValue(p_value);
}
void
LegoGuiControl::SetValue(MxS32 p_value)
{
	m_presenter->SetValue(p_value);
}
void
LegoGuiControl::SetValue(MxCharString p_value)
{
	m_presenter->SetValue(p_value);
}

void
LegoGuiControl::SetSystemVariable(MxCharString p_value)
{
	if (m_sysVar)
		LegoOmni::GetInstance()->GetVariableTable()->SetVariable(m_sysVar, p_value);
}

void
LegoGuiControl::Activate()
{
	if (LegoOmni::GetInstance()->GetVideoManager())
		LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(m_presenter);
}

void
LegoGuiControl::DeActivate()
{
	if (LegoOmni::GetInstance()->GetVideoManager())
		LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(m_presenter);
}

MxResult
LegoGuiSlider::ParseControlData(MxU8Ptr p_data)
{
	MxResult result = SUCCESS;
	m_minValue = GetS32(&p_data);
	m_maxValue = GetS32(&p_data);
	m_horizontal = GetBool(&p_data);
	m_rect.left = GetS16(&p_data);
	m_rect.top = GetS16(&p_data);
	m_rect.right = GetS16(&p_data);
	m_rect.bottom = GetS16(&p_data);
	m_numFrames = GetU8(&p_data);
	m_offsetArray = (LegoGuiScreenCoordPtr)*p_data;
	*p_data += sizeof(LegoGuiScreenCoord) * m_numFrames;
	m_bitmapArray = (MxS16Ptr)*p_data;
	*p_data += sizeof(MxS16) * m_numFrames;
	m_pickAreaArray = (LegoGuiRectPtr)*p_data;
	*p_data += sizeof(LegoGuiRect) * m_numFrames;
	m_flcIndex = GetS16(&p_data);
	m_actionName = GetString(&p_data);
	return result;
}

