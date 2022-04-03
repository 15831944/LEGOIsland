#ifndef __VIEWER_H
#define __VIEWER_H

#include <afxwin.h>
#include <rl.h>

class LegoMainWindow : public CFrameWnd {
public:
    LegoMainWindow();
    afx_msg int OnCreate(CREATESTRUCT* p_cs);
    afx_msg void OnPaint();
    afx_msg void OnActivate(UINT p_state, CWnd* p_other, BOOL p_minimized);
    afx_msg void OnLButtonDown(UINT p_flags, CPoint p_point);
    afx_msg void OnLButtonUp(UINT p_flags, CPoint p_point);
    afx_msg void OnRButtonDown(UINT p_flags, CPoint p_point);
    afx_msg void OnRButtonUp(UINT p_flags, CPoint p_point);
    afx_msg void OnMouseMove(UINT p_flags, CPoint p_point);
    afx_msg void OnOpen();
    afx_msg void OnExit();
    DECLARE_MESSAGE_MAP()
protected:
    void OpenFile(const char* p_fileName);
};

class LegoViewerApp : public CWinApp {
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL OnIdle(LONG p_count);
};

class LegoViewer {
public:
    LegoViewer();
    virtual ~LegoViewer();
    RLDevice GetDevice() { return m_device; }
    RLViewport GetViewport() { return m_viewport; }
    RLFrame GetScene() { return m_scene; }
    RLFrame GetObject() { return m_object; }
    void SetObject(RLFrame p_object);
    void SetMousePos(CPoint& p_mousePos);
    void LeftDrag(CPoint& p_mousePos);
    void RightDrag(CPoint& p_mousePos);
protected:
    RLDevice m_device;
    RLViewport m_viewport;
    RLFrame m_scene;
    RLFrame m_object;
    CPoint m_mousePos;
};

extern LegoViewer* g_viewer;

#endif // __VIEWER_H


