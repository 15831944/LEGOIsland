#ifndef _MxDirectDraw_h
#define _MxDirectDraw_h

#ifndef STRICT
#define STRICT 1
#endif

#define NOMINMAX			// to avoid conflict with STL
#include <ddraw.h>

// client needs to:
//  when WM_SIZE:   query MxDirectDraw (IgnorewWM_SIZE()) if it should ignore it

class MxDirectDraw
{
public:
    typedef void (*ErrorHandler)(const char*, HRESULT, void*);
    struct Mode
    {
        int width;
        int height;
        int bitsPerPixel;

        int operator==(const Mode& rMode) const
        {
            return ((width == rMode.width) &&
                    (height == rMode.height) &&
                    (bitsPerPixel == rMode.bitsPerPixel));
        }
    };

public:
    MxDirectDraw();
    virtual ~MxDirectDraw();

    virtual BOOL    Create(HWND,
                           BOOL fullScreen,
                           int width, int height, int bpp,
                           const PALETTEENTRY* pPaletteEntries,
                           int pPaletteEntryCount);
    virtual void    Destroy();
    virtual void    DestroyButNotDirectDraw();

    HWND                HWnd()              { return m_hWndMain; }
    IDirectDraw*        DirectDraw()        { return m_pDirectDraw; }
    IDirectDrawSurface* FrontBuffer()       { return m_pFrontBuffer; }
    IDirectDrawSurface* BackBuffer()        { return m_pBackBuffer; }
    IDirectDrawSurface* ZBuffer()           { return m_pZBuffer; }
    IDirectDrawPalette* Palette()           { return m_pPalette; }

    BOOL            IsFullScreen() const    { return m_bFullScreen; }
    const Mode&     CurrentMode() const     { return m_currentMode; }

    int             ModeCount() const       { return m_modeCount; }
    const Mode&     GetMode(int i) const    { return m_modes[i]; }
    BOOL            IsSupportedMode(int width, int height, int bpp);

    BOOL            IgnoreWM_SIZE() const   { return m_bIgnoreWM_SIZE; }

    BOOL            Activate();
    BOOL            Pause(BOOL);
    BOOL            RestoreSurfaces();
    BOOL            Flip();
    BOOL            BltBackBuffer(RECT& to, RECT& from);

    BOOL            TextToTextSurface1(const char*);
    BOOL            TextToTextSurface2(const char*);
    BOOL            TextSurface1ToBackBuffer();
    BOOL            TextSurface2ToBackBuffer();

    void            SetFatalErrorHandler(ErrorHandler, void*);
    void            SetErrorHandler(ErrorHandler, void*);

    virtual const char*     ErrorToString(HRESULT);

protected:
    BOOL    SetPaletteEntries(const PALETTEENTRY* pPaletteEntries,
                              int paletteEntryCount,
                              BOOL fullScreen);
    BOOL    CacheOriginalPaletteEntries();
    BOOL    RestoreOriginalPaletteEntries();
    BOOL    RestorePaletteEntries();
    BOOL    FlipToGDISurface();

    BOOL    DDCreate();
    BOOL    DDInit(BOOL fullScreen);
    BOOL    DDSetMode(int width, int height, int bpp);
    BOOL    DDCreateSurfaces();
    HRESULT CreateDDSurface(LPDDSURFACEDESC, LPDIRECTDRAWSURFACE*, IUnknown*);
    BOOL    GetDDSurfaceDesc(LPDDSURFACEDESC, LPDIRECTDRAWSURFACE);
    BOOL    EnumerateDisplayModes();
    HRESULT EnumDisplayModesCallback(LPDDSURFACEDESC);
    BOOL    EnumDirectDrawCallback(GUID*, char*, char*);
    long    FreeVideoMemory();
    long    TotalVideoMemory();
    BOOL    CreateZBuffer(DWORD memorytype, DWORD depth);
    BOOL    GetHardwareCaps(DDCAPS& rDriverCaps, DDCAPS& rHELCaps);

    BOOL    CreateTextSurfaces();
    BOOL    TextToTextSurface(const char*, IDirectDrawSurface*, SIZE&);
    BOOL    TextSurfaceToBackBuffer(IDirectDrawSurface*, SIZE&, int);

    static HRESULT CALLBACK EnumDisplayModesCallback(LPDDSURFACEDESC, void*);
    static BOOL CALLBACK EnumDirectDrawCallback(GUID*, char*, char*, void*);

    static int _cdecl       CompareModes(const void*, const void*);

    void    Error(const char*, HRESULT);
    void    FatalError(const char*, HRESULT);

    virtual BOOL    FilterDisplayModes(LPDDSURFACEDESC);

protected:
    BOOL                m_bOnlySoftRender;

private:
    IDirectDraw*        m_pDirectDraw;
    IDirectDrawSurface* m_pFrontBuffer;
    IDirectDrawSurface* m_pBackBuffer;
    IDirectDrawSurface* m_pZBuffer;
    IDirectDrawSurface* m_pText1Surface;    // top
    IDirectDrawSurface* m_pText2Surface;    // bottom
    IDirectDrawClipper* m_pClipper;
    IDirectDrawPalette* m_pPalette;
    PALETTEENTRY        m_paletteEntries[256];
    PALETTEENTRY        m_originalPaletteEntries[256];
    DDSCAPS             m_HWddsCaps;

    SIZE                m_text1SizeOnSurface;
    SIZE                m_text2SizeOnSurface;

    HWND                m_hWndMain;
    HFONT               m_hFont;
    Mode                m_currentMode; 
    Mode                m_modes[32];
    int                 m_modeCount;
    BOOL                m_bIgnoreWM_SIZE;

    GUID                m_guid;
    BOOL                m_bIsOnPrimaryDevice;
    BOOL                m_bPrimaryPalettized;
    BOOL                m_bFullScreen;
    BOOL                m_bLastWasFullScreen;
    BOOL                m_bOnlySystemMemory;

    long                m_totalVideoMemory;

    ErrorHandler        m_pErrorHandler;
    ErrorHandler        m_pFatalErrorHandler;
    void*               m_pErrorHandlerArg;
    void*               m_pFatalErrorHandlerArg;

    int                 m_pauseCount;
};

#endif /* _MxDirectDraw_h */
