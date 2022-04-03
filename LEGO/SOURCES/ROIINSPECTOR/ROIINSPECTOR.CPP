// ROIInspector.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ROIInspector.h"

#include "MainFrm.h"
#include "ROIDoc.h"
#include "ROIInspectorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorApp

BEGIN_MESSAGE_MAP(CROIInspectorApp, CWinApp)
	//{{AFX_MSG_MAP(CROIInspectorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorApp construction

CROIInspectorApp::CROIInspectorApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CROIInspectorApp object

CROIInspectorApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorApp initialization

BOOL CROIInspectorApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CROIDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CROIInspectorView));
	AddDocTemplate(pDocTemplate);

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CROIInspectorApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorApp commands


BOOL CROIInspectorApp::OnIdle(LONG lCount) 
{
	BOOL            bMore;
    
    // Let base class do (some of its) idle processing first
    bMore = CWinApp::OnIdle(lCount);

#if 0
    // Let base class complete its idle processing first
	if (bMore) 
    {
        return TRUE;
    }
#endif

    CView*              pActiveView = 0;
    CROIInspectorView*    pActiveROIInspectorView = 0;

    if (m_pMainWnd && m_pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
	{
        pActiveView = static_cast<CFrameWnd*>(m_pMainWnd)->GetActiveView();
    }

    if (pActiveView && pActiveView->IsKindOf(RUNTIME_CLASS(CROIInspectorView)))
	{
        pActiveROIInspectorView = static_cast<CROIInspectorView*>(pActiveView);
    }

    if (pActiveROIInspectorView)
	{
        pActiveROIInspectorView->Tickle();
        return TRUE;    // We always want idle processing if we have a Lego3DManager
    }
    else
    {
		return bMore;
	}

}
