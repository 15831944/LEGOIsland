/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGONOTIFY_H
#define __LEGONOTIFY_H

#include "MxCore.h"
#include "MxNotificationManager.h"

#include "LegoGuiControl.h"

enum {
	// NOTE: These values must not overlap with those
	// defined in MxNotificationManager.h
	c_notificationKeyPress = 1000,
	c_notificationButtonUp,
	c_notificationButtonDown,
	c_notificationMouseMove,
	c_notificationSelect,
	c_notificationDragStart,
	c_notificationDrag,
	c_notificationDragEnd,
	c_notificationTimer,

	c_notificationCtrlMsg,
};


class LegoEventNotificationParam : public MxNotificationParam {
public:
	enum {
		c_lButtonState = 1,
		c_rButtonState = 2,
		c_modKey1 = 4,
		c_modKey2 = 8,
	};


public:
	LegoEventNotificationParam(
		MxS16 p_notification,
		MxCore* p_sender,
		MxU8 p_modifier,
		MxS32 p_x, MxS32 p_y,
		MxU8 p_key) :	MxNotificationParam(p_notification, p_sender),
						m_modifier(p_modifier),
						m_x(p_x), m_y(p_y), m_key(p_key) {}
	// NOTE: Our use will set the notification and sender after the constructor
	// has been called, so we just pass dummy data to the MxNotificationParam
	// constructor.
    LegoEventNotificationParam() :  MxNotificationParam(0, 0) {}

	inline void		SetModifier(MxU8 p_modifier) { m_modifier = p_modifier; }
	inline MxU8		GetModifier() { return m_modifier; }
	inline void		SetX(MxS32 p_x) { m_x = p_x; }
	inline MxS32	GetX() { return m_x; }
	inline void		SetY(MxS32 p_y) { m_y = p_y; }
	inline MxS32	GetY() { return m_y; }
	inline void		SetKey(MxU8 p_key) { m_key = p_key; }
	inline MxU8		GetKey() { return m_key; }

protected:
	MxU8			m_modifier;
	MxS32			m_x;
	MxS32			m_y;
	MxU8			m_key;
};


class LegoMessageNotificationParam : public MxNotificationParam {
public:
	LegoMessageNotificationParam(
		MxS16 p_notification,
		MxCore* p_sender,
		LegoGuiControl::LegoGuiMessageType p_type,
		LegoGuiControl::LegoGuiMessageValue	p_value) :	MxNotificationParam(p_notification, p_sender),
						m_type(p_type),
						m_value(p_value) {}

	inline LegoGuiControl::LegoGuiMessageType	GetType() { return m_type; }
	inline MxBool				GetBoolValue() { return m_value.msgBool; }
	inline MxS32				GetIntValue() { return m_value.msgInt; }
	inline MxCharString			GetStringValue() { return m_value.msgString; }
private:
		LegoGuiControl::LegoGuiMessageType	m_type;
		LegoGuiControl::LegoGuiMessageValue	m_value;
};


#endif  // __LEGONOTIFY_H