// ROIInspectorView.h : interface of the CROIInspectorView class
//

#include "ROITreeCtrl.h"
#include "LegoView1.h"
#include "ROIInspectorController.h"
#include "LegoViewWnd.h"
#include "ViewLODList.h"            // ViewLODListManager

class CROIPropSheet;
class ViewROI;
class ViewLOD;
class ROIInspectorROI;
class BoundingBox;
class BoundingSphere;
class LegoAnim;
class CAnimateDlg;

/////////////////////////////////////////////////////////////////////////////

#define ID_ROITREECTRL 1000

class CROIInspectorView : public CView 
{
protected: // create from serialization only
	CROIInspectorView();
	DECLARE_DYNCREATE(CROIInspectorView)

// Attributes
public:
	CROIDoc*    GetDocument();

// Operations
public:
    void    Tickle();
    void    AddToScene(const ViewROI*, const ViewLOD*, unsigned long vertexCount);
    void    RemoveFromeScene(const ViewROI*, const ViewLOD*);
    void    RemoveAllFromScene();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROIInspectorView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CROIInspectorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Generated message map functions
protected:
	//{{AFX_MSG(CROIInspectorView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnViewReset();
	afx_msg void OnViewRemoveAll();
	afx_msg void OnUpdateViewRemoveAll(CCmdUI* pCmdUI);
	afx_msg void OnOptionsViewMultipleLods();
	afx_msg void OnUpdateOptionsViewMultipleLods(CCmdUI* pCmdUI);
	afx_msg void OnOptionsUseShortNames();
	afx_msg void OnUpdateOptionsUseShortNames(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnViewLods();
	afx_msg void OnUpdateViewLods(CCmdUI* pCmdUI);
	afx_msg void OnViewProperties();
	afx_msg void OnUpdateViewProperties(CCmdUI* pCmdUI);
	afx_msg void OnOptionsFitInWindow();
	afx_msg void OnUpdateOptionsFitInWindow(CCmdUI* pCmdUI);
	afx_msg void OnToolsCalculateCosts();
	afx_msg void OnUpdateToolsCalculateCosts(CCmdUI* pCmdUI);
	afx_msg void OnViewAxis();
	afx_msg void OnUpdateViewAxis(CCmdUI* pCmdUI);
	afx_msg void OnOptionsConfigureAxis();
	afx_msg void OnViewLodAxis();
	afx_msg void OnUpdateViewLodAxis(CCmdUI* pCmdUI);
	afx_msg void OnOptionsConfigureLODAxis();
	afx_msg void OnAnimationOpen();
	afx_msg void OnUpdateAnimationOpen(CCmdUI* pCmdUI);
	afx_msg void OnAnimationSetoriginal();
	afx_msg void OnUpdateAnimationSetoriginal(CCmdUI* pCmdUI);
	afx_msg void OnAnimationAnimate();
	afx_msg void OnUpdateAnimationAnimate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	afx_msg void OnSelchangedRoiTree(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnRButtonClkRoiTree(NMHDR* pNMHDR, LRESULT* pResult);
	DECLARE_MESSAGE_MAP()

    void    MoveCameraOutsideBoundingSphere();
    void    AddMultipleToScene(const ViewROI* pROI,
                               int partsDepth,
                               int lodNumber,
                               BOOL isLodNumberRelative);
    Tgl::Group* CreateAxis(Tgl::Renderer*, const Vector3&, const Vector3&,
                           double r, double g, double b);
    Tgl::Mesh*  CreateAxisMesh(Tgl::Renderer*, const Vector3&, const Vector3&,
                               double r, double g, double b);
    void        AddAxis();
    void        RemoveAxis();
    void        AddAxis(const ViewROI*);

private:
	CROITreeCtrl            m_roiTreeCtrl;
    CROIPropSheet*          m_pROIPropSheet;

    Tgl::Renderer*          m_pRenderer;
    ViewLODListManager      m_viewLODListManager;
    LegoView1               m_legoView;
    LegoViewWnd             m_legoViewWnd;
    ROIInspectorController  m_controller;
    Tgl::Group*             m_pAxis;
    BOOL                    m_lodAxis;
    Vector3                 m_axisMin;
    Vector3                 m_axisMax;
    double                  m_axisColor[3];
    BOOL                    m_isAxisMinMaxRelative;
    Vector3                 m_lodAxisMin;
    Vector3                 m_lodAxisMax;
    double                  m_lodAxisColor[3];
    BOOL                    m_isLODAxisMinMaxRelative;

    // m_pROI  - ROI that will be used to view LODs
    // When an LOD is being viewed, its geometry (Tgl::Group) is added
    // to m_pROI LOD's geometry (Tgl::Group)
    ROIInspectorROI*        m_pROI;
    
    BOOL                    m_fitInWindow;
    BOOL                    m_viewMultipleLODs;

    double                  m_renderTimeLastFrame;

    LegoAnim*               m_animations;
    unsigned long           m_animationCount;

    CAnimateDlg*            m_pAnimateDlg;
};

#ifndef _DEBUG  // debug version in ROIInspectorView.cpp
inline CROIDoc* CROIInspectorView::GetDocument()
   { return (CROIDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
