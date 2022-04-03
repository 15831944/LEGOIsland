// ProgressDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CProgressDlg dialog

class CProgressDlg : public CDialog
{
    typedef void (CWnd::*NotificationFn)();
// Construction
public:
	CProgressDlg(CWnd* pParent = NULL);   // standard constructor

    CProgressCtrl&  ProgressCtrl() { return m_progress; }
    void            SetNotification(CWnd* pNotificationWnd,
                                    UINT pauseNotificationMsg,
                                    UINT continueNotificationMsg,
                                    UINT cancelNotificationMsg);

// Dialog Data
	//{{AFX_DATA(CProgressDlg)
	enum { IDD = IDD_PROGRESS };
	CProgressCtrl	m_progress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CProgressDlg)
	virtual void OnCancel();
	afx_msg void OnPause();
	afx_msg void OnContinue();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    CWnd*   m_pNotificationWnd;
    UINT    m_pauseNotificationMsg;
    UINT    m_continueNotificationMsg;
    UINT    m_cancelNotificationMsg;
};
