// NavDlg.h : header file
//
#include <afxcmn.h>
#include "MxStd.h"
#include "MxCore.h"
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CNavDlg dialog

class CNavDlg : public CDialog
{
// Construction
public:
	CNavDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNavDlg)
	enum { IDD = IDD_NAVIGATION };
	CSliderCtrl	m_sliderRV;
	CSliderCtrl	m_sliderRS;
	CSliderCtrl	m_sliderRA;
	CSliderCtrl	m_sliderRAMin;
	CSliderCtrl	m_sliderRD;
	CSliderCtrl	m_sliderLV;
	CSliderCtrl	m_sliderLA;
	CSliderCtrl	m_sliderLAMin;
	CSliderCtrl	m_sliderLD;
	CSliderCtrl	m_sliderDZ;
	BOOL	m_useRV;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNavDlg)
	afx_msg void OnUserotvel();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
