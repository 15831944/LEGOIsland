/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOCARBUILDPRESENTER_H
#define __LEGOCARBUILDPRESENTER_H

#include "LegoWorldPresenter.h"

class LegoCarBuildPresenter : public LegoWorldPresenter 
{
protected:
    virtual void ReadyTickle();

public:
    static const MxChar* HandlerClassName() { return "LegoCarBuildPresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, ClassName())) || (LegoWorldPresenter::IsA(p_str)); }
};

#endif // __LEGOCARBUILDPRESENTER_H

