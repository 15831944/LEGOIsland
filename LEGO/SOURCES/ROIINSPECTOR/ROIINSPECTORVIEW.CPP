// ROIInspectorView.cpp : implementation of the CROIInspectorView class
//

#include "stdafx.h"
#include "ROIInspector.h"

#include "ROIDoc.h"
#include "ROIInspectorView.h"
#include "LegoROI.h"
#include "LegoAnim.h"
#include "LegoStorage.h"    // loading of .ani
#include "MxDirectDraw.h"
#include "ROIInspectorROI.h"
#include "SelectLODsDlg.h"
#include "ROIPropSheet.h"
#include "AxisDlg.h"
#include "AnimateDlg.h"

#include "float.h"  // DBL_EPSILON

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

const Vector3 gCameraPosition(0, 0, -30);
//const Vector3 gCameraPosition(0, .25, -30);
const Vector3 gCameraDirection(0, 0, 1);
const Vector3 gCameraUp(0, 1, 0);

//////////////////////////////////////////////////////////////////////////////
//
//

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorView

IMPLEMENT_DYNCREATE(CROIInspectorView, CView)

BEGIN_MESSAGE_MAP(CROIInspectorView, CView)
	//{{AFX_MSG_MAP(CROIInspectorView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_VIEW_RESET, OnViewReset)
	ON_COMMAND(ID_VIEW_REMOVEALL, OnViewRemoveAll)
	ON_UPDATE_COMMAND_UI(ID_VIEW_REMOVEALL, OnUpdateViewRemoveAll)
	ON_COMMAND(ID_OPTIONS_VIEW_MULTIPLE_LODS, OnOptionsViewMultipleLods)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_VIEW_MULTIPLE_LODS, OnUpdateOptionsViewMultipleLods)
	ON_COMMAND(ID_OPTIONS_USESHORTNAMES, OnOptionsUseShortNames)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_USESHORTNAMES, OnUpdateOptionsUseShortNames)
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_VIEW_LODS, OnViewLods)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LODS, OnUpdateViewLods)
	ON_COMMAND(ID_VIEW_ROIPROPERTIES, OnViewProperties)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ROIPROPERTIES, OnUpdateViewProperties)
	ON_COMMAND(ID_OPTIONS_FIT_IN_WINDOW, OnOptionsFitInWindow)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_FIT_IN_WINDOW, OnUpdateOptionsFitInWindow)
	ON_COMMAND(ID_TOOLS_CALCULATECOSTS, OnToolsCalculateCosts)
	ON_UPDATE_COMMAND_UI(ID_TOOLS_CALCULATECOSTS, OnUpdateToolsCalculateCosts)
	ON_COMMAND(ID_VIEW_AXIS, OnViewAxis)
	ON_UPDATE_COMMAND_UI(ID_VIEW_AXIS, OnUpdateViewAxis)
	ON_COMMAND(ID_OPTIONS_CONFIGURE_AXIS, OnOptionsConfigureAxis)
	ON_COMMAND(ID_VIEW_LODAXIS, OnViewLodAxis)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LODAXIS, OnUpdateViewLodAxis)
	ON_COMMAND(ID_OPTIONS_CONFIGURELODAXIS, OnOptionsConfigureLODAxis)
	ON_COMMAND(ID_ANIMATION_OPEN, OnAnimationOpen)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_OPEN, OnUpdateAnimationOpen)
	ON_COMMAND(ID_ANIMATION_SETORIGINAL, OnAnimationSetoriginal)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_SETORIGINAL, OnUpdateAnimationSetoriginal)
	ON_COMMAND(ID_ANIMATION_ANIMATE, OnAnimationAnimate)
	ON_UPDATE_COMMAND_UI(ID_ANIMATION_ANIMATE, OnUpdateAnimationAnimate)
	//}}AFX_MSG_MAP
	ON_NOTIFY(TVN_SELCHANGED, ID_ROITREECTRL, OnSelchangedRoiTree)
	ON_NOTIFY(NM_RCLICK, ID_ROITREECTRL, OnRButtonClkRoiTree)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorView construction/destruction

