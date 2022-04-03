// MxDirect3DWnd.h : header file
//

#include "MxDirectDrawWnd.h"

class MxDirect3D;

/////////////////////////////////////////////////////////////////////////////
// MxDirect3DWnd window

class MxDirect3DWnd : public MxDirectDrawWnd
{
// Construction
public:
	MxDirect3DWnd();

// Attributes
public:
    MxDirect3D* Direct3D() { return (MxDirect3D*) DirectDraw(); }

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MxDirect3DWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MxDirect3DWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(MxDirect3DWnd)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    MxDirectDraw*   CreateDirectDraw();
};

/////////////////////////////////////////////////////////////////////////////
