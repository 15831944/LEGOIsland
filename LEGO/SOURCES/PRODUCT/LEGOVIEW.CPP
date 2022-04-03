// LegoView.cpp : implementation of the CLegoView class
//

#include "stdafx.h"
#include "Lego.h"

#include "LegoDoc.h"
#include "LegoView.h"
#include "MxLegoCitizenView.h"
#include "MxLegoEditorView.h"

#include "Town.h"

#include "legoroi.h"        // loading of .mod
#include "legostorage.h"
#include "legoanim.h"
#include "version.h"


using namespace Tgl;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLegoView

IMPLEMENT_DYNCREATE(CLegoView, CView)

BEGIN_MESSAGE_MAP(CLegoView, CView)
	//{{AFX_MSG_MAP(CLegoView)
	ON_WM_DESTROY()
	ON_COMMAND(ID_EDITOR_SELECTNEXT, OnEditorSelectnext)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SELECTNEXT, OnUpdateEditorSelectnext)
	ON_COMMAND(ID_EDITOR_REMOVE_ALL, OnEditorRemoveAll)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_REMOVE_ALL, OnUpdateEditorRemoveAll)
	ON_COMMAND(ID_EDITOR_SELECTPREVIOUS, OnEditorSelectprevious)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_SELECTPREVIOUS, OnUpdateEditorSelectprevious)
	ON_COMMAND(ID_EDITOR_REMOVE, OnEditorRemove)
	ON_UPDATE_COMMAND_UI(ID_EDITOR_REMOVE, OnUpdateEditorRemove)
	ON_COMMAND(ID_VIEW_EDITOR, OnViewEditor)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EDITOR, OnUpdateViewEditor)
	ON_COMMAND(ID_VIEW_PLAYER, OnViewCitizen)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLAYER, OnUpdateViewCitizen)
	ON_COMMAND(ID_VIEW_RENDERWHENNOTACTIVE, OnViewRenderwhennotactive)
	ON_UPDATE_COMMAND_UI(ID_VIEW_RENDERWHENNOTACTIVE, OnUpdateViewRenderwhennotactive)
	ON_COMMAND(ID_TOWN_LOADMODEL, OnTownLoadmodel)
	ON_UPDATE_COMMAND_UI(ID_TOWN_LOADMODEL, OnUpdateTownLoadmodel)
	ON_COMMAND(ID_TOWN_LOADPILLARS, OnTownLoadpillars)
	ON_UPDATE_COMMAND_UI(ID_TOWN_LOADPILLARS, OnUpdateTownLoadpillars)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLegoView construction/destruction

CLegoView::CLegoView()
{
	// TODO: add construction code here
    m_pCurrentView  = 0;
    m_pCitizenView  = 0;
    m_pEditorView   = 0;
    m_pViewLODListManager   = 0;
    m_paletteEntryCount     = 0;
    m_bitsPerPixel          = 0;
}

CLegoView::~CLegoView()
{
    DestroyCurrentView();

    delete m_pViewLODListManager;
    m_pViewLODListManager = 0;
}

BOOL CLegoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

int CLegoView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!GetResourceBitmapPaletteEntries(MAKEINTRESOURCE(IDB_PALETTE),
                                         sizeof(m_paletteEntry) / sizeof(m_paletteEntry[0]),
                                         m_paletteEntry,
                                         m_paletteEntryCount))
    {
        return -1;
    }

    {
        CClientDC   dc(this);

        m_bitsPerPixel = dc.GetDeviceCaps(PLANES) * dc.GetDeviceCaps(BITSPIXEL);
    }
	
	return 0;
}

void CLegoView::DestroyCurrentView()
{
    if (m_pCurrentView)
    {
        AfxGetApp()->WriteProfileInt("Preferences",
                                     "RenderWhenNotActive",
                                     m_pCurrentView->RenderWhenNotActive());

        m_pCurrentView->DestroyWindow();
        m_pCurrentView  = 0;
        m_pCitizenView  = 0;
        m_pEditorView   = 0;
    }
}

/////////////////////////////////////////////////////////////////////////////
// CLegoView drawing

