// RealismDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Lego.h"
#include "RealismDlg.h"

#include "ViewManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRealismDlg dialog


CRealismDlg::CRealismDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRealismDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRealismDlg)
	//}}AFX_DATA_INIT

    m_pViewManager = 0;
}


void CRealismDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealismDlg)
	DDX_Control(pDX, IDC_STATIC_RENDERTIME_CURRENT, m_currentRenderTime);
	DDX_Control(pDX, IDC_STATIC_RENDERRATE_CURRENT, m_currentRenderRate);
	DDX_Control(pDX, IDC_STATIC_RENDERRATE, m_renderRate);
	DDX_Control(pDX, IDC_STATIC_RENDERTIME, m_renderTime);
	DDX_Control(pDX, IDC_REALISM, m_realism);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRealismDlg, CDialog)
	//{{AFX_MSG_MAP(CRealismDlg)
	ON_WM_HSCROLL()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRealismDlg message handlers

void CRealismDlg::SetViewManager(ViewManager* pViewManager)
{
    m_pViewManager = pViewManager;
    if (m_pViewManager)
    {
        //m_realism.SetPos(m_pViewManager->GetDesiredRenderTime());
        m_pViewManager->SetSecondsAllowed(m_realism.GetPos() / 1000.0);
    }

    UpdateStaticText();
}

void CRealismDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl*    pSlider = (CSliderCtrl*) (CWnd*) pScrollBar;

    if (m_pViewManager)
    {
        m_pViewManager->SetSecondsAllowed(m_realism.GetPos() / 1000.0);
    }

    UpdateStaticText();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CRealismDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_realism.SetRange(0, 1000);
	m_realism.SetTicFreq(100);
    m_realism.SetPos(LoadFromRegistry());
    m_realism.SetPageSize(10);

    if (m_pViewManager)
    {
        m_pViewManager->SetSecondsAllowed(m_realism.GetPos() / 1000.0);
    }
	
    UpdateStaticText();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRealismDlg::OnClose() 
{
    SaveToRegistry(m_realism.GetPos());
    ShowWindow(SW_HIDE);
}

void CRealismDlg::UpdateStaticText()
{
    CString desiredRenderTimeText;
    CString desiredRenderRateText;
    double  desiredRenderTime;

    CString currentRenderTimeText;
    CString currentRenderRateText;
    double  currentRenderTime;

    if (m_pViewManager)
    {
        desiredRenderTime = m_pViewManager->GetSecondsAllowed();
        currentRenderTime = m_pViewManager->GetSecondsUsedLastFrame();
    }
    else
    {
        desiredRenderTime = m_realism.GetPos();
        currentRenderTime = 0;
    }

    desiredRenderTimeText.Format("%ld ms", (long) (desiredRenderTime * 1000.0));
    if (desiredRenderTime)
    {
        desiredRenderRateText.Format("%.1f fps", 1 / desiredRenderTime);
    }
    else
    {
        desiredRenderRateText.Format("* fps");
    }

    currentRenderTimeText.Format("%ld ms", (long) (currentRenderTime * 1000.0));
    if (currentRenderTime)
    {
        currentRenderRateText.Format("%.1f fps", 1 / currentRenderTime);
    }
    else
    {
        currentRenderRateText.Format("* fps");
    }

    m_renderTime.SetWindowText(desiredRenderTimeText);
    m_renderRate.SetWindowText(desiredRenderRateText);
    m_currentRenderTime.SetWindowText(currentRenderTimeText);
    m_currentRenderRate.SetWindowText(currentRenderRateText);
}


void CRealismDlg::SaveToRegistry(int realism)
{
    AfxGetApp()->WriteProfileInt("Realtime View Weights",
                                 "Realism",
                                 realism);
}

int CRealismDlg::LoadFromRegistry()
{
    return (int) AfxGetApp()->GetProfileInt("Realtime View Weights",
                                            "Realism",
                                            250);
}
