/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include <afxdlgs.h>
#include <stdio.h>

#include "MxOmni.h"
#include "StdLego.h"
#include "LegoOmni.h"
#include "LWorld.h"

#include "GuiDemo.h"
#include "resource.h"
#include "idler.h"
#include "LegoGui.h"
#include "LegoNotify.h"

#define APSTUDIO_INVOKED
#include "resource.h"
#undef APSTUDIO_INVOKED

using namespace std;

#define MAX_STREAMS         1000

// #define MAIN_PRIORITY (LAST_PRIORITY-1) // for testing with a low UI priority
#define MAIN_PRIORITY (FIRST_PRIORITY+2) // for testing with a medium UI priority
// #define MAIN_PRIORITY (FIRST_PRIORITY+1) // for testing with a high UI priority

CDemo demo;
LegoWorld legoWorld;

CMainWindow::CMainWindow()
{
	Create(NULL, "Demo", WS_OVERLAPPEDWINDOW, rectDefault, NULL, MAKEINTRESOURCE(IDR_MENU));
    m_dc = new CClientDC(this);
	m_palette = NULL;
    LegoOmni::CreateInstance();
    LegoOmni::GetInstance()->Create(MxOmniCreateParam(m_fileName, GetSafeHwnd(), m_dc->GetSafeHdc(), 640, 480, m_palette, MxOmniCreateFlags()));
    m_running = FALSE;
    m_positioned = FALSE;
    m_nextCommandId = _APS_NEXT_COMMAND_VALUE;
    m_preloadedResident = FALSE;
	m_inputMan = LegoOmni::GetInstance()->GetInputManager();
    UpdateMenu();
}

CMainWindow::~CMainWindow()
{
    LegoOmni::DestroyInstance();
	if (m_palette) {
		delete m_palette;
	}
    delete m_dc;

    while(!m_startList.empty())
    {
        StartList::iterator startIterator = m_startList.begin();
        ActionsToStart* action = *startIterator;
        m_startList.erase(startIterator);
        delete action;
    }
}

LRESULT
CMainWindow::WindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
//	if ((message >= WM_LBUTTONDOWN) && (message <= WM_MOUSELAST))
	if ((message >= WM_MOUSEFIRST) && (message <= WM_MOUSELAST))
	{
		MxS16 type;
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
		}
		m_inputMan->QueueEvent(type, wParam, LOWORD(lParam), HIWORD(lParam), 0); 
		return 0;
	}
	else
	{
		return CWnd::WindowProc(message, wParam, lParam);
	}
}

void
CMainWindow::UpdateMenu()
{
    CMenu* menu = GetMenu();
    menu->EnableMenuItem(ID_START, !m_running && 
                                   (m_startList.size()!=0 || m_preloadedResident) ? 
                                    MF_ENABLED : MF_GRAYED);
    menu->EnableMenuItem(ID_STOP, m_running ? MF_ENABLED : MF_GRAYED);
    DrawMenuBar();
}

void 
CMainWindow::AddMenuItem(MxStreamController *p_controller)
{
    CMenu* menu = GetMenu();
    HMENU hPopupMenu = CreatePopupMenu();
    const MxChar *sourceName = *(p_controller->GetSourceName());

    menu->AppendMenu(MF_STRING | MF_POPUP | MF_ENABLED, (UINT)hPopupMenu, sourceName);
    for( int i = 0; i < p_controller->GetNumberOfMedias(); i++)
    {
       HMENU hMenu = CreatePopupMenu();
        AppendMenu(hPopupMenu, MF_STRING | MF_POPUP | MF_ENABLED, (UINT)hMenu, 
                   p_controller->GetMedia(i)->GetMediaObjectName());
        AppendMenu(hMenu, MF_STRING | MF_ENABLED, m_nextCommandId++, "Add To Start");
        AppendMenu(hMenu, MF_STRING | MF_ENABLED, m_nextCommandId++, "Preload Resident");
    }
}

void 
CMainWindow::OnOpenInterleafFile()
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
        m_fileName = CString(fileName, n);

        MxStreamController *controller = LegoOmni::GetInstance()->GetStreamer()->Open((LPCSTR)m_fileName, OC_DISK_STREAMING);
        if(!controller)
        {
            MessageBox("MxStreamer:Open() failed");
            return;
        }

        AddMenuItem(controller);
        m_controllers.push_back(controller);

        UpdateMenu();
    }
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
    		if (m_palette) {
    			delete m_palette;
    		}
			m_palette = bitmap.CreatePalette();
			if (LegoOmni::GetInstance()->GetVideoManager()) {
				LegoOmni::GetInstance()->GetVideoManager()->RealizePalette(m_palette);
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
    LegoOmni::GetInstance()->Destroy();
    DestroyWindow();
}

void 
CMainWindow::OnStart()
{
    MxResult ret;

    for(StartList::iterator startIterator = m_startList.begin();
        startIterator != m_startList.end();
        startIterator++)
    {
        ActionsToStart* action = *startIterator;

        ret = LegoOmni::GetInstance()->Start((LPCSTR)action->m_source, 
                                           (LPCSTR)action->m_action,
										   &legoWorld);

        if(ret != SUCCESS)
        {
            MessageBox("LegoOmni:Start() failed");
            return;
        }
        m_running = TRUE;
        m_positioned = FALSE;
    }


    UpdateMenu();
}

void 
CMainWindow::OnStop()
{
    LegoOmni::GetInstance()->Stop();
    m_running = FALSE;
    UpdateMenu();
}

