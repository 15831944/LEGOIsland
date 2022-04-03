/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOBUILD_H
#define __LEGOBUILD_H

#include "LWorld.h"

//===========================================================================
// class LegoBuild

class LegoBuild : public LegoWorld
{
protected:
    void Destroy(MxBool p_fromDestructor);
public:
    LegoBuild();
    virtual ~LegoBuild();
    virtual MxResult Create(const MxChar* p_name);
    virtual void Destroy();

    virtual const MxChar* ClassName() { return "LegoBuild"; }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoBuild::ClassName())) || (LegoWorld::IsA(p_str)); }
};


//===========================================================================
// class LegoCarBuild

class LegoCarBuild : public LegoBuild
{
    enum 
    { 
        e_idle,
        e_select, 
        e_repeat 
    };

protected:
    LegoEntity* m_selectedPart;
    void SelectPart();
    void UnselectPart() { m_selectedPart = NULL; }
    void RotateSelectedPart();
    void DragSelectedPart(MxS32 p_x, MxS32 p_y);

    MxS32 m_state;

    void Destroy(MxBool p_fromDestructor);
public:
    LegoCarBuild();
    virtual ~LegoCarBuild();
    virtual MxResult Create(const MxChar* p_name);
    virtual void Destroy();
	virtual MxResult Tickle();
	virtual MxS32 Notify(MxParam &p_param);

    virtual const MxChar* ClassName() { return "LegoCarBuild"; }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, ClassName())) || (LegoBuild::IsA(p_str)); }
};

#endif // __LEGOBUILD_H
