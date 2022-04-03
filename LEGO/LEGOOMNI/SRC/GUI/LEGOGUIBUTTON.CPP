/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#include "StdLego.h"
#include "MxString.h"
#include "LegoGuiControl.h"
#include "LegoGui.h"
#include "LegoGuiButton.h"
#include "LegoGuiButtonPresenter.h"


MxResult
LegoGuiPushButton::ParseControlData(MxU8Ptr p_data)
{
	MxResult result = SUCCESS;
	GetGuiAction(&m_releasedState, &p_data, &result);
	GetGuiAction(&m_selectAction, &p_data, &result);
	GetGuiAction(&m_selectedState, &p_data, &result); 
	GetGuiAction(&m_releaseAction, &p_data, &result);
	m_presenter = new LegoGuiButtonPresenter;
	m_presenter->Create(this);
	return result;
}

MxResult
LegoGuiToggle::ParseControlData(MxU8Ptr p_data)
{
	MxResult result = SUCCESS;
	m_isRadio = GetBool(&p_data);
	m_state = GetBool(&p_data);
	GetGuiAction(&m_releasedState, &p_data, &result);
	GetGuiAction(&m_selectAction, &p_data, &result); 
	GetGuiAction(&m_selectedState, &p_data, &result); 
	GetGuiAction(&m_releaseAction, &p_data, &result); 
	m_presenter = new LegoGuiButtonPresenter;
	m_presenter->Create(this);
	return result;
}

MxResult
LegoGuiRadio::ParseControlData(MxU8Ptr p_data)
{
	MxResult result = SUCCESS;
	m_numToggles = GetU8(&p_data);
	for (int i=0; i<m_numToggles; i++)
	{
		MxU32 len = GetU32(&p_data);
		MxU8Ptr savedPtr = p_data;

		LegoGuiToggle *toggle	= new LegoGuiToggle;
		MxCharString controlName = GetString(&p_data);
		MxU32 controlId = m_gui->MakeControlId(controlName);
		MxCharString objName = GetString(&p_data);
		result = toggle->Create(
//			controlId,		// ID
			controlName,	// Name
			objName,		// object to attach to
			NULL,			// system variable is handled by RADIO control.
			e_toggle,		// type is toggle
			m_eventMask,
			m_keyRangeLow,
			m_keyRangeHigh,
			m_gui,			// my parent gui
			p_data);

		if (result != SUCCESS)
			break;
		toggle->SetRadioPtr(this);
		m_toggleList.Append(toggle);
		p_data = savedPtr + len;
	}
	return result;
}

