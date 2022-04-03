/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#include "StdLego.h"
#include "MxString.h"
#include "MxVariableTable.h"
#include "LegoOmni.h"
#include "LegoGuiControl.h"
#include "LegoGui.h"
#include "LegoGuiString.h"
#include "LegoGuiStringPresenter.h"


#define ASCII_BACKSPACE 8

LegoGuiString::LegoGuiString()
{
	m_string = NULL;
	m_length = 0;
}

LegoGuiString::~LegoGuiString()
{
	if (m_string)
		delete [] m_string;
}

MxResult
LegoGuiString::ParseControlData(MxU8Ptr p_data)
{
	MxResult result = SUCCESS;

	m_maxLength = GetU8(&p_data);
	m_font = GetU8(&p_data);
	m_string = new char[m_maxLength+1];
	m_string[0] = '\0';

	GetGuiAction(&m_releasedState, &p_data, &result);
	GetGuiAction(&m_selectAction, &p_data, &result);
	GetGuiAction(&m_selectedState, &p_data, &result); 
	GetGuiAction(&m_releaseAction, &p_data, &result);
	m_presenter = new LegoGuiStringPresenter;
	m_presenter->Create(this);

	return result;
}

void
LegoGuiString::SetValue(MxCharString p_string)
{
	// replace string completely
	strncpy(m_string, p_string, m_maxLength-1);
	m_string[m_maxLength-1] = '\0';
	m_length = strlen(m_string);

	// sync up any system variable
	SetSystemVariable(m_string);

	// tell our presenter to refresh
	m_presenter->Refresh();
}

void
LegoGuiString::SetValue(MxS32 p_char)
{
	// check for backspace
	if (p_char == ASCII_BACKSPACE)
	{
		if(m_length)
			m_string[--m_length] = '\0';
	}

	// add on to end of string
	else if (p_char && m_length < m_maxLength)
	{
		m_string[m_length++] = (char)p_char;
		m_string[m_length] = '\0';
	}

	// sync up any system variable
	SetSystemVariable(m_string);

	// tell our presenter to refresh
	m_presenter->Refresh();
}


void
LegoGuiString::InitFromSystemVariable()
{
	if (m_sysVar)
	{
		MxConstCharString value =
			LegoOmni::GetInstance()->GetVariableTable()->GetVariable(m_sysVar);
		if (value)
		{
			strncpy(m_string, value, m_maxLength-1);
			m_string[m_maxLength-1] = '\0';
			m_length = strlen(m_string);
			m_presenter->Refresh();
		}
	}
}