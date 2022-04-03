/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOGUISTRINGPRESENTER_H
#define __LEGOGUISTRINGPRESENTER_H

// Omni header files
#include "MxPresenter.h"

// LegoOmni header files
#include "LegoGuiCtrlPresenter.h"

class LegoGuiStringPresenter : public LegoGuiCtrlPresenter {
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
//	LegoGuiStringPresenter();
//	virtual ~LegoGuiStringPresenter();
//	virtual void PutFrame();

//	virtual MxResult Create(LegoGuiString *p_control);
	MxBool	GetNextFrameNum(MxBool p_stable);
	virtual void CreateFrameBitmap();


	virtual MxResult Tickle();
	virtual MxResult RStateTickle();
	virtual MxResult SActionTickle();
	virtual MxResult SStateTickle();
	virtual MxResult RActionTickle();

    static const MxChar* HandlerClassName() { return "LegoGuiStringPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
	virtual void SetValue(MxCharString p_value) { ((LegoGuiString *)m_control)->SetValue(p_value); }
	virtual void SetValue(MxS32 p_value) { ((LegoGuiString *)m_control)->SetValue(p_value); }
};


#endif // __LEGOGUISTRINGPRESENTER_H

