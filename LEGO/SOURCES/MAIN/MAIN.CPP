/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdMain.h"
#include <afxdlgs.h>
#include <stdio.h>
#include "main.h"
#include "LegoOmni.h"
#include "LegoNotify.h"
#include "LegoVideoManager.h"
#include "LegoInputManager.h"
#include "Lego3DManager.h"
#include "Lego3DView.h"
#include "RealismDlg.h"
#include "RVWeightsDlg.h"
#include "TimeAverage.h"
#include "MxVariableTable.h"
#include "LegoGameState.h"
#include "NavDlg.h"
#include "resource.h"

#define TICKLE_INTERVAL		10		// call TickleManager every 10 msecs.
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480

#define VIDEO_HEADROOM 0.25			// 25 percent

CMain* g_main;
static CMainApp main;

CMain::CMain()
{
	::SetOmniUserMessage(LegoUserMessage);
    m_running = FALSE;
    m_positioned = FALSE;
    m_tickleInterval = TICKLE_INTERVAL;
	m_pRealtimeViewWeightsDlg = NULL;
	m_pRealismDlg = NULL;
    m_pNavigationDlg = NULL;
    m_timeAverage = NULL;
    m_gameState = NULL;
	m_videoOverhead = 0;
	m_videoParam = MxVideoParam(MxRect32(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT));
    m_window = (CMainWindow*) main.m_pMainWnd;
    LegoOmni::CreateInstance();
    LegoOmni::GetInstance()->Create(MxOmniCreateParam("", m_window->GetSafeHwnd(), m_videoParam, MxOmniCreateFlags()));
    ResetVideo(m_videoParam);
	m_timeAverage = new TimeAverage(TRUE);
	m_gameState = new LegoGameState();
	MeasureVideoOverhead();
	UpdateFrameTime();
}

CMain::~CMain()
{
	delete m_gameState;
	delete m_timeAverage;
	delete m_pNavigationDlg;
    delete m_pRealismDlg;
    delete m_pRealtimeViewWeightsDlg;
    LegoOmni::GetInstance()->Destroy();
    LegoOmni::DestroyInstance();
    delete m_videoParam.GetPalette();
    POSITION pos;
    for (pos = m_startList.GetHeadPosition(); pos; m_startList.GetNext(pos)) {
        delete m_startList.GetAt(pos);
    }
    for (pos = m_sourceList.GetHeadPosition(); pos; m_sourceList.GetNext(pos)) {
        delete m_sourceList.GetAt(pos);
    }
}

void
CMain::ResetVideo(MxVideoParam& p_videoParam)
{
    LegoOmni::GetInstance()->GetVideoManager()->Destroy();
    m_window->Resize(
        p_videoParam.GetRect().GetWidth(), 
        p_videoParam.GetRect().GetHeight(), 
        !
        (
            p_videoParam.GetFullScreen() 
            || 
            (
                p_videoParam.GetRect().GetWidth() == GetSystemMetrics(SM_CXSCREEN)
                &&
                p_videoParam.GetRect().GetHeight() == GetSystemMetrics(SM_CYSCREEN)
            )
        )
    );
    LegoOmni::GetInstance()->GetVideoManager()->Create(p_videoParam);
}

void
CMain::UpdateFrameTime()
{
	if (LegoOmni::GetInstance()->GetVideoManager())
	{
		int renderTime = ((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->
					Get3DManager()->GetLego3DView()->GetViewManager()->GetSecondsAllowed() * 1000;

		int frameTime = renderTime * (1 + VIDEO_HEADROOM) + m_videoOverhead;

		LegoOmni::GetInstance()->GetTickleManager()->SetClientTickleInterval(
								LegoOmni::GetInstance()->GetVideoManager(), frameTime);
	}
}

void
CMain::MeasureVideoOverhead()
{
	int i;
	const int numSamples = 10;

	if (LegoOmni::GetInstance()->GetVideoManager())
	{
		// let video cycle run to stabilize
		for (i=0; i<10; i++)
		{
			LegoOmni::GetInstance()->GetVideoManager()->Tickle();
		}

		// time a few cycles
		MxTime startTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
		for (i=0; i<numSamples; i++)
		{
			LegoOmni::GetInstance()->GetVideoManager()->Tickle();
		}
 		MxTime endTime = LegoOmni::GetInstance()->GetTimer()->GetTime();

		m_videoOverhead = (endTime - startTime)/numSamples;
	}
}


void 
CMain::Tickle(BOOL p_yieldOK)
{
	static MxTime lastTickleTime = 0;

    if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetTickleManager() && LegoOmni::GetInstance()->GetTimer()) {
		MxTime currentTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
		if (lastTickleTime > currentTime)
			lastTickleTime = -g_main->GetTickleInterval();

        if (currentTime > lastTickleTime + g_main->GetTickleInterval())
		{
			LegoOmni::GetInstance()->GetTickleManager()->Tickle();
            lastTickleTime = currentTime;
		}
		else if (p_yieldOK)
			Sleep(0);
	}
}

CMainWindow::CMainWindow()
{
	Create(NULL, "Main", 0, rectDefault, NULL, NULL);
}

CMainWindow::~CMainWindow()
{
}

void 
CMainWindow::Resize(int p_width, int p_height, BOOL p_titleBar)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    long style;
    long exStyle;
    if (p_titleBar) {
        style = WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME | WS_VISIBLE;
        exStyle = WS_EX_CLIENTEDGE | WS_EX_WINDOWEDGE;
    }
    else {
        style = WS_VISIBLE;
        exStyle = 0;
    }
    SetWindowLong(GetSafeHwnd(), GWL_STYLE, style);
    SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, exStyle);
    UpdateWindow();
    style = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
    exStyle = GetWindowLong(GetSafeHwnd(), GWL_EXSTYLE);
    CRect windowRect;
    GetWindowRect(windowRect);
    CRect clientRect;
    GetClientRect(clientRect);
    SetWindowPos(
        p_titleBar ? &wndNoTopMost : &wndTopMost, 
        (screenWidth - p_width) / 2, 
        (screenHeight - p_height) / 2, 
        p_width + windowRect.Width() - clientRect.Width(), 
        p_height + windowRect.Height() - clientRect.Height(), 
        0
    );
}

