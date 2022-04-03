#ifndef _TglSurface_h
#define _TglSurface_h

#include "MxStopWatch.h"

class Tgl::Renderer;
class Tgl::Device;
class Tgl::View;
class Tgl::Group;

/////////////////////////////////////////////////////////////////////////////
// TglSurface

class TglSurface
{
public:
    // ???
    struct CreateStruct
    {
        const GUID*         m_pDriverGUID;
        HWND                m_hWnd;
        IDirectDraw*        m_pDirectDraw;
        IDirectDrawSurface* m_pFrontBuffer;
        IDirectDrawSurface* m_pBackBuffer;
        IDirectDrawPalette* m_pPalette;
        BOOL                m_isFullScreen;
    };

public:
    TglSurface();
    virtual ~TglSurface();

    virtual BOOL    Create(const CreateStruct&,
                           Tgl::Renderer*, Tgl::Group* pScene);
    virtual void    Destroy();
    virtual double  Render();   // render time in seconds

    Tgl::Renderer*  GetRenderer() const { return m_pRenderer; }
    Tgl::Device*    GetDevice() const   { return m_pDevice; }
    Tgl::View*      GetView() const     { return m_pView; }
    Tgl::Group*     GetScene() const    { return m_pScene; }

    unsigned long   GetWidth() const    { return m_width; }
    unsigned long   GetHeight() const   { return m_height; }

    double          GetRenderingRate() const    { return m_renderingRateMeter.Frequency(); }
    double          GetFrameRate() const        { return m_frameRateMeter.Frequency(); }
    unsigned long   GetFrameCount() const       { return m_frameCount; }
#ifdef _DEBUG
    double          GetTriangleRate() const     { return m_triangleRateMeter.Frequency(); }
#endif

protected:
    virtual Tgl::View*      CreateView(Tgl::Renderer*, Tgl::Device*) = 0;
    virtual void            DestroyView();

private:
    Tgl::Renderer*          m_pRenderer;
    Tgl::Device*            m_pDevice;
    Tgl::View*              m_pView;
    Tgl::Group*             m_pScene;

    unsigned long           m_width;
    unsigned long           m_height;

    BOOL                    m_isInitialized;
    BOOL                    m_stopRendering;

    // statistics
    MxFrequencyMeter        m_renderingRateMeter;
    MxFrequencyMeter        m_frameRateMeter;
    unsigned long           m_frameCount;
#ifdef _DEBUG
    MxFrequencyMeter        m_triangleRateMeter;
    unsigned long           m_triangleCount;
#endif
};

/////////////////////////////////////////////////////////////////////////////

#endif /* _TglSurface_h */
