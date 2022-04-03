// SelectLODsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelectLODsDlg dialog

class CSelectLODsDlg : public CDialog
{
// Construction
public:
	CSelectLODsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSelectLODsDlg)
	enum { IDD = IDD_SELECT_LODS };
	int		m_depth;
	int		m_lodNumber;
	BOOL	m_isLODNumberRelative;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelectLODsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelectLODsDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