LRESULT
CMainWindow::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	MxS16 type;
	MxU8 key = 0;
	switch(message)
	{
		case WM_LBUTTONUP:
			type = c_notificationButtonUp;
			break;
		case WM_LBUTTONDOWN:
			type = c_notificationButtonDown;
			break;
		case WM_MOUSEMOVE:
			type = c_notificationMouseMove;
			break;
		case WM_KEYDOWN:
			type = c_notificationKeyPress;
			key = wParam;
            if (wParam == VK_ESCAPE) {
                if (g_main->GetRunning()) {
                    OnStop();
                }
            }
			break;
		case WM_TIMER:
			type = c_notificationTimer;
			break;
		default:
			return CWnd::WindowProc(message, wParam, lParam);
	}

	CRealismDlg::StartEventTrace(type);
    
    if (LegoOmni::GetInstance()->GetInputManager())
		LegoOmni::GetInstance()->GetInputManager()->QueueEvent(type, wParam, LOWORD(lParam), HIWORD(lParam), key);
	
    CRealismDlg::EndEventTrace(type);

    return 0;
}

void 
CMainWindow::OnOpenOnDisk()
{
    Open(OC_DISK_STREAMING);
}

void 
CMainWindow::OnOpenInRam()
{
    Open(OC_MEMORY_STREAMING);
}

void 
CMainWindow::OnOpenPaletteFile()
{
    CFileDialog dlg(
        TRUE, "BMP", "*.BMP", 
        OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST,
        "Bitmap Files  (*.bmp)|*.BMP||", NULL
    );
    if (dlg.DoModal() == IDOK) {
		MxBitmap bitmap;
        if (bitmap.Read(dlg.GetPathName()) == SUCCESS) {
    		if (g_main->GetVideoParam().GetPalette()) {
    			delete g_main->GetVideoParam().GetPalette();
    		}
			g_main->GetVideoParam().SetPalette(bitmap.CreatePalette());
			if (LegoOmni::GetInstance()->GetVideoManager()) {
				LegoOmni::GetInstance()->GetVideoManager()->RealizePalette(g_main->GetVideoParam().GetPalette());
			}
        }
        else {
            MessageBox("Unable to open palette file");
        }
    }
}

void 
CMainWindow::OnExit()
{
    DestroyWindow();
}

void 
CMainWindow::OnStart()
{
    g_main->ResetVideo(g_main->GetVideoParam());
    for (
        POSITION pos = g_main->GetStartList().GetHeadPosition();
        pos;
        g_main->GetStartList().GetNext(pos)
    ) {
        CStartListElement* element = g_main->GetStartList().GetAt(pos);
        CString sourceName(element->GetSourceName());
        int i = sourceName.ReverseFind('.');
        int n = i == -1 ? sourceName.GetLength() : i;
        if (LegoOmni::GetInstance()->Start(CString(sourceName, n), element->GetActionName()) != SUCCESS) {
            MessageBox("LegoOmni:Start() failed");
            return;
        }
        g_main->SetRunning(TRUE);
        g_main->SetPositioned(FALSE);
    }
}

void 
CMainWindow::OnStop()
{
    LegoOmni::GetInstance()->Stop();
    while (!LegoOmni::GetInstance()->IsStoped()) {
        g_main->Tickle(TRUE);
    }
    g_main->ResetVideo(MxVideoParam(MxRect32(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT)));
    g_main->SetRunning(FALSE);
}

void 
CMainWindow::Open(UINT p_openMode)
{
    CFileDialog dlg(
        TRUE, "SI", "*.SI", 
        OFN_HIDEREADONLY | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST,
        "Interleaf Files  (*.si)|*.SI||", NULL
    );
    if (dlg.DoModal() == IDOK) {
        CString fileName = dlg.GetPathName();
        int i = fileName.ReverseFind('.');
        int n = i == -1 ? fileName.GetLength() : i;

        MxStreamController *controller = LegoOmni::GetInstance()->GetStreamer()->Open(CString(fileName, n), p_openMode);
        if(!controller)
        {
            MessageBox("MxStreamer::Open() failed");
            return;
        }
        g_main->GetSourceList().AddTail(new CSourceListElement(fileName, p_openMode));
    }
}

CGetVariableDialog::CGetVariableDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_GETVARIABLE, p_parent) 
{
}

