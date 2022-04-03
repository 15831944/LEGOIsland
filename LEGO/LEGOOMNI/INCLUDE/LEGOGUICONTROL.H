/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#ifndef __LEGOGUICONTROL_H
#define __LEGOGUICONTROL_H

#include "MxCore.h"
#include "MxList.h"
#include "MxGeometry.h"

#include "LegoGuiBase.h"


// forward references
//
class LegoGui;
typedef LegoGui *LegoGuiPtr;
class LegoGuiCtrlPresenter;


//
// LegoGuiControl is an Abstract Base Class to derive specific
// controls from. The Create function must be supplied by the
// derived class.
//
class LegoGuiControl : public LegoGuiBase
{
	//friend class LegoGui;

// local types
private:

// exported types
public:

	enum LegoGuiCtrlType {
			e_pushbutton = 0,
			e_toggle,
			e_radio,
			e_slider,
			e_string,
	};

	enum LegoEventMask {
			c_buttonUp = 1,
			c_buttonDown = 2,
			c_drag = 4,
	};

	enum LegoGuiMessageType {
			e_boolMsg = 0,
			e_intMsg,
			e_stringMsg,
			e_sysVarMsg,
	};


	struct LegoGuiScreenCoord {
		MxS16				x;
		MxS16				y;
	};
	typedef LegoGuiScreenCoord *LegoGuiScreenCoordPtr;

	struct LegoGuiRect {
		MxS16				left;
		MxS16				top;
		MxS16				right;
		MxS16				bottom;
	};
	typedef LegoGuiRect *LegoGuiRectPtr;

	typedef LegoGuiRectPtr LegoGuiRectAreaPtr;	   // temp

	union LegoGuiMessageValue {
		MxBool			msgBool;
		MxS32			msgInt;
		MxCharString	msgString;
	};

	class LegoGuiMessage : public MxCore
	{
	public:
		LegoGuiMessage() {}
		~LegoGuiMessage(){}

	public:
		MxCharString		GetTarget() { return m_target; }
		void				SetTarget(MxCharString p_target) { m_target = p_target; }
		LegoGuiMessageType	GetType() { return m_type; }
		void				SetType(LegoGuiMessageType p_type) { m_type = p_type; }
		LegoGuiMessageValue	GetValue() { return m_value; }
		MxBool				GetBoolValue() { return m_value.msgBool; }
		MxS32				GetIntValue() { return m_value.msgInt; }
		MxCharString		GetStringValue() { return m_value.msgString; }
		void				SetValue(MxBool p_value) { m_value.msgBool = p_value; }
		void				SetValue(MxS32 p_value) { m_value.msgInt = p_value; }
		void				SetValue(MxCharString p_value) { m_value.msgString = p_value; }
	private:
		MxCharString		m_target;
		LegoGuiMessageType	m_type;
		LegoGuiMessageValue	m_value;
	};
	typedef LegoGuiMessage *LegoGuiMessagePtr;

	class LegoGuiMessageList : public MxPtrList<LegoGuiMessage> {
	public:
		LegoGuiMessageList(MxBool p_ownership = TRUE) : MxPtrList<LegoGuiMessage>(p_ownership) {}
	};

	class LegoGuiMessageListCursor : public MxPtrListCursor<LegoGuiMessage> {
	protected:
		MxS8 Compare(LegoGuiMessagePtr p_element1, LegoGuiMessagePtr p_element2) { return p_element1 - p_element2; }
	public:
		LegoGuiMessageListCursor(LegoGuiMessageList* p_list) : MxPtrListCursor<LegoGuiMessage>(p_list) {}
	};



