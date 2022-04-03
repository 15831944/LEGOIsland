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
#include "MxStreamController.h"
#include "MxTimer.h"
#include "LegoOmni.h"
#include "LegoGuiPresenter.h"
#include "LegoGui.h"
#include "MxTickleManager.h"


LegoGuiPresenter::LegoGuiPresenter()
{
	Init();
}

LegoGuiPresenter::~LegoGuiPresenter()
{
	Destroy();
}

void
LegoGuiPresenter::Init()
{
    m_background = 0;
	m_gui = 0;
	m_chunk = 0;
}



MxResult
LegoGuiPresenter::Create()
{
    MxResult result = FAILURE;
    if (MxMediaPresenter::Create() != SUCCESS) {
        goto done;
    }

	// Using TickleManager for Tickle().
    if (!LegoOmni::GetInstance()->GetTickleManager()) {
        goto done;
    }
	LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 100);
    
	result = SUCCESS;

done:
    return result;
}

void
LegoGuiPresenter::Destroy()
{
	if (LegoOmni::GetInstance()->GetTickleManager()) {
	    LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);
    }

	if (m_gui)
		delete m_gui;

    m_criticalSection.Enter();

    if (m_background) {
        delete m_background;
    }  
    Init();
    m_criticalSection.Leave();

}

void 
LegoGuiPresenter::ReadyTickle()
{
    m_criticalSection.Enter();
    m_chunk = m_subscriber->PopData();
    m_criticalSection.Leave();
    if (m_chunk && m_chunk->GetData()) 
	{
		// Process the header chunk.
		m_gui = new LegoGui;
		if (m_gui)
		{
			m_gui->SetBaseDisplayZ(GetDisplayZ());
			m_gui->ParseGuiData(m_chunk->GetData());
			m_gui->SetSourceId((MxAtomId)m_controller->GetSourceNameId());
			m_state = e_starting;
		}
    }
}

void 
LegoGuiPresenter::StartingTickle()
{
    m_criticalSection.Enter();
	m_gui->Tickle();

	// wait for Gui startup to finish, then create background presenter.
	if (m_gui->GetState() == LegoGui::e_waiting)
	{
		m_background = new LegoGuiBGPresenter;
		m_background->Create(m_gui);

		m_state = e_streaming;
	}
    m_criticalSection.Leave();
}

void 
LegoGuiPresenter::StreamingTickle()
{
	m_state = e_repeating;
}

void 
LegoGuiPresenter::RepeatingTickle()
{
	// Process second and subsequent data chunks.
	// We are expecting only the end of stream chunk!!!
    m_criticalSection.Enter();
    MxDSChunk* chunk = m_subscriber->PopData();
	if(chunk && (chunk->GetChunkFlags() & DS_CHUNK_END_OF_STREAM))
	{
        m_subscriber->FreeDataChunk(chunk);
	}

	// This is where all interactive Gui handling will go.
	// The Gui presenter will be in the repeating tickle state for it's
	// usefull life. This code should call EndAction() to terminate the Gui.
	m_gui->Tickle();

	if (m_gui->GetState() == LegoGui::e_complete)
	{
		if (m_chunk)
			m_subscriber->FreeDataChunk(m_chunk);
		EndAction();
	}
    m_criticalSection.Leave();
}

MxResult 
LegoGuiPresenter::Tickle()
{
    switch (m_state) {
    case e_ready:
        ReadyTickle();
        if (m_state != e_starting) {
            break;
        }
        // fall through
    case e_starting:
        StartingTickle();
        if (m_state != e_streaming) {
            break;
        }
        // fall through
    case e_streaming:
        StreamingTickle();
        if (m_state != e_repeating) {
            break;
        }
        // fall through
    case e_repeating:
        RepeatingTickle();
        break;
    }
    return SUCCESS;
}

void
LegoGuiPresenter::EndAction()
{
    MxMediaPresenter::EndAction();
}

