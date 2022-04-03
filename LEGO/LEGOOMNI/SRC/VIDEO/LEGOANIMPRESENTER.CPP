#include "StdLego.h"
#include "LegoAnimPresenter.h"
#include "LegoStorage.h"
#include "LegoAnim.h"
#include "LegoROI.h"
#include "LegoOmni.h"
#include "MxDSSubscriber.h"
#include "MxTimer.h"

LegoAnimPresenter::LegoAnimPresenter()
{
    Init();
}

LegoAnimPresenter::~LegoAnimPresenter()
{
    Destroy(TRUE);
}

void 
LegoAnimPresenter::Init()
{
    m_anim = NULL;
}

void 
LegoAnimPresenter::Destroy(MxBool p_fromDestructor)
{
    m_criticalSection.Enter();
    if (m_anim) {
        delete m_anim;
    }
    Init();
    m_criticalSection.Leave();
    if (!p_fromDestructor) {
        MxVideoPresenter::Destroy();
    }
}

MxResult 
LegoAnimPresenter::CreateAnim(MxDSChunk* p_chunk)
{
    MxResult result = FAILURE;

    LegoMemory storage(p_chunk->GetData());
    LegoU32 numAnims;
    if (storage.Read(&numAnims, sizeof(numAnims)) != SUCCESS) {
        goto done;
    }   
    if (!(m_anim = new LegoAnim())) {
        goto done;
    }
    if (m_anim->Read(&storage) != SUCCESS) {
        goto done;
    }

    result = SUCCESS;

done:
    if (result != SUCCESS) {
        if (m_anim) {
            delete m_anim;
        }
    }
    return result;
}

void 
LegoAnimPresenter::PutFrame()
{
    if (m_entity && m_entity->GetROI()) {
        LegoTime time = LegoOmni::GetInstance()->GetTimer()->GetTime();
        m_entity->GetROI()->SetFrame(m_anim, time);
    }
}

void 
LegoAnimPresenter::ReadyTickle()
{
    m_state = e_starting;
}

void 
LegoAnimPresenter::StartingTickle()
{
    MxDSChunk* chunk = m_subscriber->PeekData();
    if (chunk && LegoOmni::GetInstance()->GetTimer()->GetTime() >= chunk->GetTimeTicks()) {
        chunk = m_subscriber->PopData();
        MxResult result = CreateAnim(chunk);
        m_subscriber->FreeDataChunk(chunk);
        if (result == SUCCESS) {
            m_state = e_streaming;  
        }
        else {
            EndAction();
        }
    }
}

void 
LegoAnimPresenter::StreamingTickle()
{
    if (LegoOmni::GetInstance()->GetTimer()->GetTime() > m_anim->GetDuration()) {
        EndAction();
    }
}

MxResult 
LegoAnimPresenter::Create()
{
    return MxVideoPresenter::Create();
}

void 
LegoAnimPresenter::Destroy()
{
    Destroy(FALSE);
}

void 
LegoLoopingAnimPresenter::StreamingTickle()
{
    if (m_action->GetDuration() != INDEFINITE && LegoOmni::GetInstance()->GetTimer()->GetTime() > m_action->GetDuration()) {
        EndAction();
    }
}

void 
LegoLoopingAnimPresenter::PutFrame()
{
    if (m_entity && m_entity->GetROI()) {
        LegoTime time = LegoOmni::GetInstance()->GetTimer()->GetTime() % m_anim->GetDuration();
        m_entity->GetROI()->SetFrame(m_anim, time);
    }
}

LegoLocomotionAnimPresenter::LegoLocomotionAnimPresenter()
{
    Init();
}

LegoLocomotionAnimPresenter::~LegoLocomotionAnimPresenter()
{
    Destroy(TRUE);
}

void 
LegoLocomotionAnimPresenter::Init()
{
    m_numTranslationKeys = 0;
    m_translationKeys = NULL;
    m_prevPhysicalTime = -1;
    m_prevAnimTime = -1;
}

