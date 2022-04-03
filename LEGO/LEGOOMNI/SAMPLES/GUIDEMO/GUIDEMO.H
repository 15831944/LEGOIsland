/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __DEMO_H
#define __DEMO_H

#include <afxwin.h>
#include "MxSTLWrap.h"
#include "MxStreamController.h"
#include "LegoInputManager.h"

class MxPalette;
class CIdler;


class ActionsToStart
{
public:
    MxString m_source;
    MxString m_action;
    MxBool m_active;
};

class StartList : public std::list<ActionsToStart*> {};


class CMainWindow : public CFrameWnd {
protected:
    CClientDC* m_dc;
    CString m_fileName;
    MxPalette* m_palette;
    BOOL m_running;
    BOOL m_positioned;
    UINT m_nextCommandId;
    MxStreamControllerList m_controllers;
    StartList m_startList;
    StartList m_residentList;
    BOOL m_preloadedResident;
	DWORD m_videoManagerThreadId;
	LegoInputManager *m_inputMan;

public:
	CMainWindow();
    ~CMainWindow();
	virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	void UpdateMenu();
    void AddMenuItem(MxStreamController *p_controller);
	afx_msg void OnOpenInterleafFile();
	afx_msg void OnOpenPaletteFile();
	afx_msg void OnExit();
	afx_msg void OnGoTo();
	afx_msg void OnGetVariable();
	afx_msg void OnSetVariable();
	afx_msg void OnSetSoundVolume();
	afx_msg void OnSetMusicVolume();
	afx_msg void OnStart();
	afx_msg void OnStop();
    afx_msg void OnSelectAction(UINT nID);
	afx_msg void OnInitMenuPopup(CMenu* p_menu, UINT p_index, BOOL p_system);
	afx_msg void OnPaint();
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* p_focusWindow);
	DECLARE_MESSAGE_MAP()
};

class CDemo : public CWinApp {
protected:
    CIdler* m_idler;
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
    virtual BOOL OnIdle(LONG p_counter);
    virtual BOOL InitApplication();
};

class CGoToDialog : public CDialog {
protected:
    CString m_currentAction;
    void OnOK();
public:
    CGoToDialog(CWnd* p_parent);
    CString& GetCurrentAction() { return m_currentAction; }
    BOOL OnInitDialog();
};

class CGetVariableDialog : public CDialog {
protected:
    CString m_name;
    void OnOK();
public:
    CGetVariableDialog(CWnd* p_parent);
    CString& GetName() { return m_name; }
    BOOL OnInitDialog();
};


class CSetVariableDialog : public CDialog {
protected:
    CString m_name;
    CString m_value;
    void OnOK();
public:
    CSetVariableDialog(CWnd* p_parent);
    CString& GetName() { return m_name; }
    CString& GetValue() { return m_value; }
    BOOL OnInitDialog();
};

class CSetSoundVolumeDialog : public CDialog {
protected:
    int m_soundVolume;
    void OnOK();
public:
    CSetSoundVolumeDialog(CWnd* p_parent);
    int GetSoundVolume() { return m_soundVolume; }
    BOOL OnInitDialog();
};

class CSetMusicVolumeDialog : public CDialog {
protected:
    int m_musicVolume;
    void OnOK();
public:
    CSetMusicVolumeDialog(CWnd* p_parent);
    int GetMusicVolume() { return m_musicVolume; }
    BOOL OnInitDialog();
};


#endif // __DEMO_H

