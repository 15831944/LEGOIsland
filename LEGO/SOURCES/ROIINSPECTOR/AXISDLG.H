// AxisDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAxisDlg dialog

class CAxisDlg : public CDialog
{
// Construction
public:
	CAxisDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAxisDlg)
	enum { IDD = IDD_CONFIGURE_AXIS };
	double	m_xAxisMin;
	double	m_xAxisMax;
	double	m_yAxisMin;
	double	m_yAxisMax;
	double	m_zAxisMin;
	double	m_zAxisMax;
	BOOL	m_relative;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAxisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAxisDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
