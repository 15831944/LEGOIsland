#ifndef _MxLegoView_h
#define _MxLegoView_h

// MxLegoView.h : header file
//

#include "TglWnd.h"

class MouseController;

/////////////////////////////////////////////////////////////////////////////
// MxLegoView window

class MxLegoView : public TglWnd
{
// Construction
protected:
    MxLegoView()    {}
    ~MxLegoView()   {}

// Attributes
public:

// Operations
public:
    virtual void    Tickle();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(MxLegoView)
	//}}AFX_VIRTUAL

// Implementation
public:
    // Generated message map functions
protected:
    //{{AFX_MSG(MxLegoView)
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    virtual MouseController*    GetController() = 0;
};

/////////////////////////////////////////////////////////////////////////////

#endif /* _MxLegoView_h */
