// TglWnd.cpp : implementation file

#include "TglAfx.h"
#include "TglWnd.h"
#include "MxDirect3D.h"

using namespace Tgl;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TglWnd


TglWnd::TglWnd()
{
    m_pRenderer                 = 0;
    m_pDevice                   = 0;
    m_pView                     = 0;

    m_isActive                  = FALSE;
    m_renderWhenNotActive       = FALSE;
    m_stopRendering             = FALSE;
    m_isInitialized             = FALSE;

    // statistics
    m_frameCount                = 0;
#ifdef _DEBUG
    m_triangleCount             = 0;
#endif
    m_frameRate                 = 0;
    m_renderingRate             = 0;
#ifdef _DEBUG
    m_triangleRate              = 0;
#endif
}

TglWnd::~TglWnd()
{
}

BOOL TglWnd::DestroyWindow()
{
    DestroyDevice();

    return MxDirect3DWnd::DestroyWindow();
}

BOOL TglWnd::Create(const CString& windowName,
                    const CWnd* pParentWnd,
                    Renderer* pRenderer,
                    BOOL fullScreen,
                    int width,
                    int height,
                    int bitsPerPixel,
                    const PALETTEENTRY* pPaletteEntries,
                    int paletteEntryCount)
{
    if (!MxDirect3DWnd::Create(windowName, pParentWnd,
                               fullScreen, width, height, bitsPerPixel,
                               pPaletteEntries, paletteEntryCount))
    {
        return FALSE;
    }

    m_pRenderer = pRenderer;

    m_pDevice   = CreateDevice();
    if (!m_pDevice)
    {
        return FALSE;
    }

    m_pView     = CreateView();
    if (!m_pView)
    {
        return FALSE;
    }

    m_isActive      = TRUE;
    m_isInitialized = TRUE;

    return TRUE;
}

Device* TglWnd::CreateDevice()
{                    
    Device*                     pDevice;

#if 0
    DeviceDirect3DCreateData    createData = {
                                                Direct3D()->Direct3D(),
                                                Direct3D()->Direct3DDevice()
                                             };
#else
    DeviceDirectDrawCreateData  createData = {
                                                0, // const GUID*
                                                GetSafeHwnd(),
                                                DirectDraw()->DirectDraw(),
                                                DirectDraw()->FrontBuffer(),
                                                DirectDraw()->BackBuffer(),
                                                DirectDraw()->Palette(),
                                                DirectDraw()->IsFullScreen()
                                             };
#endif

    pDevice = m_pRenderer->CreateDevice(createData);
    ASSERT(pDevice); 

    if (pDevice)
    {
        ColorModel      colorModel = Ramp;
        ShadingModel    shadingModel = Gouraud;
	    int             shadeCount = 32;
	    BOOL            dither = TRUE;
	    int             textureShadeCount = -1;
	    int             textureColorCount = -1;
        int             bitsPerPixel = DirectDraw()->CurrentMode().bitsPerPixel;
        BOOL            result;

        if (bitsPerPixel == 1)
	    {
		    shadeCount          = 4;
		    textureShadeCount	= 4;
        }
        else if (bitsPerPixel == 16)
        {
		    shadeCount          = 32;
		    dither              = FALSE;
		    textureShadeCount	= 32;
		    textureColorCount	= 64;
        }
        else if (bitsPerPixel >= 24)
        {
		    shadeCount          = 256;
		    dither              = FALSE;
		    textureShadeCount   = 256;
		    textureColorCount   = 64;
        }
        else
        {
            dither              = FALSE;
        }

        result = pDevice->SetColorModel(colorModel);
        ASSERT(result);
        result = pDevice->SetShadingModel(shadingModel);
        ASSERT(result);
        result = pDevice->SetShadeCount(shadeCount);
        ASSERT(result);
        result = pDevice->SetDither(dither);
        ASSERT(result);

        m_frameRateMeter.Reset();
        m_renderingRateMeter.Reset();
#ifdef _DEBUG
        m_triangleRateMeter.Reset();
#endif
        m_frameRateMeter.StartOperation();
    }

    return pDevice;
} 

void TglWnd::DestroyDevice()
{
    // first destroy the view
    DestroyView();

    delete m_pDevice;
    m_pDevice = 0;
}

void TglWnd::DestroyView()
{
    delete m_pView;
    m_pView  = 0;
}

BOOL TglWnd::SwitchMode(BOOL isFullScreen,
                        int width, int height, int bitsPerPixel)
{
    m_isInitialized = FALSE;

    DestroyView();
    DestroyDevice();

    DirectDraw()->DestroyButNotDirectDraw();
    DirectDraw()->Create(GetSafeHwnd(), isFullScreen,
                         width, height, bitsPerPixel,
                         PaletteEntries(), PaletteEntryCount());

    m_pDevice   = CreateDevice();
    m_pView     = CreateView();

    m_isInitialized = (m_pDevice != 0) && (m_pView != 0);

    return m_isInitialized;
}

BEGIN_MESSAGE_MAP(TglWnd, MxDirect3DWnd)
    //{{AFX_MSG_MAP(TglWnd)
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
 
