#include <afxdlgs.h>
#include <rl.h>
#include <rlwin.h>
#include "viewer.h"
#include "LegoTypes.h"
#include "LegoMesh.h"
#include "LegoStorage.h"
#include "LegoBox.h"
#include "LegoUtil.h"
#undef TRACE2
#undef TRACE3
#include "vec.h"
#include "resource.h"

LegoViewer* g_viewer = NULL;
static LegoViewerApp viewerApp;

LegoMainWindow::LegoMainWindow()
{
    Create(NULL, "Viewer", WS_OVERLAPPEDWINDOW, rectDefault, NULL, MAKEINTRESOURCE(IDR_MENU));
}

int
LegoMainWindow::OnCreate(CREATESTRUCT* p_cs)
{
	if (CFrameWnd::OnCreate(p_cs) == -1) {
		return -1;
    }
    CRect windowRect;
    GetWindowRect(windowRect);
    CRect clientRect;
    GetClientRect(clientRect);
    SetWindowPos(
        NULL, 
        0, 
        0, 
        640 + windowRect.Width() - clientRect.Width(), 
        480 + windowRect.Height() - clientRect.Height(), 
        SWP_NOMOVE | SWP_NOZORDER
    );
    return 0;
}

void 
LegoMainWindow::OnPaint()
{
    if (g_viewer) {
        CPaintDC dc(this);
        RLWinHandlePaint(g_viewer->GetDevice(), dc.GetSafeHdc());
    }
    else {
        CFrameWnd::OnPaint();
    }
}

void 
LegoMainWindow::OnActivate(UINT p_state, CWnd* p_other, BOOL p_minimized)
{
    if (g_viewer) {
        RLWinHandleActivate(g_viewer->GetDevice(), p_state);
    }
    else {
        CFrameWnd::OnActivate(p_state, p_other, p_minimized);
    }
}

void 
LegoMainWindow::OnLButtonDown(UINT p_flags, CPoint p_point) 
{
	if(g_viewer) {
		g_viewer->SetMousePos(p_point);
    }
	SetCapture();
	CFrameWnd::OnLButtonDown(p_flags, p_point);
}

void 
LegoMainWindow::OnLButtonUp(UINT p_flags, CPoint p_point) 
{
	if (CWnd::GetCapture() == this) {
		ReleaseCapture();
    }
	CFrameWnd::OnLButtonUp(p_flags, p_point);
}

void 
LegoMainWindow::OnRButtonDown(UINT p_flags, CPoint p_point) 
{
	if(g_viewer) {
		g_viewer->SetMousePos(p_point);
    }
	SetCapture();
	CFrameWnd::OnRButtonDown(p_flags, p_point);
}

void 
LegoMainWindow::OnRButtonUp(UINT p_flags, CPoint p_point) 
{
	if (CWnd::GetCapture() == this) {
		ReleaseCapture();
    }
	CFrameWnd::OnRButtonUp(p_flags, p_point);
}

void 
LegoMainWindow::OnMouseMove(UINT p_flags, CPoint p_point) 
{
	if(g_viewer) {
		if(p_flags & MK_LBUTTON) {
			g_viewer->LeftDrag(p_point);
        }
		else if (p_flags & MK_RBUTTON) {
			g_viewer->RightDrag(p_point);	
        }
    }
	CFrameWnd::OnMouseMove(p_flags, p_point);
}

void 
LegoMainWindow::OnOpen()
{
    CFileDialog dialog(
        TRUE, 
        NULL, 
        "*.leg", 
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Lego Files (*.leg)|*.leg|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        OpenFile(dialog.GetPathName());
        InvalidateRect(NULL);
        UpdateWindow();
    }
}

void 
LegoMainWindow::OnExit()
{
    DestroyWindow();
}


BEGIN_MESSAGE_MAP(LegoMainWindow, CFrameWnd)
    ON_WM_CREATE()
    ON_WM_PAINT()
    ON_WM_ACTIVATE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_COMMAND(ID_FILE_OPEN, OnOpen)
    ON_COMMAND(ID_FILE_EXIT, OnExit)
END_MESSAGE_MAP()