BOOL 
CGetVariableDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}

void 
CGetVariableDialog::OnOK()
{
    GetDlgItem(IDC_NAME)->GetWindowText(m_name);
    CDialog::OnOK();
}

CSetVariableDialog::CSetVariableDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_SETVARIABLE, p_parent) 
{
}

BOOL 
CSetVariableDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}

void 
CSetVariableDialog::OnOK()
{
    GetDlgItem(IDC_NAME)->GetWindowText(m_name);
    GetDlgItem(IDC_VALUE)->GetWindowText(m_value);
    CDialog::OnOK();
}

CSetSoundVolumeDialog::CSetSoundVolumeDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_SETSOUNDVOLUME, p_parent) 
{
}

BOOL 
CSetSoundVolumeDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}

void 
CSetSoundVolumeDialog::OnOK()
{
    m_soundVolume = GetDlgItemInt(IDC_SOUNDVOLUME);
    CDialog::OnOK();
}

CSetMusicVolumeDialog::CSetMusicVolumeDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_SETMUSICVOLUME, p_parent) 
{
}

BOOL 
CSetMusicVolumeDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}

void 
CSetMusicVolumeDialog::OnOK()
{
    m_musicVolume = GetDlgItemInt(IDC_MUSICVOLUME);
    CDialog::OnOK();
}

CActionsDialog::CActionsDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_ACTIONS, p_parent) 
{
}

BOOL 
CActionsDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
    POSITION pos;
    int i;
    CComboBox* sources = (CComboBox*) GetDlgItem(IDC_SOURCES);
    for (
        pos = g_main->GetSourceList().GetHeadPosition();
        pos;
        g_main->GetSourceList().GetNext(pos)
    ) {
        sources->AddString(g_main->GetSourceList().GetAt(pos)->GetSource());
    }
    sources->SetCurSel(0);
    OnSelChange();

    CListCtrl* start = (CListCtrl*) GetDlgItem(IDC_START);
    start->InsertColumn(0, "Source");
    start->SetColumnWidth(0, 150);
    start->InsertColumn(1, "Action");
    start->SetColumnWidth(1, 100);
    for (
        pos = g_main->GetStartList().GetHeadPosition(), i = 0;
        pos;
        g_main->GetStartList().GetNext(pos), i++
    ) {
        CStartListElement* element = g_main->GetStartList().GetAt(pos);
        start->InsertItem(i, element->GetSourceName());
        start->SetItem(i, 1, LVIF_TEXT, element->GetActionName(), 0, 0, 0, NULL);
    }
    start->SetItemState(0, LVIS_SELECTED, LVIS_SELECTED);

    UpdateControls();

    return TRUE;
}

void 
CActionsDialog::OnOK()
{
    CDialog::OnOK();
    CListCtrl* start = (CListCtrl*) GetDlgItem(IDC_START);
    LV_ITEM itemInfo;
    char text[256];
    memset(&itemInfo, 0, sizeof(itemInfo));
    itemInfo.mask = LVIF_TEXT;
    itemInfo.pszText = text;
    itemInfo.cchTextMax = sizeof(text);
    for (int i = 0; i < start->GetItemCount(); i++) {
        itemInfo.iItem = i;
        itemInfo.iSubItem = 0;
        start->GetItem(&itemInfo);
        CString source = text;
        itemInfo.iSubItem = 1;
        start->GetItem(&itemInfo);
        CString action = text;
        CStartListElement* element = new CStartListElement(source, action);
        m_startList.AddTail(element);
    }

}

void 
CActionsDialog::UpdateControls()
{
    CListBox* actions = (CListBox*) GetDlgItem(IDC_ACTIONS);
    GetDlgItem(IDC_ADD)->EnableWindow(actions->GetCurSel() != -1);
    CListCtrl* start = (CListCtrl*) GetDlgItem(IDC_START);
    GetDlgItem(IDC_DELETE)->EnableWindow(start->GetNextItem(-1, LVNI_SELECTED) != -1);
    GetDlgItem(IDC_PROPERTIES)->EnableWindow(start->GetNextItem(-1, LVNI_SELECTED) != -1);
}

void
CActionsDialog::OnSelChange()
{
    CComboBox* sources = (CComboBox*) GetDlgItem(IDC_SOURCES);
    CString source;
    sources->GetLBText(sources->GetCurSel(), source);
    int i = source.ReverseFind('.');
    int n = i == -1 ? source.GetLength() : i;
    MxStreamController* controller = LegoOmni::GetInstance()->GetStreamer()->GetController((char*) (const char*) CString(source, n));
    CListBox* actions = (CListBox*) GetDlgItem(IDC_ACTIONS);
    actions->ResetContent();
    for (i = 0; i < controller->GetNumberOfMedias(); i++) {
        MxDSMedia* media = controller->GetMedia(i);
        if (media->GetLevel() == 0) {
            actions->AddString(media->GetMediaObjectName());
        }
    }
    actions->SetCurSel(0);
}

void
CActionsDialog::OnAdd()
{
    CComboBox* sources = (CComboBox*) GetDlgItem(IDC_SOURCES);
    CString source;
    sources->GetLBText(sources->GetCurSel(), source);
    CListBox* actions = (CListBox*) GetDlgItem(IDC_ACTIONS);
    CString action;
    actions->GetText(actions->GetCurSel(), action);
    CListCtrl* start = (CListCtrl*) GetDlgItem(IDC_START);
    int i = start->GetItemCount();
    start->InsertItem(i, source);
    start->SetItem(i, 1, LVIF_TEXT, action, 0, 0, 0, NULL);
    start->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    UpdateControls();
}

