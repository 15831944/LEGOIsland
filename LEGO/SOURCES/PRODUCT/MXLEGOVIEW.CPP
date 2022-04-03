// MxLegoView.cpp : implementation file
//
#include "stdafx.h"
#include "MxLegoView.h"
#include "MxDirect3D.h"

#include "Town.h"       // MouseController

using namespace Tgl;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MxLegoView

BEGIN_MESSAGE_MAP(MxLegoView, TglWnd)
    //{{AFX_MSG_MAP(MxLegoView)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
 
void MxLegoView::Tickle()
{
    Render();
}

/////////////////////////////////////////////////////////////////////////////
// MxLegoView message handlers

void MxLegoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (GetController())
    {
        GetController()->LeftDown(point.x, point.y);
        SetCapture();
    }
}

void MxLegoView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (GetCapture() == this)
    {
        ReleaseCapture();
    }

    if (GetController())
    {
        GetController()->LeftUp(point.x, point.y);
    }
}

void MxLegoView::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if (GetController())
    {
        GetController()->RightDown(point.x, point.y);
        SetCapture();
    }
}

void MxLegoView::OnRButtonUp(UINT nFlags, CPoint point) 
{
    if (GetCapture() == this)
    {
        ReleaseCapture();
    }

    if (GetController())
    {
        GetController()->RightUp(point.x, point.y);
    }
}

void MxLegoView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (GetController())
    {
        if (nFlags & MK_LBUTTON)
        {
            GetController()->LeftDrag(point.x, point.y);
        }
        else
        {
            GetController()->RightDrag(point.x, point.y);	
        }
    }
}

