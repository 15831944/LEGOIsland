// MxDirectDrawWnd.cpp : implementation file
//

#include "TglAfx.h"
#include "MxDirectDrawWnd.h"
#include "MxDirectDraw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
//
// Helper

BOOL GetResourceBitmapPaletteEntries(const char* pResourceName,
                                     int paletteEntryCount,
                                     PALETTEENTRY* pPaletteEntry,
                                     int& rPaletteEntryCount)
{
	HINSTANCE   hInst = AfxFindResourceHandle(pResourceName, RT_BITMAP);
	HRSRC       hRsrc = ::FindResource(hInst, pResourceName, RT_BITMAP);

    if (hRsrc)
    {
        HGLOBAL hGlobal = ::LoadResource(hInst, hRsrc);

        if (hGlobal)
        {
            LPBITMAPINFOHEADER  pBitmapInfoHeader = (LPBITMAPINFOHEADER) ::LockResource(hGlobal);
            LPBITMAPINFO        pBitmapInfo = (LPBITMAPINFO) pBitmapInfoHeader;

            if (pBitmapInfoHeader->biBitCount <= 8)
            {
                rPaletteEntryCount = (1 << pBitmapInfoHeader->biBitCount);
            }
            else
            {
                rPaletteEntryCount = 0;  // No palette needed for 24 BPP DIB
            }

            if (rPaletteEntryCount)
            {
                int i;

                for (i = 0;  (i < rPaletteEntryCount) && (i < paletteEntryCount);  i++)
                {
                    pPaletteEntry[i].peRed   = pBitmapInfo->bmiColors[i].rgbRed;
                    pPaletteEntry[i].peGreen = pBitmapInfo->bmiColors[i].rgbGreen;
                    pPaletteEntry[i].peBlue  = pBitmapInfo->bmiColors[i].rgbBlue;
                    pPaletteEntry[i].peFlags = 0;
                }
            }

            ::UnlockResource(hGlobal);
            ::FreeResource(hGlobal);
            return TRUE;
        }
    }

    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// MxDirectDrawWnd

MxDirectDrawWnd::MxDirectDrawWnd()
{
    m_pDirectDraw       = 0;
    m_handleActivate    = FALSE;
    m_pPaletteEntries   = 0;
    m_paletteEntryCount = 0;
}

MxDirectDrawWnd::~MxDirectDrawWnd()
{
    delete m_pDirectDraw;
}


BEGIN_MESSAGE_MAP(MxDirectDrawWnd, CWnd)
	//{{AFX_MSG_MAP(MxDirectDrawWnd)
	ON_WM_SIZE()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void MxDirectDrawWnd::FatalErrorHandler(const char* message, HRESULT error, void* pArg)
{
    static BOOL g_isInsideFatalErrorHandler = FALSE;

    if (g_isInsideFatalErrorHandler)
    {
        return;
    }

    g_isInsideFatalErrorHandler = TRUE;

    MxDirectDrawWnd*    pThis = (MxDirectDrawWnd*) pArg;
    CString             errorMessage = message;
    
    errorMessage += "\n";
    errorMessage += pThis->m_pDirectDraw->ErrorToString(error);

    TRACE("MxDirectDrawWnd::FatalErrorHandler(): %s\n", errorMessage);

    pThis->m_pDirectDraw->Destroy();
    pThis->m_pDirectDraw = 0;

    AfxMessageBox(errorMessage, MB_OK);
    PostQuitMessage(0);

    g_isInsideFatalErrorHandler = FALSE;
}

void MxDirectDrawWnd::ErrorHandler(const char* message, HRESULT error, void* pArg)
{
    static BOOL g_isInsideErrorHandler = FALSE;

    if (g_isInsideErrorHandler)
    {
        return;
    }

    g_isInsideErrorHandler = TRUE;

    MxDirectDrawWnd*    pThis = (MxDirectDrawWnd*) pArg;
    CString             errorMessage = message;
    
    errorMessage += "\n";
    errorMessage += pThis->m_pDirectDraw->ErrorToString(error);

    TRACE("MxDirectDrawWnd::ErrorHandler(): %s\n", errorMessage);

    AfxMessageBox(errorMessage, MB_OK);

    g_isInsideErrorHandler = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// MxDirectDrawWnd message handlers

BOOL MxDirectDrawWnd::Create(const char* windowName,
                             const CWnd* pParentWnd,
                             BOOL fullScreen,
                             int width,
                             int height,
                             int bitsPerPixel,
                             const PALETTEENTRY* pPaletteEntries,
                             int paletteEntryCount) 
{
    BOOL    result;

    if (!CreateEx(WS_EX_TOPMOST,
                  AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
                                      AfxGetApp()->LoadCursor(IDC_ARROW),
                                      NULL,
                                      NULL),
                  windowName,
                  WS_VISIBLE | WS_POPUP | WS_SYSMENU,
                  0, 0, width, height,
                  pParentWnd ? pParentWnd->GetSafeHwnd() : 0,
                  0))
    {
        return FALSE;
    }

    m_pPaletteEntries   = new PALETTEENTRY[paletteEntryCount];
    m_paletteEntryCount = paletteEntryCount;
    for (int i = 0; i < paletteEntryCount; i++)
    {
        m_pPaletteEntries[i] = pPaletteEntries[i];
    }

    m_pDirectDraw   = CreateDirectDraw();
    m_pDirectDraw->SetErrorHandler(ErrorHandler, (void*) this);
    m_pDirectDraw->SetFatalErrorHandler(FatalErrorHandler, (void*) this);

    m_handleActivate = FALSE;
    result = m_pDirectDraw->Create(GetSafeHwnd(),
                                   fullScreen,
                                   width, height, bitsPerPixel,
                                   m_pPaletteEntries, m_paletteEntryCount);
    m_handleActivate = TRUE;

    return result;
}

MxDirectDraw*
MxDirectDrawWnd::CreateDirectDraw()
{
    return new MxDirectDraw;
}

BOOL MxDirectDrawWnd::DestroyWindow() 
{
    m_handleActivate = FALSE;

    delete m_pDirectDraw;
    m_pDirectDraw = 0;

    delete [] m_pPaletteEntries;
    m_pPaletteEntries   = 0;
    m_paletteEntryCount = 0;

	return CWnd::DestroyWindow();
}

void MxDirectDrawWnd::OnSize(UINT nType, int cx, int cy) 
{
    if (m_pDirectDraw && m_pDirectDraw->IgnoreWM_SIZE())
    {
        return;
    }

	CWnd::OnSize(nType, cx, cy);

    if (m_pDirectDraw && m_pDirectDraw->DirectDraw() && !m_pDirectDraw->IsFullScreen())
    {
        BOOL    isFullScreen = m_pDirectDraw->IsFullScreen();
        int     bitsPerPixel = m_pDirectDraw->CurrentMode().bitsPerPixel;

        m_handleActivate = FALSE;
        m_pDirectDraw->DestroyButNotDirectDraw();
        m_pDirectDraw->Create(GetSafeHwnd(), isFullScreen, cx, cy, bitsPerPixel,
                              m_pPaletteEntries, m_paletteEntryCount);
        m_handleActivate = TRUE;
    }
}

void MxDirectDrawWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
    if ((nState != WA_INACTIVE) && m_handleActivate)
    {
        m_pDirectDraw->Activate();
    }

	CWnd::OnActivate(nState, pWndOther, bMinimized);
}
