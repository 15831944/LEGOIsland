// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Lego.h"

#include "MainFrm.h"
#include "LegoView.h"
#include "MxLegoCitizenView.h"
#include "RVWeightsDlg.h"
#include "RealismDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_REALTIMEVIEW_WEIGHTS, OnViewRealtimeViewWeights)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REALTIMEVIEW_WEIGHTS, OnUpdateViewRealtimeViewWeights)
	ON_COMMAND(ID_VIEW_REALISM, OnViewRealism)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REALISM, OnUpdateViewRealism)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_RENDERERMEMORY,
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
    m_pRealtimeViewWeightsDlg   = 0;	
    m_pRealismDlg               = 0;
}

CMainFrame::~CMainFrame()
{
    delete m_pRealtimeViewWeightsDlg;
    delete m_pRealismDlg;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.Create(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Remove this if you don't want tool tips or a resizeable toolbar
	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

    cs.x = 400;
    cs.y = 20;
    cs.cx = 400;
    cs.cy = 140;

	return CFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnViewRealtimeViewWeights() 
{
    if (!m_pRealtimeViewWeightsDlg)
    {
        m_pRealtimeViewWeightsDlg = new CRVWeightsDlg;

        m_pRealtimeViewWeightsDlg->Create(CRVWeightsDlg::IDD);
    }

    if (m_pRealtimeViewWeightsDlg->IsWindowVisible())
    {
        m_pRealtimeViewWeightsDlg->ShowWindow(SW_HIDE);
    }
    else
    {
        m_pRealtimeViewWeightsDlg->ShowWindow(SW_SHOW);
    }
}

void CMainFrame::OnViewRealism() 
{
    if (!m_pRealismDlg)
    {
        m_pRealismDlg = new CRealismDlg();

        m_pRealismDlg->Create(CRealismDlg::IDD);
    }

    if (m_pRealismDlg->IsWindowVisible())
    {
        m_pRealismDlg->ShowWindow(SW_HIDE);
    }
    else
    {
	    ASSERT(GetActiveView() &&
               GetActiveView()->IsKindOf(RUNTIME_CLASS(CLegoView)));

        MxLegoCitizenView*  pCitizenView = ((CLegoView*) GetActiveView())->GetLegoCitizenView();

        m_pRealismDlg->SetViewManager(pCitizenView ? pCitizenView->GetViewMgr() : 0);
        m_pRealismDlg->ShowWindow(SW_SHOW);
    }
}

void CMainFrame::OnUpdateViewRealtimeViewWeights(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_pRealtimeViewWeightsDlg &&
                     m_pRealtimeViewWeightsDlg->IsWindowVisible());
}

void CMainFrame::OnUpdateViewRealism(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_pRealismDlg &&
                     m_pRealismDlg->IsWindowVisible());
}