void
LegoMainWindow::OpenFile(const char* p_fileName)
{
    LegoFile file;
    if (file.Open((char*) p_fileName, LegoFile::c_read) != SUCCESS) {
        MessageBox("Unable to open file");
        return;
    }
    LegoU32 i, j, k;
    RLFrame object = RLCreateFrame(g_viewer->GetScene());
    g_viewer->SetObject(object);
    LegoBox box;
    LegoU32 numMeshes;
    file.Read(&numMeshes, sizeof(numMeshes));
    for (i = 0; i < numMeshes; i++) {
        LegoMesh legoMesh;
        legoMesh.Read(&file);
        RLVector* vertices = new RLVector[legoMesh.GetNumVertices()];
        int* faceData = new int[legoMesh.GetNumFaces() * 4 + 1];
        for (j = 0; j < legoMesh.GetNumVertices(); j++) {
            vertices[j].x = legoMesh.GetVertex(j).GetX();
            vertices[j].y = legoMesh.GetVertex(j).GetY();
            vertices[j].z = legoMesh.GetVertex(j).GetZ();
            box.AddVertex(legoMesh.GetVertex(j));
        }
        int* p = faceData;
        for (j = 0; j < legoMesh.GetNumFaces(); j++) {
            *p++ = 3;
            for (k = 0; k < 3; k++) {
                *p++ = legoMesh.GetFace(j).GetVertexIndex(k);
            }
        }
        *p = 0;
        RLMesh rlMesh = RLCreateMesh();
        RLMeshAddFaces(
            rlMesh, 
            legoMesh.GetNumVertices(),
            vertices,
            0,
            NULL,
            faceData,
            NULL,
            NULL
        );
        delete [] vertices;
        delete [] faceData;
        RLMeshSetColourRGB(rlMesh, 0.0F, 0.0F, 1.0F);
        RLFrameAddVisual(object, rlMesh);
    }
    LegoVertex center = box.GetCenter();
    float span = Max(box.GetDX(), box.GetDY(), box.GetDZ());
	RLFrameAddTranslation(object, RLCombineAfter, -center.GetX(), -center.GetY(), -center.GetZ());
	RLFrameAddScale(object, RLCombineAfter, 1.0F / span, 1.0F / span, 1.0F / span);
}

BOOL 
LegoViewerApp::InitInstance()
{
    m_pMainWnd = new LegoMainWindow();
    m_pMainWnd->ShowWindow(m_nCmdShow);
    m_pMainWnd->UpdateWindow();
    
    g_viewer = new LegoViewer();
    return TRUE;
}

int
LegoViewerApp::ExitInstance()
{
    delete g_viewer;
    return 0;
}

BOOL 
LegoViewerApp::OnIdle(LONG p_count)
{
    if (CWinApp::OnIdle(p_count)) {
        return TRUE;
    }
    RLTick();
    return TRUE;
}

LegoViewer::LegoViewer()
{
    CRect rect;
    m_object = NULL;
    viewerApp.m_pMainWnd->GetClientRect(rect);
    m_device = RLWinCreateDevice(viewerApp.m_pMainWnd->GetSafeHwnd(), NULL, rect.Width(), rect.Height());
	RLDeviceSetDither(m_device, FALSE);
    RLDeviceSetColourModel(m_device, RLColourRamp);
    RLDeviceSetQuality(m_device, RLRenderGouraud);
    m_scene = RLCreateFrame(NULL);
    RLFrame camera = RLCreateFrame(m_scene);
    m_viewport = RLCreateViewport(
        m_device, 
        camera, 
        0, 0,
	    RLDeviceGetWidth(m_device),
	    RLDeviceGetHeight(m_device)
	);
    RLViewportSetBack(m_viewport, 5000.0F);
    RLFrame lights = RLCreateFrame(m_scene);
    RLFrameSetPosition(lights, m_scene, 5.0F, 5.0F, -1.0F);
    RLFrameAddLight(lights, RLCreateLightRGB(RLLightDirectional, 0.9F, 0.8F, 0.7F));
    RLFrameAddLight(m_scene, RLCreateLightRGB(RLLightAmbient, 0.1F, 0.1F, 0.1F));
    RLFrameSetPosition(camera, m_scene, 0.0F, 0.0F, -3.0F);
    RLFrameSetOrientation(camera, m_scene, 0.0F, 0.0F, 1.0F, 0.0F, 1.0F, 0.0F);
}

LegoViewer::~LegoViewer()
{
    RLObjectDestroy(m_viewport);
    RLObjectDestroy(m_scene);
    RLObjectDestroy(m_device);
}

void 
LegoViewer::SetObject(RLFrame p_object)
{
    if (m_object) {
        RLFrameRemoveChild(m_scene, m_object);
		RLObjectDestroy(m_object);
    }
    m_object = p_object;
}

void 
LegoViewer::SetMousePos(CPoint& p_mousePos)
{
    m_mousePos = p_mousePos;
}

void 
LegoViewer::LeftDrag(CPoint& p_mousePos)
{
	float dragDir[3];
	dragDir[0] = (float) (p_mousePos.x - m_mousePos.x);
	dragDir[1] = 0.0F;
	dragDir[2] = (float) (p_mousePos.y - m_mousePos.y);
	static const float yDir[] = { 0.0F, 1.0F, 0.0F };
	static const float rotSF = 0.5F; 
 	float axis[3];
	VXV3(axis, dragDir, yDir);
	float degrees = (float) sqrt(NORMSQRD3(dragDir)) * rotSF;
	RLFrameAddRotation(
        m_object, 
        RLCombineAfter,
		-axis[0], 
        -axis[1], 
        -axis[2],
		DToR(degrees)
    );
    SetMousePos(p_mousePos);
}

void 
LegoViewer::RightDrag(CPoint& p_mousePos)
{
	double xDiff = p_mousePos.x - m_mousePos.x, yDiff = p_mousePos.y - m_mousePos.y;
	double maxDiff = (Abs(xDiff) > Abs(yDiff)) ? xDiff : yDiff;
	RLValue sf = maxDiff > 0 ? 1.1F : 0.9F;
	RLFrameAddScale(m_object, RLCombineAfter, sf, sf, sf);
    SetMousePos(p_mousePos);
}
