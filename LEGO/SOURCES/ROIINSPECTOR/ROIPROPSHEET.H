// ROIPropSheet.h : header file
//

#include "ROIPropPage.h"
#include "CostsPage.h"
#include "LODPropPage.h"

class LegoROI;
class LegoLOD;

/////////////////////////////////////////////////////////////////////////////
// CROIPropSheet

class CROIPropSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CROIPropSheet)

// Construction
public:
	CROIPropSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CROIPropSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	CROIPropPage    m_roiPropPage;
    CCostsPage      m_costsPage;
	CLODPropPage    m_lodPropPage;

// Operations
public:
	void Display(const LegoROI*, const LegoLOD*);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROIPropSheet)
	public:
	virtual BOOL OnInitDialog();
	protected:
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CROIPropSheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CROIPropSheet)
	afx_msg void OnClose();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	HICON m_hIcon;
};

/////////////////////////////////////////////////////////////////////////////
