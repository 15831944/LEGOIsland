/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __PPRESENT_H
#define __PPRESENT_H

// Omni header files
#include "MxPresenter.h"
// LegoOmni header files
#include "LWorld.h"
#include "LActor.h"
#include "LegoActorPresenter.h"


class LegoPathStructPresenter : public MxMediaPresenter {
protected:
	LegoWorld* m_world;

    void Destroy(MxBool p_fromDestructor);
	void Init();

    void ReadyTickle();
    void StartingTickle();
    void StreamingTickle();
    void RepeatingTickle();

public:
	LegoPathStructPresenter();
	virtual ~LegoPathStructPresenter();
    virtual MxResult Create();
    virtual void Destroy();
	virtual void EndAction();
	virtual MxResult Tickle();
    virtual MxResult PutData();
    static const MxChar* HandlerClassName() { return "LegoPathStructPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoPathStructPresenter::ClassName())) || (MxPresenter::IsA(p_str)) ; }

	void SetWorld(LegoWorld* p_world) {m_world = p_world;}
	LegoWorld* GetWorld() {return m_world;}
};


#endif // __PPRESENT_H

