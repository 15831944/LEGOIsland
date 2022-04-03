/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOGUIBGPRESENTER_H
#define __LEGOGUIBGPRESENTER_H

// Omni header files
#include "MxPresenter.h"
#include "MxDSChunk.h"

// LegoOmni header files
#include "LegoBitmap.h"
#include "LegoGui.h"


class LegoGuiBGPresenter : public MxMediaPresenter {
protected:
	LegoGui		*m_gui;
    LegoBitmap	*m_frameBitmap;
	MxRect32	m_bBox;
	MxBool		m_transBitMaps;
public:
	LegoGuiBGPresenter();
	virtual ~LegoGuiBGPresenter();
    virtual MxResult Create(LegoGui *p_gui);
    void Init();
    virtual void Destroy();
	virtual void EndAction();
    virtual void StartingTickle();
	virtual MxResult Tickle();
    virtual MxResult PutData();
	virtual void PutFrame();
	void CreateFrameBitmap();
	virtual MxBool	IsHit(MxS32 p_x, MxS32 p_y);
	void			SetBBox();

    static const MxChar* HandlerClassName() { return "LegoGuiBGPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
};


#endif // __LEGOGUIBGPRESENTER_H

