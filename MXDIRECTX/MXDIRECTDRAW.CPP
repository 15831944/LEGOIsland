#include "MxDirectX.h"
#include "assert.h"

#define TRACE Trace
#define RELEASE(x) if (x != NULL) {x->Release(); x = NULL;}

#ifdef _DEBUG

extern "C" int vsprintf(char *, const char *, va_list);

void Trace(const char* format, ...)
{
	va_list args;
	int     count;
	char    buffer[512];

	va_start(args, format);
	count = vsprintf(buffer, format, args);
	va_end(args);

    OutputDebugString(buffer);
}

#else

inline void Trace(const char*, ...) {}

#endif /* _DEBUG */

//////////////////////////////////////////////////////////////////////////////
//
// MxDirectDraw

MxDirectDraw::MxDirectDraw()
{
    m_pFrontBuffer          = 0;
    m_pBackBuffer           = 0;
    m_pZBuffer              = 0;
    m_pClipper              = 0;
    m_pPalette              = 0;
    m_pDirectDraw           = 0;
    m_bIsOnPrimaryDevice    = TRUE;
    m_pText1Surface         = 0;
    m_pText2Surface         = 0;
    memset(&m_HWddsCaps, 0, sizeof(m_HWddsCaps));

    // instead of AppInfo app
    m_hWndMain              = 0;
    m_modeCount             = 0;
    m_bIgnoreWM_SIZE        = FALSE;

    // Parameters and status flags
    m_bPrimaryPalettized    = FALSE;
    m_bOnlySystemMemory     = FALSE;

    memset(&m_guid, 0, sizeof(m_guid));
    m_bFullScreen           = FALSE;
    m_bOnlySoftRender       = FALSE;

    m_pauseCount            = 0;

    m_pErrorHandler         = 0;
    m_pFatalErrorHandler    = 0;
    m_pErrorHandlerArg      = 0;
    m_pFatalErrorHandlerArg = 0;
}

MxDirectDraw::~MxDirectDraw()
{
    Destroy();
}

BOOL
MxDirectDraw::Create(HWND hWnd,
                     BOOL fullScreen,
                     int width, int height, int bpp,
                     const PALETTEENTRY* pPaletteEntries,
                     int paletteEntryCount)
{
    //assert(!m_hWndMain);

    // ??? we should reset all data members

    m_hWndMain  = hWnd;

    if (!m_pDirectDraw)
    {
        CacheOriginalPaletteEntries();

        if (!DDCreate())
        {
            return FALSE;
        }
    }

    // if DirectDraw is not on primary display, assume it only does fullscreen
    if (!m_bIsOnPrimaryDevice)
    {
        fullScreen = TRUE;
    }

    if (!DDInit(fullScreen))
    {
        return FALSE;
    }

    if (!SetPaletteEntries(pPaletteEntries, paletteEntryCount, fullScreen))
    {
        return FALSE;
    }

    if (!DDSetMode(width, height, bpp))
    {
        return FALSE;
    }

    return TRUE;
}

// Save the original palette for when we are paused
// In case we start in fullScreen, put it in m_paletteEntries
BOOL MxDirectDraw::CacheOriginalPaletteEntries()
{
    HDC hdc;

    hdc = GetDC(NULL);
    GetSystemPaletteEntries(hdc, 0, (1 << 8), &m_originalPaletteEntries[0]);
#if 0
    for (i = 0; i < 256; i++)
    {
        m_paletteEntries[i] = m_originalPaletteEntries[i];
    }
#endif
    ReleaseDC(NULL, hdc);

    return TRUE;
}


BOOL MxDirectDraw::SetPaletteEntries(const PALETTEENTRY* pPaletteEntries,
                                     int paletteEntryCount,
                                     BOOL fullScreen)
{
    int reservedLowEntryCount;
    int reservedHighEntryCount;
    HDC hdc;
    int i;

    hdc = GetDC(NULL);
    // start out with system palette
    GetSystemPaletteEntries(hdc, 0, (1 << 8), m_paletteEntries);
    ReleaseDC(NULL, hdc);

    if (fullScreen)
    {
        reservedLowEntryCount = 1;
        reservedHighEntryCount = 1;
    }
    else
    {
        reservedLowEntryCount = 10;
        reservedHighEntryCount = 10;
    }

    for (i = 0; i < reservedLowEntryCount; i++)
    {
        m_paletteEntries[i].peFlags = D3DPAL_READONLY;
    }
    
    for (i = reservedLowEntryCount; i < 256 - reservedHighEntryCount; i++)
    {
        m_paletteEntries[i].peFlags = D3DPAL_READONLY;
    }

    for (i = 256 - reservedHighEntryCount; i < 256; i++)
    {
        m_paletteEntries[i].peFlags = D3DPAL_READONLY;
    }

    // then replace entries as specified
    assert(paletteEntryCount <= (sizeof(m_paletteEntries) / sizeof(m_paletteEntries[0])));
    // ??? In fullscreen:  should we set entry 0 and 255
    //     In window mode: should we set entry 0-9 and 246-255
    for (i = reservedLowEntryCount;
         (i < paletteEntryCount) && (i < 256 - reservedHighEntryCount);
         i++)
    {
        m_paletteEntries[i].peRed   = pPaletteEntries[i].peRed;
        m_paletteEntries[i].peGreen = pPaletteEntries[i].peGreen;
        m_paletteEntries[i].peBlue  = pPaletteEntries[i].peBlue;
    }

    if (m_pPalette)
    {
        HRESULT result;

        result = m_pPalette->SetEntries(0, 0, 
                                        sizeof(m_paletteEntries)/sizeof(m_paletteEntries[0]),
                                        m_paletteEntries);
        if (result != DD_OK)
        {
            Error("SetEntries failed", result);
            return FALSE;
        }
    }

    return TRUE;
}

// Releases all objects, scene, textures and other memory.
void
MxDirectDraw::Destroy()
{
    DestroyButNotDirectDraw();
    RELEASE(m_pDirectDraw);

    // ??? reset other members, or in Create()
    m_bIsOnPrimaryDevice    = TRUE;
}

