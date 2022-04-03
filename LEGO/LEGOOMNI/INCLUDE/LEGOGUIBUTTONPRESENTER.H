/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOGUIBUTTONPRESENTER_H
#define __LEGOGUIBUTTONPRESENTER_H

// Omni header files
#include "MxPresenter.h"

// LegoOmni header files
#include "LegoGuiCtrlPresenter.h"

class LegoGuiButtonPresenter : public LegoGuiCtrlPresenter {
protected:
	enum {
	// NOTE: These values must not overlap with those
	// defined in MxPresenter.h
		e_rstate = e_guiStateBase,
		e_saction,
		e_sstate,
		e_raction,
	};

public:
//	LegoGuiButtonPresenter();
//	virtual ~LegoGuiButtonPresenter();
//	virtual void PutFrame();

//	virtual MxResult Create(LegoGuiPushButton *p_control);
	MxBool	GetNextFrameNum(MxBool p_stable);

	virtual MxResult Tickle();
	virtual MxResult RStateTickle();
	virtual MxResult SActionTickle();
	virtual MxResult SStateTickle();
	virtual MxResult RActionTickle();

    static const MxChar* HandlerClassName() { return "LegoGuiButtonPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
	virtual void SetValue(MxBool p_value);
};


#endif // __LEGOGUIBUTTONPRESENTER_H

