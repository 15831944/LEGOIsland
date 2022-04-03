#ifndef _TglWnd_h
#define _TglWnd_h

// TglWnd.h : header file
//

#include "MxDirect3DWnd.h"
#include "MxStopWatch.h"
#include "tgl.h"

/////////////////////////////////////////////////////////////////////////////
// TglWnd window

class TglWnd : public MxDirect3DWnd
{
// Construction
protected:
    TglWnd();
    ~TglWnd();

    BOOL    Create(const CString& windowName,
                   const CWnd* pParentWnd,
                   Tgl::Renderer*,
                   BOOL fullScreen,
                   int width, int height, int bitsPerPixel,
                   const PALETTEENTRY* pPaletteEntries,
                   int pPaletteEntryCount);

// Attributes
public:

// Operations
public:
    virtual void    Render();

    BOOL            SwitchMode(BOOL isFullScreen,
                               int width, int height, int bitsPerPixel);

    // ??? for now
    BOOL            ToggleFullscreen();
    BOOL            SwitchToPreviousMode();
    BOOL            SwitchToNextMode();

    void            SetRenderWhenNotActive(BOOL b) { m_renderWhenNotActive = b; }
    BOOL            RenderWhenNotActive() const { return m_renderWhenNotActive; }

    double          RenderingRate() const   { return m_renderingRateMeter.Frequency(); }
    double          FrameRate() const       { return m_frameRateMeter.Frequency(); }
    double          GetTriangleRate() const { return m_triangleRateMeter.Frequency(); }
    unsigned long   FrameCount() const      { return m_frameCount; }

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(TglWnd)
	//}}AFX_VIRTUAL

    BOOL DestroyWindow();

// Implementation
public:
    // Generated message map functions
protected:
    //{{AFX_MSG(TglWnd)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
    DECLARE_MESSAGE_MAP()

protected:
    virtual Tgl::Device*        CreateDevice();
    virtual void                DestroyDevice();
    virtual Tgl::View*          CreateView() = 0;
    virtual void                DestroyView();
    virtual Tgl::Group*         GetScene() = 0;

    Tgl::Renderer*              GetRenderer()   { return m_pRenderer; }
    Tgl::Device*                GetDevice()     { return m_pDevice; }
    Tgl::View*                  GetView()       { return m_pView; }

    virtual void                GetOutputTextTop(CString&);
    virtual void                GetOutputTextBottom(CString&);

    void                        DoRender();

private:
    Tgl::Renderer*          m_pRenderer;
    Tgl::Device*            m_pDevice;
    Tgl::View*              m_pView;

    BOOL                    m_isInitialized;
    BOOL                    m_isActive;
    BOOL                    m_renderWhenNotActive;
    BOOL                    m_stopRendering;

    // statistics
    MxFrequencyMeter        m_renderingRateMeter;
    MxFrequencyMeter        m_frameRateMeter;
    unsigned long           m_frameCount;
    double                  m_frameRate;
    double                  m_renderingRate;
#ifdef _DEBUG
    MxFrequencyMeter        m_triangleRateMeter;
    unsigned long           m_triangleCount;
    double                  m_triangleRate;
#endif
};

/////////////////////////////////////////////////////////////////////////////

#endif /* _TglWnd_h */