void 
LegoLocomotionAnimPresenter::Destroy(MxBool p_fromDestructor)
{
    m_criticalSection.Enter();
    if (m_translationKeys) {
        delete m_translationKeys;
    }
    Init();
    m_criticalSection.Leave();
    if (!p_fromDestructor) {
        LegoLoopingAnimPresenter::Destroy();
    }
}

MxResult 
LegoLocomotionAnimPresenter::CreateAnim(MxDSChunk* p_chunk)
{
    MxResult result = LegoLoopingAnimPresenter::CreateAnim(p_chunk);
    if (result != SUCCESS) {
        return result;
    }
    LegoAnimNodeData* data = (LegoAnimNodeData*) m_anim->GetRoot()->GetData();
    m_numTranslationKeys = data->GetNumTranslationKeys();
    m_translationKeys = data->GetTranslationKeys();
    data->SetNumTranslationKeys(0);
    data->SetTranslationKeys(NULL);
    return SUCCESS;
}

MxResult 
LegoLocomotionAnimPresenter::Create()
{
    return LegoLoopingAnimPresenter::Create();
}

void 
LegoLocomotionAnimPresenter::Destroy()
{
    Destroy(FALSE);
}

void 
LegoLocomotionAnimPresenter::PutFrame()
{
    LegoTime curPhysicalTime;
    LegoTime animTime = -1;
    LegoFloat speed;
    LegoTime elapsedPhysicalTime;
    LegoFloat distance;
    LegoU32 i;
    LegoFloat d1;
    LegoFloat d2;
    LegoTime t1;
    LegoTime t2;
    LegoFloat d;

    if (m_entity && m_entity->GetROI()) {
        curPhysicalTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
        if (m_prevPhysicalTime == -1 || m_prevAnimTime == -1) {
            animTime = 0;
        }
        else {
            speed = fabs(m_entity->GetWorldSpeed());
            elapsedPhysicalTime = curPhysicalTime - m_prevPhysicalTime;
            distance = speed * elapsedPhysicalTime / 1000;
            for (
                i = 1; 
                m_prevAnimTime > m_translationKeys[i].GetTime(); 
                i++
            );
            if (m_prevAnimTime < m_translationKeys[i].GetTime()) {
                d1 = GetDistance(i - 1);
                d2 = GetDistance(i);
                t1 = m_translationKeys[i - 1].GetTime();
                t2 = m_translationKeys[i].GetTime();
                d = (d2 - d1) * (t2 - m_prevAnimTime) / (t2 - t1);
                if (d < distance) {
                    animTime = CalculateAnimTime(i, distance - d);
                }
                else {
                    animTime = m_prevAnimTime + (t2 - m_prevAnimTime) * distance / d;
                }
            }
            else {
                animTime = CalculateAnimTime(i, distance);
            }
        }
        m_entity->GetROI()->SetFrame(m_anim, animTime);
        m_prevPhysicalTime = curPhysicalTime;
        m_prevAnimTime = animTime;
    }
}

LegoFloat
LegoLocomotionAnimPresenter::GetDistance(LegoU32 p_i)
{
    LegoFloat x = m_translationKeys[p_i].GetX();
    LegoFloat y = m_translationKeys[p_i].GetY();
    LegoFloat z = m_translationKeys[p_i].GetZ();
    return sqrt(x * x + y * y + z * z);
}

LegoTime
LegoLocomotionAnimPresenter::CalculateAnimTime(LegoU32 p_i, LegoFloat p_distance)
{
    LegoTime animTime;
    LegoFloat d1;
    LegoFloat d2;
    LegoTime t1;
    LegoTime t2;
    LegoFloat d;

    for (;;) {
        if (++p_i >= m_numTranslationKeys) {
            p_i = 1;
        }
        d1 = GetDistance(p_i - 1);
        d2 = GetDistance(p_i);
        d = d2 - d1;
        if (d > p_distance) {
            break;
        }
        p_distance -= d;
    }
    t1 = m_translationKeys[p_i - 1].GetTime();
    t2 = m_translationKeys[p_i].GetTime();
    animTime = t1 + (t2 - t1) * p_distance / d;
    return animTime;
}