void
CActionsDialog::OnDelete()
{
    CListCtrl* start = (CListCtrl*) GetDlgItem(IDC_START);
    int i = start->GetNextItem(-1, LVNI_SELECTED);
    start->DeleteItem(i);
    if (i == start->GetItemCount()) {
        i--;
    }
    start->SetItemState(i, LVIS_SELECTED, LVIS_SELECTED);
    UpdateControls();
}

void
CActionsDialog::OnProperties()
{
    CListCtrl* start = (CListCtrl*) GetDlgItem(IDC_START);
    int i = start->GetNextItem(-1, LVNI_SELECTED);

    if(i == -1)
        return;

    CString title;
    LV_ITEM itemInfo;
    char text[256];
    memset(&itemInfo, 0, sizeof(itemInfo));
    itemInfo.mask = LVIF_TEXT;
    itemInfo.pszText = text;
    itemInfo.cchTextMax = sizeof(text);
    itemInfo.iItem = i;
    itemInfo.iSubItem = 0;
    start->GetItem(&itemInfo);
    title = text; // source name
    itemInfo.iSubItem = 1;
    start->GetItem(&itemInfo);
    title += " / ";
    title += text; // action name
    title += " properties";

    CPropertySheet propertySheet(title, this);
    CGeneralActionProperties generalProperties;
    CTimeActionProperties timeProperties;
    CLocationActionProperties locationProperties;

    propertySheet.AddPage(&generalProperties);
    propertySheet.AddPage(&timeProperties);
    propertySheet.AddPage(&locationProperties);
    if(propertySheet.DoModal() == IDOK)
    {
        ;
    }

    UpdateControls();
}

BEGIN_MESSAGE_MAP(CActionsDialog, CDialog)
    ON_COMMAND(IDC_ADD, OnAdd)
    ON_COMMAND(IDC_DELETE, OnDelete)
    ON_COMMAND(IDC_PROPERTIES, OnProperties)
    ON_CBN_SELCHANGE(IDC_SOURCES, OnSelChange)
END_MESSAGE_MAP()


//===========================================================================
// CGeneralActionProperties

CGeneralActionProperties::CGeneralActionProperties() 
    : CPropertyPage(IDD_ACTION_PROPERTIES_GENERAL, IDS_ACTION_PROPERTIES_GENERAL)
{
    m_residentTime = MxNAN_TIME;
    m_preloadResident = FALSE;
}

BOOL 
CGeneralActionProperties::OnInitDialog()
{
    CDialog::OnInitDialog();
    
    UpdateControls();

    return TRUE;
}

void 
CGeneralActionProperties::UpdateControls()
{
    ((CButton*)GetDlgItem(IDC_PRELOAD_RESIDENT))->SetCheck(m_preloadResident ? 1 : 0);
    GetDlgItem(IDC_PRELOAD_TIME)->EnableWindow(m_preloadResident);

    if(m_residentTime != MxNAN_TIME)
        SetDlgItemInt(IDC_PRELOAD_TIME, m_residentTime, FALSE);
    else
        GetDlgItem(IDC_PRELOAD_TIME)->SetWindowText("MxNAN_TIME");
}

void 
CGeneralActionProperties::OnPreloadResident()
{
    BOOL trans = FALSE;

    m_residentTime = GetDlgItemInt(IDC_PRELOAD_TIME, &trans, FALSE);

    if(!trans)
        m_residentTime = MxNAN_TIME;

    m_preloadResident = m_preloadResident ? FALSE : TRUE;

    UpdateControls();
}

BEGIN_MESSAGE_MAP(CGeneralActionProperties, CPropertyPage)
    ON_COMMAND(IDC_PRELOAD_RESIDENT, OnPreloadResident)
END_MESSAGE_MAP()


//===========================================================================
// CTimeActionProperties

CTimeActionProperties::CTimeActionProperties() 
                        : CPropertyPage(IDD_ACTION_PROPERTIES_TIME, IDS_ACTION_PROPERTIES_TIME)
{
    m_startTime = MxNAN_TIME;
    m_duration = MxNAN_TIME;
    m_loopCount = 1;
    m_useDuration = FALSE;
}

BOOL 
CTimeActionProperties::OnInitDialog()
{
    CDialog::OnInitDialog();
    UpdateControls();
    return TRUE;
}

