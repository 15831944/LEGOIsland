// AnimateDlg.h : header file
//

class LegoROI;
class LegoAnim;

/////////////////////////////////////////////////////////////////////////////
// CAnimateDlg dialog

class CAnimateDlg : public CDialog
{
// Construction
public:
	CAnimateDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAnimateDlg)
	enum { IDD = IDD_ANIMATE };
	CSliderCtrl	m_timeSlider;
	CString	m_maxTime;
	CString	m_time;
	//}}AFX_DATA

    void Set(LegoROI*, int, LegoAnim*);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnimateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAnimateDlg)
	afx_msg void OnClose();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    LegoROI*    m_pROI;
    int         m_animationCount;
    LegoAnim*   m_pAnimations;
};
