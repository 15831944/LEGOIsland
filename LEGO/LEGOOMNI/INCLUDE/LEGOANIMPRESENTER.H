#ifndef __LEGOANIMPRESENTER_H
#define __LEGOANIMPRESENTER_H

#include "LegoTypes.h"
#include "MxVideoPresenter.h"

class LegoAnim;
class LegoEntity;
class LegoTranslationKey;

class LegoAnimPresenter : public MxVideoPresenter {
protected:
    LegoAnim* m_anim;
    LegoEntity* m_entity;
    void Init();
    void Destroy(MxBool p_fromDestructor);
    virtual MxResult CreateAnim(MxDSChunk* p_chunk);
    virtual void PutFrame();
    virtual void ReadyTickle();
    virtual void StartingTickle();
    virtual void StreamingTickle();
public:
    LegoAnimPresenter();
    ~LegoAnimPresenter();
    void SetEntity(LegoEntity* p_entity) { m_entity = p_entity; }
    virtual MxResult Create();
    virtual void Destroy();
    static const MxChar* HandlerClassName() { return "LegoAnimPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
};

class LegoLoopingAnimPresenter : public LegoAnimPresenter {
protected:
    virtual void PutFrame();
    virtual void StreamingTickle();
};

class LegoLocomotionAnimPresenter : public LegoLoopingAnimPresenter {
protected:
    LegoU32 m_numTranslationKeys;
    LegoTranslationKey* m_translationKeys;
    LegoTime m_prevPhysicalTime;
    LegoTime m_prevAnimTime;
    void Init();
    void Destroy(MxBool p_fromDestructor);
    virtual MxResult CreateAnim(MxDSChunk* p_chunk);
    virtual void PutFrame();
    LegoFloat GetDistance(LegoU32 p_i);
    LegoTime CalculateAnimTime(LegoU32 p_i, LegoFloat p_distance);
public:
    LegoLocomotionAnimPresenter();
    ~LegoLocomotionAnimPresenter();
    virtual MxResult Create();
    virtual void Destroy();
};


#endif // __LEGOANIMPRESENTER_H


