// ROIPropPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CROIPropPage dialog

class LegoROI;

class CROIPropPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CROIPropPage)

// Construction
public:
	CROIPropPage();
	~CROIPropPage();

// Dialog Data
	//{{AFX_DATA(CROIPropPage)
	enum { IDD = IDD_ROI_PROP };
	CString	m_name;
	CString	m_lodCount;
	CString	m_partsCount;
	CString	m_translation;
	CString	m_direction;
	CString	m_up;
	CString	m_boundingSphereCenter;
	CString	m_boundingSphereRadius;
	CString	m_boundingBoxMin;
	CString	m_boundingBoxMax;
	//}}AFX_DATA


public:
    void Display(const LegoROI*);

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CROIPropPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CROIPropPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
