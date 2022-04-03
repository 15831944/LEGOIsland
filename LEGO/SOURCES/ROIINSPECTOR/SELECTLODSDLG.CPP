// SelectLODs.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "SelectLODsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelectLODsDlg dialog


CSelectLODsDlg::CSelectLODsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSelectLODsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelectLODsDlg)
	m_depth = 0;
	m_lodNumber = 0;
	m_isLODNumberRelative = FALSE;
	//}}AFX_DATA_INIT
}


void CSelectLODsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelectLODsDlg)
	DDX_Text(pDX, IDC_EDIT1, m_depth);
	DDX_Text(pDX, IDC_EDIT2, m_lodNumber);
	DDX_Check(pDX, IDC_CHECK1, m_isLODNumberRelative);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelectLODsDlg, CDialog)
	//{{AFX_MSG_MAP(CSelectLODsDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelectLODsDlg message handlers