void 
CTimeActionProperties::UpdateControls()
{
    if(m_startTime != MxNAN_TIME)
        SetDlgItemInt(IDC_START_TIME, m_startTime, FALSE);
    else
        GetDlgItem(IDC_START_TIME)->SetWindowText("MxNAN_TIME");

    if(m_useDuration)
    {
        ((CButton*)GetDlgItem(IDC_LOOPING))->SetCheck(0);
        GetDlgItem(IDC_LOOPING_TIMES)->EnableWindow(FALSE);
        ((CButton*)GetDlgItem(IDC_DURATION))->SetCheck(1);
        GetDlgItem(IDC_DURATION_VALUE)->EnableWindow(TRUE);
    }
    else
    {
        ((CButton*)GetDlgItem(IDC_LOOPING))->SetCheck(1);
        GetDlgItem(IDC_LOOPING_TIMES)->EnableWindow(TRUE);
        ((CButton*)GetDlgItem(IDC_DURATION))->SetCheck(0);
        GetDlgItem(IDC_DURATION_VALUE)->EnableWindow(FALSE);
    }

    if(m_duration != MxNAN_TIME)
        SetDlgItemInt(IDC_DURATION_VALUE, m_duration, FALSE);
    else
        GetDlgItem(IDC_DURATION_VALUE)->SetWindowText("MxNAN_TIME");

    SetDlgItemInt(IDC_LOOPING_TIMES, m_loopCount, FALSE);

}

void 
CTimeActionProperties::OnLooping()
{
    BOOL trans = FALSE;
    m_useDuration = FALSE;

    m_duration = GetDlgItemInt(IDC_DURATION_VALUE, &trans, FALSE);
    if(!trans)
        m_duration = MxNAN_TIME;

    m_startTime = GetDlgItemInt(IDC_START_TIME, &trans, FALSE);
    if(!trans)
        m_startTime = MxNAN_TIME;

    UpdateControls();
}

void 
CTimeActionProperties::OnDuration()
{
    BOOL trans = FALSE;
    m_useDuration = TRUE;

    m_loopCount = GetDlgItemInt(IDC_LOOPING_TIMES, &trans, FALSE);
    if(!trans)
        m_loopCount = 1;

    m_startTime = GetDlgItemInt(IDC_START_TIME, &trans, FALSE);
    if(!trans)
        m_startTime = MxNAN_TIME;

    UpdateControls();
}

BEGIN_MESSAGE_MAP(CTimeActionProperties, CPropertyPage)
    ON_COMMAND(IDC_LOOPING, OnLooping)
    ON_COMMAND(IDC_DURATION, OnDuration)
END_MESSAGE_MAP()


//===========================================================================
// CLocationActionProperties

CLocationActionProperties::CLocationActionProperties() 
                        : CPropertyPage(IDD_ACTION_PROPERTIES_LOCATION, IDS_ACTION_PROPERTIES_LOCATION)
{
	m_location.Fill(MxNAN_DBL);
	m_direction.Fill(MxNAN_DBL);
	m_up.Fill(MxNAN_DBL);
}

BOOL 
CLocationActionProperties::OnInitDialog()
{
    CDialog::OnInitDialog();
    return TRUE;
}

BEGIN_MESSAGE_MAP(CLocationActionProperties, CPropertyPage)
END_MESSAGE_MAP()


CVideoDialog::CVideoDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_VIDEO, p_parent) 
{
}

BOOL 
CVideoDialog::OnInitDialog()
{
    CDialog::OnInitDialog();

    if (g_main->GetVideoParam().GetRect().GetWidth() == 320 && g_main->GetVideoParam().GetRect().GetHeight() == 240) {
        CheckRadioButton(IDC_320x240, IDC_640x480, IDC_320x240);
    }
    else {
        CheckRadioButton(IDC_320x240, IDC_640x480, IDC_640x480);
    }
    if (g_main->GetVideoParam().GetNumBackBuffers() == 1) {
        CheckRadioButton(IDC_1, IDC_2, IDC_1);
    }
    else {
        CheckRadioButton(IDC_1, IDC_2, IDC_2);
    }
    CheckDlgButton(IDC_FULLSCREEN, g_main->GetVideoParam().GetFullScreen());
    CheckDlgButton(IDC_FLIPSURFACES, g_main->GetVideoParam().GetFlip());
    CheckDlgButton(IDC_BACKBUFFERSINVIDEOMEMORY, g_main->GetVideoParam().GetBackBuffersInVideoMemory());

    UpdateControls();

    return TRUE;
}

void 
CVideoDialog::OnFullScreen()
{
    UpdateControls();
}

void 
CVideoDialog::OnFlipSurfaces()
{
    UpdateControls();
}

void 
CVideoDialog::OnOK()
{
    CDialog::OnOK();

    if (IsDlgButtonChecked(IDC_320x240)) {
        m_videoParam.SetRect(MxRect32(0, 0, 320, 240));
    }
    else {
        m_videoParam.SetRect(MxRect32(0, 0, 640, 480));
    }
    if (IsDlgButtonChecked(IDC_1)) {
        m_videoParam.SetNumBackBuffers(1);
    }
    else {
        m_videoParam.SetNumBackBuffers(2);
    }
    m_videoParam.SetFullScreen(IsDlgButtonChecked(IDC_FULLSCREEN));
    m_videoParam.SetFlip(IsDlgButtonChecked(IDC_FLIPSURFACES));
    m_videoParam.SetBackBuffersInVideoMemory(IsDlgButtonChecked(IDC_BACKBUFFERSINVIDEOMEMORY));
}

void 
CVideoDialog::UpdateControls()
{
    GetDlgItem(IDC_FLIPSURFACES)->EnableWindow(IsDlgButtonChecked(IDC_FULLSCREEN));
    GetDlgItem(IDC_1)->EnableWindow(IsDlgButtonChecked(IDC_FLIPSURFACES));
    GetDlgItem(IDC_2)->EnableWindow(IsDlgButtonChecked(IDC_FLIPSURFACES));
    GetDlgItem(IDC_BACKBUFFERSINVIDEOMEMORY)->EnableWindow(!IsDlgButtonChecked(IDC_FLIPSURFACES));
}

