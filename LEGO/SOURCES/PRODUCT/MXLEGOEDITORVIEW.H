// MxLegoEditorView.h : header file
//
#include "MxLegoView.h"

class EditorController;

/////////////////////////////////////////////////////////////////////////////
// MxLegoEditorView window

class MxLegoEditorView : public MxLegoView
{
// Construction
public:
    MxLegoEditorView(Tgl::Group* pScene);

    BOOL    Create(const CString& windowName,
                   const CWnd* pParentWnd,
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
	//{{AFX_VIRTUAL(MxLegoEditorView)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MxLegoEditorView();

	// Generated message map functions
protected:
	//{{AFX_MSG(MxLegoEditorView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

    Tgl::View*          CreateView();
    MouseController*    GetController();
    Tgl::Camera*        GetCamera();
    Tgl::Group*         GetScene();

public:
    EditorController*   GetEditorController() { return m_pEditorController; }

private:
    Tgl::Group*         m_pScene;
    EditorController*   m_pEditorController;

    Tgl::Camera*        m_pCamera;
    Tgl::Light*         m_pSunLight;
    Tgl::Light*         m_pDirectionalLight;
    Tgl::Light*         m_pAmbientLight;
};

/////////////////////////////////////////////////////////////////////////////
