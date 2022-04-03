// NavDlg.cpp : implementation file
//

#include "StdMain.h"
#include "LegoOmni.h"
#include "LegoNavController.h"
#include "NavDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNavDlg dialog


CNavDlg::CNavDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNavDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNavDlg)
	m_useRV = FALSE;
	//}}AFX_DATA_INIT
}


void CNavDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNavDlg)
	DDX_Control(pDX, IDC_SLIDERRV, m_sliderRV);
	DDX_Control(pDX, IDC_SLIDERRS, m_sliderRS);
	DDX_Control(pDX, IDC_SLIDERRA, m_sliderRA);
	DDX_Control(pDX, IDC_SLIDERRAMIN, m_sliderRAMin);
	DDX_Control(pDX, IDC_SLIDERRD, m_sliderRD);
	DDX_Control(pDX, IDC_SLIDERLV, m_sliderLV);
	DDX_Control(pDX, IDC_SLIDERLA, m_sliderLA);
	DDX_Control(pDX, IDC_SLIDERLAMIN, m_sliderLAMin);
	DDX_Control(pDX, IDC_SLIDERLD, m_sliderLD);
	DDX_Control(pDX, IDC_SLIDERDZ, m_sliderDZ);
	DDX_Check(pDX, IDC_USEROTVEL, m_useRV);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNavDlg, CDialog)
	//{{AFX_MSG_MAP(CNavDlg)
	ON_BN_CLICKED(IDC_USEROTVEL, OnUserotvel)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNavDlg message handlers

void CNavDlg::OnUserotvel() 
{
	m_useRV = !m_useRV;
	LegoNavController::SetDefaults(m_sliderDZ.GetPos(),
			(double)m_sliderLV.GetPos(), (double)m_sliderRV.GetPos(),
			(double)m_sliderLA.GetPos(), (double)m_sliderRA.GetPos(),
			(double)m_sliderLD.GetPos(), (double)m_sliderRD.GetPos(),
			(double)m_sliderLAMin.GetPos(), (double)m_sliderRAMin.GetPos(),
			(double)m_sliderRS.GetPos(), m_useRV);
}

void CNavDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);

	SetDlgItemInt(IDC_DZ, m_sliderDZ.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINVEL, m_sliderLV.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTVEL, m_sliderRV.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINACCEL, m_sliderLA.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTACCEL, m_sliderRA.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINACCELMIN, m_sliderLAMin.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTACCELMIN, m_sliderRAMin.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINDECCEL, m_sliderLD.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTDECCEL, m_sliderRD.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTSENS, m_sliderRS.GetPos(), FALSE);

	LegoNavController::SetDefaults(m_sliderDZ.GetPos(),
			(double)m_sliderLV.GetPos(), (double)m_sliderRV.GetPos(),
			(double)m_sliderLA.GetPos(), (double)m_sliderRA.GetPos(),
			(double)m_sliderLD.GetPos(), (double)m_sliderRD.GetPos(),
			(double)m_sliderLAMin.GetPos(), (double)m_sliderRAMin.GetPos(),
			(double)m_sliderRS.GetPos()/100.0, m_useRV);
}


BOOL CNavDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int dz;
	double lv, rv;
	double la, ra;
	double ld, rd;
	double lamin, ramin;
	double rs;
	MxBool useRV;

	LegoNavController::GetDefaults(&dz,
				&lv, &rv, &la, &ra, &ld, &rd, &lamin, &ramin, &rs, &useRV);
	m_useRV = useRV;

	CheckDlgButton(IDC_USEROTVEL, m_useRV);

    m_sliderDZ.SetRange(0, 100);
    m_sliderDZ.SetPos(dz);
    m_sliderLV.SetRange(0, 100);
    m_sliderLV.SetPos(lv);
    m_sliderRV.SetRange(0, 100);
    m_sliderRV.SetPos(rv);
    m_sliderLA.SetRange(0, 100);
    m_sliderLA.SetPos(la);
    m_sliderRA.SetRange(0, 100);
    m_sliderLAMin.SetRange(0, 100);
    m_sliderLAMin.SetPos(lamin);
    m_sliderRAMin.SetRange(0, 100);
    m_sliderRAMin.SetPos(ramin);
	m_sliderRA.SetPos(ra);
    m_sliderLD.SetRange(0, 100);
    m_sliderLD.SetPos(ld);
    m_sliderRD.SetRange(0, 100);
    m_sliderRD.SetPos(rd);
	m_sliderRS.SetRange(0, 100);
    m_sliderRS.SetPos(rs * 100);

	SetDlgItemInt(IDC_DZ, m_sliderDZ.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINVEL, m_sliderLV.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTVEL, m_sliderRV.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINACCEL, m_sliderLA.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTACCEL, m_sliderRA.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINACCELMIN, m_sliderLAMin.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTACCELMIN, m_sliderRAMin.GetPos(), FALSE);
	SetDlgItemInt(IDC_LINDECCEL, m_sliderLD.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTDECCEL, m_sliderRD.GetPos(), FALSE);
	SetDlgItemInt(IDC_ROTSENS, m_sliderRS.GetPos(), FALSE);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
