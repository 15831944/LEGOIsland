#ifndef _LegoViewWnd_h
#define _LegoViewWnd_h

#include "MxDirect3DWnd.h"

class LegoView;
class MouseController;

/////////////////////////////////////////////////////////////////////////////
//
// LegoViewWnd
// ??? temporary to deliver mouse events

class LegoViewWnd : public MxDirect3DWnd
{
// Construction
public:
    LegoViewWnd();
    BOOL    Create(const char* windowName,
                   const CWnd* pParentWnd,
                   BOOL fullScreen,
                   int width, int height, int bitsPerPixel,
                   const PALETTEENTRY* pPaletteEntries,
                   int paletteEntryCount);

    void    SetLegoView(LegoView* pLegoView) { m_pLegoView = pLegoView; }
    void    SetMouseController(MouseController* pMouseController) { m_pMouseController = pMouseController; }
    
    MouseController*    GetMouseController() const { return m_pMouseController; }

// Attributes
public:

// Operations
public:
    double  Render();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(LegoViewWnd)
	//}}AFX_VIRTUAL

    BOOL    DestroyWindow();

// Implementation
public:
    // Generated message map functions
protected:
    //{{AFX_MSG(LegoViewWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    void    GetOutputTextTop(CString&);
    void    GetOutputTextBottom(CString&);

private:
    LegoView*           m_pLegoView;
    MouseController*    m_pMouseController;
    BOOL                m_isActive;
    BOOL                m_isInitialized;
    BOOL                m_renderWhenNotActive;
    BOOL                m_stopRendering;
    double              m_frameRate;
    double              m_renderingRate;
#ifdef _DEBUG
    double              m_triangleRate;
#endif
};

#endif /* _LegoViewWnd_h */