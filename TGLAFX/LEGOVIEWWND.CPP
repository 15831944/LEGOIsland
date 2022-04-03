#include "TglAfx.h"
#include "LegoViewWnd.h"
#include "MxDirect3D.h"
#include "Lego3DView.h"
#include "Controller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
// LegoViewWnd

BEGIN_MESSAGE_MAP(LegoViewWnd, MxDirect3DWnd)
    //{{AFX_MSG_MAP(LegoViewWnd)
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LegoViewWnd::LegoViewWnd()
{
    m_pLegoView             = 0;
    m_pMouseController      = 0;
    m_isActive              = FALSE;
    m_renderWhenNotActive   = FALSE;
    m_stopRendering         = FALSE;
    m_isInitialized         = FALSE;
    m_frameRate             = 0;
    m_renderingRate         = 0;
#ifdef _DEBUG
    m_triangleRate          = 0;
#endif
}

BOOL LegoViewWnd::Create(const char* windowName,
                         const CWnd* pParentWnd,
                         BOOL fullScreen,
                         int width, int height, int bitsPerPixel,
                         const PALETTEENTRY* pPaletteEntries,
                         int paletteEntryCount)
{
    BOOL    result;

    result = MxDirect3DWnd::Create(windowName, pParentWnd,
                                   fullScreen,
                                   width, height, bitsPerPixel,
                                   pPaletteEntries, paletteEntryCount);

    if (result)
    {
        m_isInitialized = TRUE;
    }

    return result;
}

BOOL LegoViewWnd::DestroyWindow()
{
    BOOL    result;

    result = MxDirect3DWnd::DestroyWindow();
    if (result)
    {
        m_isInitialized = FALSE;
    }

    return result;
}

void LegoViewWnd::OnSize(UINT nType, int cx, int cy) 
{
    if (DirectDraw() && DirectDraw()->IgnoreWM_SIZE())
    { 
        return;
    }

    m_isInitialized = FALSE;

    if (m_pLegoView)
    {
        m_pLegoView->Destroy();
        // ??? how to re-create LegoView (probably derived class), and
        //     how to add ROIs, set point of view etc.
        //     if LegoView had destroy/create surface it would be much easier...
    }

    MxDirect3DWnd::OnSize(nType, cx, cy);

    if (DirectDraw())
    {
        if (m_pLegoView)
        {
            ASSERT(0);
            //???
            //m_isInitialized = m_pLegoView->Create(...);
            // add rois
            // set point of view
            // ...
        }
    }
}

void LegoViewWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	MxDirect3DWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
    m_isActive = (nState != WA_INACTIVE);

    Tgl::Device*    pDevice = m_pLegoView ? m_pLegoView->GetDevice() : 0;

    if (pDevice)
    {
        // fActive = LOWORD(wParam);           // activation flag 
        // fMinimized = (BOOL) HIWORD(wParam); // minimized flag 
        pDevice->HandleActivate(MAKEWPARAM(nState, bMinimized));
    }
}

void LegoViewWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

    // ???
#if 0
    switch (nChar)
    {
    case 'n':
        SwitchToNextMode();
        break;
    case 'p':
        SwitchToPreviousMode();
        break;
    case '\r':
        ToggleFullscreen();
        break;
    }
#endif
	MxDirect3DWnd::OnChar(nChar, nRepCnt, nFlags);
}

void LegoViewWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
    if (m_pMouseController)
    {
        m_pMouseController->LeftDown(point.x, point.y);
        SetCapture();
    }
}

void LegoViewWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if (GetCapture() == this)
    {
        ReleaseCapture();
    }

    if (m_pMouseController)
    {
        m_pMouseController->LeftUp(point.x, point.y);
    }
}

void LegoViewWnd::OnRButtonDown(UINT nFlags, CPoint point) 
{
    if (m_pMouseController)
    {
        m_pMouseController->RightDown(point.x, point.y);
        SetCapture();
    }
}

void LegoViewWnd::OnRButtonUp(UINT nFlags, CPoint point) 
{
    if (GetCapture() == this)
    {
        ReleaseCapture();
    }

    if (m_pMouseController)
    {
        m_pMouseController->RightUp(point.x, point.y);
    }
}

void LegoViewWnd::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (m_pMouseController)
    {
        if (nFlags & MK_LBUTTON)
        {
            m_pMouseController->LeftDrag(point.x, point.y);
        }
        else
        {
            m_pMouseController->RightDrag(point.x, point.y);	
        }
    }
}

void LegoViewWnd::GetOutputTextTop(CString& rText)
{
    // rates may be huge if no, or little time, has elapsed
#ifdef _DEBUG
    rText.Format("%.1f fps (%.1f fps %.0f tps)",
                 (double) m_frameRate,
                 (double) m_renderingRate,
                 (double) m_triangleRate);
#else
    rText.Format("%.1f fps (%.1f fps)",
                 (double) m_frameRate,
                 (double) m_renderingRate);
#endif
}

void LegoViewWnd::GetOutputTextBottom(CString& rText)
{
    const MxDirectDraw::Mode&   currentMode = DirectDraw()->CurrentMode();

    rText.Format("%dx%dx%d",
                 (int) currentMode.width,
                 (int) currentMode.height,
                 (int) currentMode.bitsPerPixel);
}

double
LegoViewWnd::Render()
{
    double  renderTime = 0;

    if (m_pLegoView &&
        m_isInitialized && 
        //??? for now: LegoViewWnd never gets the activate message
        //(m_isActive || m_renderWhenNotActive) && 
        !m_stopRendering)
    {
        CString textTop;
        CString textBottom;

        GetOutputTextTop(textTop);
        GetOutputTextBottom(textBottom);

        DirectDraw()->RestoreSurfaces();

        if (!textTop.IsEmpty())
        {
            DirectDraw()->TextToTextSurface1(textTop);
        }

        if (!textBottom.IsEmpty())
        {
            DirectDraw()->TextToTextSurface2(textBottom);
        }

        // Clear the back-buffer and Z-buffer
        // ??? for now use ForceUpdate() (to clear the TextSurface areas) and Clear()
        {
            m_pLegoView->GetView()->ForceUpdate(0, 0, m_pLegoView->GetWidth(), m_pLegoView->GetHeight());
            m_pLegoView->GetView()->Clear();
        }

        renderTime = m_pLegoView->Render();
		m_pLegoView->GetDevice()->Update();

        if (!textTop.IsEmpty())
        {
            DirectDraw()->TextSurface1ToBackBuffer();
        }

        if (!textBottom.IsEmpty())
        {
            DirectDraw()->TextSurface2ToBackBuffer();
        }

        // Flip or blt
        if (DirectDraw()->IsFullScreen())
        {  
            DirectDraw()->Flip();
        }
        else
        {
            CRect   clientRect;
            CRect   screenRect; // destination rectangle in front buffer

            GetClientRect(&clientRect);
            screenRect = clientRect;
            ClientToScreen(screenRect);

            // ??? be smarter about what to update
            DirectDraw()->BltBackBuffer(screenRect, clientRect);
        }

        // update statistics every 20 frames
        if ((m_pLegoView->GetFrameCount() % 20) == 0)
        {
            m_frameRate     = m_pLegoView->GetFrameRate();
            m_renderingRate = m_pLegoView->GetRenderingRate();
#ifdef _DEBUG
            m_triangleRate  = m_pLegoView->GetTriangleRate();
#endif
        }
    }

    return renderTime;
}
