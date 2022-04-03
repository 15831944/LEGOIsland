#include "StdLego.h"
#include "LegoModelPresenter.h"
#include "LegoOmni.h"
#include "MxTimer.h"
#include "MxDSSubscriber.h"
#include "LegoVideoManager.h"
#include "LegoStorage.h"
#include "LegoROI.h"
#include "LegoAnim.h"
#include "Lego3DManager.h"
#include "MxGeometry3D.h"
#include "MxDSAction.h"
#include "LegoActorPresenter.h"
#include "LegoEntityPresenter.h"
#include "LegoContainer.h"
#include "LActor.h"
#include "Version.h"

#ifdef USE_SMART_HEAP
#include "Smrtheap.hpp"
#ifdef MEM_DEBUG
#include "memtrace.h"
#endif // MEM_DEBUG
#endif // USE_SMART_HEAP


LegoModelPresenter::LegoModelPresenter()
{
    Init();
}

LegoModelPresenter::~LegoModelPresenter()
{
    Destroy(TRUE);
}

void 
LegoModelPresenter::Init()
{
    m_roi = NULL;
}

void 
LegoModelPresenter::Destroy(MxBool p_fromDestructor)
{
    m_criticalSection.Enter();
    Init();
    m_criticalSection.Leave();
    if (!p_fromDestructor) {
        MxVideoPresenter::Destroy();
    }
}

MxResult 
LegoModelPresenter::Create()
{
    return MxVideoPresenter::Create();
}

void 
LegoModelPresenter::Destroy()
{
    Destroy(FALSE);
}

MxResult
LegoModelPresenter::CreateROI(MxDSChunk* p_chunk)
{
    MxResult result = FAILURE;
    LegoU32 numROIs;
    Mx3DPointDouble vect;
    LegoMemory storage(p_chunk->GetData());
    LegoAnim anim;
    LegoU32 version;
	Matrix4 mat;

#if defined(_DEBUG) && defined(USE_SMART_HEAP)
    MxTrace("Heap> LegoModelPresenter::CreateROI (before): %u bytes\n", GetHeapSize());
#endif // _DEBUG && USE_SMART_HEAP
#ifdef MEM_DEBUG
            dbgStartTracing("MemTrace.Log");
#endif // MEM_DEBUG

    if (m_roi) {
        delete m_roi;
    }
    if (!(m_roi = new LegoROI(((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->GetRenderer()))) {
        goto done;
    }
    if (storage.Read(&version, sizeof(version)) != SUCCESS) {
        goto done;
    }
    if (version != MODEL_VERSION) {
        goto done;
    }
    if (storage.Read(&numROIs, sizeof(numROIs)) != SUCCESS) {
        goto done;
    }
    if (anim.Read(&storage) != SUCCESS) {
        goto done;
    } 
    if (m_roi->Read(((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->GetRenderer(), ((LegoOmni*) LegoOmni::GetInstance())->GetViewLODListManager(), &storage) != SUCCESS) {
        goto done;
    }
    if (m_roi->SetFrame(&anim, 0) != SUCCESS) {
        goto done;
    }

	// Get scripted location, direction and up vectors

	CalcLocalTransform(	Vector3(m_action->GetLocation().GetX(), 
								m_action->GetLocation().GetY(), 
								m_action->GetLocation().GetZ()),
						Vector3(m_action->GetDirection().GetX(),
								m_action->GetDirection().GetY(),
								m_action->GetDirection().GetZ()),
						Vector3(m_action->GetUp().GetX(), 
								m_action->GetUp().GetY(), 
								m_action->GetUp().GetZ()),
						mat);
	m_roi->SetLocalTransform(mat);

#if CLEANUP
	m_roi->SetPosition(::Vector3(m_action->GetLocation().GetX(), m_action->GetLocation().GetY(), m_action->GetLocation().GetZ()));
	m_roi->SetDirection(::Vector3(m_action->GetDirection().GetX(), m_action->GetDirection().GetY(), m_action->GetDirection().GetZ()));
	m_roi->SetUp(::Vector3(m_action->GetUp().GetX(), m_action->GetUp().GetY(), m_action->GetUp().GetZ()));
#endif

    result = SUCCESS;

done:
    if (result != SUCCESS) {
        if (m_roi) {
            delete m_roi;
            m_roi = NULL;
        }
    }
#if defined(_DEBUG) && defined(USE_SMART_HEAP)
    MxTrace("Heap> LegoModelPresenter::CreateROI (after): %u bytes\n", GetHeapSize());
#endif // _DEBUG && USE_SMART_HEAP
#ifdef MEM_DEBUG
            dbgEndTracing();
#endif // MEM_DEBUG
    return result;
}

void 
LegoModelPresenter::StartingTickle()
{
    MxDSChunk* chunk = m_subscriber->PeekData();
	if(m_parent && m_parent->IsA("LegoActorPresenter"))
	{	// wait for parent presenter to get ready
		if(((LegoActorPresenter*)m_parent)->GetState() <= e_ready)
			return;
	}
	else if(m_parent && m_parent->IsA("LegoEntityPresenter"))
	{	// wait for parent presenter to get ready
		if(((LegoEntityPresenter*)m_parent)->GetState() <= e_ready)
			return;
	}
    if (chunk && MxOmni::GetInstance()->GetTimer()->GetTime() >= chunk->GetTimeTicks()) {
        m_state = e_streaming;
    }
}

void 
LegoModelPresenter::StreamingTickle()
{
    MxDSChunk* chunk = m_subscriber->PopData();
    MxResult result = CreateROI(chunk);
    m_subscriber->FreeDataChunk(chunk);
    if (result == SUCCESS) {
	    m_state = e_freezing;
    }
    else {
        EndAction();
    }
}

MxResult 
LegoModelPresenter::Tickle()
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
LegoModelPresenter::PutData()
{
    m_criticalSection.Enter();
    switch (m_state) {
    case e_freezing:
        if (m_roi) {
            ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->Add(*m_roi);
            ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->Moved(*m_roi);
			if(m_parent && m_parent->IsA("LegoEntityPresenter"))
				((LegoEntityPresenter*)m_parent)->GetEntity()->SetROI(m_roi);
        }
        EndAction();
        break;
    }
    m_criticalSection.Leave();
    return SUCCESS;
}