CROIInspectorView::CROIInspectorView()
{
	// TODO: add construction code here
    m_pRenderer                 = 0;
    m_pROI                      = 0;
    m_pROIPropSheet             = 0;
    m_fitInWindow               = FALSE;
    m_viewMultipleLODs          = FALSE;
    
    m_pAxis                     = 0;
    m_lodAxis                   = FALSE;
    
    m_axisMin                   = Vector3(-1, -1, -1);
    m_axisMax                   = Vector3( 1,  1,  1);
    m_isAxisMinMaxRelative      = TRUE;

    FILLVEC3(m_lodAxisMin, 0);
    FILLVEC3(m_lodAxisMax, 1);
    m_isLODAxisMinMaxRelative   = TRUE;

    FILLVEC3(m_axisColor, 0);
    FILLVEC3(m_lodAxisColor, 1);

    m_renderTimeLastFrame       = 0;

    m_animations                = 0;
    m_animationCount            = 0;
    m_pAnimateDlg               = 0;
}

CROIInspectorView::~CROIInspectorView()
{
    RemoveAllFromScene();

    if (m_pROIPropSheet)
    {
        m_pROIPropSheet->DestroyWindow();
        m_pROIPropSheet = 0;
    }

    if (m_pAxis)
    {
        if (m_pROI)
        {
            m_pROI->GetGeometry()->Remove(m_pAxis);
        }
        delete m_pAxis;
    }

    if (m_pROI)
    {
        m_legoView.GetScene()->Remove(m_pROI->GetGeometry());
        delete m_pROI;
    }

    delete [] m_animations;
    m_animations        = 0;
    m_animationCount    = 0;
    
    delete m_pAnimateDlg;
    m_pAnimateDlg       = 0;

    m_legoViewWnd.DestroyWindow();
    m_legoView.Destroy();

    delete m_pRenderer;
    m_pRenderer = 0;
}

BOOL CROIInspectorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int CROIInspectorView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_roiTreeCtrl.Create(WS_VISIBLE | WS_CHILD, // styles
		                 CRect(0,0,0,0),        // bounding rectangle,
                         this,                  // parent
                         ID_ROITREECTRL);       // id
	
    ASSERT(!m_pRenderer);
    m_pRenderer = Tgl::CreateRenderer();
    ASSERT(m_pRenderer);

    {
        LegoView1::CreateStruct createStruct;
        int                     width = 600;
        int                     height = 600;  
        int                     bitsPerPixel;
        BOOL                    result;
        PALETTEENTRY            paletteEntry[256];
        int                     paletteEntryCount;

        if (!GetResourceBitmapPaletteEntries(MAKEINTRESOURCE(IDB_PALETTE),
                                             sizeof(paletteEntry) / sizeof(paletteEntry[0]),
                                             paletteEntry,
                                             paletteEntryCount))
        {
            return -1;
        }

        if ((paletteEntry[142].peRed == paletteEntry[159].peRed) &&
            (paletteEntry[142].peGreen == paletteEntry[159].peGreen) &&
            (paletteEntry[142].peBlue == paletteEntry[159].peBlue))
        {
            // ??? duplicate palette entry
            //     system palette will reject 159, and all remaining entries
            //     will thus be shifted 1
            paletteEntry[159].peBlue++;
        }

        {
            CClientDC   dc(this);

            bitsPerPixel = dc.GetDeviceCaps(PLANES) * dc.GetDeviceCaps(BITSPIXEL);
        }

        result = m_legoViewWnd.Create("ROI Inspector", 0, FALSE,
                                      width, height, bitsPerPixel,
                                      paletteEntry, paletteEntryCount);
        ASSERT(result);
        if (!result)
        {
            return -1;
        }
        m_legoViewWnd.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
        m_legoViewWnd.SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);

        createStruct.m_pDriverGUID  = 0;
        createStruct.m_hWnd         = m_legoViewWnd.GetSafeHwnd();
        createStruct.m_pDirectDraw  = m_legoViewWnd.DirectDraw()->DirectDraw();
        createStruct.m_pFrontBuffer = m_legoViewWnd.DirectDraw()->FrontBuffer();
        createStruct.m_pBackBuffer  = m_legoViewWnd.DirectDraw()->BackBuffer();
        createStruct.m_pPalette     = m_legoViewWnd.DirectDraw()->Palette();
        createStruct.m_isFullScreen = FALSE;

        if (!m_legoView.Create(createStruct, m_pRenderer))
        {
            return -1;
        }

        // allow LegoViewWnd's mouse events control xxx
        m_legoViewWnd.SetMouseController(&m_controller);

        // allow LegoViewWnd's handle rendering (incl. blt-ing frame rate)
        m_legoViewWnd.SetLegoView(&m_legoView);

        // set camera position
