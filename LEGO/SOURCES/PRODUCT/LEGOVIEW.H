// LegoView.h : interface of the CLegoView class
//
/////////////////////////////////////////////////////////////////////////////

class MxLegoCitizenView;
class MxLegoEditorView;
class MxLegoView;
class ViewLODListManager;

class CLegoView : public CView
{
protected: // create from serialization only
	CLegoView();
	DECLARE_DYNCREATE(CLegoView)

// Attributes
public:
	CLegoDoc*   GetDocument();


    MxLegoCitizenView* GetLegoCitizenView() { return m_pCitizenView; }

// Operations
public:
    void Tickle();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLegoView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLegoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    // Generated message map functions
protected:
    //{{AFX_MSG(CLegoView)
	afx_msg void OnDestroy();
	afx_msg void OnEditorSelectnext();
	afx_msg void OnUpdateEditorSelectnext(CCmdUI* pCmdUI);
	afx_msg void OnEditorRemoveAll();
	afx_msg void OnUpdateEditorRemoveAll(CCmdUI* pCmdUI);
	afx_msg void OnEditorSelectprevious();
	afx_msg void OnUpdateEditorSelectprevious(CCmdUI* pCmdUI);
	afx_msg void OnEditorRemove();
	afx_msg void OnUpdateEditorRemove(CCmdUI* pCmdUI);
	afx_msg void OnViewEditor();
	afx_msg void OnUpdateViewEditor(CCmdUI* pCmdUI);
	afx_msg void OnViewCitizen();
	afx_msg void OnUpdateViewCitizen(CCmdUI* pCmdUI);
	afx_msg void OnViewRenderwhennotactive();
	afx_msg void OnUpdateViewRenderwhennotactive(CCmdUI* pCmdUI);
	afx_msg void OnTownLoadmodel();
	afx_msg void OnUpdateTownLoadmodel(CCmdUI* pCmdUI);
	afx_msg void OnTownLoadpillars();
	afx_msg void OnUpdateTownLoadpillars(CCmdUI* pCmdUI);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    void    DestroyCurrentView();

private:
    int                 m_bitsPerPixel;
    PALETTEENTRY        m_paletteEntry[256];
    int                 m_paletteEntryCount;

    MxLegoCitizenView*    m_pCitizenView;
    MxLegoEditorView*     m_pEditorView;
    MxLegoView*           m_pCurrentView;

    ViewLODListManager*     m_pViewLODListManager;
};

#ifndef _DEBUG  // debug version in LegoView.cpp
inline CLegoDoc* CLegoView::GetDocument()
   { return (CLegoDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////
