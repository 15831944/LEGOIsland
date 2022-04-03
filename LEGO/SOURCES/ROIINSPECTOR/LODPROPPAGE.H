// LODPropPage.h : header file
//

class LegoROI;
class LegoLOD;

/////////////////////////////////////////////////////////////////////////////
// CLODPropPage dialog

class CLODPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CLODPropPage)

// Construction
public:
	CLODPropPage();
	~CLODPropPage();

public:
    void Display(const LegoLOD*);

// Dialog Data
	//{{AFX_DATA(CLODPropPage)
	enum { IDD = IDD_LOD_PROP };
	CListCtrl	m_costList;
	CString	m_vertixCount;
	CString	m_costCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLODPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
    static int CALLBACK PixelsCoveredCmp(LPARAM, LPARAM, LPARAM);
    static int CALLBACK CostCmp(LPARAM, LPARAM, LPARAM);
    static int CALLBACK EstimatedCost1Cmp(LPARAM, LPARAM, LPARAM);

	// Generated message map functions
	//{{AFX_MSG(CLODPropPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    const LegoLOD*  m_pLOD;
};
