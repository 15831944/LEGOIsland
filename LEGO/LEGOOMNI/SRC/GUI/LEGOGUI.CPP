/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxPresenter.h"
#include "LegoOmni.h"
#include "LegoGui.h"
#include "LegoGuiControl.h"
#include "LegoGuiButton.h"
#include "LegoGuiString.h"
#include "LegoNotify.h"
#include "LegoInputManager.h"
#include "LegoVideoManager.h"

MxU8
LegoGuiBase::GetU8(MxU8Ptr *p_data)
{
	MxU8 var = *(MxU8 *)*p_data;
	*p_data += sizeof(MxU8);
	return var;
}
MxS8
LegoGuiBase::GetS8(MxU8Ptr *p_data)
{
	MxS8 var = *(MxS8 *)*p_data;
	*p_data += sizeof(MxS8);
	return var;
}
MxU16
LegoGuiBase::GetU16(MxU8Ptr *p_data)
{
	MxU16 var = *(MxU16 *)*p_data;
	*p_data += sizeof(MxU16);
	return var;
}
MxS16
LegoGuiBase::GetS16(MxU8Ptr *p_data)
{
	MxS16 var = *(MxS16 *)*p_data;
	*p_data += sizeof(MxS16);
	return var;
}
MxU32
LegoGuiBase::GetU32(MxU8Ptr *p_data)
{
	MxU32 var = *(MxU32 *)*p_data;
	*p_data += sizeof(MxU32);
	return var;
}
MxS32
LegoGuiBase::GetS32(MxU8Ptr *p_data)
{
	MxS32 var = *(MxS32 *)*p_data;
	*p_data += sizeof(MxS32);
	return var;
}
MxBool
LegoGuiBase::GetBool(MxU8Ptr *p_data)
{
	MxBool var = *(MxBool *)*p_data;
	*p_data += sizeof(MxBool);
	return var;
}
MxTime
LegoGuiBase::GetTime(MxU8Ptr *p_data)
{
	MxTime var = *(MxTime *)*p_data;
	*p_data += sizeof(MxTime);
	return var;
}
MxCharString
LegoGuiBase::GetString(MxU8Ptr *p_data)
{
	MxCharString var = (MxCharString)*p_data;
	*p_data += strlen(var) + 1;
	if (!strcmp(var, "NONE") || !*var)
		var = NULL;
	return var;
}

LegoGui *LegoGui::m_gui = 0;

LegoGui::LegoGui()
{
	m_numControls = 0;
	m_numBitmaps = 0;
	m_numSounds = 0;
	m_numNamedActions = 0;
	m_numFonts = 0;
	m_guiName = NULL;
	m_locXY.SetX(0);
	m_locXY.SetY(0);
	m_startUpDone = FALSE;
	m_shutDownDone = FALSE;
	m_backgroundBitmapIdx = 0;
	m_state = e_idle;
	m_bitmapPool = NULL;
	m_soundPool = NULL;
	m_namedActionPool = NULL;
	m_fontPool = NULL;
	m_startUp = NULL;
	m_shutDown = NULL;
	m_cameraName = NULL;
	m_chainAction = NULL;
	m_advanceState = FALSE;
	m_exitMessageFound = FALSE;
	m_nextDisplayZ = 0;
	m_baseDisplayZ = 0;

	m_timer = new MxTimer();

	// register for keyboard events
	LegoOmni::GetInstance()->GetInputManager()->Register(this);

	// remove any mouse capture
	LegoOmni::GetInstance()->GetInputManager()->EndCaptureMouseRaw();
}

LegoGui::~LegoGui()
{
	// shut off keyboard events
	LegoOmni::GetInstance()->GetInputManager()->UnRegister(this);

	if (m_bitmapPool)
		delete m_bitmapPool;
	if (m_soundPool)
		delete m_soundPool;
	if (m_namedActionPool)
		delete m_namedActionPool;
	if (m_fontPool)
		delete m_fontPool;
	if (m_timer)
	    delete m_timer;

}