#if 0
        m_legoView.GetCamera()->SetPosition(gCameraPosition.elements);
        m_legoView.GetCamera()->SetOrientation(gCameraDirection.elements,
                                               gCameraUp.elements);
#else
        {
            Tgl::DoubleMatrix4  transformation;
            Matrix4             transform;

            CalcLocalTransform(gCameraPosition, gCameraDirection, gCameraUp, transform);
            SETMAT4(transformation, transform);
            m_legoView.GetCamera()->SetTransformation(transformation);
        }
#endif

        // create InspectorROI that will hold LODs being viewed
        m_pROI = new ROIInspectorROI(m_pRenderer);

        // add the InspectorROI to the scene
        ASSERT(m_legoView.GetScene());
        ASSERT(m_pROI->GetGeometry());
	    m_legoView.GetScene()->Add(m_pROI->GetGeometry());

        // let controller control scene ROI
        m_controller.SetROI(m_pROI);
    }

    // tell document about renderer and LODList manager
    GetDocument()->SetManagers(m_pRenderer, &m_viewLODListManager);

    // move frame window off LegoView window
    CFrameWnd*  pFrameWnd = GetParentFrame();
    CRect       legoViewWndRect;

    m_legoViewWnd.GetWindowRect(legoViewWndRect);
    pFrameWnd->MoveWindow(legoViewWndRect.right, legoViewWndRect.top,
                          320, legoViewWndRect.bottom - legoViewWndRect.top,
                          FALSE);

    return 0;
}

void CROIInspectorView::Tickle()
{
    // Let LegoViewWnd do the rendering to allow it adding
    // statistics etc.
    // LegoView.Render();
    m_renderTimeLastFrame = m_legoViewWnd.Render();
}

void CROIInspectorView::AddToScene(const ViewROI* pROI,
                                   const ViewLOD* pLOD,
                                   unsigned long vertexCount)
{
    ASSERT(m_pROI);
    m_pROI->Add(pROI, pLOD, vertexCount);

    if (m_lodAxis)
    {
        AddAxis(pROI);
    }
}

void CROIInspectorView::AddMultipleToScene(const ViewROI* pROI,
                                           int partsDepth,
                                           int lodNumber,
                                           BOOL isLodNumberRelative)
{
    ASSERT(pROI);

    const CompoundObject*   pParts = pROI->GetComp();

    if ((partsDepth == 0) || !pParts)
    {
        // select an LOD of pROI

        if (isLodNumberRelative)
        {
            lodNumber = (lodNumber * pROI->GetLODCount()) / 100;
        }

        if (lodNumber >= pROI->GetLODCount())
        {
            lodNumber = pROI->GetLODCount() - 1;
        }

        ASSERT(lodNumber < pROI->GetLODCount());
        ASSERT(pROI->GetLOD(lodNumber));

        AddToScene(pROI, 
                   static_cast<const ViewLOD*>(pROI->GetLOD(lodNumber)),
                   static_cast<const LegoLOD*>(pROI->GetLOD(lodNumber))->GetNumVertices());
    }
    else
    {
        CompoundObject::const_iterator  iterator;

        for (iterator = pParts->begin(); !(iterator == pParts->end()); ++iterator)
        {
            const ROI*      pPart = *iterator;
            const ViewROI*  pViewROI = static_cast<const ViewROI*>(pPart);

            AddMultipleToScene(pViewROI, 
                               partsDepth - 1,
                               lodNumber,
                               isLodNumberRelative);
        }
    }
}

