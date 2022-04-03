/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __MAIN_H
#define __MAIN_H

#include <afxwin.h>
#include <afxtempl.h>
#include "resource.h"
#include "MxOmni.h"

class MxPalette;
class CRealismDlg;
class CRVWeightsDlg;
class LegoWorld;
class TimeAverage;
class CMainWindow;
class LegoGameState;
class CNavDlg;

class CStartListElement {
protected:
    CString m_source;
    MxDSAction m_action;
    MxTime m_residentTime;
public:
    CStartListElement(const char* p_source, const char* p_action) 
        { m_source = p_source;
          m_action.SetSourceName(p_source); 
          m_action.SetObjectName(p_action);
          m_residentTime = MxNAN_TIME; }
    LPCSTR GetSourceName() { return m_source; }
    LPCSTR GetActionName() { return m_action.GetObjectName(); }
    MxDSAction* GetAction() { m_action.SetSourceName(m_source); return &m_action; }
};

class CStartList : public CList<CStartListElement*, CStartListElement*> {};

class CSourceListElement {
protected:
    CString m_source;
    UINT m_mode;
public:
    CSourceListElement(const char* p_source, UINT p_mode) { m_source = p_source; m_mode = p_mode; }
    CString& GetSource() { return m_source; }
    UINT GetMode() { return m_mode; }
};

class CSourceList : public CList<CSourceListElement*, CSourceListElement*> {};


class CMain {
protected:
    BOOL m_running;
    BOOL m_positioned;
    MxTime m_tickleInterval;
    MxVideoParam m_videoParam;
	CRVWeightsDlg* m_pRealtimeViewWeightsDlg;
	CRealismDlg* m_pRealismDlg;
	CNavDlg* m_pNavigationDlg;
	TimeAverage* m_timeAverage;
	LegoGameState* m_gameState;
    CStartList m_startList;
    CSourceList m_sourceList;
    CMainWindow* m_window;
	int m_videoOverhead;
public:
    CMain();
    ~CMain();
    BOOL GetRunning() { return m_running; }
    void SetRunning(BOOL p_running) { m_running = p_running; }
    BOOL GetPositioned() { return m_positioned; }
    void SetPositioned(BOOL p_positioned) { m_positioned = p_positioned; }
    MxTime GetTickleInterval() { return m_tickleInterval; }
    void SetTickleInterval(MxTime p_tickleInterval) { m_tickleInterval = p_tickleInterval; }
    MxVideoParam& GetVideoParam() { return m_videoParam; }
    void SetVideoParam(MxVideoParam& p_videoParam) { m_videoParam = p_videoParam; }
	CRVWeightsDlg* GetRealtimeViewWeightsDlg() { return m_pRealtimeViewWeightsDlg; }
	void SetRealtimeViewWeightsDlg(CRVWeightsDlg* p_pRealtimeViewWeightsDlg) { m_pRealtimeViewWeightsDlg = p_pRealtimeViewWeightsDlg; }
	CRealismDlg* GetRealismDlg() { return m_pRealismDlg; }
	void SetRealismDlg(CRealismDlg* p_pRealismDlg) { m_pRealismDlg = p_pRealismDlg; }
	CNavDlg* GetNavigationDlg() { return m_pNavigationDlg; }
	void SetNavigationDlg(CNavDlg* p_pNavigationDlg) { m_pNavigationDlg = p_pNavigationDlg; }
    CStartList& GetStartList() { return m_startList; }
    CSourceList& GetSourceList() { return m_sourceList; }
    CMainWindow* GetWindow() { return m_window; }
    void ResetVideo(MxVideoParam& p_videoParam);
	void Tickle(BOOL p_yieldOK);
	int GetVideoOverhead() { return m_videoOverhead; }
	void MeasureVideoOverhead();
	void UpdateFrameTime();
};

