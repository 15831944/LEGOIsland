// Lego.h : main header file for the LEGO application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLegoApp:
// See Lego.cpp for the implementation of this class
//

class CLegoDoc;
class CLegoView;

class CLegoApp : public CWinApp
{
public:
	CLegoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLegoApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

	BOOL IsAppActive() const;
	CLegoDoc* GetActiveLegoDoc();
    CLegoView* GetActiveLegoView();

// Implementation

	//{{AFX_MSG(CLegoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
