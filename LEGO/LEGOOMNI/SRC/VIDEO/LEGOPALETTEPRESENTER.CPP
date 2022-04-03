#include "StdLego.h"
#include "LegoPalettePresenter.h"
#include "LegoOmni.h"
#include "LegoStorage.h"
#include "MxPalette.h"
#include "MxVideoManager.h"
#include "MxDSSubscriber.h"
#include "MxTimer.h"

LegoPalettePresenter::LegoPalettePresenter()
{
    Init();
}

LegoPalettePresenter::~LegoPalettePresenter()
{
    Destroy(TRUE);
}

void 
LegoPalettePresenter::Init()
{
    m_palette = NULL;
}

void 
LegoPalettePresenter::Destroy(MxBool p_fromDestructor)
{
    m_criticalSection.Enter();
    if (m_palette) {
        delete m_palette;
    }
    Init();
    m_criticalSection.Leave();
    if (!p_fromDestructor) {
        MxVideoPresenter::Destroy();
    }
}

MxResult 
LegoPalettePresenter::Create()
{
    return MxVideoPresenter::Create();
}

void 
LegoPalettePresenter::Destroy()
{
    Destroy(FALSE);
}

MxResult
LegoPalettePresenter::CreatePalette(MxDSChunk* p_chunk)
{
    MxResult result = FAILURE;
    RGBQUAD colors[256];
    BITMAPINFOHEADER header;
    LegoMemory storage(p_chunk->GetData());


    if (storage.Read(&header, sizeof(header)) != SUCCESS) {
        goto done;
    }
    if (storage.Read(colors, sizeof(colors)) != SUCCESS) {
        goto done;
    }   
    if (!(m_palette = new MxPalette())) {
        goto done;
    }
    if (m_palette->Create(colors) != SUCCESS) {
        goto done;
    }

    result = SUCCESS;

done:
    if (result != SUCCESS) {
        if (m_palette) {
            delete m_palette;
            m_palette = NULL;
        }
    }
    return result;
}

void 
LegoPalettePresenter::StartingTickle()
{
    MxDSChunk* chunk = m_subscriber->PeekData();
    if (chunk && MxOmni::GetInstance()->GetTimer()->GetTime() >= chunk->GetTimeTicks()) {
        m_state = e_streaming;
    }
}

void 
LegoPalettePresenter::StreamingTickle()
{
    MxDSChunk* chunk = m_subscriber->PopData();
    MxResult result = CreatePalette(chunk);
    m_subscriber->FreeDataChunk(chunk);
    if (result == SUCCESS) {
	    m_state = e_freezing;
    }
    else {
        EndAction();
    }
}

MxResult 
LegoPalettePresenter::Tickle()
{
    m_criticalSection.Enter();
    switch (m_state) {
    case e_ready:
        m_state = e_starting;
        // fall through
    case e_starting:
        StartingTickle();
        if (m_state != e_streaming) {
            break;
        }
        // fall through
    case e_streaming:
        StreamingTickle();
        break;
    case e_freezing:
        break;
    }
    m_criticalSection.Leave();
    return SUCCESS;
}

MxResult 
LegoPalettePresenter::PutData()
{
    m_criticalSection.Enter();
    switch (m_state) {
    case e_freezing:
        if (m_palette) {
            LegoOmni::GetInstance()->GetVideoManager()->RealizePalette(m_palette);
        }
        EndAction();
        break;
    }
    m_criticalSection.Leave();
    return SUCCESS;
}

