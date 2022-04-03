#include "StdLego.h"
#include <ddraw.h>
#include "MxPresenter.h"
#include "MxDisplaySurface.h"
#include "MxPalette.h"
#include "MxRegion.h"
#include "LegoOmni.h"
#include "LegoVideoManager.h"
#include "Lego3DManager.h"
#include "Lego3DView.h"
#include "LegoROI.h"
#include "LegoUtil.h"

#ifdef DO_TIME_MEASUREMENT
#include "LegoTestTimer.h"
#endif // DO_TIME_MEASUREMENT

using namespace Tgl;

LegoVideoManager::LegoVideoManager()
{
    m_renderer = NULL;
    m_3dManager = NULL;
    m_viewROI = NULL;
}

LegoVideoManager::~LegoVideoManager()
{
    Destroy();
}

MxResult 
LegoVideoManager::Create(MxVideoParam& p_param, MxTime p_tickleInterval, MxBool p_createThread)
{
#ifdef DO_TIME_MEASUREMENT
	m_testTimer = new LegoTestTimer(7, 5, 300, 0);
#endif // DO_TIME_MEASUREMENT

    if (MxVideoManager::Create(p_param, p_tickleInterval, p_createThread) != SUCCESS) {
        return FAILURE;
    }   

    AUTOLOCK(m_criticalSection);

    if (!(m_renderer = CreateRenderer())) {
        return FAILURE;
    }
    if (!(m_3dManager = new Lego3DManager())) {
        return FAILURE;
    }

    Lego3DManager::CreateStruct cs;
    memset(&cs, 0, sizeof(cs));
    cs.m_hWnd = LegoOmni::GetInstance()->GetWindow();
    cs.m_pDirectDraw = m_directDraw;
    cs.m_pFrontBuffer = m_displaySurface->GetFrontSurface();
    cs.m_pBackBuffer = m_displaySurface->GetBackSurface();
    cs.m_pPalette = m_param.GetPalette()->GetDirectDrawPalette();
    cs.m_isFullScreen = FALSE;
    if (!m_3dManager->Create(cs)) {
        return FAILURE;
    }

	ViewLODList* pLODList = m_3dManager->GetViewLODListManager()->Create("CameraROI", 1);
    m_viewROI = new LegoROI(m_renderer, pLODList);
    pLODList->Release(); // Decrease refference counter, because it 2 now
    
    ::Vector3 position(0, 1.25, -50);
    ::Vector3 direction(sin(DToR(45./2)), 0, cos(DToR(45./2)));
    ::Vector3 up(0, 1, 0);
	::Matrix4 mat;

	CalcLocalTransform(position, direction, up, mat);
	m_viewROI->SetLocalTransform(mat);

#if CLEANUP
    m_viewROI->SetPosition(position);
    m_viewROI->SetDirection(direction);
    m_viewROI->SetUp(up);
#endif
	m_3dManager->Add(*m_viewROI);
    m_3dManager->SetPointOfView(*m_viewROI);

    return SUCCESS;
}

void 
LegoVideoManager::Destroy()
{
#ifdef DO_TIME_MEASUREMENT
	if (m_testTimer)
		delete m_testTimer;
#endif // DO_TIME_MEASUREMENT

   if (m_renderer) {
        delete m_renderer;
    }
    if (m_viewROI) {
		if (m_3dManager)
			m_3dManager->Remove(*m_viewROI);
        delete m_viewROI;
    }
    if (m_3dManager) {
        delete m_3dManager;
    }
    MxVideoManager::Destroy();
}

MxResult
LegoVideoManager::Tickle()
{
    AUTOLOCK(m_criticalSection)

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(0);
#endif // DO_TIME_MEASUREMENT

    SortPresenterList();
    MxPresenter* presenter;
    MxPresenterListCursor cursor(m_presenterList);
    while (cursor.Next(presenter)) {
        presenter->Tickle();
    }

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(1);
#endif // DO_TIME_MEASUREMENT

    m_3dManager->GetLego3DView()->GetView()->Clear();

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(2);
#endif // DO_TIME_MEASUREMENT

    MxRect32 rect(0, 0, m_param.GetRect().GetWidth(), m_param.GetRect().GetHeight());
    InvalidateRect(rect);
    cursor.Reset();
    while (cursor.Next(presenter) && presenter->GetDisplayZ() >= 0) {
        presenter->PutData();
    }

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(3);
#endif // DO_TIME_MEASUREMENT

    m_3dManager->Render();

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(4);
#endif // DO_TIME_MEASUREMENT

    cursor.Prev();
    while (cursor.Next(presenter)) {
        presenter->PutData();
    }

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(5);
#endif // DO_TIME_MEASUREMENT

	UpdateRegion();

#ifdef DO_TIME_MEASUREMENT
	m_testTimer->Tick(6);
#endif // DO_TIME_MEASUREMENT

    m_region->Reset();
    return SUCCESS;
}

MxPresenter *
LegoVideoManager::GetPresenterAt(MxS32 p_x, MxS32 p_y)
{
    MxPresenter* presenter;
    MxPresenterListCursor cursor(m_presenterList);
    while (cursor.Prev(presenter)) {
        if (presenter->IsHit(p_x, p_y))
			return presenter;
    }
	return 0;
}