class CMainWindow : public CFrameWnd {
protected:
    void Open(UINT p_openMode);
    BOOL ChangeVideoMode(int p_width, int p_height);
public:
	CMainWindow();
    ~CMainWindow();
    void Resize(int p_width, int p_height, BOOL p_titleBar);
	virtual LRESULT WindowProc( UINT message, WPARAM wParam, LPARAM lParam );
	afx_msg void OnOpenOnDisk();
	afx_msg void OnOpenInRam();
	afx_msg void OnOpenPaletteFile();
	afx_msg void OnGetVariable();
	afx_msg void OnSetVariable();
	afx_msg void OnSetSoundVolume();
	afx_msg void OnSetMusicVolume();
	afx_msg void OnRealtimeviewWeights();
	afx_msg void OnRealism();
	afx_msg void OnUpdateRealtimeviewWeights(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRealism(CCmdUI* pCmdUI);
	afx_msg void OnNavigation();
	afx_msg void OnActions();
	afx_msg void OnVideo();
	afx_msg void OnTickle();
	afx_msg void OnStart();
	afx_msg void OnStop();
	afx_msg void OnExit();
	afx_msg void OnInitMenuPopup(CMenu* p_menu, UINT p_index, BOOL p_system);
	afx_msg void OnPaint();
    afx_msg BOOL OnQueryNewPalette();
    afx_msg void OnPaletteChanged(CWnd* p_focusWindow);
    afx_msg void OnRButtonUp(UINT p_flags, CPoint p_point);
	DECLARE_MESSAGE_MAP()
};

class CMainApp : public CWinApp {
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void DisconnectTickle();
	virtual int Run();
	BOOL CollapseMouseMoves(MSG *pMsg);
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

class CActionsDialog : public CDialog {
protected:
    CStartList m_startList;
    void OnOK();
    void UpdateControls();
public:
    CActionsDialog(CWnd* p_parent);
    CStartList& GetStartList() { return m_startList; }
    BOOL OnInitDialog();
    afx_msg void OnSelChange();
    afx_msg void OnAdd();
    afx_msg void OnDelete();
    afx_msg void OnProperties();
	DECLARE_MESSAGE_MAP()
};


//===========================================================================
// CGeneralActionProperties

class CGeneralActionProperties : public CPropertyPage
{
    MxTime m_residentTime;
    BOOL m_preloadResident;
    void UpdateControls();
public:
	CGeneralActionProperties();
    BOOL OnInitDialog();
    afx_msg void OnPreloadResident();
    void SetResidentTime(MxTime p_time) { m_residentTime = p_time; }
    MxTime GetResidentTime() { return m_residentTime; }

protected:
	DECLARE_MESSAGE_MAP()
};


//===========================================================================
// CTimeActionProperties

class CTimeActionProperties : public CPropertyPage
{
    MxTime m_startTime;
    MxTime m_duration;
    MxS16 m_loopCount;
    BOOL m_useDuration;
    void UpdateControls();

public:
	CTimeActionProperties();
    BOOL OnInitDialog();
    afx_msg void OnLooping();
    afx_msg void OnDuration();

protected:
	DECLARE_MESSAGE_MAP()
};


//===========================================================================
// CLocationActionProperties

class CLocationActionProperties : public CPropertyPage
{
	Mx3DPointDouble m_location;
	Mx3DPointDouble m_direction;
	Mx3DPointDouble m_up;

public:
	CLocationActionProperties();
    BOOL OnInitDialog();

protected:
	DECLARE_MESSAGE_MAP()
};


class CVideoDialog : public CDialog {
protected:
    MxVideoParam m_videoParam;
    void OnOK();
    void UpdateControls();
public:
    CVideoDialog(CWnd* p_parent);
    MxVideoParam& GetVideoParam() { return m_videoParam; }
    BOOL OnInitDialog();
    afx_msg void OnFullScreen();
    afx_msg void OnFlipSurfaces();
	DECLARE_MESSAGE_MAP()
};

class CTickleIntervalDialog : public CDialog {
protected:
    CString m_name;
	MxTickleManager *m_tickleManager;
	MxVideoManager *m_videoManager;
	MxNotificationManager *m_notifyManager;
	MxSoundManager *m_soundManager;
	MxMusicManager *m_musicManager;
	MxEventManager *m_eventManager;
    void OnOK();
public:
    CTickleIntervalDialog(CWnd* p_parent);
    CString& GetName() { return m_name; }
    BOOL OnInitDialog();
    afx_msg void OnRead();
	DECLARE_MESSAGE_MAP()
};

void LegoUserMessage(const char *p_txt, int p_type);

#endif // __MAIN_H