	struct LegoGuiAction {
		MxBool					looping;
		MxTime					frameTime;
		MxU8					numFrames;
		LegoGuiScreenCoordPtr	offsetArray;
		MxS16Ptr				bitmapArray;
		MxS16					soundActionIdx;
		LegoGuiMessageList		messageList;
		MxS16					actionNameIdx;
		MxBool					bitmapNoBlt;
	};
	typedef LegoGuiAction *LegoGuiActionPtr;


// local member functions
private:

// GuiControl cannot be used on it's own.
// The ParseControlData member function must
// be provided by the derived class.
protected:
	LegoGuiControl();

	void GetGuiAction(LegoGuiActionPtr p_action, MxU8Ptr *p_data, MxResult *p_result);

// exported member functions
public:
	~LegoGuiControl();

	MxResult Create(
//			MxU32 p_controlId,
			MxCharString p_controlName,
			MxCharString p_objectName,
			MxCharString p_sysVar,
			MxU8 p_type,
			MxU8 p_eventMask,
			MxU8 p_keyLow,
			MxU8 p_keyHigh,
			LegoGuiPtr p_gui,
			MxU8Ptr p_dataPtr);

	virtual MxResult ParseControlData(MxU8Ptr p_dataPtr) = 0;
	
	void	GetActionLoc(LegoGuiActionPtr p_action, MxU8 p_idx, MxPoint32 *p_loc);
	LegoGuiPtr				GetParentGui() { return m_gui; }
	MxU8					GetType() { return m_controlType; }
	void					SendActionMessages(LegoGuiActionPtr p_action);
	void					StartActionSound(LegoGuiActionPtr p_action);
	MxCharString			GetControlName() { return m_controlName; }
	virtual MxS32			Notify(MxParam& p_param);
	MxU8					GetKeyRangeLow() { return m_keyRangeLow; }
	MxU8					GetKeyRangeHigh() { return m_keyRangeHigh; }
	void					SetValue(MxBool p_value);
	void					SetValue(MxS32 p_value);
	void					SetValue(MxCharString p_value);
	void					SetSystemVariable(MxCharString p_value);
	virtual void			InitFromSystemVariable() { }
	void					Activate();
	void					DeActivate();




protected:
	MxU8					m_eventMask;
	LegoGuiPtr				m_gui;
	LegoGuiCtrlPresenter	*m_presenter;
	MxU8					m_keyRangeLow;
	MxU8					m_keyRangeHigh;
	MxCharString			m_sysVar;
private:
	MxU32					m_controlId;
	MxCharString			m_controlName;
	MxCharString			m_objectName;
	MxU8					m_controlType;
};

typedef LegoGuiControl * LegoGuiControlPtr;

class LegoGuiControlList : public MxPtrList<LegoGuiControl> {
public:
    LegoGuiControlList(MxBool p_ownership = FALSE) : MxPtrList<LegoGuiControl>(p_ownership) {}
};

class LegoGuiControlListCursor : public MxPtrListCursor<LegoGuiControl> {
protected:
	MxS8 Compare(LegoGuiControlPtr p_element1, LegoGuiControlPtr p_element2) { return p_element1 - p_element2; }
public:
    LegoGuiControlListCursor(LegoGuiControlList* p_list) : MxPtrListCursor<LegoGuiControl>(p_list) {}
};


class LegoGuiSlider : public LegoGuiControl
{
// local types
private:

// exported types
public:

// local member functions
private:

// exported member functions
public:
	MxResult		ParseControlData(MxU8Ptr p_dataPtr); 
	MxS32			GetValue() { return m_value; }
	void			SetValue(MxS32 p_value);

// Attributes
private:
	MxS32					m_value;
	MxS32					m_minValue;
	MxS32					m_maxValue;
	MxBool					m_horizontal;
	LegoGuiRect				m_rect;
	MxU8					m_numFrames;
	LegoGuiScreenCoordPtr	m_offsetArray;
	MxS16Ptr				m_bitmapArray;
	LegoGuiRectAreaPtr		m_pickAreaArray;
	MxS16					m_flcIndex;
	MxCharString			m_actionName;
};

#endif // __LEGOGUICONTROL_H