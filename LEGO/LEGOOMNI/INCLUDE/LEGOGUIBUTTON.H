/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#ifndef __LEGOGUIBUTTON_H
#define __LEGOGUIBUTTON_H

#include "MxCore.h"
#include "MxList.h"

#include "LegoGuiBase.h"
#include "LegoGuiControl.h"


// forward references
//
class LegoGuiRadio;
typedef LegoGuiRadio *LegoGuiRadioPtr;


// Usable controls are derived from LegoGuiControl base class.
class LegoGuiButton : public LegoGuiControl
{
// local types
private:

// exported types
public:

// local member functions
private:

// exported member functions
public:
	virtual MxResult	ParseControlData(MxU8Ptr p_dataPtr) = 0;
	LegoGuiActionPtr	GetRState() { return &m_releasedState; }
	LegoGuiActionPtr	GetSAction() { return &m_selectAction; }
	LegoGuiActionPtr	GetSState() { return &m_selectedState; }
	LegoGuiActionPtr	GetRAction() { return &m_releaseAction; }

// Attributes
protected:
	LegoGuiAction		m_releasedState;
	LegoGuiAction		m_selectAction;
	LegoGuiAction		m_selectedState;
	LegoGuiAction		m_releaseAction;
};

class LegoGuiPushButton : public LegoGuiButton
{
// local types
private:

// exported types
public:

// local member functions
private:

// exported member functions
public:
	virtual MxResult	ParseControlData(MxU8Ptr p_dataPtr); 

// Attributes
private:
};

class LegoGuiToggle : public LegoGuiButton
{
	friend class LegoGuiRadio;

// local types
private:

// exported types
public:

// local member functions
private:
protected:
	void			SetRadioPtr(LegoGuiRadioPtr p_radio) { m_radio = p_radio; }

// exported member functions
public:
	virtual MxResult	ParseControlData(MxU8Ptr p_dataPtr); 
	MxBool				GetState() { return m_state; }
	void				SetState(MxBool p_state);

// Attributes
private:
	MxBool				m_state;
	MxBool				m_isRadio;
	LegoGuiRadioPtr		m_radio;
};

typedef LegoGuiToggle * LegoGuiTogglePtr;

class LegoGuiToggleList : public MxPtrList<LegoGuiToggle> {
public:
    LegoGuiToggleList(MxBool p_ownership = FALSE) : MxPtrList<LegoGuiToggle>(p_ownership) {}
};

class LegoGuiToggleListCursor : public MxPtrListCursor<LegoGuiToggle> {
protected:
	MxS8 Compare(LegoGuiTogglePtr p_element1, LegoGuiTogglePtr p_element2) { return p_element1 - p_element2; }
public:
    LegoGuiToggleListCursor(LegoGuiToggleList* p_list) : MxPtrListCursor<LegoGuiToggle>(p_list) {}
};


class LegoGuiRadio : public LegoGuiControl
{
// local types
private:

// exported types
public:

// local member functions
private:
	void			toggleCallback(MxU32 p_id, MxU32 p_param);

// exported member functions
public:
	MxResult		ParseControlData(MxU8Ptr p_dataPtr); 
	MxU8			GetState() { return m_state; }
	void			SetState(MxU8 p_state);

// Attributes
private:
	MxU8					m_state;
	MxU8					m_numToggles;
	LegoGuiToggleList		m_toggleList;
};


#endif // __LEGOGUIBUTTON_H