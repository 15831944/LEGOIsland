/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOWORLDPRESENTER_H
#define __LEGOWORLDPRESENTER_H

#include "MxPresenter.h"
#include "MxGeometry3D.h"
#include "LegoEntityPresenter.h"

class LegoWorld;

class LegoWorldPresenter : public LegoEntityPresenter {
protected:
    void ReadyTickle();
	
public:
	LegoWorldPresenter();
	virtual ~LegoWorldPresenter();
    static const MxChar* HandlerClassName() { return "LegoWorldPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoWorldPresenter::ClassName())) || (LegoEntityPresenter::IsA(p_str)) ; }
};

typedef LegoWorldPresenter * LegoWorldPresenterPtr;

class LegoWorldPresenterList : public MxPtrList<LegoWorldPresenter> {
protected:
	MxS8 Compare(LegoWorldPresenterPtr p_element1, LegoWorldPresenterPtr p_element2) 
				{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoWorldPresenterList(MxBool p_ownership=FALSE) : MxPtrList<LegoWorldPresenter>(p_ownership) {}
};

class LegoWorldPresenterListCursor : public MxPtrListCursor<LegoWorldPresenter> {
public:
    LegoWorldPresenterListCursor(LegoWorldPresenterList* p_list) : MxPtrListCursor<LegoWorldPresenter>(p_list) {}
};


#endif // __LEGOWORLDPRESENTER_H

