/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxNotificationManager.h"
#include "MxDSAction.h"
#include "LegoOmni.h"
#include "PPresent.h"
#include "LWorld.h"
#include "LActor.h"
#include "PathCtrl.h"
#include "LegoCameraController.h"
#include "LegoActorPresenter.h"
#include "LegoVideoManager.h"


// ----------------------------------------------------------------
// LegoWorld Class
LegoWorld::LegoWorld()
{
	m_pathController = NULL;
	m_cameraController = NULL;
    m_entityList = NULL;
}

LegoWorld::~LegoWorld()
{
	Destroy(TRUE);
}

MxResult 
LegoWorld::Create(const MxChar* p_name)
{
	MxResult result = LegoEntity::Create(p_name, NULL);
    if(result != SUCCESS)
        return result;
    
    m_entityList = new LegoEntityList(TRUE);
    if(!m_entityList)
        return FAILURE;
    
    if(!CreateCameraController())
        return FAILURE;
	
	return SUCCESS;
}

void LegoWorld::Destroy(MxBool p_fromDestructor)
{
    if (m_pathController) {
        delete m_pathController;
		m_pathController = NULL;
    }
    if (m_cameraController) {
        delete m_cameraController;
		m_cameraController = NULL;
    }

    if(m_entityList) {
        delete m_entityList;
        m_entityList = NULL;
    }

	if(!p_fromDestructor)
		LegoEntity::Destroy();
}

void LegoWorld::Destroy()
{
	Destroy(FALSE);
}

void LegoWorld::ProcessPresenterTree(MxPresenter *p_presenter)
{
	if(!p_presenter)
		return;

	if(p_presenter->IsA("LegoEntityPresenter"))
		((LegoEntityPresenter*)p_presenter)->SetWorld(this);

	else if(p_presenter->IsA("LegoPathStructPresenter"))
		((LegoPathStructPresenter*)p_presenter)->SetWorld(this);

	if(p_presenter->IsA("MxCompositePresenter")) 
	{
		MxPresenterListCursor cursor(((MxCompositePresenter*)p_presenter)->GetPresenterList());
		MxPresenter *subPresenter;
		while (cursor.Next(subPresenter))
			ProcessPresenterTree(subPresenter);  // RECURSION
	}
}

MxS32 LegoWorld::Notify(MxParam& p_param)
{
	switch (((MxNotificationParam&) p_param).GetNotification()) {
	case c_notificationEndAction:
	{
		MxPresenter *presenter;
		presenter = (MxPresenter*)((MxEndActionNotificationParam&) p_param).GetSender();
		if(presenter)
		{
			delete presenter;
		}
        delete ((MxEndActionNotificationParam&) p_param).GetAction();
	}
	break;
	case c_notificationNewPresenter:
	{
		MxCompositePresenter * presenter;
		presenter = (MxCompositePresenter*)((MxNewPresenterNotificationParam&) p_param).GetPresenter();
		ProcessPresenterTree(presenter);
	}
	break;
	}
	return SUCCESS;
}

LegoPathController * LegoWorld::CreatePathController()
{
    MxBool ok = FALSE;
    LegoPathController* pathController = NULL;

	if(m_pathController)
		delete m_pathController;
	m_pathController = NULL;

    if (!(pathController = new LegoPathController())) {
        goto done;
    }
    if (pathController->Create() != SUCCESS) {
        goto done;
    }

	m_pathController = pathController;
    ok = TRUE;

done:
    if (!ok) {
        if (pathController) {
            delete pathController;
            pathController = NULL;
        }
    }
    return pathController;
}

LegoCameraController * LegoWorld::CreateCameraController()
{
    MxBool ok = FALSE;
    LegoCameraController* cameraController = NULL;

	if(m_cameraController)
		delete m_cameraController;
	m_cameraController = NULL;

    if (!LegoOmni::GetInstance()->GetVideoManager()) {
        goto done;
    }
    if (!(cameraController = new LegoCameraController())) {
        goto done;
    }
    if (cameraController->Create() != SUCCESS) {
        goto done;
    }

	m_cameraController = cameraController;
    m_cameraController->OnViewSize(LegoOmni::GetInstance()->GetVideoManager()->GetParam().GetRect().GetWidth(),  LegoOmni::GetInstance()->GetVideoManager()->GetParam().GetRect().GetHeight());
	ok = TRUE;

done:
    if (!ok) {
        if (cameraController) {
            delete cameraController;
            cameraController = NULL;
        }
    }
    return cameraController;
}

LegoEntity* LegoWorld::GetEntity(const MxChar* p_entityName)
{
    if(m_entityList)
    {
        LegoEntity* entity;
        LegoEntityListCursor cursor(m_entityList);
        while(cursor.Next(entity))
        {
            if(!strcmp(entity->GetEntityName(), p_entityName))
                return entity;
        }
    }

    return NULL;
}
