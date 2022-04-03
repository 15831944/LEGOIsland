/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxRegion.h"
#include "MxDisplaySurface.h"
#include "MxDSSubscriber.h"
#include "MxDSAction.h"
#include "MxTimer.h"
#include "LegoOmni.h"
#include "LegoGuiBGPresenter.h"
#include "LegoGui.h"
#include "MxVideoManager.h"


LegoGuiBGPresenter::LegoGuiBGPresenter()
{
	Init();
}

LegoGuiBGPresenter::~LegoGuiBGPresenter()
{
	Destroy();
}

void
LegoGuiBGPresenter::Init()
{
    m_frameBitmap = NULL;
	m_gui = 0;
	m_state = e_starting;
}



MxResult
LegoGuiBGPresenter::Create(LegoGui *p_gui)
{
    MxResult result = FAILURE;

	m_gui = p_gui;
	m_transBitMaps = FALSE;
	SetDisplayZ(m_gui->GetBaseDisplayZ());

    if (MxMediaPresenter::Create() != SUCCESS) {
        goto done;
    }

    if (!LegoOmni::GetInstance()->GetVideoManager()) {
        goto done;
    }
	LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(this);
    
	result = SUCCESS;

done:
    return result;
}

void
LegoGuiBGPresenter::Destroy()
{
	if (LegoOmni::GetInstance()->GetVideoManager()) {
	    LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(this);
    }

    m_criticalSection.Enter();

    if (m_frameBitmap) {
        delete m_frameBitmap;
    }  
    Init();
    m_criticalSection.Leave();

}

void 
LegoGuiBGPresenter::StartingTickle()
{
    m_criticalSection.Enter();

	CreateFrameBitmap();
	SetBBox();

    m_criticalSection.Leave();
}

MxResult 
LegoGuiBGPresenter::Tickle()
{
    switch (m_state) {
    case e_ready:
    case e_starting:
        StartingTickle();
		m_state = e_repeating;
        // fall through
    case e_streaming:
    case e_repeating:
        break;
    }
    return SUCCESS;
}

MxResult
LegoGuiBGPresenter::PutData()
{
    m_criticalSection.Enter();
    switch (m_state) {
    case e_repeating:
		if (m_gui->GetState() == LegoGui::e_active)
			PutFrame();
        break;
    }
    m_criticalSection.Leave();
    return SUCCESS;
}

void 
LegoGuiBGPresenter::PutFrame()
{
    MxDisplaySurface* displaySurface =
		MxOmni::GetInstance()->GetVideoManager()->GetDisplaySurface();
    MxRegion* region = MxOmni::GetInstance()->GetVideoManager()->GetRegion();
	MxRect32 dataRect(m_gui->GetLoc(),
		MxSize32(m_frameBitmap->GetWidth(), m_frameBitmap->GetHeight()));
    MxRegionCursor cursor(region);
    MxRect32* regionRect;
    while (regionRect = cursor.Next(dataRect)) {
        if (m_transBitMaps) {
            displaySurface->TransBlt(	m_frameBitmap,
										regionRect->GetLeft()-m_gui->GetX(),
										regionRect->GetTop()-m_gui->GetY(),
										regionRect->GetLeft(),
										regionRect->GetTop(),
										regionRect->GetWidth(),
										regionRect->GetHeight());
        }
        else {
            displaySurface->Blt(	m_frameBitmap,
										regionRect->GetLeft()-m_gui->GetX(),
										regionRect->GetTop()-m_gui->GetY(),
										regionRect->GetLeft(),
										regionRect->GetTop(),
										regionRect->GetWidth(),
										regionRect->GetHeight());
        }
    }
}

void 
LegoGuiBGPresenter::CreateFrameBitmap()
{
    if (m_frameBitmap) {
        delete m_frameBitmap;
    }
    m_frameBitmap = new LegoBitmap();
    m_frameBitmap->Create(m_gui->GetBGBitmapInfo(), m_gui->GetBGBitmapImage());
}


MxBool
LegoGuiBGPresenter::IsHit(MxS32 p_x, MxS32 p_y)
{
//	return FALSE;

	return	p_x >= m_bBox.GetLeft() && p_x < m_bBox.GetRight() &&
			p_y >= m_bBox.GetTop() && p_y < m_bBox.GetBottom();
}

void
LegoGuiBGPresenter::SetBBox()
{
	m_bBox.SetLeft(m_gui->GetX());
	m_bBox.SetTop(m_gui->GetY());
	m_bBox.SetRight(m_gui->GetX()+m_frameBitmap->GetWidth());
	m_bBox.SetBottom(m_gui->GetY()+m_frameBitmap->GetHeight());

	LegoOmni::GetInstance()->GetVideoManager()->InvalidateRect(m_bBox);
}

void
LegoGuiBGPresenter::EndAction()
{
    MxMediaPresenter::EndAction();
}

