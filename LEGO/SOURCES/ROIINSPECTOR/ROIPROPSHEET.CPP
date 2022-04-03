// ROIPropSheet.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "ROIPropSheet.h"

#include "LegoROI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROIPropSheet

IMPLEMENT_DYNAMIC(CROIPropSheet, CPropertySheet)

CROIPropSheet::CROIPropSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.hIcon = m_hIcon;

	AddPage(&m_roiPropPage);
    AddPage(&m_costsPage);
	AddPage(&m_lodPropPage);
}

CROIPropSheet::CROIPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_psh.dwFlags |= PSP_USEHICON;
	m_psh.hIcon = m_hIcon;

    AddPage(&m_roiPropPage);
    AddPage(&m_costsPage);
	AddPage(&m_lodPropPage);
}

CROIPropSheet::~CROIPropSheet()
{
}

void CROIPropSheet::PostNcDestroy() 
{
	CPropertySheet::PostNcDestroy();
	delete this;
}

void CROIPropSheet::Display(const LegoROI* pROI, const LegoLOD* pLOD)
{
	m_roiPropPage.Display(pROI);
    m_costsPage.Display(pROI);
	m_lodPropPage.Display(pLOD);
}

BEGIN_MESSAGE_MAP(CROIPropSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CROIPropSheet)
	ON_WM_CLOSE()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROIPropSheet message handlers


void CROIPropSheet::OnClose() 
{
    // this is a modeless dialog - do not close it; that would
    // destroy it; just hide it

    ShowWindow(SW_HIDE);
}

HCURSOR CROIPropSheet::OnQueryDragIcon() 
{
	return (HCURSOR) m_hIcon;
}

BOOL CROIPropSheet::OnInitDialog() 
{
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	return CPropertySheet::OnInitDialog();
}
