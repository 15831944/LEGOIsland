/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/
#include "StdLego.h"

// Omni header files
#include "MxDSSubscriber.h"
#include "MxDSAction.h"
#include "MxTimer.h"

// LegoOmni header files
#include "LegoOmni.h"
#include "LegoGui.h"
#include "LegoGuiButton.h"
#include "LegoGuiButtonPresenter.h"

#include "MxVideoManager.h"  // just using for the Tickle



MxResult 
LegoGuiButtonPresenter::Tickle()
{
    switch (m_state) {
    case e_ready:
    case e_active:
		m_startTime = m_control->GetParentGui()->GetTimer()->GetTime();
		SetActionInfo(((LegoGuiButton *)m_control)->GetRState());
		m_currentFrameNum = NEW_FRAME;
		m_state = e_rstate;
        // fall through
    case e_rstate:
		RStateTickle();
		if (m_state != e_saction) {
            break;
        }
		// send any inter-control messages at start of new action
		m_control->SendActionMessages(((LegoGuiButton *)m_control)->GetSAction());
		// start any required sounds at start of new action
		m_control->StartActionSound(((LegoGuiButton *)m_control)->GetSAction());
		// sync named system variable to new state (selected == TRUE)
		m_control->SetSystemVariable("TRUE");
        // fall through
    case e_saction:
		SActionTickle();
        if (m_state != e_sstate) {
            break;
        }
 		// send any inter-control messages at start of new action
		m_control->SendActionMessages(((LegoGuiButton *)m_control)->GetSState());
		// start any required sounds at start of new action
		m_control->StartActionSound(((LegoGuiButton *)m_control)->GetSState());
       // fall through
    case e_sstate:
		SStateTickle();
        if (m_state != e_raction) {
            break;
        }
  		// send any inter-control messages at start of new action
		m_control->SendActionMessages(((LegoGuiButton *)m_control)->GetRAction());
		// start any required sounds at start of new action
		m_control->StartActionSound(((LegoGuiButton *)m_control)->GetRAction());
		// sync named system variable to new state (released == FALSE)
		m_control->SetSystemVariable("FALSE");
       // fall through
    case e_raction:
		RActionTickle();
        if (m_state == e_rstate) {
  			// send any inter-control messages at start of new action
			m_control->SendActionMessages(((LegoGuiButton *)m_control)->GetRState());
			// start any required sounds at start of new action
			m_control->StartActionSound(((LegoGuiButton *)m_control)->GetRState());
        }
        break;
    }
    return SUCCESS;
}

MxBool
LegoGuiButtonPresenter::GetNextFrameNum(MxBool p_stable)
{
	MxBool endOfState = FALSE;
	MxTime currentTime = m_control->GetParentGui()->GetTimer()->GetTime();
	if (m_frameTime > 0)
	{
		MxU8 savedFrameNum =
				(m_currentFrameNum == NEW_FRAME ? 0: m_currentFrameNum);
		MxTime elapsedTime = currentTime - m_startTime;
		m_currentFrameNum = (MxU8)((elapsedTime/m_frameTime) % m_numFrames);

		// wrapped around ?
		if ((m_currentFrameNum < savedFrameNum) || (m_numFrames == 1))
		{
			if (p_stable)
			{
				if (!m_looping)
					m_currentFrameNum = m_numFrames - 1;
			}
			else if ((m_numFrames > 1) || (elapsedTime >= m_frameTime))
			{
				m_startTime = currentTime;
				m_currentFrameNum = NEW_FRAME;
				endOfState = TRUE;
			}
		}
	}
	else
	{
		if (p_stable)
		{
			m_currentFrameNum = 0;
		}
		else
		{
			endOfState = TRUE;
			m_currentFrameNum = NEW_FRAME;
			m_startTime = currentTime;
		}
	}

	return endOfState;
}

MxResult 
LegoGuiButtonPresenter::RStateTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// buttons are stable in the released state unless there
	// has been a select action on the button (m_advanceState == TRUE)
	// or a target state has been set via an inter-control message.
	if (m_targetState == m_state)
		m_targetState = 0;
	MxBool stableState = !(m_advanceState || m_targetState);
	if (GetNextFrameNum(stableState) == TRUE)
	{
		m_advanceState = FALSE;
		SetActionInfo(((LegoGuiButton *)m_control)->GetSAction());
		m_state = e_saction;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiButton *)m_control)->GetRState(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}

MxResult
LegoGuiButtonPresenter::SActionTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// buttons are not stable in the select transition.
	if (GetNextFrameNum(FALSE) == TRUE)
	{
		SetActionInfo(((LegoGuiButton *)m_control)->GetSState());
		m_state = e_sstate;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiButton *)m_control)->GetSAction(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}

MxResult
LegoGuiButtonPresenter::SStateTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// toggle buttons are stable in the selected state unless there
	// has been a select action on the button (m_advanceState == TRUE)
	// or a target state has been set via an inter-control message.
	// pushbuttons are not stable in the selected state unless a holdState
	// is in effect.
	if (m_targetState == m_state)
		m_targetState = 0;

	MxBool stableState =
		m_control->GetType() == LegoGuiControl::e_pushbutton ? m_holdState:
									!(m_advanceState || m_targetState);
	if (GetNextFrameNum(stableState) == TRUE)
	{
		if (m_control->GetType() == LegoGuiControl::e_toggle)
			m_advanceState = FALSE;
		SetActionInfo(((LegoGuiButton *)m_control)->GetRAction());
		m_state = e_raction;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiButton *)m_control)->GetSState(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}

MxResult
LegoGuiButtonPresenter::RActionTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// buttons are not stable in the release transition.
	if (GetNextFrameNum(FALSE) == TRUE)
	{
		SetActionInfo(((LegoGuiButton *)m_control)->GetRState());
		m_state = e_rstate;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiButton *)m_control)->GetRAction(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}


void
LegoGuiButtonPresenter::SetValue(MxBool p_value)
{
	// set a target state shoot for
	if (!m_targetState)
		m_targetState = p_value ? e_sstate: e_rstate;
}