void 
CMainWindow::OnSelectAction(UINT p_nID)
{
    MxStreamController* controller;

    UINT startRangeID = _APS_NEXT_COMMAND_VALUE,
         endRangeID;

    for(MxStreamControllerList::iterator controllerIterator = m_controllers.begin();
        controllerIterator != m_controllers.end();
        controllerIterator++)
    {
        controller = *controllerIterator;
        endRangeID = startRangeID + controller->GetNumberOfMedias() * 2;
        if(p_nID >= startRangeID && p_nID < endRangeID)
        {
            ActionsToStart* action = new ActionsToStart;
            action->m_source = *controller->GetSourceName();
            action->m_action = controller->GetMedia((p_nID - startRangeID)/2)->GetMediaObjectName();
            if((p_nID - startRangeID) % 2)
            {
                LegoOmni::GetInstance()->GetStreamer()->PreloadResident(action->m_source, action->m_action);
                m_preloadedResident = TRUE;
            }
            m_startList.push_back(action);
            break;
        }
        startRangeID = endRangeID;
    }

    UpdateMenu();
}


CGoToDialog::CGoToDialog(CWnd* p_parent) : CDialog(IDD_GOTO, p_parent) 
{
}

BOOL 
CGoToDialog::OnInitDialog()
{
    return TRUE;
}

void 
CGoToDialog::OnOK()
{
    CComboBox* actions = (CComboBox*)GetDlgItem(IDC_ACTION_NAME);
    actions->GetWindowText(m_currentAction);
    CDialog::OnOK();
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

void 
CMainWindow::OnGoTo()
{
    CGoToDialog dialog(this);

    if(dialog.DoModal() == IDOK) {
        LegoOmni::GetInstance()->GetStreamer()->Stop();
        // LegoOmni::GetInstance()->GetStreamer()->GoTo(dialog.GetCurrentAction());
        m_positioned = TRUE;
    }
}

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
CMainWindow::OnInitMenuPopup(CMenu* p_menu, UINT p_index, BOOL p_system)
{
    CMenu* menu = GetMenu();
    switch (p_index) {
    case 0:
        menu->EnableMenuItem(ID_FILE_OPENINTERLEAFFILE, m_running ? MF_GRAYED : MF_ENABLED);
        menu->EnableMenuItem(ID_FILE_OPENPALETTEFILE, m_running ? MF_GRAYED : MF_ENABLED);
        break;
    case 1:
        menu->EnableMenuItem(ID_COMMANDS_GOTO, !m_running && m_fileName != "" ? MF_ENABLED : MF_GRAYED);
        menu->EnableMenuItem(ID_COMMANDS_GETVARIABLE, !m_running && m_fileName != "" ? MF_ENABLED : MF_GRAYED);
        menu->EnableMenuItem(ID_COMMANDS_SETVARIABLE, !m_running && m_fileName != "" ? MF_ENABLED : MF_GRAYED);
        break;
    }
}

void 
CMainWindow::OnPaint()
{
    PAINTSTRUCT ps;
	BeginPaint(&ps);
	MxRect32 rect;
	GetClientRect((RECT*) &rect);
	MxVideoManager* videoManager = LegoOmni::GetInstance()->GetVideoManager();
	if (videoManager) {
		videoManager->InvalidateRect(rect);
	}
    EndPaint(&ps);
}


BOOL 
CMainWindow::OnQueryNewPalette()
{
	if (LegoOmni::GetInstance()->GetVideoManager()) {
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

BEGIN_MESSAGE_MAP(CMainWindow, CFrameWnd)
	ON_COMMAND(ID_FILE_OPENINTERLEAFFILE, OnOpenInterleafFile)
	ON_COMMAND(ID_FILE_OPENPALETTEFILE, OnOpenPaletteFile)
	ON_COMMAND(ID_FILE_EXIT, OnExit)
	ON_COMMAND(ID_COMMANDS_GOTO, OnGoTo)
	ON_COMMAND(ID_COMMANDS_GETVARIABLE, OnGetVariable)
	ON_COMMAND(ID_COMMANDS_SETVARIABLE, OnSetVariable)
	ON_COMMAND(ID_COMMANDS_SETSOUNDVOLUME, OnSetSoundVolume)
	ON_COMMAND(ID_COMMANDS_SETMUSICVOLUME, OnSetMusicVolume)
	ON_COMMAND(ID_START, OnStart)
	ON_COMMAND(ID_STOP, OnStop)
	ON_COMMAND_RANGE(_APS_NEXT_COMMAND_VALUE, _APS_NEXT_COMMAND_VALUE + 2 * MAX_STREAMS, OnSelectAction)
    ON_WM_INITMENUPOPUP()
	ON_WM_PAINT()
    ON_WM_QUERYNEWPALETTE()
    ON_WM_PALETTECHANGED()
END_MESSAGE_MAP()

BOOL 
CDemo::InitInstance()
{
	m_pMainWnd = new CMainWindow();
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
    m_idler = new CIdler();

	return TRUE;
}

int 
CDemo::ExitInstance()
{
    delete m_idler;
    return 0;
}

BOOL CDemo::OnIdle(LONG p_counter) 
{
    if (CWinApp::OnIdle(p_counter)) {
        return TRUE;
    }
	return m_idler->Idle(p_counter);
}

BOOL CDemo::InitApplication() 
{
    BOOL retVal = CWinApp::InitApplication();
    if(retVal)
    {
	    // Prepare the main thread at the given priority.and yield.
        // Other threads with any priority may run before we get back here.
        // This is probably not the best place to do this, but it is convenient.
        if (MxScheduler::GetInstance()) {
	        MxScheduler::GetInstance()->StartMultiTasking(MAIN_PRIORITY);
        }
    }
    return retVal;
}

