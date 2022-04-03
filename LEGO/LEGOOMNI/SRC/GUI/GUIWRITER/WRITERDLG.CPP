// writerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "lmcons.h"
#include "writer.h"

#include "LegoGuiControl.h"

#include "LegoGuiFile.h"
#include "writerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriterDlg dialog

CWriterDlg::CWriterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWriterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWriterDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWriterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWriterDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWriterDlg, CDialog)
	//{{AFX_MSG_MAP(CWriterDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE_INPUT, OnBrowseInput)
	ON_BN_CLICKED(IDC_BROWSE_OUTPUT, OnBrowseOutput)
	ON_BN_CLICKED(IDC_WRITE, OnWrite)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWriterDlg message handlers

BOOL CWriterDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWriterDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWriterDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWriterDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWriterDlg::OnBrowseInput() 
{
	CFileDialog dlg(TRUE, "LGA", NULL, OFN_HIDEREADONLY, "Gui ascii | *.lga||", NULL);

	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_INPUT_FNAME)->SetWindowText(dlg.GetPathName());
	}
}

void CWriterDlg::OnBrowseOutput() 
{
	CFileDialog dlg(TRUE, "LGB", NULL, NULL, "Gui binary | *.lgb||", NULL);

	if (dlg.DoModal() == IDOK)
	{
		GetDlgItem(IDC_OUTPUT_FNAME)->SetWindowText(dlg.GetPathName());
	}
}

void CWriterDlg::OnWrite() 
{
	char infname[PATHLEN+1], outfname[PATHLEN+1];
	char inpath[PATHLEN+1];
	char tbuf[PATHLEN+1];
	int len;
	char *ptr;


	if ((len = GetDlgItem(IDC_INPUT_FNAME)->GetWindowText( infname, PATHLEN )) == 0)
		return;
	infname[len] = 0;
	strcpy(inpath, infname);
	if (ptr = strrchr(inpath, '\\'))
	{
		*ptr = '\0';
		BOOL result = SetCurrentDirectory(inpath);
		GetCurrentDirectory(PATHLEN, tbuf);
	}

	if ((len = GetDlgItem(IDC_OUTPUT_FNAME)->GetWindowText( outfname, PATHLEN )) == 0)
		return;
	outfname[len] = 0;

	LegoGuiFile gui;
	gui.DoWrite(infname, outfname);

	AfxMessageBox("Done!");

}

