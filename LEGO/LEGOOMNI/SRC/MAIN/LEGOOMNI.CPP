/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"
#include "LFactory.h"
#include "PathCtrl.h"
#include "LegoVideoManager.h"
#include "LegoInputManager.h"
#include "LegoContainer.h"
#include "MxTickleManager.h"
#include "ViewLODList.h"

#ifdef USE_SMART_HEAP
#include "Smrtheap.hpp"
#ifdef MEM_DEBUG
#include "memtrace.h"
#endif // MEM_DEBUG
#endif // USE_SMART_HEAP


LegoOmni::LegoOmni()
{
	Init();
}

LegoOmni::~LegoOmni()
{
	Destroy();
}

void
LegoOmni::Init()
{
	MxOmni::Init();
	m_inputManager = NULL;
    m_viewLODListManager = NULL;
    m_textureContainer = NULL;
    m_worldList = NULL;
}

void
LegoOmni::Destroy()
{
    AUTOLOCK(m_mainCS);    

    if(m_worldList) {
        delete m_worldList;
    }
    if (m_textureContainer) {
        delete m_textureContainer;
    }
    if (m_viewLODListManager) {
        delete m_viewLODListManager;
    }
    if (m_inputManager) {
        delete m_inputManager;
		m_inputManager = 0;
    }
	MxOmni::Destroy();
}

MxResult 
LegoOmni::Create(MxOmniCreateParam& p_param)
{
    MxResult result = FAILURE;

    AUTOLOCK(m_mainCS);    

#ifdef _DEBUG
#ifdef USE_SMART_HEAP
    MxTrace("LegoOmni::Create (before): %u bytes\n", GetHeapSize());
#endif // _USE_SMART_HEAP
#ifdef MEM_DEBUG
            dbgStartTracing("MemTrace.Log");
#endif // MEM_DEBUG
#endif // _DEBUG

    p_param.GetFlags().SetCreateObjectFactory(FALSE);
    p_param.GetFlags().SetCreateVideoManager(FALSE);
    p_param.GetFlags().SetCreateTickleManager(FALSE);

	// The default TickleManager creats it's own thread.
	// For the Lego app, we're tickling the TickleManager
	// from the main message loop. In this case the TickleManager must
	// exist before	the Omni::Create call because the other managers
	// will attempt to register with the TickleManager.
	if (m_tickleManager = new MxTickleManager()) {
		if (m_tickleManager->Create(0) != SUCCESS) {
			delete m_tickleManager;
			m_tickleManager = NULL;
		}
	}

    if (MxOmni::Create(p_param) != SUCCESS) {
        goto done;
    }
    if (!(m_objectFactory = new LegoObjectFactory())) {
        goto done;
    }
	if (m_videoManager = new LegoVideoManager()) {
        if (m_videoManager->Create(p_param.GetVideoParam()) != SUCCESS) {
            delete m_videoManager;
            m_videoManager = NULL;
        }
    }
	if (m_inputManager = new LegoInputManager()) {
        if (m_inputManager->Create() != SUCCESS) {
            delete m_inputManager;
            m_inputManager = NULL;
        }
    }
    m_viewLODListManager = new ViewLODListManager();
    m_textureContainer = new LegoTextureContainer();
    m_worldList = new LegoWorldList(TRUE);

    result = SUCCESS;

done:
#ifdef _DEBUG
#ifdef USE_SMART_HEAP
    MxTrace("LegoOmni::Create (after): %u bytes\n", GetHeapSize());
#endif // _USE_SMART_HEAP
#ifdef MEM_DEBUG
            dbgEndTracing();
#endif // MEM_DEBUG
#endif // _DEBUG
    return result;
}

void 
LegoOmni::CreateInstance() 
{ 
	DestroyInstance();
    SetInstance(new LegoOmni());
}

LegoOmni* 
LegoOmni::GetInstance() 
{ 
    return (LegoOmni*) MxOmni::GetInstance(); 
}

LegoWorld* 
LegoOmni::GetWorld(const MxChar* p_worldName)
{
    if(m_worldList)
    {
        LegoWorld* world;
        LegoWorldListCursor cursor(m_worldList);
        while(cursor.Next(world))
        {
            if(!strcmp(world->GetEntityName(), p_worldName))
                return world;
        }
    }

    return NULL;
}
