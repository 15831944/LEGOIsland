/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxTickleManager.h"
#include "LegoOmni.h"
#include "LegoVideoManager.h"
#include "LegoNotify.h"
#include "LegoInputManager.h"

//#define QUEUE_EVENTS


LegoInputManager::LegoInputManager()
{
	m_keyboardNotifyList = 0;
	m_mouseCaptureRaw = 0;
	m_mouseCapture = 0;
	m_eventQueue = 0;
	m_drag = FALSE;
	m_dragThreshold = 1;
	m_autoDragTime = 1000;
	m_autoDragTimerID = 0;
	m_buttonDownX = 0;
	m_buttonDownY = 0;
}

LegoInputManager::~LegoInputManager()
{
	Destroy();
}


MxResult
LegoInputManager::Create()
{
	MxResult result = SUCCESS;

	if (!m_keyboardNotifyList)
		m_keyboardNotifyList = new LegoNotifyList;

    if (!m_eventQueue)
		m_eventQueue = new LegoEventQueue;

	if (!m_keyboardNotifyList || !m_eventQueue)
	{
		Destroy();
		result = FAILURE;
	}
#ifdef QUEUE_EVENTS
	else
	{
		if (LegoOmni::GetInstance()->GetTickleManager()) {
			LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 50);
		}
	}
#endif // QUEUE_EVENTS

    return result;
}

void
LegoInputManager::Destroy()
{
#ifdef QUEUE_EVENTS
	if (LegoOmni::GetInstance()->GetTickleManager()) {
	    LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);
    }
#endif // QUEUE_EVENTS

	if (m_keyboardNotifyList)
		delete m_keyboardNotifyList;
    m_keyboardNotifyList = 0;
	if (m_eventQueue)
		delete m_eventQueue;
    m_eventQueue = 0;

}

void
LegoInputManager::Register(MxCore *p_notify)
{
    AUTOLOCK(m_criticalSection)

	m_keyboardNotifyList->Append(p_notify); 
}

void
LegoInputManager::UnRegister(MxCore *p_notify)
{
    AUTOLOCK(m_criticalSection)

    LegoNotifyListCursor cursor(m_keyboardNotifyList);
    if (cursor.Find(p_notify))
		cursor.Detach();
}

void
LegoInputManager::BeginCaptureMouse( MxCore *p_control)
{
	// do the system capture here

	m_mouseCapture = p_control;
}

void
LegoInputManager::EndCaptureMouse()
{
	m_mouseCapture = NULL;
}

void
LegoInputManager::BeginCaptureMouseRaw( MxCore *p_control)
{
	// do the system capture here

	m_mouseCaptureRaw = p_control;
}

void
LegoInputManager::EndCaptureMouseRaw()
{
	m_mouseCaptureRaw = NULL;
}

void
LegoInputManager::QueueEvent(MxS16 p_type, MxU8 p_modifier,
							 MxS32 p_x, MxS32 p_y, MxU8 p_key)
{ 
	LegoEventNotificationParam event(
		p_type,					// event type			
		NULL,					// null sender
		p_modifier,				// keystate modifier
		p_x,					// x
		p_y,					// y
		p_key);					// key

#ifdef QUEUE_EVENTS
	m_criticalSection.Enter();
	m_eventQueue->Enqueue(event);
	m_criticalSection.Leave();
#else // immediate event notification
	ProcessOneEvent(event);
#endif // QUEUE_EVENTS
}

void
LegoInputManager::ProcessEvents()
{
	AUTOLOCK(m_criticalSection)

	LegoEventNotificationParam event;

	while (m_eventQueue->Dequeue(event))
	{
		if (ProcessOneEvent(event))
			break;
	}
}

MxBool
LegoInputManager::ProcessOneEvent(LegoEventNotificationParam& event)
{
	MxBool eventUsed = FALSE;

	if (event.GetNotification() == c_notificationKeyPress)
	{
		LegoNotifyListCursor cursor(m_keyboardNotifyList);
		MxCore *target;
		while (!eventUsed && cursor.Next(target))
		{
			eventUsed = (MxBool)target->Notify(event);
			// only process one key per cycle.
			if (eventUsed)
				return eventUsed;
		}
	}
	else
	{
		if (m_mouseCaptureRaw)
		{
			eventUsed = (MxBool)m_mouseCaptureRaw->Notify(event);
		}
		
		// translate to select/drag/release event
		if (!eventUsed && TranslateEvent(event))
		{
			// presenters get select events only
			if (event.GetNotification() == c_notificationSelect)
			{
				LegoVideoManager *vman =
					(LegoVideoManager *)LegoOmni::GetInstance()->GetVideoManager();
				if (vman)
				{
					MxPresenter *control =
						vman->GetPresenterAt(event.GetX(), event.GetY());
					if (control)
						eventUsed = (MxBool)control->Notify(event); 
				}
			}

			if (m_mouseCapture && !eventUsed)
			{
				eventUsed = (MxBool)m_mouseCapture->Notify(event);
			}
		}
	}
	return eventUsed;
}

MxBool
LegoInputManager::TranslateEvent(LegoEventNotificationParam& event)
{
	MxBool eventTranslated = FALSE;

	switch (event.GetNotification())
	{
		case c_notificationButtonDown:
			m_buttonDownX = event.GetX();
			m_buttonDownY = event.GetY();
			m_drag = FALSE;
			StartAutoDragTimer();
			break;
		case c_notificationButtonUp:
			StopAutoDragTimer();
			if (m_drag)
			{
				event.SetNotification(c_notificationDragEnd);
				eventTranslated = TRUE;
			}
			else
			{
				event.SetX(m_buttonDownX);
				event.SetY(m_buttonDownY);
				event.SetNotification(c_notificationSelect);
				eventTranslated = TRUE;
			}
			m_drag = FALSE;
			break;
		case c_notificationMouseMove:
			if (event.GetModifier() & LegoEventNotificationParam::c_lButtonState)
			{
				if (!m_drag)
				{
					MxS32 dx = event.GetX() - m_buttonDownX;
					MxS32 dy = event.GetY() - m_buttonDownY;
					MxS32 d2 = (dx * dx) + (dy * dy);
					if (d2 > m_dragThreshold)
					{
						StopAutoDragTimer();
						m_drag = TRUE;
						event.SetNotification(c_notificationDragStart);
						eventTranslated = TRUE;
						event.SetX(m_buttonDownX);
						event.SetY(m_buttonDownY);
					}
				}
				else
				{
					event.SetNotification(c_notificationDrag);
					eventTranslated = TRUE;
				}
			}
			break;
		case c_notificationTimer:
			if (event.GetModifier() == m_autoDragTimerID)
			{
				// fake a start drag event
				StopAutoDragTimer();
				m_drag = TRUE;
				event.SetX(m_buttonDownX);
				event.SetY(m_buttonDownY);
				event.SetModifier(LegoEventNotificationParam::c_lButtonState);
				event.SetNotification(c_notificationDragStart);
				eventTranslated = TRUE;
			}
	}

	return eventTranslated;
}

void
LegoInputManager::StartAutoDragTimer()
{
#ifdef WIN32
	m_autoDragTimerID = ::SetTimer(LegoOmni::GetInstance()->GetWindow(), 1, m_autoDragTime, NULL);
#else
	m_autoDragTimerID = 0;
#endif // WIN32
}

void
LegoInputManager::StopAutoDragTimer()
{
#ifdef WIN32
	if (m_autoDragTimerID)
		::KillTimer(LegoOmni::GetInstance()->GetWindow(), m_autoDragTimerID);
#endif // WIN32
}
