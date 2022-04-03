// MxLegoCitizenView.h : header file
//
#include "MxLegoView.h"

class CitizenController;
class LegoCitizen;
class ViewManager;
class ViewLODListManager;

/////////////////////////////////////////////////////////////////////////////
// MxLegoCitizenView window

class MxLegoCitizenView : public MxLegoView
{
// Construction
public:
	MxLegoCitizenView(Tgl::Group* pScene);

    BOOL    Create(const CString& windowName,
                   const CWnd* pParentWnd,
                   ViewLODListManager*,
                   Tgl::Renderer*,
                   BOOL fullScreen,
                   int width, int height, int bitsPerPixel,
                   const PALETTEENTRY* pPaletteEntries,
                   int paletteEntryCount);
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MxLegoCitizenView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MxLegoCitizenView();

    ViewManager*    GetViewMgr() { return m_pViewMgr; }

	// Generated message map functions
protected:
	//{{AFX_MSG(MxLegoCitizenView)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    Tgl::Device*        CreateDevice();
    Tgl::View*          CreateView();
    MouseController*    GetController();
    Tgl::Camera*        GetCamera();
    Tgl::Group*         GetScene();

    void                Render();

private:
    Tgl::Group*         m_pScene;
    CitizenController*  m_pCitizenController;

    Tgl::Light*         m_pSunLight;
    Tgl::Light*         m_pDirectionalLight;
    Tgl::Light*         m_pAmbientLight;

    // scene manager
    LegoCitizen*        m_pCitizen;
  	ViewManager*        m_pViewMgr;

    double              m_previousRenderTime;
};

/////////////////////////////////////////////////////////////////////////////
