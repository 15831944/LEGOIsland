/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOGUICTRLPRESENTER_H
#define __LEGOGUICTRLPRESENTER_H

// Omni header files
#include "MxPresenter.h"
#include "LegoBitmap.h"

// LegoOmni header files
#include "LegoGuiControl.h"

#define NEW_FRAME 255

class LegoGuiCtrlPresenter : public MxPresenter {
protected:
	enum {
        e_idle = 0,
		e_ready,
        e_active,
		e_done,
		e_guiStateBase,
	};
    LegoBitmap			*m_frameBitmap;
	MxPoint32			m_frameLoc;
	MxRect32			m_bBox;
	MxU8				m_currentFrameNum;
	MxU8				m_numFrames;
	MxTime				m_frameTime;
	MxTime				m_startTime;
	MxBool				m_looping;
	MxS16Ptr			m_bitmapArray;
	MxBool				m_advanceState;
	LegoGuiControl		*m_control;
	MxBool				m_transBitMaps;
	MxS32				m_targetState;
	MxBool				m_holdState;
	MxBool				m_bitmapNoBlt;

public:
	LegoGuiCtrlPresenter();
	virtual ~LegoGuiCtrlPresenter();
    void Init();
    virtual void Destroy();
	virtual void EndAction();
	virtual MxResult Create(LegoGuiControl *p_control);
	virtual MxResult Tickle() = 0;
    virtual MxResult PutData();
	virtual void PutFrame();
	virtual void CreateFrameBitmap();
	virtual void SetActionInfo(LegoGuiControl::LegoGuiActionPtr p_action);
	void	SetBBox();
	virtual MxS32		Notify(MxParam& p_param);
	virtual MxBool		IsHit(MxS32 p_x, MxS32 p_y);
	virtual void		Refresh();


    static const MxChar* HandlerClassName() { return "LegoGuiCtrlPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }

	virtual void SetValue(MxBool p_value) {}
	virtual void SetValue(MxS32 p_value) {}
	virtual void SetValue(MxCharString p_value) {}

};


#endif // __LEGOGUICTRLPRESENTER_H

