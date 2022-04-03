/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LFACTORY_H
#define __LFACTORY_H

#include "MxObjectFactory.h"

class LegoObjectFactory : public MxObjectFactory {
	MxU32 m_entityPresenterAtom;
	MxU32 m_actorPresenterAtom;
	MxU32 m_worldPresenterAtom;
	MxU32 m_guiPresenterAtom;
	MxU32 m_modelPresenterAtom;
    MxU32 m_palettePresenterAtom;
	MxU32 m_pathStructPresenterAtom;
	MxU32 m_animPresenterAtom;
	MxU32 m_loopingAnimPresenterAtom;
	MxU32 m_locomotionAnimPresenterAtom;
    MxU32 m_carBuildPresenterAtom;
public:
    LegoObjectFactory();
    virtual MxCore* Create(MxConstCharString p_id);
    virtual void Destroy(MxCore* p_object);
};

#endif // __LFACTORY_H