void CLegoView::OnDraw(CDC* pDC)
{
    // ???
#if 0
	CLegoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	if(!GetUpdateRect(NULL))
    {
        if (m_pDevice)
        {
            // ??? HDC passed as void*
            m_pDevice->HandlePaint((void*) pDC->GetSafeHdc());
        }
	}
#endif
}

/////////////////////////////////////////////////////////////////////////////
// CLegoView diagnostics

#ifdef _DEBUG
void CLegoView::AssertValid() const
{
	CView::AssertValid();
}

void CLegoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLegoDoc* CLegoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLegoDoc)));
	return (CLegoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLegoView message handlers

void CLegoView::Tickle()
{
    if (m_pCurrentView)
    {
        m_pCurrentView->Tickle();
    }
}

void CLegoView::OnDestroy() 
{
	// Tell the document that we're goin' down
	CLegoDoc* pDoc = GetDocument();

	ASSERT_VALID(pDoc);

	CView::OnDestroy();
}


void CLegoView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
    if (!m_pViewLODListManager)
    {
        m_pViewLODListManager = new ViewLODListManager;
    }

    OnViewCitizen();
}

void CLegoView::OnTownLoadmodel() 
{
    ASSERT(m_pCitizenView);

	CFileDialog	dlg(TRUE,
					0,
					0,
					OFN_HIDEREADONLY,
					"ROI Files (*.mod)|*.mod|All Files (*.*)|*.*||",
					this);

	dlg.m_ofn.lpstrTitle	= "Load";

    if (dlg.DoModal() == IDOK)
    {
	    LegoROI*        pROI = new LegoROI(GetDocument()->GetTown()->GetRenderer());
	    LegoFile        store;
	    LegoAnim        tree;
        LegoResult      result;
	    int             roiCount, version;
		static double	model_offset=0;

        BeginWaitCursor();

	    result = store.Open(dlg.GetPathName(), LegoFile::c_read);
        ASSERT(result == SUCCESS);
		result = store.Read(&version, sizeof(version));
		ASSERT(result == SUCCESS);
		ASSERT(version == MODEL_VERSION);
	    result = store.Read(&roiCount, sizeof(roiCount));
        ASSERT(result == SUCCESS);
	    result = tree.Read(&store);
        ASSERT(result == SUCCESS);
	    result = pROI->Read(GetDocument()->GetTown()->GetRenderer(),
                            m_pViewLODListManager,
                            &store);
        ASSERT(result == SUCCESS);
	    result = pROI->SetFrame(&tree, 0);
        ASSERT(result == SUCCESS);

        // ??? who deletes memory
		Matrix4 new_position;
		IDENTMAT4(new_position);
		new_position[3][0] = model_offset;
		pROI->SetLocalTransform(new_position);
		model_offset += 10;
	    m_pCitizenView->GetViewMgr()->Add(*pROI);

        EndWaitCursor();
    }
}

void CLegoView::OnUpdateTownLoadmodel(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((m_pCurrentView != 0) &&
                   (m_pCurrentView == m_pCitizenView));
}

void CLegoView::OnTownLoadpillars() 
{
    ASSERT(m_pCitizenView);

    m_pCitizenView->GetViewMgr()->AddTestROIs(GetDocument()->GetTown()->GetRenderer(),
                                              m_pViewLODListManager);
}

void CLegoView::OnUpdateTownLoadpillars(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((m_pCurrentView != 0) &&
                   (m_pCurrentView == m_pCitizenView));
}

void CLegoView::OnEditorRemoveAll() 
{
	// TODO: Add your command handler code here
    m_pEditorView->GetEditorController()->RemoveAll();
}

void CLegoView::OnUpdateEditorRemoveAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_pCurrentView != 0) &&
                   (m_pCurrentView == m_pEditorView) &&
                   (m_pEditorView->GetEditorController()->Objects().size() > 0));
}

void CLegoView::OnEditorSelectprevious() 
{
	// TODO: Add your command handler code here
    vector<Group*>::iterator   iter;

    iter = find(m_pEditorView->GetEditorController()->Objects().begin(),
                m_pEditorView->GetEditorController()->Objects().end(),
                m_pEditorView->GetEditorController()->CurrentObject());

    m_pEditorView->GetEditorController()->SetCurrentObject(*(--iter));
}

