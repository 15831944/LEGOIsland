#ifndef __GUI_H
#define __GUI_H

#include <afxwin.h>
#include "LegoTypes.h"

class CImageList;

class LegoConvertDialog : public CModalDialog {
public:
    LegoConvertDialog();
    virtual BOOL OnInitDialog();
    afx_msg void OnScript();
    afx_msg void OnStudioFile();
    afx_msg void OnModelDirectory();
    afx_msg void OnExit();
    DECLARE_MESSAGE_MAP()
};

class LegoScriptDialog : public CModalDialog {
public:
    LegoScriptDialog();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnBrowse();
    afx_msg void OnRun();
    afx_msg void OnFileChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateFile();
    void UpdateControls();
    LegoBool m_fileChanged;
};

class LegoStudioFileDialog : public CModalDialog {
public:
    LegoStudioFileDialog();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnBrowse();
    afx_msg void OnMeshes();
    afx_msg void OnTextures();
    afx_msg void OnAnimations();
    afx_msg void OnFileChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateFile();
    void UpdateControls();
    LegoBool m_fileChanged;
};

class LegoModelDirectoryDialog : public CModalDialog {
public:
    LegoModelDirectoryDialog();
    virtual BOOL OnInitDialog();
    virtual void OnOK();
    afx_msg void OnBrowse();
    afx_msg void OnModels();
    afx_msg void OnDirectoryChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateDirectory();
    void UpdateControls();
    LegoBool m_directoryChanged;
};

class LegoMeshDialog : public CModalDialog {
public:
    LegoMeshDialog();
    virtual BOOL OnInitDialog();
    afx_msg void OnSave();
    afx_msg void OnClose();
    afx_msg void OnSelChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateControls();
};

class LegoTextureDialog : public CModalDialog {
public:
    LegoTextureDialog();
    virtual BOOL OnInitDialog();
    afx_msg void OnSave();
    afx_msg void OnClose();
    afx_msg void OnSelChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateControls();
};

class LegoAnimationDialog : public CModalDialog {
public:
    LegoAnimationDialog();
    virtual BOOL OnInitDialog();
    afx_msg void OnSave();
    afx_msg void OnClose();
    afx_msg void OnSelChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateControls();
};

class LegoModelDialog : public CModalDialog {
public:
    LegoModelDialog();
    virtual BOOL OnInitDialog();
    afx_msg void OnSave();
    afx_msg void OnClose();
    afx_msg void OnSelChange();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateControls();
};

class LegoOpenModelDirectoryDialog : public CModalDialog {
public:
    LegoOpenModelDirectoryDialog();
    CString& GetName() { return m_name; }
    virtual void OnOK();
    virtual BOOL OnInitDialog();
    void OnSelChanged();
    void OnItemExpanding(HTREEITEM p_item);
    void  OnItemCollapsing(HTREEITEM p_item);
    virtual BOOL OnNotify(WPARAM p_param1, LPARAM p_param2, LRESULT* p_result);
    afx_msg void OnDestroy();
    DECLARE_MESSAGE_MAP()
protected:
    void UpdateControls();
    void InitTree();
    void ExpandPath(char* p_path);
    HTREEITEM FindDrive(char* p_drive);
    HTREEITEM FindDirectory(HTREEITEM p_parent, char* p_directory);
    CString GetItemPath(HTREEITEM p_item);
    LegoBool HasSubdirectories(const char* p_directory);
    CImageList* CreateImageList();
    CString m_name;
    int m_cdROMDrive;
    int m_closedFolder;
    int m_computer;
    int m_fixedDrive;
    int m_openFolder;
    int m_remoteDrive;
    int m_removableDrive;
};

class LegoConvertApp : public CWinApp {
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    void  UpdateStackingChain(CWnd* p_top);
};

#endif // __GUI_H

