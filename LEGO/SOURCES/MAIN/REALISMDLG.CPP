// RealismDlg.cpp : implementation file
//
#include "StdMain.h"
#include <afxdlgs.h>
#include "main.h"
#include "LegoOmni.h"
#include "LegoNotify.h"
#include "RealismDlg.h"
#include "resource.h"
#include "ViewManager.h"
#include "TglSurface.h"
#include "MxTickleManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMain* g_main;

/////////////////////////////////////////////////////////////////////////////
// CRealismDlg dialog


CRealismDlg::CRealismDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRealismDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRealismDlg)
	//}}AFX_DATA_INIT

    m_pViewManager = 0;
   
}

CRealismDlg::~CRealismDlg()
{
	LegoOmni::GetInstance()->GetTickleManager()->UnregisterClient(this);
	CDialog::~CDialog();
}


void CRealismDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRealismDlg)
	DDX_Control(pDX, IDC_STATIC_RENDERTIME_CURRENT, m_currentRenderTime);
	DDX_Control(pDX, IDC_STATIC_RENDERTIME, m_renderTime);
	DDX_Control(pDX, IDC_REALISM, m_realism);
	DDX_Control(pDX, IDC_STATIC_FRAMETIME_MIN, m_frameTimeMin);
	DDX_Control(pDX, IDC_STATIC_FRAMETIME_MAX, m_frameTimeMax);
	DDX_Control(pDX, IDC_STATIC_FRAMETIME_AVERAGE, m_frameTimeAverage);
	DDX_Control(pDX, IDC_STATIC_FRAMETIME_REQUESTED, m_frameTimeRequested);
	DDX_Control(pDX, IDC_STATIC_FRAMERATE_MIN, m_frameRateMin);
	DDX_Control(pDX, IDC_STATIC_FRAMERATE_MAX, m_frameRateMax);
	DDX_Control(pDX, IDC_STATIC_FRAMERATE_AVERAGE, m_frameRateAverage);
	DDX_Control(pDX, IDC_STATIC_FRAMERATE_REQUESTED, m_frameRateRequested);
	DDX_Control(pDX, IDC_STATIC_BUTTON_DOWN, m_notificationButtonDown);
	DDX_Control(pDX, IDC_STATIC_BUTTON_DOWN_TIME, m_notificationButtonDownTime);
	DDX_Control(pDX, IDC_STATIC_BUTTON_DOWN_AVR_TIME, m_notificationButtonDownAverageTime);
	DDX_Control(pDX, IDC_STATIC_BUTTON_DOWN_FRAME_TIME, m_notificationButtonDownFrameTime);
	DDX_Control(pDX, IDC_STATIC_MOUSE_MOVE, m_notificationMouseMove);
	DDX_Control(pDX, IDC_STATIC_MOUSE_MOVE_TIME, m_notificationMouseMoveTime);
	DDX_Control(pDX, IDC_STATIC_MOUSE_MOVE_AVR_TIME, m_notificationMouseMoveAverageTime);
	DDX_Control(pDX, IDC_STATIC_MOUSE_MOVE_FRAME_TIME, m_notificationMouseMoveFrameTime);
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
        m_realism.SetPos(m_pViewManager->GetSecondsAllowed() * 1000);
        //m_pViewManager->SetSecondsAllowed(m_realism.GetPos() / 1000.0);
    }

    UpdateStaticText();
}

void CRealismDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CSliderCtrl*    pSlider = (CSliderCtrl*) (CWnd*) pScrollBar;

    if (m_pViewManager)
    {
		int renderTime = m_realism.GetPos();
        m_pViewManager->SetSecondsAllowed(renderTime / 1000.0);
		g_main->UpdateFrameTime();
    }

    UpdateStaticText();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CRealismDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_realism.SetRange(0, 1000);
	m_realism.SetTicFreq(100);
    //m_realism.SetPos(LoadFromRegistry());
    m_realism.SetPageSize(10);

    if (m_pViewManager)
    {
        m_realism.SetPos(m_pViewManager->GetSecondsAllowed() * 1000);
    }

	LegoOmni::GetInstance()->GetTickleManager()->RegisterClient(this, 2000);

	UpdateStaticText();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CRealismDlg::OnClose() 
{
    //SaveToRegistry(m_realism.GetPos());
    ShowWindow(SW_HIDE);
}

