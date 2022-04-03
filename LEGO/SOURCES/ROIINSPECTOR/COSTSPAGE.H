// CostsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCostsPage dialog

class LegoROI;

class CCostsPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CCostsPage)

// Construction
public:
	CCostsPage();   // standard constructor
	~CCostsPage();

// Dialog Data
	//{{AFX_DATA(CCostsPage)
	enum { IDD = IDD_COSTS };
	CListCtrl	m_costList;
	CComboBox	m_pixelsCoveredCombo;
	//}}AFX_DATA


public:
    void Display(const LegoROI*);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCostsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

    void UpdateCostList(double pixelsCovered);
    static int CALLBACK LODCmp(LPARAM, LPARAM, LPARAM);
    static int CALLBACK CostCmp(LPARAM, LPARAM, LPARAM);

    // Generated message map functions
	//{{AFX_MSG(CCostsPage)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    const LegoROI*  m_pROI;
};
