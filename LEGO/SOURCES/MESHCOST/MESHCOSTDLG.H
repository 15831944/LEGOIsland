// MeshCostDlg.h : header file
//

#include "LegoStorage.h"
#include "LegoAnim.h"
#include "CostCalculation.h"

class LegoLOD;
class CProgressDlg;
class ViewLODListManager;
class LegoView1;
class LegoViewWnd;

/////////////////////////////////////////////////////////////////////////////
// CMeshCostDlg dialog

#define WM_USER_CALCULATION_DONE        (WM_USER + 0x100 + 1)
#define WM_USER_CALCULATION_IN_PROGRESS (WM_USER + 0x100 + 2)
#define WM_USER_CALCULATION_CANCEL      (WM_USER + 0x100 + 3)
#define WM_USER_CALCULATION_PAUSE       (WM_USER + 0x100 + 4)
#define WM_USER_CALCULATION_CONTINUE    (WM_USER + 0x100 + 5)

class CMeshCostDlg : public CDialog
{

// Construction
public:
	CMeshCostDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMeshCostDlg)
	enum { IDD = IDD_MESHCOST_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMeshCostDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMeshCostDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLoadModel();
	afx_msg void OnSave();
	afx_msg void OnCalculateCost();
	//}}AFX_MSG
	LRESULT OnCalculationInProgress(WPARAM wParam, LPARAM lParam);
	LRESULT OnCalculationDone(WPARAM wParam, LPARAM lParam);
	LRESULT OnCalculationPause(WPARAM wParam, LPARAM lParam);
	LRESULT OnCalculationContinue(WPARAM wParam, LPARAM lParam);
	LRESULT OnCalculationCancel(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

    int         LODCount(const ROI*);
    int         LODCount(LegoROI**, int);

private:
    LegoROI**       m_pROIs;
    LegoAnim*       m_trees;
	int             m_roiCount;
    CString         m_pathName;

    LegoView1*          m_pLegoView;
    LegoViewWnd*        m_pLegoViewWnd;
    CProgressDlg*       m_pProgressDlg;

    CWinThread*         m_pCalculationThread;
    CostCalculation     m_costCalculation;

    Tgl::Renderer*      m_pRenderer;
    ViewLODListManager* m_pViewLodListManager;
};