void CLegoView::OnUpdateEditorSelectprevious(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_pCurrentView != 0) &&
                   (m_pCurrentView == m_pEditorView) &&
                   (m_pEditorView->GetEditorController()->CurrentObject() != 0) &&
                   (m_pEditorView->GetEditorController()->CurrentObject() != *(m_pEditorView->GetEditorController()->Objects().begin())));
}

void CLegoView::OnEditorSelectnext() 
{
	// TODO: Add your command handler code here
    vector<Group*>::iterator   iter;

    iter = find(m_pEditorView->GetEditorController()->Objects().begin(),
                m_pEditorView->GetEditorController()->Objects().end(),
                m_pEditorView->GetEditorController()->CurrentObject());

    m_pEditorView->GetEditorController()->SetCurrentObject(*(++iter));
	
}

void CLegoView::OnUpdateEditorSelectnext(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

    if ((m_pCurrentView != 0) && 
        (m_pCurrentView == m_pEditorView) &&
        (m_pEditorView->GetEditorController()->CurrentObject() != 0))
    {
        vector<Group*>::iterator   iter = find(m_pEditorView->GetEditorController()->Objects().begin(),
                                               m_pEditorView->GetEditorController()->Objects().end(),
                                               m_pEditorView->GetEditorController()->CurrentObject());

        if (++iter != m_pEditorView->GetEditorController()->Objects().end())
        {
            pCmdUI->Enable(TRUE);
            return;
        }

    }

    pCmdUI->Enable(FALSE);
}

void CLegoView::OnEditorRemove() 
{
	// TODO: Add your command handler code here
	m_pEditorView->GetEditorController()->Remove(m_pEditorView->GetEditorController()->CurrentObject());
}

void CLegoView::OnUpdateEditorRemove(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->Enable((m_pCurrentView != 0) &&
                   (m_pCurrentView == m_pEditorView) &&
                   (m_pEditorView->GetEditorController()->CurrentObject() != 0));
}

void CLegoView::OnViewCitizen() 
{
	// TODO: Add your command handler code here
    if (!m_pCurrentView || (m_pCurrentView != m_pCitizenView))
    {
        DestroyCurrentView();

        m_pCitizenView = new MxLegoCitizenView(GetDocument()->GetTown()->GetScene());
        m_pCitizenView->Create("Lego Citizen View", 0, m_pViewLODListManager,
                               GetDocument()->GetTown()->GetRenderer(),
                               FALSE, 320, 200, m_bitsPerPixel,
                               m_paletteEntry, m_paletteEntryCount);
        m_pCurrentView = m_pCitizenView;
        m_pCurrentView->SetRenderWhenNotActive(
                            (int) AfxGetApp()->GetProfileInt("Preferences",
                                                             "RenderWhenNotActive",
                                                             1));
    }
}

void CLegoView::OnViewEditor() 
{
    if (!m_pCurrentView || (m_pCurrentView != m_pEditorView))
    {
        DestroyCurrentView();

        m_pEditorView = new MxLegoEditorView(GetDocument()->GetTown()->GetScene());
        m_pEditorView->Create("Lego Editor View", 0,
                              GetDocument()->GetTown()->GetRenderer(),
                              FALSE, 320, 200, m_bitsPerPixel,
                              m_paletteEntry, m_paletteEntryCount);
        m_pCurrentView = m_pEditorView;
        m_pCurrentView->SetRenderWhenNotActive(
                            (int) AfxGetApp()->GetProfileInt("Preferences",
                                                             "RenderWhenNotActive",
                                                             1));
    }
}

void CLegoView::OnViewRenderwhennotactive() 
{
    m_pCurrentView->SetRenderWhenNotActive(!m_pCurrentView->RenderWhenNotActive());
}

void CLegoView::OnUpdateViewCitizen(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_pCurrentView && (m_pCurrentView == m_pCitizenView));
}

void CLegoView::OnUpdateViewEditor(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_pCurrentView && (m_pCurrentView == m_pEditorView));
}

void CLegoView::OnUpdateViewRenderwhennotactive(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(m_pCurrentView != 0);
    pCmdUI->SetCheck(m_pCurrentView && m_pCurrentView->RenderWhenNotActive());
}

///////////////////////////////////////////////////////////////////////////





