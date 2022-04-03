/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"
#include "PPresent.h"
#include "LFactory.h"
#include "LegoActorPresenter.h"
#include "LegoWorldPresenter.h"
#include "LegoGuiPresenter.h"
#include "LegoModelPresenter.h"
#include "LegoAnimPresenter.h"
#include "LegoPalettePresenter.h"
#include "LegoCarBuildPresenter.h"
#include "MxAtom.h"

LegoObjectFactory::LegoObjectFactory()
{
    MxAtomTable* atomTable = LegoOmni::GetInstance()->GetAtomTable();
	m_entityPresenterAtom = atomTable->LookUp("LegoEntityPresenter");
	m_actorPresenterAtom = atomTable->LookUp("LegoActorPresenter");
	m_worldPresenterAtom = atomTable->LookUp("LegoWorldPresenter");
	m_animPresenterAtom = atomTable->LookUp("LegoAnimPresenter");
	m_guiPresenterAtom = atomTable->LookUp("LegoGuiPresenter");
	m_modelPresenterAtom = atomTable->LookUp("LegoModelPresenter");
	m_palettePresenterAtom = atomTable->LookUp("LegoPalettePresenter");
	m_pathStructPresenterAtom = atomTable->LookUp("LegoPathStructPresenter");
	m_animPresenterAtom = atomTable->LookUp("LegoAnimPresenter");
	m_loopingAnimPresenterAtom = atomTable->LookUp("LegoLoopingAnimPresenter");
	m_locomotionAnimPresenterAtom = atomTable->LookUp("LegoLocomotionAnimPresenter");
	m_carBuildPresenterAtom = atomTable->LookUp("LegoCarBuildPresenter");
}

MxCore*
LegoObjectFactory::Create(MxConstCharString p_id)
{
    MxCore* object = NULL;
    MxU32 atom = LegoOmni::GetInstance()->GetAtomTable()->LookUp(p_id);
	if(atom == m_guiPresenterAtom) {
		object = new LegoGuiPresenter();
    }
	else if(atom == m_modelPresenterAtom) {
		object = new LegoModelPresenter();
    }
	else if(atom == m_entityPresenterAtom) {
		object = new LegoEntityPresenter();
    }
	else if(atom == m_actorPresenterAtom) {
		object = new LegoActorPresenter();
    }
	else if(atom == m_worldPresenterAtom) {
		object = new LegoWorldPresenter();
    }
	else if(atom == m_palettePresenterAtom) {
		object = new LegoPalettePresenter();
    }
	else if(atom == m_pathStructPresenterAtom) {
		object = new LegoPathStructPresenter();
    }
	else if(atom == m_animPresenterAtom) {
		object = new LegoAnimPresenter();
    }
	else if(atom == m_loopingAnimPresenterAtom) {
		object = new LegoLoopingAnimPresenter();
    }
	else if(atom == m_locomotionAnimPresenterAtom) {
		object = new LegoLocomotionAnimPresenter();
    }
	else if(atom == m_carBuildPresenterAtom) {
		object = new LegoCarBuildPresenter();
    }
	else {
		object = MxObjectFactory::Create(p_id);
    }
    
    assert(object!=NULL);
    
    return object;
}

void 
LegoObjectFactory::Destroy(MxCore* p_object)
{
    delete p_object;
}