// Releases all objects, scene, textures and other memory except DirectDraw
void
MxDirectDraw::DestroyButNotDirectDraw()
{
    //???
    RestoreOriginalPaletteEntries();

    if (m_bFullScreen)
    {
        if (m_pDirectDraw)
        {
            m_bIgnoreWM_SIZE = TRUE;
            m_pDirectDraw->RestoreDisplayMode();
            m_bIgnoreWM_SIZE = FALSE;
        }
    }

    RELEASE(m_pPalette);
    RELEASE(m_pClipper);
    RELEASE(m_pText1Surface);
    RELEASE(m_pText2Surface);
    RELEASE(m_pZBuffer);
    RELEASE(m_pBackBuffer);
    RELEASE(m_pFrontBuffer);
}

void MxDirectDraw::SetErrorHandler(ErrorHandler errorHandler, void* pArg)
{
    m_pErrorHandler         = errorHandler;
    m_pErrorHandlerArg      = pArg;
}

void MxDirectDraw::SetFatalErrorHandler(ErrorHandler errorHandler, void* pArg)
{
    m_pFatalErrorHandler         = errorHandler;
    m_pFatalErrorHandlerArg      = pArg;
}

/*************************************************************************
  DirectDraw functions
 *************************************************************************/                                                

// Checks to see if there is enough free video memory
long
MxDirectDraw::FreeVideoMemory()
{
    HRESULT result;
    DDCAPS  ddcaps;

    memset(&ddcaps, 0, sizeof(ddcaps));
    ddcaps.dwSize = sizeof( ddcaps );
    result = m_pDirectDraw->GetCaps(&ddcaps, NULL );
    if(result != DD_OK )
    {
        Error("GetCaps failed while checking for free memory", result);
        return FALSE;
    }
    return ddcaps.dwVidMemFree;
}

long
MxDirectDraw::TotalVideoMemory()
{
    HRESULT result;
    DDCAPS  ddcaps;

    memset(&ddcaps, 0, sizeof(ddcaps));
    ddcaps.dwSize = sizeof( ddcaps );
    result = m_pDirectDraw->GetCaps(&ddcaps, NULL);
    if (result != DD_OK)
    {
         Error("GetCaps failed while checking for total video memory", result);
         return FALSE;
    }

    return (long)(ddcaps.dwVidMemTotal);
}

// Determines Z buffer depth.
BOOL
MxDirectDraw::GetHardwareCaps(DDCAPS& rDriverCaps, DDCAPS& rHELCaps)
{
    HRESULT result;

    memset(&rDriverCaps, 0, sizeof(rDriverCaps));
    memset(&rHELCaps, 0, sizeof(rHELCaps));
    rDriverCaps.dwSize  = sizeof(DDCAPS);
    rHELCaps.dwSize     = sizeof(DDCAPS);

    result = m_pDirectDraw->GetCaps(&rDriverCaps, &rHELCaps);
    if (result != DD_OK)
    {
        Error("GetCaps failed", result);
    }

    return (result == DD_OK);
}

BOOL CALLBACK
MxDirectDraw::EnumDirectDrawCallback(GUID* pGUID,
                                     char* pDriverDesc,
                                     char* pDriverName,
                                     void* pContext)
{
    MxDirectDraw*   pDirectDraw = (MxDirectDraw*) pContext;

    return pDirectDraw->EnumDirectDrawCallback(pGUID, pDriverDesc, pDriverName);
}

BOOL MxDirectDraw::EnumDirectDrawCallback(GUID* pGUID,
                                          char* pDriverDesc,
                                          char* pDriverName)
{
    if (pGUID)
    {
        IDirectDraw*    pDirectDraw;
        DDCAPS          driverCaps, helCaps;
        HRESULT         result;

        result = DirectDrawCreate(pGUID, &pDirectDraw, NULL);
        if (result != DD_OK)
        {
            Error("Failing creating a DirectDraw device for testing. Continuing...", result);
            return DDENUMRET_OK;
        }

        if (!GetHardwareCaps(driverCaps, helCaps))
        {
            pDirectDraw->Release();
            return DDENUMRET_OK;
        }

        if (driverCaps.dwCaps & DDCAPS_3D)
        {
            // We have found a 3d hardware device
            memcpy(&m_guid, pGUID, sizeof(GUID));

            m_bIsOnPrimaryDevice    = FALSE;
            m_pDirectDraw           = pDirectDraw;
            return DDENUMRET_CANCEL;
        }

        // just to be sure
        m_bIsOnPrimaryDevice    = TRUE;
        m_pDirectDraw           = 0;
        pDirectDraw->Release();
    }

    return DDENUMRET_OK;
}

// Create the DirectDraw object.
BOOL
MxDirectDraw::DDCreate()
{
    HRESULT result;

    assert(!m_pDirectDraw);

    // search for a 3D DirectDraw device
    result = DirectDrawEnumerate(EnumDirectDrawCallback, (void*) this);
    if (result != DD_OK)
    {
        Error("DirectDrawEnumerate failed", result);
    }

    if (!m_pDirectDraw)
    {
        // did not find 3D DirectDraw device, use HEL
        m_bIsOnPrimaryDevice = TRUE;
        memset(&m_guid, 0, sizeof(m_guid));
        result = DirectDrawCreate(0, &m_pDirectDraw, NULL);
        if (result != DD_OK)
        {
            Error("DirectDrawCreate failed", result);
        }
    }

    return (m_pDirectDraw != 0);
}

// Initialize the DirectDraw object.
BOOL
MxDirectDraw::DDInit(BOOL fullScreen)
{
    DDSURFACEDESC   ddsd;
    DDCAPS          driverCaps, helCaps;
    HRESULT         result;

    assert(m_pDirectDraw);

    if (fullScreen)
    {
        m_bIgnoreWM_SIZE = TRUE;
        result = m_pDirectDraw->SetCooperativeLevel(m_hWndMain,
#ifdef _DEBUG
                                                    DDSCL_ALLOWREBOOT |
#endif
#if 0
                                                    DDSCL_ALLOWMODEX |
#endif
                                                    DDSCL_EXCLUSIVE |
                                                    DDSCL_FULLSCREEN);
        m_bIgnoreWM_SIZE = FALSE;
    }
    else
    {
        result = m_pDirectDraw->SetCooperativeLevel(m_hWndMain, DDSCL_NORMAL);
    }

    if (result != DD_OK)
    {
        Error("SetCooperativeLevel failed", result);
        return FALSE;
    }

    if (!GetHardwareCaps(driverCaps, helCaps))
    {
        return FALSE;
    }
    memcpy(&m_HWddsCaps, &driverCaps.ddsCaps, sizeof(m_HWddsCaps));

    m_totalVideoMemory  = TotalVideoMemory();

    if (!EnumerateDisplayModes())
    {
        return FALSE;
    }

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    result = m_pDirectDraw->GetDisplayMode(&ddsd);
    if (result != DD_OK) {
        Error("GetDisplayMode failed", result);
        return FALSE;
    }

#if 0
    m_szWindowsDisplay.cx = ddsd.dwWidth;
    m_szWindowsDisplay.cy = ddsd.dwHeight;
#endif

    m_bFullScreen = fullScreen;

    return TRUE;
}