void CRealismDlg::UpdateStaticText()
{
	if (m_hWnd)
	{
		int fTime;
		CString desiredRenderTimeText;
		double  desiredRenderTime;

		CString currentRenderTimeText;
		double  currentRenderTime;

		CString frameTimeMinText;
		CString frameTimeMaxText;
		CString frameTimeAverageText;
		CString frameTimeRequestedText;
		CString frameRateMinText;
		CString frameRateMaxText;
		CString frameRateAverageText;
		CString frameRateRequestedText;

		if (m_pViewManager)
		{
			desiredRenderTime = m_pViewManager->GetSecondsAllowed();
#ifdef _DEBUG
			currentRenderTime = m_pViewManager->GetSecondsUsedLastFrame();
#else
			currentRenderTime = 0;
#endif // _DEBUG
		}
		else
		{
			desiredRenderTime = m_realism.GetPos();
			currentRenderTime = 0;
		}

		desiredRenderTimeText.Format("%ld ms", (long) (desiredRenderTime * 1000.0));
		currentRenderTimeText.Format("%ld ms", (long) (currentRenderTime * 1000.0));

		fTime = m_timeAverage.GetMin();
		frameTimeMinText.Format("%4d ms", fTime);
		if (fTime)
			frameRateMinText.Format("%3.1f fps", 1000.0/fTime);

		fTime = m_timeAverage.GetMax();
		frameTimeMaxText.Format("%4d ms", fTime);
		if (fTime)
			frameRateMaxText.Format("%3.1f fps", 1000.0/fTime);

		fTime = m_timeAverage.GetAverage();
		frameTimeAverageText.Format("%4d ms", fTime);
		if (fTime)
			frameRateAverageText.Format("%3.1f fps", 1000.0/fTime);

		fTime = LegoOmni::GetInstance()->GetTickleManager()->GetClientTickleInterval(
											LegoOmni::GetInstance()->GetVideoManager());
		frameTimeRequestedText.Format("%4d ms", fTime);
		if (fTime)
			frameRateRequestedText.Format("%3.1f fps", 1000.0/fTime);

		m_timeAverage.ResetAtNextTickle();

		m_renderTime.SetWindowText(desiredRenderTimeText);
		m_currentRenderTime.SetWindowText(currentRenderTimeText);

		m_frameTimeMin.SetWindowText(frameTimeMinText);
		m_frameTimeMax.SetWindowText(frameTimeMaxText);
		m_frameTimeAverage.SetWindowText(frameTimeAverageText);
		m_frameTimeRequested.SetWindowText(frameTimeRequestedText);

		m_frameRateMin.SetWindowText(frameRateMinText);
		m_frameRateMax.SetWindowText(frameRateMaxText);
		m_frameRateAverage.SetWindowText(frameRateAverageText);
		m_frameRateRequested.SetWindowText(frameRateRequestedText);

        // Events profiling
        CString text;

        // c_notificationButtonDown
        text.Format("%d", m_leftMouseDownEventCount);
        m_notificationButtonDown.SetWindowText(text);
        text.Format("%d ms", m_leftMouseDownSum);
	    m_notificationButtonDownTime.SetWindowText(text);
        if(m_leftMouseDownEventCount)
            text.Format("%d ms", m_leftMouseDownSum / m_leftMouseDownEventCount);
        else
            text.Format("* ms");
        m_notificationButtonDownAverageTime.SetWindowText(text);
        text.Format("* ms");
        m_notificationButtonDownFrameTime.SetWindowText(text);

        // c_notificationMouseMove
        text.Format("%d", m_mouseMoveCount);
        m_notificationMouseMove.SetWindowText(text);
        text.Format("%d ms", m_mouseMoveSum);
	    m_notificationMouseMoveTime.SetWindowText(text);
        if(m_mouseMoveCount)
            text.Format("%d ms", m_mouseMoveSum / m_mouseMoveCount);
        else
            text.Format("* ms");
        m_notificationMouseMoveAverageTime.SetWindowText(text);
        text.Format("* ms");
        m_notificationMouseMoveFrameTime.SetWindowText(text);
    }
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


// For notification profiling
MxTime	CRealismDlg::m_leftMouseDownStart = 0;
MxTime	CRealismDlg::m_leftMouseDownSum = 0;
MxU32   CRealismDlg::m_leftMouseDownEventCount = 0;
MxTime	CRealismDlg::m_mouseMoveStart = 0;
MxTime	CRealismDlg::m_mouseMoveSum = 0;
MxU32   CRealismDlg::m_mouseMoveCount = 0;

void CRealismDlg::StartEventTrace(MxS16 p_event)
{
	switch(p_event)
	{
		case c_notificationButtonDown:
            m_leftMouseDownStart = GetTickCount();
			break;
		
        case c_notificationMouseMove:
            m_mouseMoveStart = GetTickCount();
			break;

		default:
			break;
	}
}


void CRealismDlg::EndEventTrace(MxS16 p_event)
{
	switch(p_event)
	{
		case c_notificationButtonDown:
            m_leftMouseDownEventCount++;
            m_leftMouseDownSum += GetTickCount() - m_leftMouseDownStart;
			break;
		
        case c_notificationMouseMove:
            m_mouseMoveCount++;
            m_mouseMoveSum += GetTickCount() - m_mouseMoveStart;
			break;

		default:
			break;
	}
}