void CROIInspectorView::RemoveFromeScene(const ViewROI* pROI,
                                         const ViewLOD* pLOD)
{
    ASSERT(m_pROI);
    m_pROI->Remove(pROI, pLOD);
}

void CROIInspectorView::RemoveAllFromScene()
{
    ASSERT(m_pROI);
    m_pROI->RemoveAll();
}

void CROIInspectorView::MoveCameraOutsideBoundingSphere()
{
    ASSERT(m_legoView.GetCamera());
    ASSERT(m_pROI);

    Vector3                 position = gCameraPosition;
    const BoundingSphere&   rBoundingSphere = m_pROI->GetWorldBoundingSphere();
    int                     frontClippingPlane = 1;

    // ??? for now just move camera in Z direction
    //     and assume m_pROI is at origin

    // also assume front clipping plane is at 1
    // we could set it here...

#if 0
    ASSERT(fabs(position[0]) <= DBL_EPSILON); 
    ASSERT(fabs(position[1]) <= DBL_EPSILON); 
    ASSERT(fabs(position[2]) > DBL_EPSILON); 
#endif

    position[2] = -(frontClippingPlane + rBoundingSphere.Radius());

#if 0
    m_legoView.GetCamera()->SetPosition(position.elements);
#else
    {
        Tgl::DoubleMatrix4  transformation;
        Matrix4             transform;

        CalcLocalTransform(position, gCameraDirection, gCameraUp, transform);
        SETMAT4(transformation, transform);
        m_legoView.GetCamera()->SetTransformation(transformation);
    }
#endif

#if 0
    TRACE("MoveCameraOutsideBoundingSphere: Camera at [%.4f, %.4f, %.4f]\n",
            (double)position[0],(double)position[1],(double)position[2]);
#endif
}

Tgl::Mesh*  CROIInspectorView::CreateAxisMesh(Tgl::Renderer* pRenderer,
                                              const Vector3& rFrom, 
                                              const Vector3& rTo,
                                              double r, double g, double b)
{
    float axisVertices[][3] =
    {
        { EXPAND3(rFrom) },	// 0
        { EXPAND3(rFrom) },	// 1 
        { EXPAND3(rFrom) },	// 2
        { EXPAND3(rFrom) },	// 3
        { EXPAND3(rTo)   },	// 4
        { EXPAND3(rTo)   },	// 5
        { EXPAND3(rTo)   },	// 6
        { EXPAND3(rTo)   },	// 7
    };

    unsigned long axisFaces[] = 
    {
        0,1,3,2,
        0,2,6,4,
        2,3,7,6,
        3,1,5,7,
        1,0,4,5,
        4,6,7,5
    };

    int         vertexCount = sizeof(axisVertices) / sizeof(axisVertices[0]);
    int         vertexPerFaceCount = 4;
    int         faceCount   = sizeof(axisFaces) / (sizeof(axisFaces[0]) * vertexPerFaceCount);
    Tgl::Mesh*  pMesh;
    Tgl::Result result;

    pMesh = pRenderer->CreateMesh(vertexCount,
                                 (const float(*)[3])axisVertices,
                                 0,
                                 faceCount,
                                 vertexPerFaceCount,
                                 axisFaces);

    result = pMesh->SetShadingModel(Tgl::Wireframe);
    ASSERT(Tgl::Succeeded(result));

    result = pMesh->SetColor(r, g, b);
    ASSERT(Tgl::Succeeded(result));

    return pMesh;
}

