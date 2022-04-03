/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxVideoManager.h"
#include "MxDisplaySurface.h"
#include "MxDSSubscriber.h"
#include "MxDSAction.h"
#include "MxGeometry.h"
#include "LegoOmni.h"
#include "PathCtrl.h"
#include "PPresent.h"
#include "LActor.h"

LegoPathStructPresenter::LegoPathStructPresenter()
{
	Init();
}

void LegoPathStructPresenter::Init()
{
	m_world = NULL;
}

LegoPathStructPresenter::~LegoPathStructPresenter()
{
	Destroy(TRUE);
}

MxResult
LegoPathStructPresenter::Create()
{
    MxResult result = FAILURE;
    if (!LegoOmni::GetInstance()->GetVideoManager()) {
        goto done;
    }
    if (MxMediaPresenter::Create() != SUCCESS) {
        goto done;
    }
	LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(this);
    
	result = SUCCESS;

done:
    return result;
}

void
LegoPathStructPresenter::Destroy(MxBool p_fromDestructor)
{
	if (LegoOmni::GetInstance()->GetVideoManager()) {
	    LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(this);
    }
	{
		AUTOLOCK(m_criticalSection);
		Init();
	}
    if (!p_fromDestructor) {
        MxMediaPresenter::Destroy();
    }
}

void
LegoPathStructPresenter::Destroy()
{
	Destroy(FALSE);
}

void 
LegoPathStructPresenter::ReadyTickle()
{
    MxDSChunk* chunk;
	if(m_world) // wait for this to be set in world's Notify()
	{
		chunk = m_subscriber->PopData();
	    if (chunk) 
		{
			// Process the header chunk.
			LegoPaths pathsData;
			pathsData.SetData(chunk->GetData());
			pathsData.SetDataSize(chunk->GetDataSize());
			LegoPathController *pathController = m_world->CreatePathController();
			if(pathController)
				pathController->Create(&pathsData, m_action->GetLocation());
			m_subscriber->FreeDataChunk(chunk);
			m_state = e_starting;
			pathsData.SetData(NULL);
			pathsData.SetDataSize(0);
		}
	}
}

void 
LegoPathStructPresenter::StartingTickle()
{
	// Process the first data chunk.
	m_state = e_streaming;
}

void 
LegoPathStructPresenter::StreamingTickle()
{
	// Process second and subsequent data chunks.
    MxDSChunk* chunk = m_subscriber->PopData();
	if(chunk)
	{
		if(chunk->GetChunkFlags() & DS_CHUNK_END_OF_STREAM)
             m_state = e_repeating;
		m_subscriber->FreeDataChunk(chunk);
	}
}

void 
LegoPathStructPresenter::RepeatingTickle()
{
    if (m_action->GetDuration() != INDEFINITE) 
	{
        EndAction();
    }
}

MxResult 
LegoPathStructPresenter::Tickle()
{
    AUTOLOCK(m_criticalSection);

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

MxResult
LegoPathStructPresenter::PutData()
{
    AUTOLOCK(m_criticalSection);

	switch (m_state) {
    case e_streaming:
    case e_repeating:
        break;
    }
    return SUCCESS;
}

void
LegoPathStructPresenter::EndAction()
{
    MxMediaPresenter::EndAction();
}

