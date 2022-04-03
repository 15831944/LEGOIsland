// MeshCostDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MeshCost.h"
#include "MeshCostDlg.h"
#include "LegoROI.h"
#include "ProgressDlg.h"
#include "Lego3DView.h"         // LegoView1
#include "LegoViewWnd.h"
#include "MxDirectDraw.h"
#include "Version.h"

#include "ViewManager.h"    // ViewLODListManager

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMeshCostDlg dialog

CMeshCostDlg::CMeshCostDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMeshCostDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMeshCostDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_pROIs                 = 0;
    m_trees                 = 0;
    m_roiCount              = 0;
    m_pProgressDlg          = 0;
    m_pCalculationThread    = 0;
    m_pLegoView             = 0;
    m_pLegoViewWnd          = 0;

    m_pRenderer             = 0;
    m_pViewLodListManager   = 0;
}

BOOL CMeshCostDlg::DestroyWindow() 
{
    int i;

	if (m_pCalculationThread)
	{
		SetEvent(m_costCalculation.KillThreadEvent());
		WaitForSingleObject(m_costCalculation.ThreadKilledEvent(),
                            INFINITE);
	}

    for (i = 0; i < m_roiCount; i++)
    {
        delete m_pROIs[i];
        m_pROIs[i] = 0;
    }
    delete [] m_pROIs;
    delete [] m_trees;
    m_pROIs                 = 0;
    m_trees                 = 0;
    m_roiCount              = 0;

    delete m_pViewLodListManager;
    m_pViewLodListManager = 0;

    if (m_pProgressDlg)
    {
        m_pProgressDlg->DestroyWindow();
        delete m_pProgressDlg;
	    m_pProgressDlg = 0;
    }

    if (m_pLegoViewWnd)
    {
        m_pLegoViewWnd->DestroyWindow();
        delete m_pLegoViewWnd;
	    m_pLegoViewWnd = 0;
    }

    if (m_pLegoView)
    {
        m_pLegoView->Destroy();
        delete m_pLegoView;
	    m_pLegoView = 0;
    }

    delete m_pRenderer;
    m_pRenderer = 0;

	return CDialog::DestroyWindow();
}

void CMeshCostDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMeshCostDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMeshCostDlg, CDialog)
	//{{AFX_MSG_MAP(CMeshCostDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD_MODEL, OnLoadModel)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_CALCULATE_COST, OnCalculateCost)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_USER_CALCULATION_DONE, OnCalculationDone)
	ON_MESSAGE(WM_USER_CALCULATION_IN_PROGRESS, OnCalculationInProgress)
	ON_MESSAGE(WM_USER_CALCULATION_PAUSE, OnCalculationPause)
	ON_MESSAGE(WM_USER_CALCULATION_CONTINUE, OnCalculationContinue)
	ON_MESSAGE(WM_USER_CALCULATION_CANCEL, OnCalculationCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMeshCostDlg message handlers


BOOL CMeshCostDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	if (!m_pRenderer)
    {
        m_pRenderer = Tgl::CreateRenderer();
        ASSERT(m_pRenderer);
    }

	if (!m_pViewLodListManager)
    {
        m_pViewLodListManager = new ViewLODListManager;
    }

    if (!m_pLegoViewWnd)
    {
        int             bitsPerPixel;
        PALETTEENTRY    paletteEntry[256];
        int             paletteEntryCount;
        BOOL            result;

        if (!GetResourceBitmapPaletteEntries(MAKEINTRESOURCE(IDB_PALETTE),
                                             sizeof(paletteEntry) / sizeof(paletteEntry[0]),
                                             paletteEntry,
                                             paletteEntryCount))
        {
            return -1;
        }

        {
            CClientDC   dc(this);

            bitsPerPixel = dc.GetDeviceCaps(PLANES) * dc.GetDeviceCaps(BITSPIXEL);
        }

        m_pLegoViewWnd = new LegoViewWnd;
        result = m_pLegoViewWnd->Create("Mesh Cost Calculation", 0,
                                        FALSE, 600, 600, bitsPerPixel,
                                        paletteEntry, paletteEntryCount);
        ASSERT(result);
        m_pLegoViewWnd->ShowWindow(FALSE);
        m_pLegoViewWnd->SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), FALSE);
        m_pLegoViewWnd->SetIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME), TRUE);
    }

    // Foobar(m_pLegoViewWnd->Direct3D());

    if (!m_pLegoView)
    {
        LegoView1::CreateStruct createStruct;
        BOOL                    result;

        m_pLegoView = new LegoView1;

        createStruct.m_pDriverGUID  = 0;
        createStruct.m_hWnd         = m_pLegoViewWnd->GetSafeHwnd();
        createStruct.m_pDirectDraw  = m_pLegoViewWnd->DirectDraw()->DirectDraw();
        createStruct.m_pFrontBuffer = m_pLegoViewWnd->DirectDraw()->FrontBuffer();
        createStruct.m_pBackBuffer  = m_pLegoViewWnd->DirectDraw()->BackBuffer();
        createStruct.m_pPalette     = m_pLegoViewWnd->DirectDraw()->Palette();
        createStruct.m_isFullScreen = FALSE;

        result = m_pLegoView->Create(createStruct, m_pRenderer);
        ASSERT(result);

        // let LegoViewWnd handle rendering
        m_pLegoViewWnd->SetLegoView(m_pLegoView);
    }

    if (!m_pProgressDlg)
    {
        m_pProgressDlg = new CProgressDlg(this);
    }

    // move dialog and progress dialog off LegoView window
    CRect    dialogWindowRect;
    CRect    progressDialogWindowRect;
    CRect    legoViewWindowRect;

    GetWindowRect(dialogWindowRect);
    m_pProgressDlg->GetWindowRect(progressDialogWindowRect);
    m_pLegoViewWnd->GetWindowRect(legoViewWindowRect);

    MoveWindow(legoViewWindowRect.right, dialogWindowRect.top,
               dialogWindowRect.Width(), dialogWindowRect.Height(), FALSE);
    m_pProgressDlg->MoveWindow(legoViewWindowRect.right, 
                               dialogWindowRect.bottom,
                               progressDialogWindowRect.Width(),
                               progressDialogWindowRect.Height(), FALSE);

    return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMeshCostDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMeshCostDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMeshCostDlg::OnLoadModel() 
{
    if (!m_pCalculationThread)
    {
	    CFileDialog	dlg(TRUE,
					    0,
					    0,
					    OFN_HIDEREADONLY,
					    "Lego Model Files (*.mod)|*.mod|All Files (*.*)|*.*||",
					    this);

	    dlg.m_ofn.lpstrTitle	= "Load Lego Model";

        if (dlg.DoModal() == IDOK)
        {
            LegoFile        file;
            LegoResult      result;

            // clean up after previous
            for (int i = 0; i < m_roiCount; i++)
            {
                delete m_pROIs[i];
                m_pROIs[i] = 0;
            }
            delete [] m_pROIs;
            delete [] m_trees;
            m_pROIs     = 0;
            m_trees     = 0;
            m_roiCount  = 0;

            m_pathName = dlg.GetPathName();

            BeginWaitCursor();
            result = file.Open(m_pathName, LegoFile::c_read);
            if (result == SUCCESS)
            {
                LegoU32 version;

                result = file.Read(&version, sizeof(version));
                if (result == SUCCESS)
                {
                    if (version == MODEL_VERSION)
                    {
                        result = file.Read(&m_roiCount, sizeof(m_roiCount));
                        if (result == SUCCESS)
                        {
                            int i;

                            m_pROIs = new LegoROI* [m_roiCount];
                            // ??? one tree per roi ???
                            m_trees = new LegoAnim[m_roiCount];

                            for (i = 0; i < m_roiCount; i++)
                            {
	                            if (result == SUCCESS)
                                {
            	                    result = m_trees[i].Read(&file);
                                }
	                            if (result == SUCCESS)
                                {
                                    m_pROIs[i] = new LegoROI(m_pLegoView->GetRenderer());
        	                        result = m_pROIs[i]->Read(m_pLegoView->GetRenderer(),
                                                              m_pViewLodListManager,
                                                              &file,
                                                              TRUE);
                                }
                                if (result == SUCCESS)
                                {
        	                        result = m_pROIs[i]->SetFrame(&m_trees[i], 0);
                                }
                            }
                        }
                    }
                    else
                    {
                        CString msg;

                        msg.Format("Version mismatch: File created by converter version %ld expected\n%s was created by converter version %ld",
                                    (long) MODEL_VERSION, (const char*) m_pathName, (long) version);

                        AfxMessageBox(msg);
                        result = FAILURE;
                    }
                }
        	    file.Close();
            }
            EndWaitCursor();

            if (result != SUCCESS)
            {
                for (int i = 0; i < m_roiCount; i++)
                {
                    delete m_pROIs[i];
                    m_pROIs[i] = 0;
                }

                delete [] m_pROIs;
                delete [] m_trees;
                m_pROIs     = 0;
                m_trees     = 0;
                m_roiCount  = 0;

                AfxMessageBox("Failed to load");
            }
        }	
    }
}

