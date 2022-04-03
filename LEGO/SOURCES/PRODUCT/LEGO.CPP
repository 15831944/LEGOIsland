// Lego.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Lego.h"

#include "MainFrm.h"
#include "LegoDoc.h"
#include "LegoView.h"
#include "Town.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLegoApp

BEGIN_MESSAGE_MAP(CLegoApp, CWinApp)
	//{{AFX_MSG_MAP(CLegoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegoApp construction

CLegoApp::CLegoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLegoApp object

CLegoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CLegoApp initialization

BOOL CLegoApp::InitInstance()
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
		RUNTIME_CLASS(CLegoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLegoView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

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
		// No message handlers
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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CLegoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLegoApp commands

BOOL CLegoApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class

#if 0
    // Let base class complete its idle processing first
	if (CWinApp::OnIdle(lCount))
		return TRUE;

	CLegoDoc*	pLegoDoc = GetActiveLegoDoc();
    Town*       pTown = pLegoDoc ? pLegoDoc->GetTown() : 0;

    if (pTown)
    {
    	CLegoView*	pLegoView = GetActiveLegoView();

        pTown->Tickle();

        if (pLegoView)
        {
            pLegoView->Tickle();
        }

        // We always want idle processing if we have a town
	    return TRUE;
    }

	return FALSE;
#else
    // Let base class do (some of its) idle processing first
	BOOL    bMore;
    
    bMore = CWinApp::OnIdle(lCount);

	CLegoDoc*	pLegoDoc = GetActiveLegoDoc();
    Town*       pTown = pLegoDoc ? pLegoDoc->GetTown() : 0;

    if (pTown)
    {
    	CLegoView*	pLegoView = GetActiveLegoView();

        pTown->Tickle();

        if (pLegoView)
        {
            pLegoView->Tickle();
        }

        // We always want idle processing if we have a town
	    return TRUE;
    }

	return bMore;
#endif
}

CLegoView* CLegoApp::GetActiveLegoView()
{
	if (!m_pMainWnd || !m_pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
	{
		return NULL;
	}

	CView* pView = ((CFrameWnd*) m_pMainWnd)->GetActiveView();

	if (!pView || !pView->IsKindOf(RUNTIME_CLASS(CLegoView)))
	{
		return NULL;
	}

	return (CLegoView*) pView;
}

CLegoDoc* CLegoApp::GetActiveLegoDoc()
{
	if (!m_pMainWnd || !m_pMainWnd->IsKindOf(RUNTIME_CLASS(CFrameWnd)))
	{
		return NULL;
	}

	CDocument* pDoc = ((CFrameWnd*) m_pMainWnd)->GetActiveDocument();

	if (!pDoc || !pDoc->IsKindOf(RUNTIME_CLASS(CLegoDoc)))
	{
		return NULL;
	}

	return (CLegoDoc*) pDoc;
}

BOOL CLegoApp::IsAppActive() const
{

#ifdef WIN32

	// In Win32, if the active window isn't yours, you get a NULL handle.
	return (NULL != ::GetActiveWindow());

#else

	// In Win16, if the active window isn't yours, you still get a handle;
	// check to see if the window belongs to this app.
	//BUGBUG: if the window was created for you by a DLL you're calling,
	//        then this does not work properly.  But that's rare anyway.
	HWND hWndActive = ::GetActiveWindow();
	HINSTANCE hInstActive = ::GetWindowWord(hWndActive, GWW_HINSTANCE);
	return (hInstActive == AfxGetInstanceHandle());

#endif // WIN32

}