Tgl::Group*  CROIInspectorView::CreateAxis(Tgl::Renderer* pRenderer,
                                           const Vector3& rAxisMin,
                                           const Vector3& rAxisMax,
                                           double r, double g, double b)
{
    Tgl::Group* pGroup;
    Tgl::Mesh*  pMesh;
    Tgl::Result result;

    pGroup = pRenderer->CreateGroup();
    ASSERT(pGroup);

    pMesh = CreateAxisMesh(pRenderer,
                           Vector3(rAxisMin[0], 0, 0),
                           Vector3(rAxisMax[0], 0, 0),
                           r, g, b);
    ASSERT(pMesh);
    result = pGroup->Add(pMesh);
    ASSERT(Tgl::Succeeded(result));
    delete pMesh;

    pMesh = CreateAxisMesh(pRenderer,
                           Vector3(0, rAxisMin[1], 0),
                           Vector3(0, rAxisMax[1], 0),
                           r, g, b);
    ASSERT(pMesh);
    pGroup->Add(pMesh);
    ASSERT(Tgl::Succeeded(result));
    delete pMesh;

    pMesh = CreateAxisMesh(pRenderer,
                           Vector3(0, 0, rAxisMin[2]),
                           Vector3(0, 0, rAxisMax[2]),
                           r, g, b);
    ASSERT(pMesh);
    pGroup->Add(pMesh);
    ASSERT(Tgl::Succeeded(result));
    delete pMesh;

    return pGroup;
}

void CROIInspectorView::AddAxis()
{
    if (!m_pAxis)
    {
        Vector3     axisMin = m_axisMin;
        Vector3     axisMax = m_axisMax;
        Tgl::Result result;

        if (m_isLODAxisMinMaxRelative)
        {
    	    CROIDoc*    pDoc = GetDocument();
            ROI*        pROI = (pDoc->GetROICount() > 0) ? pDoc->GetROI(0) : 0;

            if (pROI)
            {
                SXV3(axisMin, pROI->GetWorldBoundingSphere().Radius(), axisMin);
                SXV3(axisMax, pROI->GetWorldBoundingSphere().Radius(), axisMax);
            }
        }

        m_pAxis = CreateAxis(m_pRenderer, axisMin, axisMax, EXPAND3(m_axisColor));
        ASSERT(m_pAxis);
        result = m_pROI->GetGeometry()->Add(m_pAxis);
        ASSERT(Tgl::Succeeded(result));
    }
}

void CROIInspectorView::RemoveAxis()
{
    if (m_pAxis)
    {
        Tgl::Result result;

        result = m_pROI->GetGeometry()->Remove(m_pAxis);
        ASSERT(Tgl::Succeeded(result));
        delete m_pAxis;
        m_pAxis = 0;
    }
}

void CROIInspectorView::AddAxis(const ViewROI* pROI)
{
    Tgl::Group* pAxis;
    Vector3     axisMin = m_lodAxisMin;
    Vector3     axisMax = m_lodAxisMax;
    Tgl::Result result;

    ASSERT(pROI);
    
    // add axis geometry to ROI's geometry group
    // the axis geometry will be removed by InspectorROI's Remove()
    
    if (m_isLODAxisMinMaxRelative)
    {
        SXV3(axisMin, pROI->GetWorldBoundingSphere().Radius(), axisMin);
        SXV3(axisMax, pROI->GetWorldBoundingSphere().Radius(), axisMax);
    }

    pAxis = CreateAxis(m_pRenderer, axisMin, axisMax, EXPAND3(m_lodAxisColor));
    ASSERT(pAxis);
    result = const_cast<Tgl::Group*>(pROI->GetGeometry())->Add(pAxis);
    ASSERT(Tgl::Succeeded(result));
    delete pAxis;
}

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorView drawing

void CROIInspectorView::OnDraw(CDC* pDC)
{
	CROIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

void CROIInspectorView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

    RemoveAllFromScene();
    m_roiTreeCtrl.Expand(m_roiTreeCtrl.GetRootItem(), TVE_COLLAPSE);
    m_roiTreeCtrl.DeleteAllItems();
    if (m_pAnimateDlg)
    {
        m_pAnimateDlg->Set(0, 0, 0);
    }

    for (int i = 0; i < GetDocument()->GetROICount(); i++)
    {
        m_roiTreeCtrl.Insert(*GetDocument()->GetROI(i));
    }

    if (GetDocument()->GetROICount() > 0)
    {
        m_roiTreeCtrl.SelectItem(m_roiTreeCtrl.GetRootItem());
    }

    if (m_pROIPropSheet && m_pROIPropSheet->IsWindowVisible())
    {
        const LegoROI*    pROI;
        const LegoLOD*    pLOD;

        m_roiTreeCtrl.GetSelection(pROI, pLOD);

        m_pROIPropSheet->Display(pROI, pLOD);
    }

    if (m_pAnimateDlg && m_pAnimateDlg->IsWindowVisible())
    {
        if (GetDocument()->GetROICount() > 0)
        {
            m_pAnimateDlg->Set(GetDocument()->GetROI(0), m_animationCount, m_animations);
        }
        else
        {
            m_pAnimateDlg->Set(0, m_animationCount, m_animations);
        }
    }


}

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorView diagnostics