BEGIN_MESSAGE_MAP(CVideoDialog, CDialog)
    ON_COMMAND(IDC_FULLSCREEN, OnFullScreen)
    ON_COMMAND(IDC_FLIPSURFACES, OnFlipSurfaces)
END_MESSAGE_MAP()


CTickleIntervalDialog::CTickleIntervalDialog(CWnd* p_parent) 
    : 
    CDialog(IDD_TICKLE_INTERVALS, p_parent) 
{
}

BOOL 
CTickleIntervalDialog::OnInitDialog()
{
    CDialog::OnInitDialog();
	m_tickleManager = LegoOmni::GetInstance()->GetTickleManager();
	m_videoManager = LegoOmni::GetInstance()->GetVideoManager();
	m_notifyManager = LegoOmni::GetInstance()->GetNotificationManager();
	m_soundManager = LegoOmni::GetInstance()->GetSoundManager();
	m_musicManager = LegoOmni::GetInstance()->GetMusicManager();
	m_eventManager = LegoOmni::GetInstance()->GetEventManager();
	OnRead();
    return TRUE;
}

void 
CTickleIntervalDialog::OnOK()
{
	MxTime time;

	g_main->SetTickleInterval(GetDlgItemInt(IDC_TICKLEMAN, NULL, FALSE));
	
	time = GetDlgItemInt(IDC_VIDEOMAN, NULL, FALSE);
	m_tickleManager->SetClientTickleInterval(m_videoManager, time);
	
	time = GetDlgItemInt(IDC_NOTIFYMAN, NULL, FALSE);
	m_tickleManager->SetClientTickleInterval(m_notifyManager, time);
	
	time = GetDlgItemInt(IDC_SOUNDMAN, NULL, FALSE);
	m_tickleManager->SetClientTickleInterval(m_soundManager, time);
	
	time = GetDlgItemInt(IDC_MUSICMAN, NULL, FALSE);
	m_tickleManager->SetClientTickleInterval(m_musicManager, time);
	
	time = GetDlgItemInt(IDC_EVENTMAN, NULL, FALSE);
	m_tickleManager->SetClientTickleInterval(m_eventManager, time);
	
    CDialog::OnOK();
}

void 
CTickleIntervalDialog::OnRead()
{
	UINT time;

	SetDlgItemInt(IDC_TICKLEMAN, g_main->GetTickleInterval(), FALSE);

	time = (UINT)m_tickleManager->GetClientTickleInterval(m_videoManager);
	SetDlgItemInt(IDC_VIDEOMAN, time, FALSE);

	time = (UINT)m_tickleManager->GetClientTickleInterval(m_notifyManager);
	SetDlgItemInt(IDC_NOTIFYMAN, time, FALSE);

	time = (UINT)m_tickleManager->GetClientTickleInterval(m_soundManager);
	SetDlgItemInt(IDC_SOUNDMAN, time, FALSE);

	time = (UINT)m_tickleManager->GetClientTickleInterval(m_musicManager);
	SetDlgItemInt(IDC_MUSICMAN, time, FALSE);

	time = (UINT)m_tickleManager->GetClientTickleInterval(m_eventManager);
	SetDlgItemInt(IDC_EVENTMAN, time, FALSE);

}

BEGIN_MESSAGE_MAP(CTickleIntervalDialog, CDialog)
	ON_COMMAND(IDC_READ_TICKLES, OnRead)
END_MESSAGE_MAP()


void 
CMainWindow::OnGetVariable()
{
    CGetVariableDialog dialog(this);
    if(dialog.DoModal() == IDOK) {
        const char* value = LegoOmni::GetInstance()->GetVariableTable()->GetVariable(dialog.GetName());
        char msg[128];
        if (*value) {
            sprintf(msg, "%s = %s", (const char*) dialog.GetName(), value);
        }
        else {
            sprintf(msg, "%s is undefined", (const char*) dialog.GetName());
        }
        MessageBox(msg, "Variable");
    }
}

void 
CMainWindow::OnSetVariable()
{
    CSetVariableDialog dialog(this);
    if(dialog.DoModal() == IDOK) {
        LegoOmni::GetInstance()->GetVariableTable()->SetVariable(dialog.GetName(), dialog.GetValue());
    }
}

void 
CMainWindow::OnSetSoundVolume()
{
    CSetSoundVolumeDialog dialog(this);
    if(dialog.DoModal() == IDOK) {
        LegoOmni::GetInstance()->GetSoundManager()->SetVolume(dialog.GetSoundVolume());
    }
}

void 
CMainWindow::OnSetMusicVolume()
{
    CSetMusicVolumeDialog dialog(this);
    if(dialog.DoModal() == IDOK) {
        LegoOmni::GetInstance()->GetMusicManager()->SetVolume(dialog.GetMusicVolume());
    }
}

void 
CMainWindow::OnActions()
{
    CActionsDialog dialog(this);
    if(dialog.DoModal() == IDOK) {
        for (
            POSITION pos = g_main->GetStartList().GetHeadPosition();
            pos;
            g_main->GetStartList().GetNext(pos)
        ) {
            delete g_main->GetStartList().GetAt(pos);
        }
        g_main->GetStartList().RemoveAll();
        g_main->GetStartList().AddTail(&dialog.GetStartList());
    }
}

