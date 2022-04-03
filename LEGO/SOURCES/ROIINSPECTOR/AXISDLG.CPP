// AxisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "AxisDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAxisDlg dialog


CAxisDlg::CAxisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAxisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAxisDlg)
	m_xAxisMin = 0.0;
	m_xAxisMax = 0.0;
	m_yAxisMin = 0.0;
	m_yAxisMax = 0.0;
	m_zAxisMin = 0.0;
	m_zAxisMax = 0.0;
	m_relative = FALSE;
	//}}AFX_DATA_INIT
}


void CAxisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAxisDlg)
	DDX_Text(pDX, IDC_EDIT1, m_xAxisMin);
	DDX_Text(pDX, IDC_EDIT2, m_xAxisMax);
	DDX_Text(pDX, IDC_EDIT3, m_yAxisMin);
	DDX_Text(pDX, IDC_EDIT4, m_yAxisMax);
	DDX_Text(pDX, IDC_EDIT5, m_zAxisMin);
	DDX_Text(pDX, IDC_EDIT6, m_zAxisMax);
	DDX_Check(pDX, IDC_CHECK3, m_relative);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAxisDlg, CDialog)
	//{{AFX_MSG_MAP(CAxisDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAxisDlg message handlers
