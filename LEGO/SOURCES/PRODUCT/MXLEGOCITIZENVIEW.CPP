// MxLegoCitizenView.cpp : implementation file
//

#include "stdafx.h"
#include "lego.h"
#include "MxLegoCitizenView.h"

#include "Town.h"   // CitizenController

#include "legoroi.h"
#include "legostorage.h"
#include "legoanim.h"

using namespace Tgl;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MxLegoCitizenView

MxLegoCitizenView::MxLegoCitizenView(Group* pScene)
{
    m_pScene                = pScene;
    m_pCitizenController    = 0;
    m_pSunLight             = 0;
    m_pDirectionalLight     = 0;
    m_pAmbientLight         = 0;

    // scene manager
    m_pViewMgr                  = 0;
    m_pCitizen                  = 0;
    m_previousRenderTime        = 0;
}

MxLegoCitizenView::~MxLegoCitizenView()
{
    delete m_pSunLight;
    delete m_pDirectionalLight;
    delete m_pAmbientLight;
    delete m_pCitizen;
    delete m_pViewMgr;
    delete m_pCitizenController;
}

BEGIN_MESSAGE_MAP(MxLegoCitizenView, MxLegoView)
	//{{AFX_MSG_MAP(MxLegoCitizenView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL MxLegoCitizenView::Create(const CString& windowName,
                               const CWnd* pParentWnd,
                               ViewLODListManager* pViewLODListManager,
                               Renderer* pRenderer,
                               BOOL fullScreen,
                               int width,
                               int height,
                               int bitsPerPixel,
                               const PALETTEENTRY* pPaletteEntries,
                               int paletteEntryCount)
{
    // scene manager
    ViewLODList*        pLODList = pViewLODListManager->Create("LegoCitizen", 1);
    Tgl::DoubleMatrix4  transformation;
    Matrix4             transform;
    double              position[3] = { 0, 0, 0 };
    double              direction[3];
    double              up[3];

    m_pCitizen  = new LegoCitizen(pRenderer, pLODList);
    pLODList->Release();
    ASSERT((pLODList->AddRef(), pLODList->Release()) == 1);

	m_pViewMgr = new ViewManager(m_pScene, m_pCitizen);
    //m_pSceneMgr->AddActor(*m_pCitizen);
	m_pScene->Add(m_pCitizen->GetGeometry());
    m_previousRenderTime = m_pViewMgr->GetSecondsAllowed();

    m_pCitizenController = new CitizenController(m_pCitizen);

    // lights
    m_pSunLight         = pRenderer->CreateLight(Directional, .9, .9, .9);
    m_pDirectionalLight = pRenderer->CreateLight(Directional, .4, .4, .4);
    m_pAmbientLight     = pRenderer->CreateLight(Ambient, .3, .3, .3);

    direction[0] = 1, direction[1] = -1, direction[2] = 2;
    up[0] = 0, up[1] = 1, up[2] = 0;
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pSunLight->SetTransformation(transformation);

    direction[0] = -1, direction[1] = -2, direction[2] = -1;
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pDirectionalLight->SetTransformation(transformation);

    if (!MxLegoView::Create(windowName, pParentWnd, pRenderer,
                            fullScreen, width, height, bitsPerPixel,
                            pPaletteEntries, paletteEntryCount))
    {
        delete m_pSunLight;
        delete m_pDirectionalLight;
        delete m_pAmbientLight;
        delete m_pCitizen;
	    delete m_pViewMgr;
        delete m_pCitizenController;
        m_pSunLight             = 0;
        m_pDirectionalLight     = 0;
        m_pAmbientLight         = 0;
        m_pCitizen              = 0;
	    m_pViewMgr             = 0;
        m_pCitizenController    = 0;

        return FALSE;
    }

    return TRUE;
}

Device*
MxLegoCitizenView::CreateDevice()
{
    Device* pDevice = MxLegoView::CreateDevice();

    if (pDevice)
    {
        unsigned long   width = pDevice->GetWidth();
        unsigned long   height = pDevice->GetHeight();

        m_pViewMgr->SetResolution(width, height);
        m_pCitizenController->OnViewSize(width, height);
    }

    return pDevice;
}

View*
MxLegoCitizenView::CreateView()
{
    Device* pDevice = GetDevice();
    View*   pView = 0;

    if (pDevice)
    {
        pView = GetRenderer()->CreateView(pDevice,
                                          GetCamera(),
                                          0, 0,
                                          pDevice->GetWidth(),
                                          pDevice->GetHeight());
        if (pView)
        {
            double  viewAngle = 45;

            pView->SetFrustrum(1, 5000, viewAngle);
            pView->SetBackgroundColor(.2, .2, .7);

            m_pViewMgr->SetFrustrum(viewAngle, -1, -5000);

            pView->Add(m_pSunLight);
            pView->Add(m_pDirectionalLight);
            pView->Add(m_pAmbientLight);
        }
    }

    return pView;
}

MouseController*
MxLegoCitizenView::GetController()
{
    return m_pCitizenController;
}

Camera*
MxLegoCitizenView::GetCamera()
{
    return m_pCitizen->GetHead();
}

Group*
MxLegoCitizenView::GetScene()
{
    return m_pScene;
}

void MxLegoCitizenView::Render()
{
    MxStopWatch     stopWatch;

    m_pViewMgr->Update(m_previousRenderTime);

    stopWatch.Start();
    MxLegoView::Render();
    stopWatch.Stop();

    m_previousRenderTime = stopWatch.ElapsedSeconds();

    if (m_previousRenderTime <= 0)
    {
        // if something went wrong pretend render time was exactly 
        // what was asked for
        m_previousRenderTime = m_pViewMgr->GetSecondsAllowed();
    }
}

/////////////////////////////////////////////////////////////////////////////
// MxLegoCitizenView message handlers