void
LegoGui::ParseGuiData(MxU8Ptr p_data)
{
	MxResult result;

	MxU32 guiLen = GetU32(&p_data);

	// verify version of Gui data
	MxU8Ptr savePtr = p_data;
	MxCharString versionId = GetString(&p_data);
	MxCharString versionNum = GetString(&p_data);
	MxS32 versionMajor = 0;
	MxS32 versionMinor = 0;
	if (!versionId || strcmp(versionId, GUI_VERSION_ID) || !versionNum)
	{
		versionNum = GUI_OLD_VERSION;
		p_data = savePtr;
	}
	if (strcmp(versionNum, GUI_VERSION))
	{
		char str[100];
		sprintf(str, "Gui data version is %s,\nExpected version is %s.", versionNum, GUI_VERSION);
		::OmniUserMessage(str, e_msgAbortQuery);
	}
	versionMajor = atoi(versionNum);
	{
		MxCharString ptr;
		if ((ptr = strchr(versionNum, '.')) && *++ptr)
			versionMinor = atoi(ptr);
	}


	//MxCharString str = GetString(&p_data);
	//m_guiId = MakeGuiId(str);
	m_guiName = GetString(&p_data);
	m_cameraName = GetString(&p_data);

	// temp set an xy location (this will come from the camera)
	m_locXY.SetX(0);
	m_locXY.SetY(0);

	// create pointer arrays for image and sound data
	FillDataArrayIndexes(&m_numBitmaps, &m_bitmapPool, &p_data);
	FillStringArrayIndexes(&m_numSounds, &m_soundPool, &p_data);
	FillStringArrayIndexes(&m_numNamedActions, &m_namedActionPool, &p_data);
	FillDataArrayIndexes(&m_numFonts, &m_fontPool, &p_data);

	m_startUp = GetString(&p_data);
	m_shutDown = GetString(&p_data);
	m_chainAction = GetString(&p_data);

	m_backgroundBitmapIdx = GetS16(&p_data);

	// create controls and add to list
	m_numControls = GetU8(&p_data);
	for (int i=0; i<m_numControls; i++)
	{
		MxU32 controlLen = GetU32(&p_data);
		MxU8Ptr nextPtr = p_data + controlLen;
		MxCharString controlName = GetString(&p_data);
		MxU32 controlId = MakeControlId(controlName);
		MxCharString objectName = GetString(&p_data);
		MxU8 eventMask = GetU8(&p_data);
		MxU8 keyLow = GetU8(&p_data);
		MxU8 keyHigh = GetU8(&p_data);
		MxCharString sysVar = GetString(&p_data);
		MxU8 type = GetU8(&p_data);

		LegoGuiControl *control;

		switch(type)
		{
			case LegoGuiControl::e_pushbutton:
				control = new LegoGuiPushButton;
				break;
			case LegoGuiControl::e_toggle:
				control = new LegoGuiToggle;
				break;
			case LegoGuiControl::e_string:
				control = new LegoGuiString;
				break;
			default:
				control = 0;
				break;
		}
		if (control)
		{
			result = control->Create(
								//controlId,				// control name
								controlName,			// control name
								objectName,				// object name
								sysVar,					// system variable name
								type,					// type
								eventMask,				// event mask
								keyLow,
								keyHigh,
								this,					// parent gui
								p_data);				// type specific data

			if (result == SUCCESS)
			{
				m_controlList.Append(control);
			}
		}

		p_data = nextPtr;
	}

}

MxResult
LegoGui::FillDataArrayIndexes(MxS16Ptr p_num, MxU8Ptr **p_array, MxU8Ptr *p_data)
{
	MxResult result = SUCCESS;

	MxU32 PoolLen = GetU32(p_data);
	MxS16 num = GetS16(p_data);
	*p_num = num;
	if (num)
	{
		MxU8Ptr *array = new MxU8Ptr[num];
		*p_array = array;
		if (array)
		{
			for (int i=0; i<num; i++)
			{
				MxU32 Len = GetU32(p_data);
				array[i] = *p_data;
				*p_data += Len;
			}
		}
		else
			result = FAILURE;
	}
	else
		*p_array = NULL;

	return result;
}

MxResult
LegoGui::FillStringArrayIndexes(MxS16Ptr p_num, MxU8Ptr **p_array, MxU8Ptr *p_data)
{
	MxResult result = SUCCESS;

	MxU32 PoolLen = GetU32(p_data);
	MxS16 num = GetS16(p_data);
	*p_num = num;
	if (num)
	{
		MxU8Ptr *array = new MxU8Ptr[num];
		*p_array = array;
		if (array)
		{
			for (int i=0; i<num; i++)
				array[i] = (MxU8Ptr)GetString(p_data);
		}
		else
			result = FAILURE;
	}
	else
		*p_array = NULL;

	return result;
}


