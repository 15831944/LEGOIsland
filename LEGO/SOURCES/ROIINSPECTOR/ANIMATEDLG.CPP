// AnimateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "AnimateDlg.h"
#include "LegoROI.h"
#include "LegoAnim.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg dialog


CAnimateDlg::CAnimateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnimateDlg)
	m_maxTime = _T("");
	m_time = _T("");
	//}}AFX_DATA_INIT
}


void CAnimateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnimateDlg)
	DDX_Control(pDX, IDC_SLIDER1, m_timeSlider);
	DDX_Text(pDX, IDC_MAXTIME, m_maxTime);
	DDX_Text(pDX, IDC_TIME, m_time);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAnimateDlg, CDialog)
	//{{AFX_MSG_MAP(CAnimateDlg)
	ON_WM_CLOSE()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CAnimateDlg::Set(LegoROI* pROI, int animationCount, LegoAnim* pAnimations)
{
    int maxTime = (animationCount > 0) ? pAnimations[0].GetDuration() : 0;

    m_pROI              = pROI;
    m_animationCount    = animationCount;
    m_pAnimations       = pAnimations;

    m_timeSlider.SetRange(0, maxTime);
    m_timeSlider.SetPos(0);
    m_time.Format("%d", (int) m_timeSlider.GetPos());
    m_maxTime.Format("%d", (int) maxTime);

    UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg message handlers

void CAnimateDlg::OnClose() 
{
    ShowWindow(SW_HIDE);
}

void CAnimateDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl*    pSlider = (CSliderCtrl*) (CWnd*) pScrollBar;

    if (m_pROI && (m_animationCount > 0))
    {
        LegoResult  result;

        result = m_pROI->SetFrame(&m_pAnimations[0], m_timeSlider.GetPos());
        ASSERT(result == SUCCESS);
        m_time.Format("%d", (int) m_timeSlider.GetPos());
        UpdateData(FALSE);
    }

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
