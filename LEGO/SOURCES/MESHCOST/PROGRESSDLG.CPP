// ProgressDlg.cpp : implementation file
//

#include "stdafx.h"
#include "meshcost.h"
#include "ProgressDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog


CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CProgressDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

    m_pNotificationWnd          = 0;
    m_pauseNotificationMsg       = 0;
    m_continueNotificationMsg   = 0;
    m_cancelNotificationMsg     = 0;

    Create(CProgressDlg::IDD, pParent);
}


void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CProgressDlg)
	DDX_Control(pDX, IDC_PROGRESS, m_progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
	//{{AFX_MSG_MAP(CProgressDlg)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_CONTINUE, OnContinue)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CProgressDlg::SetNotification(CWnd* pNotificationWnd,
                                   UINT pauseNotificationMsg,
                                   UINT continueNotificationMsg,
                                   UINT cancelNotificationMsg)
{
    m_pNotificationWnd          = pNotificationWnd;
    m_pauseNotificationMsg      = pauseNotificationMsg;
    m_continueNotificationMsg   = continueNotificationMsg;
    m_cancelNotificationMsg     = cancelNotificationMsg;
}

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg message handlers

BOOL CProgressDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
    GetDlgItem(IDC_CONTINUE)->EnableWindow(FALSE);
    GetDlgItem(IDC_PAUSE)->ShowWindow(TRUE);
    GetDlgItem(IDC_CONTINUE)->ShowWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CProgressDlg::OnPause() 
{
    if (m_pNotificationWnd)
    {
        m_pNotificationWnd->PostMessage(m_pauseNotificationMsg);
    }
    GetDlgItem(IDC_PAUSE)->EnableWindow(FALSE);
    GetDlgItem(IDC_CONTINUE)->EnableWindow(TRUE);
    GetDlgItem(IDC_PAUSE)->ShowWindow(FALSE);
    GetDlgItem(IDC_CONTINUE)->ShowWindow(TRUE);
}

void CProgressDlg::OnContinue() 
{
    if (m_pNotificationWnd)
    {
        m_pNotificationWnd->PostMessage(m_continueNotificationMsg);
    }
    GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
    GetDlgItem(IDC_CONTINUE)->EnableWindow(FALSE);
    GetDlgItem(IDC_PAUSE)->ShowWindow(TRUE);
    GetDlgItem(IDC_CONTINUE)->ShowWindow(FALSE);
}

void CProgressDlg::OnCancel() 
{
    if (m_pNotificationWnd)
    {
        m_pNotificationWnd->PostMessage(m_cancelNotificationMsg);
    }
    GetDlgItem(IDC_PAUSE)->EnableWindow(TRUE);
    GetDlgItem(IDC_CONTINUE)->EnableWindow(FALSE);
    GetDlgItem(IDC_PAUSE)->ShowWindow(TRUE);
    GetDlgItem(IDC_CONTINUE)->ShowWindow(FALSE);
}