void TglWnd::Render()
{
    if (m_isInitialized && 
        (m_isActive || m_renderWhenNotActive) && 
        !m_stopRendering)
    {
#ifdef _DEBUG
        m_triangleRateMeter.StartOperation();
#endif
        m_renderingRateMeter.StartOperation();
        DoRender();
        m_renderingRateMeter.EndOperation();
#ifdef _DEBUG
        m_triangleRateMeter.EndOperation();
#endif

        m_frameRateMeter.EndOperation();

#ifdef _DEBUG
        {
            unsigned long triangleCount = m_pDevice->GetDrawnTriangleCount();

            m_triangleRateMeter.IncreaseOperationCount(triangleCount - m_triangleCount - 1);
            m_triangleCount  = triangleCount;
        }
#endif

        // update statistics every 20 frames
        if ((++m_frameCount % 20) == 0)
        {
            m_frameRate     = m_frameRateMeter.Frequency();
            m_renderingRate = m_renderingRateMeter.Frequency();
#ifdef _DEBUG
            m_triangleRate  = m_triangleRateMeter.Frequency();
#endif
        }

        // reset rate meters every 20 frames
        if ((++m_frameCount % 20) == 0)
        {
            m_frameRateMeter.Reset();
            m_renderingRateMeter.Reset();
#ifdef _DEBUG
            m_triangleRateMeter.Reset();
#endif
        }

        m_frameRateMeter.StartOperation();
    }
}

void
TglWnd::DoRender()
{
    CRect   clientRect;
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

    // ??? be smarter about what to update
    // ??? make sure back buffer is updated correctly
    GetClientRect(&clientRect);
    m_pView->ForceUpdate(0 , 0, clientRect.Width(), clientRect.Height());


    m_pView->Clear();
    m_pView->Render(GetScene());
    m_pDevice->Update();


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
        CRect   screenRect; // destination rectangle in front buffer

        screenRect = clientRect;
        ClientToScreen(screenRect);

        // ??? be smarter about what to update
        DirectDraw()->BltBackBuffer(screenRect, clientRect);
    }
}

void TglWnd::GetOutputTextTop(CString& rText)
{
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

void TglWnd::GetOutputTextBottom(CString& rText)
{
    const MxDirectDraw::Mode&   currentMode = DirectDraw()->CurrentMode();

    rText.Format("%dx%dx%d",
                 (int) currentMode.width,
                 (int) currentMode.height,
                 (int) currentMode.bitsPerPixel);
}

/////////////////////////////////////////////////////////////////////////////
// TglWnd message handlers

void TglWnd::OnSize(UINT nType, int cx, int cy) 
{
    if (DirectDraw() && DirectDraw()->IgnoreWM_SIZE())
    { 
        return;
    }

    m_isInitialized = FALSE;

    DestroyView();
    DestroyDevice();

    MxDirect3DWnd::OnSize(nType, cx, cy);

    if (DirectDraw())
    {
        m_pDevice   = CreateDevice();
        m_pView     = CreateView();
    }

    m_isInitialized = (m_pDevice != 0) && (m_pView != 0);
}

void TglWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	MxDirect3DWnd::OnActivate(nState, pWndOther, bMinimized);
	
	// TODO: Add your message handler code here
    m_isActive = (nState != WA_INACTIVE);	
}

void TglWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default

    // ???
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
	MxDirect3DWnd::OnChar(nChar, nRepCnt, nFlags);
}

BOOL TglWnd::ToggleFullscreen() 
{
    int width;
    int height;
    int bitsPerPixel;
    int isFullScreen;

    if (DirectDraw()->IsFullScreen())
    {
        // switching to window mode - use previous window size
        // ???
        isFullScreen    = FALSE;
        width           = 320;
        height          = 200;
        bitsPerPixel    = 16;
    }
    else
    {
        // switching to fullscreen mode - use a supported mode
        isFullScreen    = TRUE;
        width           = DirectDraw()->GetMode(0).width;
        height          = DirectDraw()->GetMode(0).height;
        bitsPerPixel    = DirectDraw()->GetMode(0).bitsPerPixel;
    }

    return SwitchMode(isFullScreen, width, height, bitsPerPixel);
}

BOOL TglWnd::SwitchToNextMode() 
{
    if (DirectDraw()->IsFullScreen())
    {
        int modeCount = DirectDraw()->ModeCount();
        int i;

        for (i = 0; i < modeCount; i++)
        {
            if (DirectDraw()->CurrentMode() == DirectDraw()->GetMode(i))
            {
                break;
            }
        }

        i++;
        if (i >= modeCount)
        {
            i = 0;
        }

        return SwitchMode(DirectDraw()->IsFullScreen(),
                          DirectDraw()->GetMode(i).width,
                          DirectDraw()->GetMode(i).height,
                          DirectDraw()->GetMode(i).bitsPerPixel);
    }
    else
    {
        return TRUE;
    }
}

BOOL TglWnd::SwitchToPreviousMode() 
{
    if (DirectDraw()->IsFullScreen())
    {
        int modeCount = DirectDraw()->ModeCount();
        int i;

        for (i = 0; i < modeCount; i++)
        {
            if (DirectDraw()->CurrentMode() == DirectDraw()->GetMode(i))
            {
                break;
            }
        }

        i--;
        if (i < 0)
        {
            i = modeCount - 1;
        }

        return SwitchMode(DirectDraw()->IsFullScreen(),
                          DirectDraw()->GetMode(i).width,
                          DirectDraw()->GetMode(i).height,
                          DirectDraw()->GetMode(i).bitsPerPixel);
    }
    else
    {
        return TRUE;
    }
}

