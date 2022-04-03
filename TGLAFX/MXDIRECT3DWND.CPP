// MxDirect3DWnd.cpp : implementation file
//
#include "TglAfx.h"
#include "MxDirect3DWnd.h"
#include "MxDirect3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MxDirect3DWnd

MxDirect3DWnd::MxDirect3DWnd()
{
}

MxDirect3DWnd::~MxDirect3DWnd()
{
}


BEGIN_MESSAGE_MAP(MxDirect3DWnd, MxDirectDrawWnd)
	//{{AFX_MSG_MAP(MxDirect3DWnd)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MxDirect3DWnd message handlers

MxDirectDraw*
MxDirect3DWnd::CreateDirectDraw()
{
    return new MxDirect3D;
}