BOOL
MxDirectDraw::IsSupportedMode(int width, int height, int bpp)
{
    Mode    mode = { width, height, bpp };
    int     i;

    for (i = 0; i < m_modeCount; i++)
    {
        if (mode == m_modes[i])
        {
            return TRUE;
        }
    }

    return FALSE;
}
void
EnableResizing(HWND hwnd, BOOL flag)
{
    static DWORD dwStyle;

    if (!flag)
    {
        dwStyle = GetWindowLong(hwnd, GWL_STYLE);
        if (dwStyle & WS_THICKFRAME)
        {
            SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) ^ WS_THICKFRAME);
        }
    }
    else
    {
        SetWindowLong(hwnd, GWL_STYLE, dwStyle);
    }
}

// Initializes DirectDraw for a new display mode or window size.
BOOL
MxDirectDraw::DDSetMode(int width, int height, int bpp)
{
    HRESULT result;

    if (m_bFullScreen)
    {
        EnableResizing(m_hWndMain, FALSE);

        // For fullScreen, set the actual display mode.
        if (!IsSupportedMode(width, height, bpp))
        {
            width   = m_modes[0].width;
            height  = m_modes[0].height;
            bpp     = m_modes[0].bitsPerPixel;
        }

        m_bIgnoreWM_SIZE = TRUE;
        result = m_pDirectDraw->SetDisplayMode(width, height, bpp);
        m_bIgnoreWM_SIZE = FALSE;

        if (result != DD_OK)
        {
            Error("SetDisplayMode failed", result);
            return FALSE;
        }
    }
    else 
    {
        // For a window, set the window size.
        RECT rc;
        DWORD dwStyle;

        if (!m_bIsOnPrimaryDevice)
        {
            Error("Attempt made enter a windowed mode on a DirectDraw device that is not the primary display",
                    DDERR_GENERIC);
            return FALSE;
        }

        // Convert to a normal app window if we are still a WS_POPUP window.
        m_bIgnoreWM_SIZE = TRUE;
        dwStyle = GetWindowLong(m_hWndMain, GWL_STYLE);
        dwStyle &= ~WS_POPUP;
        dwStyle |= WS_OVERLAPPED | WS_CAPTION | WS_THICKFRAME;
        SetWindowLong(m_hWndMain, GWL_STYLE, dwStyle);
        SetRect(&rc, 0, 0, width, height);
        AdjustWindowRectEx(&rc, GetWindowLong(m_hWndMain, GWL_STYLE),
                           GetMenu(m_hWndMain) != NULL,
                           GetWindowLong(m_hWndMain, GWL_EXSTYLE));
        SetWindowPos(m_hWndMain, NULL,
                     0, 0, rc.right-rc.left, rc.bottom-rc.top,
                     SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
        SetWindowPos(m_hWndMain, HWND_NOTOPMOST,
                     0, 0, 0, 0,
                     SWP_NOSIZE | SWP_NOMOVE | SWP_NOACTIVATE);
        m_bIgnoreWM_SIZE = FALSE;
    }

    m_currentMode.width         = width;
    m_currentMode.height        = height;
    m_currentMode.bitsPerPixel  = bpp;

    // Create the front and back buffer surfaces
    if (!DDCreateSurfaces())
    {
        return FALSE;
    }

    // Palettize if we are not in a 16-bit mode.
    DDSURFACEDESC ddsd;

    if (!GetDDSurfaceDesc(&ddsd, m_pBackBuffer))
    {
        return FALSE;
    }

    if (ddsd.ddpfPixelFormat.dwFlags & DDPF_PALETTEINDEXED8)
    {
        m_bPrimaryPalettized = TRUE;
    }
    else
    {
        m_bPrimaryPalettized = FALSE;
    }

    if (m_bPrimaryPalettized)
    {
        result = m_pDirectDraw->CreatePalette(DDPCAPS_8BIT | DDPCAPS_ALLOW256 | DDPCAPS_INITIALIZE,
                                              m_paletteEntries,
                                              &m_pPalette, NULL);
        if (result != DD_OK) 
        {
            Error("CreatePalette failed", result);
            return FALSE;
        }
        result = m_pBackBuffer->SetPalette(m_pPalette);
        result = m_pFrontBuffer->SetPalette(m_pPalette);
        if(result != DD_OK ) {
            Error("SetPalette failed", result);
            return FALSE;
        }
    }

    if (!CreateTextSurfaces())
        return FALSE;
    return TRUE;
}

// Used to create surfaces instead of calling DD directly.
HRESULT
MxDirectDraw::CreateDDSurface(LPDDSURFACEDESC lpDDSurfDesc,
                          LPDIRECTDRAWSURFACE FAR *lpDDSurface,
                          IUnknown FAR *pUnkOuter)
{
    HRESULT result;
    result = m_pDirectDraw->CreateSurface(lpDDSurfDesc, lpDDSurface, pUnkOuter);
    // TRACE("Created Surface<0x%x>\n", (void*) *lpDDSurface);
    return result;
}

// Gets a surface description.
BOOL
MxDirectDraw::GetDDSurfaceDesc(LPDDSURFACEDESC lpDDSurfDesc, LPDIRECTDRAWSURFACE lpDDSurf)
{
    HRESULT result;

    memset(lpDDSurfDesc, 0, sizeof(DDSURFACEDESC));
    lpDDSurfDesc->dwSize = sizeof(DDSURFACEDESC);
    result = lpDDSurf->GetSurfaceDesc(lpDDSurfDesc);
    if (result != DD_OK)
    {
        Error("Error getting a surface description", result);
    }

    return (result == DD_OK);
}

// Create front and back buffers as DirectDraw surfaces.
BOOL
MxDirectDraw::DDCreateSurfaces()
{
    HRESULT         result;
    DDSURFACEDESC   ddsd;
    DDSCAPS         ddscaps;

    if (m_bFullScreen) 
    {
        // Create a complex flipping surface for fullScreen mode.
        memset(&ddsd,0,sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof( ddsd );
        ddsd.dwFlags = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_3DDEVICE | DDSCAPS_COMPLEX;
        if (m_bOnlySystemMemory)
            ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
        ddsd.dwBackBufferCount = 1;
        result = CreateDDSurface(&ddsd, &m_pFrontBuffer, NULL );
        // TRACE("Created Front Buffer<0x%x>\n", (void*) m_pFrontBuffer);
        if(result != DD_OK) {
            Error("CreateSurface for front/back fullScreen buffer failed", result);
            return FALSE;
        }
        ddscaps.dwCaps = DDSCAPS_BACKBUFFER;
        result = m_pFrontBuffer->GetAttachedSurface(&ddscaps, &m_pBackBuffer);
        if (result != DD_OK)
        {
            Error("GetAttachedSurface failed to get back buffer", result);
            return FALSE;
        }
        if (!GetDDSurfaceDesc(&ddsd, m_pBackBuffer))
        {
            return FALSE;
        }

        if (!(ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY))
        {
            // ???
            m_bOnlySoftRender;
        }
    }
    else
    {
        // Window case
        memset(&ddsd,0,sizeof(DDSURFACEDESC));
        ddsd.dwSize = sizeof(DDSURFACEDESC);
        ddsd.dwFlags = DDSD_CAPS;
        ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
        result = CreateDDSurface(&ddsd, &m_pFrontBuffer, NULL);
        // TRACE("Created Front Buffer<0x%x>\n", (void*) m_pFrontBuffer);
        if(result != DD_OK)
        {
            Error("CreateSurface for window front buffer failed", result);
            return FALSE;
        }
        ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
        ddsd.dwHeight = m_currentMode.height;
        ddsd.dwWidth = m_currentMode.width;
        ddsd.ddsCaps.dwCaps= DDSCAPS_OFFSCREENPLAIN | DDSCAPS_3DDEVICE;
        if (m_bOnlySystemMemory)
            ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
        result = CreateDDSurface(&ddsd, &m_pBackBuffer, NULL);
        // TRACE("Created Back Buffer<0x%x>\n", (void*) m_pBackBuffer);
        if (result != DD_OK) {
            Error("CreateSurface for window back buffer failed", result);
            return FALSE;
        }
        if (!GetDDSurfaceDesc(&ddsd, m_pBackBuffer))
        {
            return FALSE;
        }
        if (!(ddsd.ddsCaps.dwCaps & DDSCAPS_VIDEOMEMORY))
        {
            // ???
            m_bOnlySoftRender;
        }

        // Create a DirectDrawClipper object.
        result = m_pDirectDraw->CreateClipper(0, &m_pClipper, NULL);
        if(result != DD_OK )
        {
            Error("CreateClipper failed", result);
            return FALSE;
        }
        result = m_pClipper->SetHWnd(0, m_hWndMain);
        if(result != DD_OK )
        {
            Error("Clipper SetHWnd failed", result);
            return FALSE;
        }
        result = m_pFrontBuffer->SetClipper(m_pClipper);
        if(result != DD_OK )
        {
            Error("SetClipper failed", result);
            return FALSE;
        }
    }

    return TRUE;
}

BOOL
MxDirectDraw::TextSurfaceToBackBuffer(IDirectDrawSurface* pSurface,
                                      SIZE& textSizeOnSurface,
                                      int y)
{
    if (textSizeOnSurface.cx > 0 &&
        textSizeOnSurface.cy > 0 &&
        textSizeOnSurface.cx < m_currentMode.width && 
        textSizeOnSurface.cy < m_currentMode.height)
    {
        HRESULT result;
        RECT    rc;
        int     x;

        SetRect(&rc, 0, 0, textSizeOnSurface.cx, textSizeOnSurface.cy);
        x = (int)(0.5 * (m_currentMode.width - textSizeOnSurface.cx) + 0.5);
        result = m_pBackBuffer->BltFast(x, y, pSurface, &rc,
                                        DDBLTFAST_SRCCOLORKEY | DDBLTFAST_WAIT);
        if (result != DD_OK)
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL
MxDirectDraw::TextSurface1ToBackBuffer()
{
    return TextSurfaceToBackBuffer(m_pText1Surface,
                                    m_text1SizeOnSurface,
                                    0);
}

BOOL
MxDirectDraw::TextSurface2ToBackBuffer()
{
    return TextSurfaceToBackBuffer(m_pText2Surface,
                                    m_text2SizeOnSurface,
                                    m_currentMode.height - m_text2SizeOnSurface.cy);
}

BOOL
MxDirectDraw::TextToTextSurface(const char* text,
                                IDirectDrawSurface* pSurface,
                                SIZE& textSizeOnSurface)
{
    HRESULT result;
    HDC     hdc;
    RECT    rc;
    size_t  textLength;

    if (!pSurface) return FALSE;

    result = pSurface->GetDC(&hdc);
    if (result != DD_OK)
    {
        Error("GetDC for text surface failed", result);
        return FALSE;
    }

    textLength = strlen(text);

    SelectObject(hdc, m_hFont);
    SetTextColor(hdc, RGB(255,255,0));
    SetBkColor(hdc, RGB(0,0,0));
    SetBkMode(hdc, OPAQUE);
    GetTextExtentPoint32(hdc, text, textLength, &textSizeOnSurface);
    SetRect(&rc, 0, 0, textSizeOnSurface.cx, textSizeOnSurface.cy);
    ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rc, text, textLength, NULL);
    pSurface->ReleaseDC(hdc);

    return TRUE;
}

BOOL
MxDirectDraw::TextToTextSurface1(const char* text)
{
    return TextToTextSurface(text, m_pText1Surface, m_text1SizeOnSurface);
}

BOOL
MxDirectDraw::TextToTextSurface2(const char* text)
{
    return TextToTextSurface(text, m_pText2Surface, m_text2SizeOnSurface);
}

BOOL
MxDirectDraw::CreateTextSurfaces()
{
    HRESULT         result;
    DDCOLORKEY      ddck;
    DDSURFACEDESC   ddsd;
    HDC             hdc;
    char            dummyinfo[] = "000x000x00 (RAMP) 0000";
    char            dummyfps[] = "000.00 fps (000.00 fps (000.00 fps) 00000 tps)";
    /*
     * Create the font.
     */
    if (m_hFont != NULL) {
        DeleteObject(m_hFont);
    }
    m_hFont = CreateFont(m_currentMode.width <= 600 ? 12 : 24,
                         0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE,
                         ANSI_CHARSET,
                         OUT_DEFAULT_PRECIS,
                         CLIP_DEFAULT_PRECIS,
                         DEFAULT_QUALITY,
                         VARIABLE_PITCH,
                         "Arial" );

    hdc = GetDC(NULL);
    SelectObject(hdc, m_hFont);
    GetTextExtentPoint(hdc, dummyfps, strlen(dummyfps), &m_text1SizeOnSurface);
    GetTextExtentPoint(hdc, dummyinfo, strlen(dummyinfo), &m_text2SizeOnSurface);
    ReleaseDC(NULL, hdc);

    memset( &ddsd, 0, sizeof( ddsd ) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    if(m_bOnlySystemMemory)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    ddsd.dwHeight = m_text1SizeOnSurface.cy;
    ddsd.dwWidth = m_text1SizeOnSurface.cx;
    result = CreateDDSurface(&ddsd, &m_pText1Surface, NULL);
    // TRACE("Created Text1 Surface<0x%x>\n", (void*) m_pText1Surface);
    if (result != DD_OK) {
        Error("CreateSurface for text surface 1 failed", result);
        return FALSE;
    }
    memset(&ddck, 0, sizeof(ddck));
    m_pText1Surface->SetColorKey(DDCKEY_SRCBLT, &ddck);
    if (!TextToTextSurface1(dummyfps)) return FALSE;

    memset( &ddsd, 0, sizeof( ddsd ) );
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    if(m_bOnlySystemMemory)
        ddsd.ddsCaps.dwCaps |= DDSCAPS_SYSTEMMEMORY;
    ddsd.dwHeight = m_text2SizeOnSurface.cy;
    ddsd.dwWidth = m_text2SizeOnSurface.cx;
    result = CreateDDSurface(&ddsd, &m_pText2Surface, NULL);
    // TRACE("Created Text2 Surface<0x%x>\n", (void*) m_pText2Surface);
    if (result != DD_OK) 
    {
        Error("CreateSurface for text surface 2 failed", result);
        return FALSE;
    }
    memset(&ddck, 0, sizeof(ddck));
    m_pText2Surface->SetColorKey(DDCKEY_SRCBLT, &ddck);
    if (!TextToTextSurface2(dummyinfo))
        return FALSE;
    return TRUE;
}

// Restores any lost surfaces.
BOOL
MxDirectDraw::RestoreSurfaces()
{
    HRESULT result;

    if (m_pFrontBuffer->IsLost() == DDERR_SURFACELOST)
    {
        result = m_pFrontBuffer->Restore();
        if (result != DD_OK)
        {
            Error("Restore of front buffer failed", result);
            return FALSE;
        }
    }
    if (m_pBackBuffer->IsLost() == DDERR_SURFACELOST)
    {
        result = m_pBackBuffer->Restore();
        if (result != DD_OK)
        {
            Error("Restore of back buffer failed", result);
            return FALSE;
        }
    }
    if (m_pZBuffer->IsLost() == DDERR_SURFACELOST) 
    {
        result = m_pZBuffer->Restore();
        if (result != DD_OK)
        {
            Error("Restore of Z-buffer failed", result);
            return FALSE;
        }
    }
    if (m_pText1Surface->IsLost() == DDERR_SURFACELOST)
    {
        result = m_pText1Surface->Restore();
        if (result != DD_OK)
        {
            Error("Restore of text surface 1 failed", result);
            return FALSE;
        }
    }
    if (m_pText2Surface->IsLost() == DDERR_SURFACELOST)
    {
        result = m_pText2Surface->Restore();
        if (result != DD_OK)
        {
            Error("Restore of text surface 2 failed", result);
            return FALSE;
        }
    }

    return TRUE;
}

/*************************************************************************
 Enumerating the display modes.
 *************************************************************************/

HRESULT CALLBACK MxDirectDraw::EnumDisplayModesCallback(LPDDSURFACEDESC pddsd, LPVOID pContext)
{
    MxDirectDraw*   pDirectDraw = (MxDirectDraw*) pContext;

    return pDirectDraw->EnumDisplayModesCallback(pddsd);
}

HRESULT
MxDirectDraw::EnumDisplayModesCallback(LPDDSURFACEDESC pddsd)
{
    if (FilterDisplayModes(pddsd))
    {
        m_modes[m_modeCount].width          = pddsd->dwWidth;
        m_modes[m_modeCount].height         = pddsd->dwHeight;
        m_modes[m_modeCount].bitsPerPixel   = pddsd->ddpfPixelFormat.dwRGBBitCount;
        // TRACE("DisplayMode %d [%dx%dx%d]\n",
        //        m_modeCount,
        //        m_modes[m_modeCount].width,
        //        m_modes[m_modeCount].height,
        //        m_modes[m_modeCount].bitsPerPixel);
        m_modeCount++;
    }

    if (m_modeCount >= (sizeof(m_modes) / sizeof(m_modes[0])))
    {
        assert(0);
        return DDENUMRET_CANCEL;
    }

    return DDENUMRET_OK;
}

BOOL
MxDirectDraw::FilterDisplayModes(LPDDSURFACEDESC)
{
    return TRUE;
}

// Compare two display modes for sorting purposes.
int _cdecl MxDirectDraw::CompareModes(const void* element1, const void* element2)
{
    Mode*   pMode1 = (Mode*) element1;
    Mode*   pMode2 = (Mode*) element2;

    if (pMode1->bitsPerPixel > pMode2->bitsPerPixel)
        return -1;
    else if (pMode2->bitsPerPixel > pMode1->bitsPerPixel)
        return 1;
    else if (pMode1->width > pMode2->width)
        return -1;
    else if (pMode2->width > pMode1->width)
        return 1;
    else if (pMode1->height > pMode2->height)
        return -1;
    else if (pMode2->height > pMode1->height)
        return 1;
    else
        return 0;
}

// Generates the list of available display modes.
BOOL
MxDirectDraw::EnumerateDisplayModes()
{
    HRESULT result;

    m_modeCount = 0;
    result      = m_pDirectDraw->EnumDisplayModes(0, 0, (void*) this,
                                                  EnumDisplayModesCallback);
    if(result != DD_OK )
    {
        Error("EnumDisplayModes failed", result);
        return FALSE;
    }
    qsort((void *)&m_modes[0], (size_t) m_modeCount, sizeof(m_modes[0]),
          CompareModes);

    return TRUE;
}

/*************************************************************************
  Direct3D initialization
 *************************************************************************/

BOOL
MxDirectDraw::CreateZBuffer(DWORD memorytype, DWORD depth)
{
    HRESULT             result;
    LPDIRECTDRAWSURFACE lpZBuffer;
    DDSURFACEDESC       ddsd;

    // Create a Z-Buffer and attach it to the back buffer.

    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize             = sizeof(ddsd);
    ddsd.dwFlags            = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS | DDSD_ZBUFFERBITDEPTH;
    ddsd.dwHeight           = m_currentMode.height;
    ddsd.dwWidth            = m_currentMode.width;
    ddsd.dwZBufferBitDepth  = depth;
    ddsd.ddsCaps.dwCaps     = DDSCAPS_ZBUFFER | memorytype;
    result = CreateDDSurface(&ddsd, &lpZBuffer, 0);

    // TRACE("Created Z Buffer<0x%x>\n", (void*) lpZBuffer);

    if (result != DD_OK)
    {
        Error("CreateSurface for fullScreen Z-buffer failed",result);
        return FALSE;
    }

    result = m_pBackBuffer->AddAttachedSurface(lpZBuffer);
    if (result != DD_OK)
    {
        Error("AddAttachedBuffer failed for Z-Buffer",result);
        return FALSE;
    }

    m_pZBuffer = lpZBuffer;
    return TRUE;
}
 
// application should call this when it "pauses"
BOOL MxDirectDraw::Pause(BOOL pause)
{
    if (pause)
    {
        ++m_pauseCount;

        if (m_pauseCount > 1)
        {
            return TRUE;
        }

        if (!RestoreOriginalPaletteEntries())
        {
            return FALSE;
        }

        if (m_bFullScreen)
        {
            if (!FlipToGDISurface())
            {
                return FALSE;
            }

            // ???
            DrawMenuBar(m_hWndMain);
            RedrawWindow(m_hWndMain, NULL, NULL, RDW_FRAME);
        }
    }
    else
    {
        --m_pauseCount;

        if (m_pauseCount > 0)
        {
            return TRUE;
        }

        if (m_pauseCount < 0) 
        {
            m_pauseCount = 0;
        }

        if (!RestorePaletteEntries())
        {
            return FALSE;
        }
    }

    return TRUE;
}

BOOL MxDirectDraw::Flip()
{
    HRESULT result;

    result = m_pFrontBuffer->Flip(m_pBackBuffer, DDFLIP_WAIT);
    if (result != DD_OK)
    {
        Error("Flip failed", result);
    }

    return (result == DD_OK);
}

BOOL MxDirectDraw::BltBackBuffer(RECT& to, RECT& from)
{
    HRESULT result;

    result = m_pFrontBuffer->Blt(&to, m_pBackBuffer, &from, DDBLT_WAIT, NULL);
    if (result != DD_OK)
    {
        Error("Blt of back to front buffer failed", result);
    }

    return (result == DD_OK);
}

BOOL MxDirectDraw::Activate()
{
    if (m_bPrimaryPalettized)
    {
        HRESULT result;

        result = m_pFrontBuffer->SetPalette(m_pPalette);
        if (result != DD_OK)
        {
            Error("SetPalette on front buffer failed", result);
        }

        return (result == DD_OK);
    }

    return TRUE;
}

BOOL MxDirectDraw::RestorePaletteEntries()
{
    if (m_bFullScreen && m_bPrimaryPalettized)
    {
        if (m_pPalette)
        {
            HRESULT result;

            result = m_pPalette->SetEntries(0, 0, 
                                            sizeof(m_paletteEntries)/sizeof(m_paletteEntries[0]),
                                            m_paletteEntries);
            if (result != DD_OK)
            {
                Error("SetEntries failed", result);
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL MxDirectDraw::RestoreOriginalPaletteEntries()
{
    if (m_bPrimaryPalettized)
    {
#if 0
        HRESULT result;

        result = m_pPalette->GetEntries(0, 0, 256, &m_paletteEntries[0]);
        if (result != DD_OK)
        {
            Error("GetEntries failed", result);
            return FALSE;
        }

        for (int i = 10; i < 246; i++)
        {
            m_originalPaletteEntries[i] = m_paletteEntries[i];
        }
#endif
        if (m_pPalette)
        {
            HRESULT result;

            result = m_pPalette->SetEntries(0, 0, 
                                            sizeof(m_originalPaletteEntries)/sizeof(m_originalPaletteEntries[0]),
                                            m_originalPaletteEntries);
            if (result != DD_OK)
            {
                Error("SetEntries failed", result);
                return FALSE;
            }
        }
    }

    return TRUE;
}

BOOL MxDirectDraw::FlipToGDISurface()
{
    if (m_pDirectDraw)
    {
        HRESULT result;

        result = m_pDirectDraw->FlipToGDISurface();
        if (result != DD_OK)
        {
            Error("FlipToGDISurface failed", result);
        }

        return (result == DD_OK);
    }

    return TRUE;
}

#if 0
// ???
        case WM_PAINT:
            if (stat.bFullscreen && !app.bAppPaused) {
                ValidateRect(hWnd, NULL);
                return 1;
            }
            break;
        case WM_NCPAINT:
            if (stat.bFullscreen && !app.bAppPaused)
                return 1;
            break;
        case WM_ERASEBKGND:
            if (stat.bFullscreen && !app.bAppPaused)
                return 1;
            break;
        case WM_MOVING:
            if (stat.bFullscreen) {
                GetWindowRect(app.hWndMain, (LPRECT)lParam);
                return 1;
            }
            break;
        case WM_MOVE:
            p1.x = p1.y = 0;
            ClientToScreen(app.hWndMain, &p1);
            p2.x = app.Mode.cx; p2.y = app.Mode.cy;
            ClientToScreen(app.hWndMain, &p2);
            SetRect(&app.rcClient, p1.x, p1.y, p2.x, p2.y);
            break;

        case WM_SIZE:
            ...;
            if (app.Mode.cx > szWindowsDisplay.cx)
                app.Mode.cx = szWindowsDisplay.cx;
            if (app.Mode.cy > szWindowsDisplay.cy)
                app.Mode.cy = szWindowsDisplay.cy;
            ...
            break;

                case MENU_FULLSCREEN:
                    if (!dd.bIsPrimary)
                        break;
                    stat.bFullscreen = !stat.bFullscreen;
                    if (!SwitchMode()) {
                        CleanUpAndPostQuit();
                        break;
                    }
#endif

void
MxDirectDraw::FatalError(const char* message, HRESULT error)
{
    static BOOL g_isInsideFatalError = FALSE;

    if (g_isInsideFatalError)
    {
        return;
    }

    g_isInsideFatalError = TRUE;

    Destroy();

    if (m_pFatalErrorHandler)
    {
        m_pFatalErrorHandler(message, error, m_pFatalErrorHandlerArg);
    }
}

void
MxDirectDraw::Error(const char* message, HRESULT error)
{
    static BOOL g_isInsideError = FALSE;

    if (g_isInsideError)
    {
        return;
    }

    g_isInsideError = TRUE;

    Destroy();

    if (m_pErrorHandler)
    {
        m_pErrorHandler(message, error, m_pErrorHandlerArg);
    }

    g_isInsideError = FALSE;
}

// Returns a pointer to a string describing the given error code.
const char*
MxDirectDraw::ErrorToString(HRESULT error)
{
    switch(error) {
        case DD_OK:
            return "No error.\0";
        case DDERR_ALREADYINITIALIZED:
            return "This object is already initialized.\0";
        case DDERR_BLTFASTCANTCLIP:
            return "Return if a clipper object is attached to the source surface passed into a BltFast call.\0";
        case DDERR_CANNOTATTACHSURFACE:
            return "This surface can not be attached to the requested surface.\0";
        case DDERR_CANNOTDETACHSURFACE:
            return "This surface can not be detached from the requested surface.\0";
        case DDERR_CANTCREATEDC:
            return "Windows can not create any more DCs.\0";
        case DDERR_CANTDUPLICATE:
            return "Can't duplicate primary & 3D surfaces, or surfaces that are implicitly created.\0";
        case DDERR_CLIPPERISUSINGHWND:
            return "An attempt was made to set a cliplist for a clipper object that is already monitoring an hwnd.\0";
        case DDERR_COLORKEYNOTSET:
            return "No src color key specified for this operation.\0";
        case DDERR_CURRENTLYNOTAVAIL:
            return "Support is currently not available.\0";
        case DDERR_DIRECTDRAWALREADYCREATED:
            return "A DirectDraw object representing this driver has already been created for this process.\0";
        case DDERR_EXCEPTION:
            return "An exception was encountered while performing the requested operation.\0";
        case DDERR_EXCLUSIVEMODEALREADYSET:
            return "An attempt was made to set the cooperative level when it was already set to exclusive.\0";
        case DDERR_GENERIC:
            return "Generic failure.\0";
        case DDERR_HEIGHTALIGN:
            return "Height of rectangle provided is not a multiple of reqd alignment.\0";
        case DDERR_HWNDALREADYSET:
            return "The CooperativeLevel HWND has already been set. It can not be reset while the process has surfaces or palettes created.\0";
        case DDERR_HWNDSUBCLASSED:
            return "HWND used by DirectDraw CooperativeLevel has been subclassed, this prevents DirectDraw from restoring state.\0";
        case DDERR_IMPLICITLYCREATED:
            return "This surface can not be restored because it is an implicitly created surface.\0";
        case DDERR_INCOMPATIBLEPRIMARY:
            return "Unable to match primary surface creation request with existing primary surface.\0";
        case DDERR_INVALIDCAPS:
            return "One or more of the caps bits passed to the callback are incorrect.\0";
        case DDERR_INVALIDCLIPLIST:
            return "DirectDraw does not support the provided cliplist.\0";
        case DDERR_INVALIDDIRECTDRAWGUID:
            return "The GUID passed to DirectDrawCreate is not a valid DirectDraw driver identifier.\0";
        case DDERR_INVALIDMODE:
            return "DirectDraw does not support the requested mode.\0";
        case DDERR_INVALIDOBJECT:
            return "DirectDraw received a pointer that was an invalid DIRECTDRAW object.\0";
        case DDERR_INVALIDPARAMS:
            return "One or more of the parameters passed to the function are incorrect.\0";
        case DDERR_INVALIDPIXELFORMAT:
            return "The pixel format was invalid as specified.\0";
        case DDERR_INVALIDPOSITION:
            return "Returned when the position of the overlay on the destination is no longer legal for that destination.\0";
        case DDERR_INVALIDRECT:
            return "Rectangle provided was invalid.\0";
        case DDERR_LOCKEDSURFACES:
            return "Operation could not be carried out because one or more surfaces are locked.\0";
        case DDERR_NO3D:
            return "There is no 3D present.\0";
        case DDERR_NOALPHAHW:
            return "Operation could not be carried out because there is no alpha accleration hardware present or available.\0";
        case DDERR_NOBLTHW:
            return "No blitter hardware present.\0";
        case DDERR_NOCLIPLIST:
            return "No cliplist available.\0";
        case DDERR_NOCLIPPERATTACHED:
            return "No clipper object attached to surface object.\0";
        case DDERR_NOCOLORCONVHW:
            return "Operation could not be carried out because there is no color conversion hardware present or available.\0";
        case DDERR_NOCOLORKEY:
            return "Surface doesn't currently have a color key\0";
        case DDERR_NOCOLORKEYHW:
            return "Operation could not be carried out because there is no hardware support of the destination color key.\0";
        case DDERR_NOCOOPERATIVELEVELSET:
            return "Create function called without DirectDraw object method SetCooperativeLevel being called.\0";
        case DDERR_NODC:
            return "No DC was ever created for this surface.\0";
        case DDERR_NODDROPSHW:
            return "No DirectDraw ROP hardware.\0";
        case DDERR_NODIRECTDRAWHW:
            return "A hardware-only DirectDraw object creation was attempted but the driver did not support any hardware.\0";
        case DDERR_NOEMULATION:
            return "Software emulation not available.\0";
        case DDERR_NOEXCLUSIVEMODE:
            return "Operation requires the application to have exclusive mode but the application does not have exclusive mode.\0";
        case DDERR_NOFLIPHW:
            return "Flipping visible surfaces is not supported.\0";
        case DDERR_NOGDI:
            return "There is no GDI present.\0";
        case DDERR_NOHWND:
            return "Clipper notification requires an HWND or no HWND has previously been set as the CooperativeLevel HWND.\0";
        case DDERR_NOMIRRORHW:
            return "Operation could not be carried out because there is no hardware present or available.\0";
        case DDERR_NOOVERLAYDEST:
            return "Returned when GetOverlayPosition is called on an overlay that UpdateOverlay has never been called on to establish a destination.\0";
        case DDERR_NOOVERLAYHW:
            return "Operation could not be carried out because there is no overlay hardware present or available.\0";
        case DDERR_NOPALETTEATTACHED:
            return "No palette object attached to this surface.\0";
        case DDERR_NOPALETTEHW:
            return "No hardware support for 16 or 256 color palettes.\0";
        case DDERR_NORASTEROPHW:
            return "Operation could not be carried out because there is no appropriate raster op hardware present or available.\0";
        case DDERR_NOROTATIONHW:
            return "Operation could not be carried out because there is no rotation hardware present or available.\0";
        case DDERR_NOSTRETCHHW:
            return "Operation could not be carried out because there is no hardware support for stretching.\0";
        case DDERR_NOT4BITCOLOR:
            return "DirectDrawSurface is not in 4 bit color palette and the requested operation requires 4 bit color palette.\0";
        case DDERR_NOT4BITCOLORINDEX:
            return "DirectDrawSurface is not in 4 bit color index palette and the requested operation requires 4 bit color index palette.\0";
        case DDERR_NOT8BITCOLOR:
            return "DirectDrawSurface is not in 8 bit color mode and the requested operation requires 8 bit color.\0";
        case DDERR_NOTAOVERLAYSURFACE:
            return "Returned when an overlay member is called for a non-overlay surface.\0";
        case DDERR_NOTEXTUREHW:
            return "Operation could not be carried out because there is no texture mapping hardware present or available.\0";
        case DDERR_NOTFLIPPABLE:
            return "An attempt has been made to flip a surface that is not flippable.\0";
        case DDERR_NOTFOUND:
            return "Requested item was not found.\0";
        case DDERR_NOTLOCKED:
            return "Surface was not locked.  An attempt to unlock a surface that was not locked at all, or by this process, has been attempted.\0";
        case DDERR_NOTPALETTIZED:
            return "The surface being used is not a palette-based surface.\0";
        case DDERR_NOVSYNCHW:
            return "Operation could not be carried out because there is no hardware support for vertical blank synchronized operations.\0";
        case DDERR_NOZBUFFERHW:
            return "Operation could not be carried out because there is no hardware support for zbuffer blitting.\0";
        case DDERR_NOZOVERLAYHW:
            return "Overlay surfaces could not be z layered based on their BltOrder because the hardware does not support z layering of overlays.\0";
        case DDERR_OUTOFCAPS:
            return "The hardware needed for the requested operation has already been allocated.\0";
        case DDERR_OUTOFMEMORY:
            return "DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OUTOFVIDEOMEMORY:
            return "DirectDraw does not have enough memory to perform the operation.\0";
        case DDERR_OVERLAYCANTCLIP:
            return "The hardware does not support clipped overlays.\0";
        case DDERR_OVERLAYCOLORKEYONLYONEACTIVE:
            return "Can only have ony color key active at one time for overlays.\0";
        case DDERR_OVERLAYNOTVISIBLE:
            return "Returned when GetOverlayPosition is called on a hidden overlay.\0";
        case DDERR_PALETTEBUSY:
            return "Access to this palette is being refused because the palette is already locked by another thread.\0";
        case DDERR_PRIMARYSURFACEALREADYEXISTS:
            return "This process already has created a primary surface.\0";
        case DDERR_REGIONTOOSMALL:
            return "Region passed to Clipper::GetClipList is too small.\0";
        case DDERR_SURFACEALREADYATTACHED:
            return "This surface is already attached to the surface it is being attached to.\0";
        case DDERR_SURFACEALREADYDEPENDENT:
            return "This surface is already a dependency of the surface it is being made a dependency of.\0";
        case DDERR_SURFACEBUSY:
            return "Access to this surface is being refused because the surface is already locked by another thread.\0";
        case DDERR_SURFACEISOBSCURED:
            return "Access to surface refused because the surface is obscured.\0";
        case DDERR_SURFACELOST:
            return "Access to this surface is being refused because the surface memory is gone. The DirectDrawSurface object representing this surface should have Restore called on it.\0";
        case DDERR_SURFACENOTATTACHED:
            return "The requested surface is not attached.\0";
        case DDERR_TOOBIGHEIGHT:
            return "Height requested by DirectDraw is too large.\0";
        case DDERR_TOOBIGSIZE:
            return "Size requested by DirectDraw is too large, but the individual height and width are OK.\0";
        case DDERR_TOOBIGWIDTH:
            return "Width requested by DirectDraw is too large.\0";
        case DDERR_UNSUPPORTED:
            return "Action not supported.\0";
        case DDERR_UNSUPPORTEDFORMAT:
            return "FOURCC format requested is unsupported by DirectDraw.\0";
        case DDERR_UNSUPPORTEDMASK:
            return "Bitmask in the pixel format requested is unsupported by DirectDraw.\0";
        case DDERR_VERTICALBLANKINPROGRESS:
            return "Vertical blank is in progress.\0";
        case DDERR_WASSTILLDRAWING:
            return "Informs DirectDraw that the previous Blt which is transfering information to or from this Surface is incomplete.\0";
        case DDERR_WRONGMODE:
            return "This surface can not be restored because it was created in a different mode.\0";
        case DDERR_XALIGN:
            return "Rectangle provided was not horizontally aligned on required boundary.\0";
        default:
            return "Unrecognized error value.\0";
    }
}