MxU32
LegoGui::MakeControlId(MxCharString p_str)
{
	static MxU32 id;

	return(id++);
}

MxU32
LegoGui::MakeGuiId(MxCharString p_str)
{
	static MxU32 id;

	return(id++);
}

void
LegoGui::DoStartUp()
{
	if (!m_startUp || (LegoOmni::GetInstance()->Start(m_sourceId, m_startUp, this) != SUCCESS))
		m_startUpDone = TRUE;
}

void
LegoGui::DoShutDown()
{
	if (!m_shutDown || (LegoOmni::GetInstance()->Start(m_sourceId, m_shutDown, this) != SUCCESS))
		m_shutDownDone = TRUE;
}


void
LegoGui::StartControls()
{
	m_gui = this;

	LegoGuiControlPtr control;
	LegoGuiControlListCursor cursor(&(m_controlList));
	while (cursor.Next(control))
	{
		control->Activate();
	}
	LegoOmni::GetInstance()->GetInputManager()->BeginCaptureMouseRaw(this);
}

void
LegoGui::EndControls()
{
	LegoOmni::GetInstance()->GetInputManager()->EndCaptureMouseRaw();
	LegoGuiControlPtr control;
	LegoGuiControlListCursor cursor(&(m_controlList));
	while (cursor.Next(control))
	{
		control->DeActivate();
		cursor.Detach();
		delete control;
	}

	m_gui = 0;
}

LegoGuiBase *
LegoGui::FindControl(MxCharString p_name)
{
	LegoGuiControlPtr control;
	LegoGuiControlListCursor cursor(&(m_controlList));
	while (cursor.Next(control))
	{
		if (!strcmp(control->GetControlName(), p_name))
			return control;
	}

	if (!strcmp(m_guiName, p_name))
		return this;
	return NULL;
}


MxResult
LegoGui::Tickle()
{
	switch (m_state)
	{
		case e_idle:
			DoStartUp();
			m_state = e_starting;
			break;
		case e_starting:
			if (m_startUpDone)
				m_state = e_waiting;
			break;
		case e_waiting:
			StartControls();
			m_state = e_active;
			break;
		case e_active:
			if (m_advanceState)
			{
				m_state = e_ending;
				m_advanceState = FALSE;
				EndControls();
				DoShutDown();
			}
			break;
		case e_ending:
			if (m_shutDownDone)
			{
				// start up chainAction
				if (m_chainAction)
					LegoOmni::GetInstance()->Start(m_sourceId, m_chainAction, NULL);
				m_state = e_complete;
			}
			break;
		case e_complete:
			break;
	}
	return SUCCESS;
}


