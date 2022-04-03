#ifndef __LEGOMODELPRESENTER_H
#define __LEGOMODELPRESENTER_H

#include "MxVideoPresenter.h"

class LegoROI;

class LegoModelPresenter : public MxVideoPresenter {
protected:
    LegoROI* m_roi;
    void Init();
    void Destroy(MxBool p_fromDestructor);
    MxResult CreateROI(MxDSChunk* p_chunk);
    virtual void StartingTickle();
    virtual void StreamingTickle();
public:
    LegoModelPresenter();
    ~LegoModelPresenter();
    virtual MxResult Create();
    virtual void Destroy();
	virtual MxResult Tickle();
    virtual MxResult PutData();
    static const MxChar* HandlerClassName() { return "LegoModelPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
	LegoROI* GetROI() {return m_roi;}
};

#endif // __LEGOMODELPRESENTER_H

