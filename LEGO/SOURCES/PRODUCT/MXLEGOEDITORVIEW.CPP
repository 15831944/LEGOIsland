// MxLegoEditorView.cpp : implementation file
//

#include "stdafx.h"
#include "lego.h"
#include "MxLegoEditorView.h"

#include "Town.h"   // EditorController
#include "math.h"

using namespace Tgl;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MxLegoEditorView

MxLegoEditorView::MxLegoEditorView(Group* pScene)
{
    m_pScene            = pScene;
    m_pEditorController = 0;
    m_pSunLight         = 0;
    m_pDirectionalLight = 0;
    m_pAmbientLight     = 0;
    m_pCamera           = 0;
}

MxLegoEditorView::~MxLegoEditorView()
{
    delete m_pSunLight;
    delete m_pDirectionalLight;
    delete m_pAmbientLight;
    delete m_pEditorController;
    delete m_pCamera;
}


BEGIN_MESSAGE_MAP(MxLegoEditorView, MxLegoView)
	//{{AFX_MSG_MAP(MxLegoEditorView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL MxLegoEditorView::Create(const CString& windowName,
                              const CWnd* pParentWnd,
                              Renderer* pRenderer,
                              BOOL fullScreen,
                              int width,
                              int height,
                              int bitsPerPixel,
                              const PALETTEENTRY* pPaletteEntries,
                              int paletteEntryCount)
{
    Tgl::DoubleMatrix4  transformation;
    Matrix4             transform;
    double  position[3] = { 0, 0, 0 };
    double  direction[3];
    double  up[3];

    m_pEditorController = new EditorController(m_pScene);

     // camera
    position[0] = 0, position[1] = -10, position[2] = 1;
    direction[0] = 0, direction[1] = 1, direction[2] = 0;
    up[0] = 0, up[1] = 0, up[2] = 1;
    m_pCamera = pRenderer->CreateCamera();
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pCamera->SetTransformation(transformation);

    // lights
    m_pSunLight         = pRenderer->CreateLight(Directional, .9, .9, .9);
    m_pDirectionalLight = pRenderer->CreateLight(Directional, .4, .4, .4);
    m_pAmbientLight     = pRenderer->CreateLight(Ambient, .3, .3, .3);

    position[0] = 0, position[1] = 0, position[2] = 0;
    direction[0] = 1, direction[1] = -1, direction[2] = 2;
    up[0] = 0, up[1] = 1, up[2] = 0;
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pSunLight->SetTransformation(transformation);

    direction[0] = -1, direction[1] = -2, direction[2] = -1;
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pDirectionalLight->SetTransformation(transformation);

    if (!MxLegoView::Create(windowName, pParentWnd, pRenderer,
                            fullScreen,
                            width, height, bitsPerPixel,
                            pPaletteEntries, paletteEntryCount))
    {
        delete m_pSunLight;
        delete m_pDirectionalLight;
        delete m_pAmbientLight;
        delete m_pEditorController;
        delete m_pCamera;
        m_pSunLight         = 0;
        m_pDirectionalLight = 0;
        m_pAmbientLight     = 0;
        m_pEditorController = 0;
        m_pCamera           = 0;
        return FALSE;
    }

    return TRUE;
}

View*
MxLegoEditorView::CreateView()
{
    Device* pDevice = GetDevice();
    View*   pView = 0;

    if (pDevice)
    {
        pView = GetRenderer()->CreateView(pDevice,
                                          GetCamera(),
                                          0, 0,
                                          pDevice->GetWidth(),
                                          pDevice->GetHeight());
        if (pView)
        {
            pView->SetFrustrum(1, 500, 2 * RadiansToDegrees(atan2(.5, 1)));
            pView->SetBackgroundColor(1, 1, 1);
            pView->Add(m_pSunLight);
            pView->Add(m_pDirectionalLight);
            pView->Add(m_pAmbientLight);
        }
    }

    return pView;
}

MouseController*
MxLegoEditorView::GetController()
{
    return m_pEditorController;
}

Camera*
MxLegoEditorView::GetCamera()
{
    return m_pCamera;
}

Group*
MxLegoEditorView::GetScene()
{
    return m_pScene;
}

/////////////////////////////////////////////////////////////////////////////
// MxLegoEditorView message handlers