void CMeshCostDlg::OnCalculateCost() 
{
    if (m_pROIs && !m_pCalculationThread)
	{
        m_pProgressDlg->ProgressCtrl().SetRange(0, LODCount(m_pROIs, m_roiCount));
        m_pProgressDlg->ProgressCtrl().SetStep(1);
        m_pProgressDlg->ProgressCtrl().SetPos(0);
        m_pProgressDlg->SetNotification(this,
                                        WM_USER_CALCULATION_PAUSE,
                                        WM_USER_CALCULATION_CONTINUE,
                                        WM_USER_CALCULATION_CANCEL);

        m_pLegoViewWnd->ShowWindow(TRUE);
        m_pProgressDlg->ShowWindow(TRUE);

        m_pCalculationThread = m_costCalculation.CalculateCostInThread(m_pLegoViewWnd,
                                                                       m_pLegoView,
                                                                       m_pROIs,
                                                                       m_roiCount,
                                                                       m_hWnd,
                                                                       WM_USER_CALCULATION_DONE,
                                                                       WM_USER_CALCULATION_IN_PROGRESS);
    }
}

void CMeshCostDlg::OnSave() 
{
    if (m_pROIs && !m_pCalculationThread && m_costCalculation.Succeeded())
    {
        LegoFile        file;
        LegoResult      result;

        BeginWaitCursor();
        result = file.Open(m_pathName, LegoFile::c_write);
        if (result == SUCCESS)
        {
            LegoU32 version = MODEL_VERSION;

            result = file.Write(&version, sizeof(version));
            if (result == SUCCESS)
            {
                result = file.Write(&m_roiCount, sizeof(m_roiCount));
            }

            for (int i = 0; i < m_roiCount; i++)
            {
                if (result == SUCCESS)
                {
        	        result = m_trees[i].Write(&file);
                }
	            if (result == SUCCESS)
                {
        	        result = m_pROIs[i]->Write(&file);
                }
            }
        	file.Close();
        }
        EndWaitCursor();

        if (result != SUCCESS)
        {
            AfxMessageBox("Failed to save");
        }
    }
}

int CMeshCostDlg::LODCount(LegoROI** pROIs, int roiCount)
{
    int i;
    int lodCount = 0;

    for (i = 0; i < roiCount; i++)
    {
        lodCount += LODCount(pROIs[i]);
    }

    return lodCount;
}

int CMeshCostDlg::LODCount(const ROI* pROI)
{
    int lodCount = 0;

    if (pROI)
    {
	    const CompoundObject*   pCompoundObject = pROI->GetComp();
    
        lodCount = pROI->GetLODCount();
        
        if (pCompoundObject)
        {
            CompoundObject::const_iterator  iterator = pCompoundObject->begin();

            while (!(iterator == pCompoundObject->end()))
            {
                lodCount += LODCount(*iterator);
                ++iterator;
            }
        }
    }

    return lodCount;
}

LRESULT CMeshCostDlg::OnCalculationInProgress(WPARAM wParam, LPARAM lParam)
{
    LegoROI*    pROI = reinterpret_cast<LegoROI*>(lParam);
    int         i = (int) wParam;
    CString     message;

    message.Format("ROI: %s, LOD#: %d",
                   (const char*) pROI ? pROI->GetName() : "?", i);

    TRACE("Processing %s...\n", (const char*) message);

    if (m_pProgressDlg)
    {
        m_pProgressDlg->ProgressCtrl().StepIt();
	    //m_pProgressDlg->UpdateWindow();
        m_pProgressDlg->SetWindowText(message);
    }


	return 0;
}

LRESULT CMeshCostDlg::OnCalculationDone(WPARAM, LPARAM)
{
	m_pCalculationThread = 0;
    m_pProgressDlg->ShowWindow(FALSE);
    m_pLegoViewWnd->ShowWindow(FALSE);

	return 0;
}

LRESULT CMeshCostDlg::OnCalculationPause(WPARAM, LPARAM)
{
	SetEvent(m_costCalculation.PauseThreadEvent());
	return 0;
}

LRESULT CMeshCostDlg::OnCalculationContinue(WPARAM, LPARAM)
{
	SetEvent(m_costCalculation.ContinueThreadEvent());
	return 0;
}

LRESULT CMeshCostDlg::OnCalculationCancel(WPARAM, LPARAM)
{
	SetEvent(m_costCalculation.KillThreadEvent());
	WaitForSingleObject(m_costCalculation.ThreadKilledEvent(), INFINITE);

	m_pCalculationThread = 0;
    m_pProgressDlg->ShowWindow(FALSE);
    m_pLegoViewWnd->ShowWindow(FALSE);
	return 0;
}

