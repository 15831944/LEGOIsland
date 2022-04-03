// RealismDlg.h : header file
//

#include <afxcmn.h>
#include "MxStd.h"
#include "MxCore.h"
#include "TimeAverage.h"

class ViewManager;

/////////////////////////////////////////////////////////////////////////////
// CRealismDlg dialog

class CRealismDlg : public CDialog, public MxCore
{
// Construction
public:
	CRealismDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRealismDlg();

// Dialog Data
	//{{AFX_DATA(CRealismDlg)
	enum { IDD = IDD_REALISM };
	CStatic	m_currentRenderTime;
	CStatic	m_renderTime;
	CSliderCtrl	m_realism;
	CStatic m_frameTimeMin;
	CStatic m_frameTimeMax;
	CStatic m_frameTimeAverage;
	CStatic m_frameTimeRequested;
	CStatic m_frameRateMin;
	CStatic m_frameRateMax;
	CStatic m_frameRateAverage;
	CStatic m_frameRateRequested;
    CStatic m_notificationButtonDown;
    CStatic m_notificationButtonDownTime;
    CStatic m_notificationButtonDownAverageTime;
    CStatic m_notificationButtonDownFrameTime;
    CStatic m_notificationMouseMove;
    CStatic m_notificationMouseMoveTime;
    CStatic m_notificationMouseMoveAverageTime;
    CStatic m_notificationMouseMoveFrameTime;
	//}}AFX_DATA

    void    SetViewManager(ViewManager*);

    // For profiling only
    static void StartEventTrace(MxS16 p_event);
    static void EndEventTrace(MxS16 p_event);

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
	virtual MxResult Tickle() { UpdateStaticText(); return SUCCESS; }

private:
    ViewManager*  m_pViewManager;
	TimeAverage m_timeAverage;

    // For profiling only
    static MxTime	m_leftMouseDownStart;
    static MxTime	m_leftMouseDownSum;
    static MxU32   m_leftMouseDownEventCount;
    static MxTime	m_mouseMoveStart;
    static MxTime	m_mouseMoveSum;
    static MxU32   m_mouseMoveCount;
};
