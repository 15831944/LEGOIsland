/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#ifndef __LEGOGUISTRING_H
#define __LEGOGUISTRING_H

#include "MxCore.h"

#include "LegoGuiBase.h"
#include "LegoGuiControl.h"


class LegoGuiString : public LegoGuiControl
{
// local types
private:

// exported types
public:

// local member functions
private:


// exported member functions
public:
	LegoGuiString();
	~LegoGuiString();
	virtual MxResult	ParseControlData(MxU8Ptr p_dataPtr); 
	MxCharString		GetValue() { return m_string; }
	void				SetValue(MxCharString p_string);
	void				SetValue(MxS32 p_char);
	MxU8				GetFont() { return m_font; }
	LegoGuiActionPtr	GetRState() { return &m_releasedState; }
	LegoGuiActionPtr	GetSAction() { return &m_selectAction; }
	LegoGuiActionPtr	GetSState() { return &m_selectedState; }
	LegoGuiActionPtr	GetRAction() { return &m_releaseAction; }
	virtual void		InitFromSystemVariable();

// Attributes
private:
	MxCharString	m_string;
	MxU8			m_font;
	MxU8			m_maxLength;
	MxU8			m_length;
	LegoGuiAction	m_releasedState;
	LegoGuiAction	m_selectAction;
	LegoGuiAction	m_selectedState;
	LegoGuiAction	m_releaseAction;
};



#endif // __LEGOGUISTRING_H