void 
CMainWindow::OnVideo()
{
    CVideoDialog dialog(this);
    if(dialog.DoModal() == IDOK) {
        g_main->SetVideoParam(dialog.GetVideoParam());
    }
}

void 
CMainWindow::OnTickle()
{
    CTickleIntervalDialog dialog(this);
    dialog.DoModal();
}

void 
CMainWindow::OnInitMenuPopup(CMenu* p_menu, UINT p_index, BOOL p_system)
{
    for (UINT i = 0; i < p_menu->GetMenuItemCount(); i++) {
        UINT enable = MF_BYPOSITION;
        BOOL change = FALSE;
        switch (p_menu->GetMenuItemID(i)) {
        case ID_FILE_OPENINTERLEAFFILE_ONDISK:
            enable |= g_main->GetRunning() ? MF_GRAYED : MF_ENABLED;
            change = TRUE;
            break;
        case ID_FILE_OPENINTERLEAFFILE_INRAM:
            enable |= g_main->GetRunning() ? MF_GRAYED : MF_ENABLED;
            change = TRUE;
            break;
        case ID_COMMANDS_GETVARIABLE:
            enable |= !g_main->GetRunning() ? MF_ENABLED : MF_GRAYED;
            change = TRUE;
            break;
        case ID_COMMANDS_SETVARIABLE:
            enable |= !g_main->GetRunning() ? MF_ENABLED : MF_GRAYED;
            change = TRUE;
            break;
        case ID_ACTIONS:
            enable |= !g_main->GetRunning() && g_main->GetSourceList().GetCount() != 0 ? MF_ENABLED : MF_GRAYED;
            change = TRUE;
            break;
        case ID_START:
            enable |= !g_main->GetRunning() && g_main->GetStartList().GetCount() != 0 ? MF_ENABLED : MF_GRAYED;
            change = TRUE;
            break;
        case ID_STOP:
            enable |= g_main->GetRunning() ? MF_ENABLED : MF_GRAYED;
            change = TRUE;
            break;
        }
        if (change) {
            p_menu->EnableMenuItem(i, enable);
        }
    }
}

void 
CMainWindow::OnPaint()
{
    PAINTSTRUCT ps;
	BeginPaint(&ps);
	MxRect32 rect;
	GetClientRect((RECT*) &rect);
    if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetVideoManager()) {
		LegoOmni::GetInstance()->GetVideoManager()->InvalidateRect(rect);
	}
    EndPaint(&ps);
}


BOOL 
CMainWindow::OnQueryNewPalette()
{
	if (LegoOmni::GetInstance() && LegoOmni::GetInstance()->GetVideoManager()) {
		LegoOmni::GetInstance()->GetVideoManager()->RealizePalette();
        InvalidateRect(NULL, FALSE);
        return TRUE;
	}
    return FALSE;
}


void 
CMainWindow::OnPaletteChanged(CWnd* p_focusWindow)
{
	if (p_focusWindow != this && LegoOmni::GetInstance()->GetVideoManager()) {
		LegoOmni::GetInstance()->GetVideoManager()->RealizePalette();
        InvalidateRect(NULL, FALSE);
	}
}

void 
CMainWindow::OnRButtonUp(UINT p_flags, CPoint p_point)
{
    ClientToScreen((POINT*) &p_point);
    CMenu menu;
    menu.LoadMenu(IDR_MENU);
    menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, p_point.x, p_point.y, this);
}


void CMainWindow::OnRealtimeviewWeights() 
{
    if (!g_main->GetRealtimeViewWeightsDlg())
    {
        g_main->SetRealtimeViewWeightsDlg(new CRVWeightsDlg);
        g_main->GetRealtimeViewWeightsDlg()->Create(CRVWeightsDlg::IDD);
    }

    if (g_main->GetRealtimeViewWeightsDlg()->IsWindowVisible())
    {
        g_main->GetRealtimeViewWeightsDlg()->ShowWindow(SW_HIDE);
    }
    else
    {
        g_main->GetRealtimeViewWeightsDlg()->ShowWindow(SW_SHOW);
    }
}

void CMainWindow::OnRealism() 
{
    if (!g_main->GetRealismDlg())
    {
        g_main->SetRealismDlg(new CRealismDlg());
        g_main->GetRealismDlg()->Create(CRealismDlg::IDD);
        g_main->GetRealismDlg()->SetViewManager(((LegoVideoManager*) LegoOmni::GetInstance()->GetVideoManager())->Get3DManager()->GetLego3DView()->GetViewManager());
    }

    if (g_main->GetRealismDlg()->IsWindowVisible())
    {
        g_main->GetRealismDlg()->ShowWindow(SW_HIDE);
    }
    else
    {
        g_main->GetRealismDlg()->ShowWindow(SW_SHOW);
    }
}

void CMainWindow::OnUpdateRealtimeviewWeights(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(g_main->GetRealtimeViewWeightsDlg() &&
                     g_main->GetRealtimeViewWeightsDlg()->IsWindowVisible());
}

