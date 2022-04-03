/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOINPUTMANAGER_H
#define __LEGOINPUTMANAGER_H

#include "MxPresenter.h"
#include "LegoNotify.h"

class LegoNotifyList : public MxPtrList<MxCore>
{
protected:
    virtual MxS8 Compare(MxCore* p_element1, MxCore* p_element2)
		{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoNotifyList(MxBool p_ownership = FALSE) : MxPtrList<MxCore>(p_ownership) {}
};

class LegoNotifyListCursor : public MxPtrListCursor<MxCore>
{
public:
    LegoNotifyListCursor(LegoNotifyList* p_list) : MxPtrListCursor<MxCore>(p_list) {}
};

class LegoEventQueue : public MxQueue<LegoEventNotificationParam> { };

class LegoInputManager : public MxPresenter
{
private:
	MxCriticalSection			m_criticalSection;
	LegoNotifyList				*m_keyboardNotifyList;
	MxCore						*m_mouseCapture;
	MxCore						*m_mouseCaptureRaw;
	LegoEventQueue				*m_eventQueue;
	MxS32						m_buttonDownX;
	MxS32						m_buttonDownY;
	MxS32						m_dragThreshold;
	MxU32						m_autoDragTimerID;
	MxU32						m_autoDragTime;
	MxBool						m_drag;

protected:

public:
	LegoInputManager();
	~LegoInputManager();

	MxResult			Create();
	virtual void		Destroy();
	void				Register(MxCore *p_notify);
	void				UnRegister(MxCore *p_notify);

	virtual MxResult	Tickle() { ProcessEvents(); return SUCCESS; }
    virtual MxResult	PutData() { return SUCCESS; }
	void				ProcessEvents();
	void				BeginCaptureMouse(MxCore *p_control);
	void				EndCaptureMouse();
	MxCore*				GetMouseCapture() {return m_mouseCapture;}
	void				BeginCaptureMouseRaw(MxCore *p_control);
	void				EndCaptureMouseRaw();
	MxCore*				GetMouseCaptureRaw() {return m_mouseCaptureRaw;}
	LegoEventQueue		*GetEventQueue() { return m_eventQueue; }
	void				QueueEvent(MxS16 p_type, MxU8 p_modifier,
								MxS32 p_x, MxS32 p_y, MxU8 p_key);
private:
	MxBool				ProcessOneEvent(LegoEventNotificationParam& event);
	MxBool				TranslateEvent(LegoEventNotificationParam& event);
	void				StartAutoDragTimer();
	void				StopAutoDragTimer();
};

#endif  // __LEGOINPUTMANAGER_H