#ifdef _DEBUG
void CROIInspectorView::AssertValid() const
{
	CView::AssertValid();
}

void CROIInspectorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CROIDoc* CROIInspectorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CROIDoc)));
	return (CROIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CROIInspectorView message handlers

void CROIInspectorView::OnSize(UINT nType, int cx, int cy) 
{
	CView::OnSize(nType, cx, cy);
	
	m_roiTreeCtrl.MoveWindow(0, 0, cx, cy);	
	
}

void CROIInspectorView::OnSelchangedRoiTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW*    pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    const LegoROI*  pROI;
    const LegoLOD*  pLOD;

    m_roiTreeCtrl.GetSelection(pROI, pLOD);
	
    if (pLOD)
    {
        if (!m_viewMultipleLODs)
        {
            RemoveAllFromScene();
        }
        
        AddToScene(pROI, pLOD, pLOD->GetNumVertices());
        
        if (m_fitInWindow)
        {
            MoveCameraOutsideBoundingSphere();
        }
    }

    if (m_pROIPropSheet && m_pROIPropSheet->IsWindowVisible())
    {
        m_pROIPropSheet->Display(pROI, pLOD);
    }

	*pResult = 0;
}

void CROIInspectorView::OnViewReset() 
{
    if (m_pROI)
    {
        Vector3 rotation( 0, 0, 0 );

        m_pROI->Scale(1);
        m_pROI->Rotate(rotation);
    }
}

void CROIInspectorView::OnViewRemoveAll() 
{
    ASSERT(m_pROI);
    m_pROI->RemoveAll();
}
	
void CROIInspectorView::OnUpdateViewRemoveAll(CCmdUI* pCmdUI) 
{
    ASSERT(m_pROI);
	pCmdUI->Enable(m_pROI->GetInspectedLODCount() > 0);
}

void CROIInspectorView::OnOptionsFitInWindow() 
{
    m_fitInWindow = !m_fitInWindow;
}

void CROIInspectorView::OnUpdateOptionsFitInWindow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_fitInWindow);
}

void CROIInspectorView::OnOptionsViewMultipleLods() 
{
    m_viewMultipleLODs = !m_viewMultipleLODs;
}

void CROIInspectorView::OnUpdateOptionsViewMultipleLods(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_viewMultipleLODs);
}

void CROIInspectorView::OnOptionsUseShortNames() 
{
    m_roiTreeCtrl.EnableShortNames(!m_roiTreeCtrl.ShortNamesEnabled(), '\\');

    // remove and re-insert items
    m_roiTreeCtrl.Expand(m_roiTreeCtrl.GetRootItem(), TVE_COLLAPSE);
    m_roiTreeCtrl.DeleteAllItems();

    for (int i = 0; i < GetDocument()->GetROICount(); i++)
    {
        m_roiTreeCtrl.Insert(*GetDocument()->GetROI(i));
    }
}

void CROIInspectorView::OnUpdateOptionsUseShortNames(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_roiTreeCtrl.ShortNamesEnabled());
}

void CROIInspectorView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	m_roiTreeCtrl.SetFocus();
}

void CROIInspectorView::OnViewLods() 
{
    if (GetDocument()->GetROICount() > 0) 
    {
        CSelectLODsDlg dlg;
        
        if (dlg.DoModal() == IDOK)
        {
            const LegoROI*  pROI = GetDocument()->GetROI(0);

            RemoveAllFromScene();

            AddMultipleToScene(pROI, dlg.m_depth, dlg.m_lodNumber, dlg.m_isLODNumberRelative);

            if (m_fitInWindow)
            {
                MoveCameraOutsideBoundingSphere();
            }
        
            m_roiTreeCtrl.SelectItem(m_roiTreeCtrl.GetRootItem());
       }
    }
}