void CMainWindow::OnUpdateRealism(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(g_main->GetRealismDlg() &&
                     g_main->GetRealismDlg()->IsWindowVisible());
}

void CMainWindow::OnNavigation() 
{
    if (!g_main->GetNavigationDlg())
    {
        g_main->SetNavigationDlg(new CNavDlg);
        g_main->GetNavigationDlg()->Create(CNavDlg::IDD);
    }

    if (g_main->GetNavigationDlg()->IsWindowVisible())
    {
        g_main->GetNavigationDlg()->ShowWindow(SW_HIDE);
    }
    else
    {
        g_main->GetNavigationDlg()->ShowWindow(SW_SHOW);
    }
}

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_COMMAND(ID_FILE_OPENINTERLEAFFILE_ONDISK, OnOpenOnDisk)
	ON_COMMAND(ID_FILE_OPENINTERLEAFFILE_INRAM, OnOpenInRam)
	ON_COMMAND(ID_FILE_OPENPALETTEFILE, OnOpenPaletteFile)
	ON_COMMAND(ID_COMMANDS_GETVARIABLE, OnGetVariable)
	ON_COMMAND(ID_COMMANDS_SETVARIABLE, OnSetVariable)
	ON_COMMAND(ID_COMMANDS_SETSOUNDVOLUME, OnSetSoundVolume)
	ON_COMMAND(ID_COMMANDS_SETMUSICVOLUME, OnSetMusicVolume)
	ON_COMMAND(ID_ACTIONS, OnActions)
	ON_COMMAND(ID_VIDEO, OnVideo)
	ON_COMMAND(ID_OPTIONS_TICKLE, OnTickle)
	ON_COMMAND(ID_OPTIONS_REALTIMEVIEWWEIGHTS, OnRealtimeviewWeights)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_REALTIMEVIEWWEIGHTS, OnUpdateRealtimeviewWeights)
	ON_COMMAND(ID_OPTIONS_REALISM, OnRealism)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_REALISM, OnUpdateRealism)
	ON_COMMAND(ID_OPTIONS_NAVIGATION, OnNavigation)
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND(ID_EXIT, OnExit)
    ON_WM_INITMENUPOPUP()
	ON_WM_PAINT()
	ON_WM_CLOSE()
    ON_WM_QUERYNEWPALETTE()
    ON_WM_PALETTECHANGED()
    ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

BOOL 
CMainApp::InitInstance()
{
	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
    g_main = new CMain();
	return TRUE;
}

int 
CMainApp::ExitInstance()
{
    delete g_main;
    return 0;
}


// NOTE: this framework is copied from the MFC CWinThread::Run()
int CMainApp::Run()
{
	ASSERT_VALID(this);

	// for tracking the idle time state
	BOOL bIdle = TRUE;
	LONG lIdleCount = 0;


	// acquire and dispatch messages until a WM_QUIT message is received.
	for (;;)
	{
		// phase1: check to see if we can do idle work
		while (bIdle &&
			!::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
		{
			g_main->Tickle(TRUE);	// Tickle can give up cpu time
							// while there aren't events to process.

			// call OnIdle while in bIdle state
			if (!OnIdle(lIdleCount++))
				bIdle = FALSE; // assume "no idle" state
		}

		// phase2: pump messages while available
		for(;;)
		{
			g_main->Tickle(FALSE);	// Don't give up our cpu time while we're
							// still getting events.

			// pump message, but quit on WM_QUIT
			if (::PeekMessage(&m_msgCur, NULL, NULL, NULL, PM_NOREMOVE))
			{
				if (!::GetMessage(&m_msgCur, NULL, NULL, NULL))
					return ExitInstance();

//				if (m_msgCur.message == WM_TIMER)
//					g_main->Tickle(FALSE);

				// process this message
				if (!PreTranslateMessage(&m_msgCur) &&
					!CollapseMouseMoves(&m_msgCur))
				{
					::TranslateMessage(&m_msgCur);
					::DispatchMessage(&m_msgCur);
				}

				// reset "no idle" state after pumping "normal" message
				if (IsIdleMessage(&m_msgCur))
				{
					bIdle = TRUE;
					lIdleCount = 0;
				}
			}
			else
				break;
		}
	}

	ASSERT(FALSE);  // not reachable
}

BOOL
CMainApp::CollapseMouseMoves(MSG *pMsg)
{
	MSG msg;

	if (pMsg->message == WM_MOUSEMOVE)
	{
		if (::PeekMessage(&msg, NULL, NULL, NULL, PM_NOREMOVE) &&
			(msg.message == WM_MOUSEMOVE))
		{
			return TRUE;
		}
	}
	return FALSE;
}


void
LegoUserMessage(const char *p_txt, int p_type)
{
	int result;
	UINT wType;

	switch (p_type)
	{
		case e_msgInfo:
			wType = MB_APPLMODAL | MB_ICONINFORMATION | MB_OK;
			break;
		case e_msgAbortAlways:
			wType = MB_APPLMODAL | MB_ICONHAND | MB_OK;
			break;
		case e_msgAbortQuery:
			wType = MB_APPLMODAL | MB_ICONHAND | MB_OKCANCEL;
			break;
	}

	result = ::MessageBox(NULL, p_txt, "Lego Critical Error", wType);
	if ((p_type == e_msgAbortAlways) || (result == IDCANCEL))
		abort();
}
