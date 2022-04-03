// RVWeightsDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRVWeightsDlg dialog

class CRVWeightsDlg : public CDialog
{
// Construction
public:
	CRVWeightsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRVWeightsDlg)
	enum { IDD = IDD_REALTIMEVIEW_WEIGHTS };
	CStatic	m_sensitivityText;
	CSpinButtonCtrl	m_sensitivity;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRVWeightsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRVWeightsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnClose();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    ConfigureSliders();
    void    SetValueFromSliderPos(int index, int sliderPos);
    int     GetSliderPosForValue(int index);
    void    GetTextForValue(int index, CString&);
    void    GetTextForSensitivity(CString&);
    void    UpdateValueText(int index);
    void    UpdateSensitivityText();

    void SaveWeightsToRegistry();
    void LoadWeightsFromRegistry();

private:
    double**    m_pWeights;
};