void CROIInspectorView::OnUpdateViewLods(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(GetDocument()->GetROICount() > 0);
}

void CROIInspectorView::OnViewProperties() 
{
    if (!m_pROIPropSheet)
    {
        m_pROIPropSheet = new CROIPropSheet("Properties", this);
        m_pROIPropSheet->Create();
    }
    else if (m_pROIPropSheet->IsWindowVisible())
    {
        m_pROIPropSheet->ShowWindow(SW_HIDE);
    }
    else
    {
        m_pROIPropSheet->ShowWindow(SW_SHOW);
    }

    if (m_pROIPropSheet->IsWindowVisible())
    {
        const LegoROI*    pROI;
        const LegoLOD*    pLOD;

        m_roiTreeCtrl.GetSelection(pROI, pLOD);

        m_pROIPropSheet->Display(pROI, pLOD);
    }
}

void CROIInspectorView::OnUpdateViewProperties(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_pROIPropSheet &&
                     m_pROIPropSheet->IsWindowVisible());
}

void CROIInspectorView::OnRButtonClkRoiTree(NMHDR* pNMHDR, LRESULT* pResult)
{
#if 0
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
    TRACE("CROIInspectorView::OnRButtonClkRoiTree()\n");

    CMenu   menu;
    CMenu*  pPopupMenu;
    POINT   cursorPosition;
    BOOL    result;

    result = menu.LoadMenu(IDR_POPUP_MENU1);
    ASSERT(result);

    pPopupMenu = menu.GetSubMenu(0);
    ASSERT(pPopupMenu);

    result = ::GetCursorPos(&cursorPosition);
    ASSERT(result);

    HitTest
    pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                               cursorPosition.x,
                               cursorPosition.y,
                               this);

#endif    
    *pResult = 0;
}

void CROIInspectorView::OnViewAxis() 
{
    if (m_pAxis)
    {
        RemoveAxis();
    }
    else
    {
        AddAxis();
    }
}

void CROIInspectorView::OnUpdateViewAxis(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_pAxis != 0);
}

void CROIInspectorView::OnOptionsConfigureAxis() 
{
    CAxisDlg    axisDlg;

    axisDlg.m_xAxisMin  = m_axisMin[0];
    axisDlg.m_xAxisMax  = m_axisMax[0];
    axisDlg.m_yAxisMin  = m_axisMin[1];
    axisDlg.m_yAxisMax  = m_axisMax[1];
    axisDlg.m_zAxisMin  = m_axisMin[2];
    axisDlg.m_zAxisMax  = m_axisMax[2];
    axisDlg.m_relative  = m_isAxisMinMaxRelative;

    if (axisDlg.DoModal())
    {
        m_axisMin = Vector3(axisDlg.m_xAxisMin, axisDlg.m_yAxisMin, axisDlg.m_zAxisMin);
        m_axisMax = Vector3(axisDlg.m_xAxisMax, axisDlg.m_yAxisMax, axisDlg.m_zAxisMax);
        m_isAxisMinMaxRelative  = axisDlg.m_relative;

        if (m_pAxis)
        {
            RemoveAxis();
            AddAxis();
        }
    }
}

void CROIInspectorView::OnOptionsConfigureLODAxis() 
{
    CAxisDlg    axisDlg;

    axisDlg.m_xAxisMin  = m_lodAxisMin[0];
    axisDlg.m_xAxisMax  = m_lodAxisMax[0];
    axisDlg.m_yAxisMin  = m_lodAxisMin[1];
    axisDlg.m_yAxisMax  = m_lodAxisMax[1];
    axisDlg.m_zAxisMin  = m_lodAxisMin[2];
    axisDlg.m_zAxisMax  = m_lodAxisMax[2];
    axisDlg.m_relative  = m_isLODAxisMinMaxRelative;

    if (axisDlg.DoModal())
    {
        m_lodAxisMin = Vector3(axisDlg.m_xAxisMin, axisDlg.m_yAxisMin, axisDlg.m_zAxisMin);
        m_lodAxisMax = Vector3(axisDlg.m_xAxisMax, axisDlg.m_yAxisMax, axisDlg.m_zAxisMax);
        m_isLODAxisMinMaxRelative   = axisDlg.m_relative;
    }
}

