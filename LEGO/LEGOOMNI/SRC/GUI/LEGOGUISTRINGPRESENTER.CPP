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
#include "LegoGuiString.h"
#include "LegoGuiStringPresenter.h"

#include "MxVideoManager.h"  // just using for the Tickle


// NOTE: GuiString background behaves like a pushbutton under the
// displayed text string. This allows indicating a selected state
// for the string and provides display and pick location information
// via the Action items.

MxResult 
LegoGuiStringPresenter::Tickle()
{
    switch (m_state) {
    case e_ready:
    case e_active:
		m_startTime = m_control->GetParentGui()->GetTimer()->GetTime();
		SetActionInfo(((LegoGuiString *)m_control)->GetRState());
		m_currentFrameNum = NEW_FRAME;
		m_state = e_rstate;
        // fall through
    case e_rstate:
		RStateTickle();
		if (m_state != e_saction) {
            break;
        }
		// send any inter-control messages at start of new action
		m_control->SendActionMessages(((LegoGuiString *)m_control)->GetSAction());
        // fall through
    case e_saction:
		SActionTickle();
        if (m_state != e_sstate) {
            break;
        }
 		// send any inter-control messages at start of new action
		m_control->SendActionMessages(((LegoGuiString *)m_control)->GetSState());
       // fall through
    case e_sstate:
		SStateTickle();
        if (m_state != e_raction) {
            break;
        }
  		// send any inter-control messages at start of new action
		m_control->SendActionMessages(((LegoGuiString *)m_control)->GetRAction());
       // fall through
    case e_raction:
		RActionTickle();
        if (m_state == e_rstate) {
  			// send any inter-control messages at start of new action
			m_control->SendActionMessages(((LegoGuiString *)m_control)->GetRState());
        }
        break;
    }
    return SUCCESS;
}

MxBool
LegoGuiStringPresenter::GetNextFrameNum(MxBool p_stable)
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
LegoGuiStringPresenter::RStateTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// buttons are stable in the released state unless there
	// has been a select action on the button (m_advanceState == TRUE)
	MxBool stableState = !m_advanceState;
	if (GetNextFrameNum(stableState) == TRUE)
	{
		m_advanceState = FALSE;
		SetActionInfo(((LegoGuiString *)m_control)->GetSAction());
		m_state = e_saction;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiString *)m_control)->GetRState(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}

MxResult
LegoGuiStringPresenter::SActionTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// buttons are not stable in the select transition.
	if (GetNextFrameNum(FALSE) == TRUE)
	{
		SetActionInfo(((LegoGuiString *)m_control)->GetSState());
		m_state = e_sstate;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiString *)m_control)->GetSAction(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}

MxResult
LegoGuiStringPresenter::SStateTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// pushbuttons are not stable in the selected state.
	if (GetNextFrameNum(FALSE) == TRUE)
	{
		if (m_control->GetType() == LegoGuiControl::e_toggle)
			m_advanceState = FALSE;
		SetActionInfo(((LegoGuiString *)m_control)->GetRAction());
		m_state = e_raction;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiString *)m_control)->GetSState(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}

MxResult
LegoGuiStringPresenter::RActionTickle()
{
	MxU8 saveFrameNum = m_currentFrameNum;

	// buttons are not stable in the release transition.
	if (GetNextFrameNum(FALSE) == TRUE)
	{
		SetActionInfo(((LegoGuiString *)m_control)->GetRState());
		m_state = e_rstate;
	}
	else if (saveFrameNum != m_currentFrameNum)
	{
		// setup the new frame.
		CreateFrameBitmap();
		m_control->GetActionLoc(((LegoGuiString *)m_control)->GetRAction(),
									m_currentFrameNum, &m_frameLoc);
		SetBBox();
	}
    return SUCCESS;
}


void 
LegoGuiStringPresenter::CreateFrameBitmap()
{
    if (m_frameBitmap)
	{
        delete m_frameBitmap;
    }

	// create bitmap to match current background
    m_frameBitmap = new LegoBitmap();
    m_frameBitmap->Create(m_control->GetParentGui()->GetBitmapInfo(m_bitmapArray[m_currentFrameNum]));
    memcpy(m_frameBitmap->GetImage(),
		m_control->GetParentGui()->GetBitmapImage(m_bitmapArray[m_currentFrameNum]),
		m_frameBitmap->GetImageSize());

	// now place text on top
	MxCharString ptr = ((LegoGuiString *)m_control)->GetValue();
	MxU8 font = ((LegoGuiString *)m_control)->GetFont();
	int x = 0;	// these need to come from control data
	int y = 0;
	while (ptr && *ptr)
	{
		// find character bitmap
		LegoBitmap *charBitmap = new LegoBitmap();
		MxS16 bmapIndex = m_control->GetParentGui()->GetFontBitmapIndex(*ptr, font);
		charBitmap->Create(m_control->GetParentGui()->GetBitmapInfo(bmapIndex),
								m_control->GetParentGui()->GetBitmapImage(bmapIndex));

		if (charBitmap)
		{
			// Blt onto background
			m_frameBitmap->TransBlt(charBitmap, 0, 0, x, y,
						charBitmap->GetWidth(), charBitmap->GetHeight());
			x += charBitmap->GetWidth();
			ptr++;
			delete charBitmap;
		}
	}
}


