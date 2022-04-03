/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOGUIPRESENTER_H
#define __LEGOGUIPRESENTER_H

// Omni header files
#include "MxPresenter.h"
#include "MxDSChunk.h"

// LegoOmni header files
#include "LegoGui.h"
#include "LegoGuiBGPresenter.h"


class LegoGuiPresenter : public MxMediaPresenter {
protected:
	MxDSChunk			*m_chunk;
	LegoGui				*m_gui;
    LegoGuiBGPresenter	*m_background;
public:
	LegoGuiPresenter();
	virtual ~LegoGuiPresenter();
    virtual MxResult Create();
    void Init();
    virtual void Destroy();
	virtual void EndAction();
    virtual void ReadyTickle();
    virtual void StartingTickle();
    virtual void StreamingTickle();
    virtual void RepeatingTickle();
	virtual MxResult Tickle();
    virtual MxResult PutData() { return SUCCESS; }
	virtual MxS32		Notify(MxParam& p_param)
							{ return m_gui->Notify(p_param); }
	virtual MxBool		IsHit(MxS32 p_x, MxS32 p_y) { return TRUE; }

    static const MxChar* HandlerClassName() { return "LegoGuiPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
};


#endif // __LEGOGUIPRESENTER_H

