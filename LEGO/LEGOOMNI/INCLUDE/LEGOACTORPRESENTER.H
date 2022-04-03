/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOACTORPRESENTER_H
#define __LEGOACTORPRESENTER_H

#include "MxPresenter.h"
#include "MxGeometry3D.h"
#include "LegoEntityPresenter.h"

class LegoActorPresenter : public LegoEntityPresenter {
protected:
    void ReadyTickle();
	
public:
	LegoActorPresenter();
	virtual ~LegoActorPresenter();
	virtual MxResult Tickle();
    virtual MxS32 Notify(MxParam& p_param);
    static const MxChar* HandlerClassName() { return "LegoActorPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoActorPresenter::ClassName())) || (LegoEntityPresenter::IsA(p_str)) ; }

};

typedef LegoActorPresenter * LegoActorPresenterPtr;

class LegoActorPresenterList : public MxPtrList<LegoActorPresenter> {
protected:
	MxS8 Compare(LegoActorPresenterPtr p_element1, LegoActorPresenterPtr p_element2) 
				{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoActorPresenterList(MxBool p_ownership=FALSE) : MxPtrList<LegoActorPresenter>(p_ownership) {}
};

class LegoActorPresenterListCursor : public MxPtrListCursor<LegoActorPresenter> {
public:
    LegoActorPresenterListCursor(LegoActorPresenterList* p_list) : MxPtrListCursor<LegoActorPresenter>(p_list) {}
};


#endif // __LEGOACTORPRESENTER_H