MxS32
LegoGui::Notify(MxParam& p_param)
{
	MxS32 result = FALSE;

	switch (((MxNotificationParam&) p_param).GetNotification()) {
	case c_notificationBeginAction:
		break;
	case c_notificationEndAction:
	{
		MxEndActionNotificationParam& param = (MxEndActionNotificationParam&) p_param;
		MxPresenter* presenter = (MxPresenter*) param.GetSender();
		delete presenter;

		switch (m_state)
		{
			case e_starting:
				m_startUpDone = TRUE;
				break;
			case e_ending:
				m_shutDownDone = TRUE;
				break;
		}
		break;
	}
	case c_notificationButtonDown:
	{
		if (m_mouseCaptureControl)
			result = m_mouseCaptureControl->Notify(p_param);
		else
		{
			// check for event over a control
			LegoVideoManager *vman =
				(LegoVideoManager *)LegoOmni::GetInstance()->GetVideoManager();
			if (vman)
			{
				MxPresenter *control =
					vman->GetPresenterAt(((LegoEventNotificationParam&)p_param).GetX(),
										((LegoEventNotificationParam&)p_param).GetY());
				if (control)
					result = (MxBool)control->Notify(p_param); 
			}
		}
		if (!result && m_state == e_active && !m_exitMessageFound)
		{
			m_advanceState = TRUE;
			result = TRUE;
		}
		break;
	}
	case c_notificationButtonUp:
	case c_notificationMouseMove:
		if (m_mouseCaptureControl)
			result = m_mouseCaptureControl->Notify(p_param);
		break;
	case c_notificationKeyPress:
	{
		// Check all controls for a keymask value matching
		// this key (upper or lowercase)
		// A match means the control wants to be activated
		MxU8 key, lcKey;
		lcKey = key = ((LegoEventNotificationParam&)p_param).GetKey();
		if (isupper(key))
			lcKey = _tolower(key);
		LegoGuiControlPtr control;
		LegoGuiControlListCursor cursor(&(m_controlList));
		while (cursor.Next(control))
		{
			MxU8 rangeLow = control->GetKeyRangeLow();
			if (isupper(rangeLow))
				rangeLow = _tolower(rangeLow);
			MxU8 rangeHigh = control->GetKeyRangeHigh();
			if (isupper(rangeHigh))
				rangeHigh = _tolower(rangeHigh);
			if ((lcKey >= rangeLow) && (lcKey <= rangeHigh))
			{
				switch(control->GetType())
				{
					case LegoGuiControl::e_pushbutton:
						// activate pushbutton by setting state to TRUE
						control->SetValue((MxBool)TRUE);
						break;
					case LegoGuiControl::e_toggle:
						// activate toggle by toggling state
						control->SetValue((MxBool)!((LegoGuiToggle*)control)->GetState());
						break;
					case LegoGuiControl::e_string:
						// send key to string control
						control->SetValue((MxS32)key);
						break;
				}
				result = TRUE;
				break;
			}
		}
		break;
	}
	case c_notificationCtrlMsg:
	{
		switch (((LegoMessageNotificationParam&)p_param).GetType())
		{
			case LegoGuiControl::e_stringMsg:	// string message is the only valid type.
			{
				MxCharString str =
					((LegoMessageNotificationParam&)p_param).GetStringValue();
				if (!strcmp(str, EXIT_MESSAGE))
					m_advanceState = TRUE;
				result = TRUE;
				break;
			}
			default:
				break;
		}
		break;
	}
	default:
		result = MxCore::Notify(p_param);
		break;
	}
	return result;
}


BITMAPINFO*
LegoGui::GetBitmapInfo(MxS16 p_index)
{
	BITMAPINFO *info = NULL;

	if (m_bitmapPool)
	{
		MxU8Ptr fileData = m_bitmapPool[p_index];
		info = (BITMAPINFO*)(fileData + sizeof(BITMAPFILEHEADER));
	}
	return info;
}

MxU8*
LegoGui::GetBitmapImage(MxS16 p_index)
{
	MxU8Ptr image = NULL;

	if (m_bitmapPool)
	{
		MxU8Ptr fileData = m_bitmapPool[p_index];
		image = fileData + ((BITMAPFILEHEADER *)fileData)->bfOffBits;
	}
	return image;
}


MxS16
LegoGui::GetFontBitmapIndex(MxU8 p_ccode, MxU8 p_font )
{
	if (m_fontPool)
	{
		MxU8Ptr fontData = m_fontPool[p_font];
		MxU8 num = *fontData++;
		// fontData is stored as ccode / index pair
		for (MxU8 i=0; i<num; i++)
		{
			if (*fontData++ == p_ccode)
				return *(MxS16 *)fontData;

			fontData += sizeof(MxS16);
		}
	}
	return 0;
}

MxCharString
LegoGui::GetSoundActionName(MxS16 p_index)
{
	MxCharString soundName = NULL;

	if (m_soundPool)
		soundName = (MxCharString)m_soundPool[p_index];

	return soundName;
}

MxCharString
LegoGui::GetNamedActionName(MxS16 p_index)
{
	MxCharString actionName = NULL;

	if (m_namedActionPool)
		actionName = (MxCharString)m_namedActionPool[p_index];

	return actionName;
}

void
LegoGui::CheckForExitMessage(MxCharString p_target, MxCharString p_msg)
{
	if (!strcmp(p_target, m_guiName) && !strcmp(p_msg, EXIT_MESSAGE))
		m_exitMessageFound = TRUE;
}

void
LegoGui::BeginCaptureMouse(MxCore *p_control)
{
	m_mouseCaptureControl = p_control;
}

void
LegoGui::EndCaptureMouse()
{
	m_mouseCaptureControl = NULL;
}

