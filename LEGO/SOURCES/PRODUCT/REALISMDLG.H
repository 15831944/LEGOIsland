// RealismDlg.h : header file
//

class ViewManager;

/////////////////////////////////////////////////////////////////////////////
// CRealismDlg dialog

class CRealismDlg : public CDialog
{
// Construction
public:
	CRealismDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRealismDlg)
	enum { IDD = IDD_REALISM };
	CStatic	m_currentRenderTime;
	CStatic	m_currentRenderRate;
	CStatic	m_renderRate;
	CStatic	m_renderTime;
	CSliderCtrl	m_realism;
	//}}AFX_DATA

    void    SetViewManager(ViewManager*);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRealismDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRealismDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    UpdateStaticText();
    void    SaveToRegistry(int);
    int     LoadFromRegistry();

private:
    ViewManager*  m_pViewManager;
};
