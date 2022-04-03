/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxDSSubscriber.h"
#include "MxDSAction.h"
#include "MxTimer.h"
#include "MxRegion.h"
#include "MxDisplaySurface.h"
#include "LegoOmni.h"
#include "LegoGuiCtrlPresenter.h"
#include "LegoGui.h"
#include "LegoNotify.h"
#include "LegoInputManager.h"
#include "MxVideoManager.h"


LegoGuiCtrlPresenter::LegoGuiCtrlPresenter()
{
	Init();
}

LegoGuiCtrlPresenter::~LegoGuiCtrlPresenter()
{
	Destroy();
}

void
LegoGuiCtrlPresenter::Init()
{
    m_frameBitmap = NULL;
	m_currentFrameNum = 0;
	m_state = e_idle;
	m_advanceState = FALSE;
	m_startTime = 0;
	m_targetState = 0;
	m_holdState = FALSE;
	m_bitmapNoBlt = FALSE;
}



void
LegoGuiCtrlPresenter::Destroy()
{
    m_criticalSection.Enter();

    if (m_frameBitmap) {
        delete m_frameBitmap;
    }  
    Init();
    m_criticalSection.Leave();

}

MxResult
LegoGuiCtrlPresenter::Create(LegoGuiControl *p_control)
{
    MxResult result = FAILURE;
    if (MxPresenter::Create() != SUCCESS) {
        goto done;
    }

	m_control = p_control;
	m_state = e_ready;
	m_transBitMaps = TRUE;
	SetDisplayZ(m_control->GetParentGui()->GetNextDisplayZ());
    
	result = SUCCESS;

done:
    return result;
}

MxBool
LegoGuiCtrlPresenter::IsHit(MxS32 p_x, MxS32 p_y)
{
	return	p_x >= m_bBox.GetLeft() && p_x < m_bBox.GetRight() &&
			p_y >= m_bBox.GetTop() && p_y < m_bBox.GetBottom();
}


MxResult
LegoGuiCtrlPresenter::PutData()
{
    m_criticalSection.Enter();

	if (m_state > e_done && !m_bitmapNoBlt)
		PutFrame();

    m_criticalSection.Leave();
    return SUCCESS;
}

void 
LegoGuiCtrlPresenter::PutFrame()
{
    MxDisplaySurface* displaySurface =
		MxOmni::GetInstance()->GetVideoManager()->GetDisplaySurface();
    MxRegion* region = MxOmni::GetInstance()->GetVideoManager()->GetRegion();
	MxRect32 dataRect(	m_frameLoc,
						MxSize32(	m_frameBitmap->GetWidth(),
									m_frameBitmap->GetHeight()));
    MxRegionCursor cursor(region);
    MxRect32* regionRect;
    while (regionRect = cursor.Next(dataRect))
	{
        if (m_transBitMaps) {
            displaySurface->TransBlt(m_frameBitmap,
								regionRect->GetLeft() - m_frameLoc.GetX(),
								regionRect->GetTop() - m_frameLoc.GetY(),
								regionRect->GetLeft(),
								regionRect->GetTop(),
								regionRect->GetWidth(),
								regionRect->GetHeight());
       }
        else
		{
            displaySurface->Blt(m_frameBitmap,
								regionRect->GetLeft() - m_frameLoc.GetX(),
								regionRect->GetTop() - m_frameLoc.GetY(),
								regionRect->GetLeft(),
								regionRect->GetTop(),
								regionRect->GetWidth(),
								regionRect->GetHeight());
        }
    }
}

void
LegoGuiCtrlPresenter::SetActionInfo(LegoGuiControl::LegoGuiActionPtr p_action)
{
	m_frameTime = p_action->frameTime;
	m_numFrames = p_action->numFrames;
	m_looping = p_action->looping;
	m_bitmapArray = p_action->bitmapArray;
	m_bitmapNoBlt = p_action->bitmapNoBlt;
}


void 
LegoGuiCtrlPresenter::CreateFrameBitmap()
{
    if (m_frameBitmap)
	{
        delete m_frameBitmap;
    }

    m_frameBitmap = new LegoBitmap();
    m_frameBitmap->Create(m_control->GetParentGui()->GetBitmapInfo(m_bitmapArray[m_currentFrameNum]),
			m_control->GetParentGui()->GetBitmapImage(m_bitmapArray[m_currentFrameNum]));
}

void
LegoGuiCtrlPresenter::SetBBox()
{
	MxRect32 updateBox(m_bBox);

	m_bBox.SetLeft(m_frameLoc.GetX());
	m_bBox.SetTop(m_frameLoc.GetY());
	m_bBox.SetRight(m_frameLoc.GetX()+m_frameBitmap->GetWidth());
	m_bBox.SetBottom(m_frameLoc.GetY()+m_frameBitmap->GetHeight());

	updateBox |= m_bBox;
	LegoOmni::GetInstance()->GetVideoManager()->InvalidateRect(updateBox);
}


void
LegoGuiCtrlPresenter::EndAction()
{
    m_criticalSection.Enter();
    if (m_frameBitmap) {
        MxRect32 rect(m_frameLoc,
			MxSize32(m_frameBitmap->GetWidth(), m_frameBitmap->GetHeight()));
	    MxOmni::GetInstance()->GetVideoManager()->InvalidateRect(rect);
    }
    m_criticalSection.Leave();
    MxPresenter::EndAction();
}

void
LegoGuiCtrlPresenter::Refresh()
{
	m_currentFrameNum = NEW_FRAME;
}

MxS32
LegoGuiCtrlPresenter::Notify(MxParam& p_param)
{
	MxS32 result = FALSE;

	switch (((MxNotificationParam&) p_param).GetNotification())
	{
		case c_notificationButtonUp:
		{
			// release mouse capture on button up
			if (m_control->GetParentGui()->GetMouseCapture() == this)
				m_control->GetParentGui()->EndCaptureMouse();

			m_holdState = FALSE;
			break;
		}
		case c_notificationMouseMove:
		{
			// release capture when mouse moves out of bbox
			if (!IsHit(((LegoEventNotificationParam&)p_param).GetX(),
					((LegoEventNotificationParam&)p_param).GetY()) &&
				m_control->GetParentGui()->GetMouseCapture() == this)
			{
				m_control->GetParentGui()->EndCaptureMouse();
				m_holdState = FALSE;
			}
			break;
		}
		case c_notificationKeyPress:
			break;
		case c_notificationButtonDown:
		{
			// capture mouse events on button down
			m_control->GetParentGui()->BeginCaptureMouse(this);
			m_holdState = TRUE;
			m_advanceState = TRUE;
			result = TRUE;
			break;
		}
		default:
			result = MxPresenter::Notify(p_param);
			break;
	}
	return result;
}