void CROIInspectorView::OnViewLodAxis() 
{
    m_lodAxis = !m_lodAxis;
}

void CROIInspectorView::OnUpdateViewLodAxis(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_lodAxis);
}

void CROIInspectorView::OnToolsCalculateCosts() 
{
    //m_roiTreeCtrl.EnableWindow(FALSE);
    //m_roiTreeCtrl.EnableWindow(TRUE);
}

void CROIInspectorView::OnUpdateToolsCalculateCosts(CCmdUI* pCmdUI) 
{
    //pCmdUI->Enable(GetDocument()->GetROICount() > 0);
    pCmdUI->Enable(FALSE);
}

//////////////////////////////////////////////////////////////////////////////

void CROIInspectorView::OnAnimationOpen() 
{
	CFileDialog	dlg(TRUE,
					0,
					0,
					OFN_HIDEREADONLY,
					"Animation Files (*.ani)|*.ani|All Files (*.*)|*.*||",
					this);

	dlg.m_ofn.lpstrTitle	= "Open Animation";

    if (dlg.DoModal() == IDOK)
    {
        LegoFile    file;
        LegoResult  result;

        BeginWaitCursor();
        result = file.Open(dlg.GetPathName(), LegoFile::c_read);
        if (result == SUCCESS)
        {
            LegoU32 animationCount;

            delete [] m_animations;
            m_animations        = 0;
            m_animationCount    = 0;

            result = file.Read(&animationCount, sizeof(animationCount));
            if (result == SUCCESS)
            {
                m_animationCount    = animationCount;
                m_animations        = new LegoAnim[m_animationCount];

                for (unsigned int i = 0; i < m_animationCount; i++)
                {
                    result = m_animations[i].Read(&file);
                }
            }
            file.Close();

            if (result != SUCCESS)
            {
                delete [] m_animations;
                m_animations        = 0;
                m_animationCount    = 0;
                AfxMessageBox("Failed to open animation");
            }

            if (m_pAnimateDlg)
            {
                if (GetDocument()->GetROICount() > 0)
                {
                    m_pAnimateDlg->Set(GetDocument()->GetROI(0), m_animationCount, m_animations);
                }
                else
                {
                    m_pAnimateDlg->Set(0, m_animationCount, m_animations);
                }
            }
        }
        EndWaitCursor();
    }
}

void CROIInspectorView::OnUpdateAnimationOpen(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(GetDocument()->GetROICount() > 0);
}

void CROIInspectorView::OnAnimationAnimate() 
{
    if (!m_pAnimateDlg)
    {
        m_pAnimateDlg = new CAnimateDlg(this);
        m_pAnimateDlg->Create(CAnimateDlg::IDD);

        if (GetDocument()->GetROICount() > 0)
        {
            m_pAnimateDlg->Set(GetDocument()->GetROI(0), m_animationCount, m_animations);
        }
        else
        {
            m_pAnimateDlg->Set(0, m_animationCount, m_animations);
        }
    }

    if (m_pAnimateDlg->IsWindowVisible())
    {
        m_pAnimateDlg->ShowWindow(SW_HIDE);
    }
    else
    {
        m_pAnimateDlg->ShowWindow(SW_SHOW);
    }
}

void CROIInspectorView::OnUpdateAnimationAnimate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((GetDocument()->GetROICount() > 0) && (m_animationCount > 0));
	pCmdUI->SetCheck(m_pAnimateDlg && m_pAnimateDlg->IsWindowVisible());
}

void CROIInspectorView::OnAnimationSetoriginal() 
{
	if (GetDocument()->GetROICount() > 0)
    {
        GetDocument()->GetROI(0)->SetFrame(GetDocument()->GetAnimation(0), 0);
    }
}

void CROIInspectorView::OnUpdateAnimationSetoriginal(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetDocument()->GetROICount() > 0);
}

