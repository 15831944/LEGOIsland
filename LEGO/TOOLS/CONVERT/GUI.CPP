#include <afxdlgs.h>
#include <afxcmn.h>
#include "Gui.h"
#include "Convert.h"
#include "Script.h"
#include "StudioFile.h"
#include "Model.h"
#include "LegoStorage.h"
#include "LegoMesh.h"
#include "LegoTexture.h"
#include "LegoAnim.h"
#include "Version.h"
#include "resource.h"

static LegoConvertApp convertApp;

LegoConvertDialog::LegoConvertDialog()
    :
    CModalDialog(IDD_CONVERT)
{
}

BOOL 
LegoConvertDialog::OnInitDialog()
{
    return TRUE;
}

void 
LegoConvertDialog::OnScript()
{
    LegoScriptDialog dialog;
    dialog.DoModal();
}

void 
LegoConvertDialog::OnStudioFile()
{
    LegoStudioFileDialog dialog;
    dialog.DoModal();
}

void 
LegoConvertDialog::OnModelDirectory()
{
    LegoModelDirectoryDialog dialog;
    dialog.DoModal();
}

void 
LegoConvertDialog::OnExit()
{
    EndDialog(IDC_EXIT);
}

BEGIN_MESSAGE_MAP(LegoConvertDialog, CModalDialog)
    ON_COMMAND(IDC_SCRIPT, OnScript)
    ON_COMMAND(IDC_STUDIOFILE, OnStudioFile)
    ON_COMMAND(IDC_MODELDIRECTORY, OnModelDirectory)
    ON_COMMAND(IDC_EXIT, OnExit)
END_MESSAGE_MAP()

LegoScriptDialog::LegoScriptDialog()
    :
    CModalDialog(IDD_SCRIPT)
{
    m_fileChanged = FALSE;
}

BOOL 
LegoScriptDialog::OnInitDialog()
{
    UpdateControls();
    return TRUE;
}

void 
LegoScriptDialog::OnOK()
{
    if (m_fileChanged) {
        UpdateFile();
    }
    else {
        EndDialog(IDOK);
    }
}

void 
LegoScriptDialog::OnBrowse()
{
    CFileDialog dialog(
        TRUE, 
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Script Files (*.scr)|*.scr|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        SetDlgItemText(IDC_FILE, dialog.GetPathName());
        UpdateFile();
    }
}

void 
LegoScriptDialog::OnRun()
{
    CWaitCursor cursor;
    g_convert->GetScript()->Run();
}

void 
LegoScriptDialog::OnFileChange()
{
    if (!m_fileChanged) {
        m_fileChanged = TRUE;
        SetDlgItemText(IDOK, "OK");
    }
}

void 
LegoScriptDialog::UpdateFile()
{
    CEdit* edit = (CEdit*) GetDlgItem(IDC_FILE);
    CString fileName;
    edit->GetWindowText(fileName);
    char path[_MAX_PATH];
    char* p;
    LegoBool ok;
    if (ok = (LegoBool) GetFullPathName(fileName, sizeof(path), path, &p)) {
        edit->SetWindowText(path);
        ok = g_convert->OpenScript(path);
    }
    if (!ok) {
        edit->SetFocus();
        edit->SetWindowText("");
    }
    m_fileChanged = FALSE;
    SetDlgItemText(IDOK, "Close");
    UpdateControls();
}

void 
LegoScriptDialog::UpdateControls()
{
    GetDlgItem(IDC_RUN)->EnableWindow(
        g_convert->GetScript()->IsOpen()
    );
}

BEGIN_MESSAGE_MAP(LegoScriptDialog, CModalDialog)
    ON_COMMAND(IDC_BROWSE, OnBrowse)
    ON_COMMAND(IDC_RUN, OnRun)
    ON_EN_CHANGE(IDC_FILE, OnFileChange)
END_MESSAGE_MAP()

LegoStudioFileDialog::LegoStudioFileDialog()
    :
    CModalDialog(IDD_STUDIOFILE)
{
    m_fileChanged = FALSE;
}

BOOL 
LegoStudioFileDialog::OnInitDialog()
{
    UpdateControls();
    return TRUE;
}

void 
LegoStudioFileDialog::OnOK()
{
    if (m_fileChanged) {
        UpdateFile();
    }
    else {
        EndDialog(IDOK);
    }
}

void 
LegoStudioFileDialog::OnBrowse()
{
    CFileDialog dialog(
        TRUE, 
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "3D Studio Files (*.3ds)|*.3ds|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        SetDlgItemText(IDC_FILE, dialog.GetPathName());
        UpdateFile();
    }
}

void 
LegoStudioFileDialog::OnMeshes()
{
    LegoMeshDialog dialog;
    dialog.DoModal();
}

void 
LegoStudioFileDialog::OnTextures()
{
    LegoTextureDialog dialog;
    dialog.DoModal();
}

void 
LegoStudioFileDialog::OnAnimations()
{
    LegoAnimationDialog dialog;
    dialog.DoModal();
}

void 
LegoStudioFileDialog::OnFileChange()
{
    if (!m_fileChanged) {
        m_fileChanged = TRUE;
        SetDlgItemText(IDOK, "OK");
    }
}

void 
LegoStudioFileDialog::UpdateFile()
{
    CEdit* edit = (CEdit*) GetDlgItem(IDC_FILE);
    CString fileName;
    edit->GetWindowText(fileName);
    char path[_MAX_PATH];
    char* p;
    LegoBool ok;
    if (ok = (LegoBool) GetFullPathName(fileName, sizeof(path), path, &p)) {
        edit->SetWindowText(path);
        ok = g_convert->OpenStudioFile(path);
    }
    if (!ok) {
        edit->SetFocus();
        edit->SetWindowText("");
    }
    m_fileChanged = FALSE;
    SetDlgItemText(IDOK, "Close");
    UpdateControls();
}

void 
LegoStudioFileDialog::UpdateControls()
{
    GetDlgItem(IDC_MESHES)->EnableWindow(
        g_convert->GetStudioFile()->GetNumMeshes()
    );
    GetDlgItem(IDC_TEXTURES)->EnableWindow(
        g_convert->GetStudioFile()->GetNumTextures()
    );
    GetDlgItem(IDC_ANIMATIONS)->EnableWindow(
        g_convert->GetStudioFile()->GetNumAnimations()
    );
}

BEGIN_MESSAGE_MAP(LegoStudioFileDialog, CModalDialog)
    ON_COMMAND(IDC_BROWSE, OnBrowse)
    ON_COMMAND(IDC_MESHES, OnMeshes)
    ON_COMMAND(IDC_TEXTURES, OnTextures)
    ON_COMMAND(IDC_ANIMATIONS, OnAnimations)
    ON_EN_CHANGE(IDC_FILE, OnFileChange)
END_MESSAGE_MAP()

LegoModelDirectoryDialog::LegoModelDirectoryDialog()
    :
    CModalDialog(IDD_MODELDIRECTORY)
{
    m_directoryChanged = FALSE;
}

BOOL 
LegoModelDirectoryDialog::OnInitDialog()
{
    UpdateControls();
    return TRUE;
}

void 
LegoModelDirectoryDialog::OnOK()
{
    if (m_directoryChanged) {
        UpdateDirectory();
    }
    else {
        EndDialog(IDOK);
    }
}

void 
LegoModelDirectoryDialog::OnBrowse()
{
    LegoOpenModelDirectoryDialog dialog;
    if (dialog.DoModal() == IDOK) {
        SetDlgItemText(IDC_DIRECTORY, dialog.GetName());
        UpdateDirectory();
    }
}

void 
LegoModelDirectoryDialog::OnModels()
{
    LegoModelDialog dialog;
    dialog.DoModal();
}

void 
LegoModelDirectoryDialog::OnDirectoryChange()
{
    if (!m_directoryChanged) {
        m_directoryChanged = TRUE;
        SetDlgItemText(IDOK, "OK");
    }
}

void 
LegoModelDirectoryDialog::UpdateDirectory()
{
    CEdit* edit = (CEdit*) GetDlgItem(IDC_DIRECTORY);
    CString dirName;
    edit->GetWindowText(dirName);
    char path[_MAX_PATH];
    char* p;
    LegoBool ok;
    if (ok = (LegoBool) GetFullPathName(dirName, sizeof(path), path, &p)) {
        edit->SetWindowText(path);
        CWaitCursor cursor;
        ok = g_convert->OpenModelDirectory(path);
    }
    if (!ok) {
        edit->SetFocus();
        edit->SetWindowText("");
    }
    m_directoryChanged = FALSE;
    SetDlgItemText(IDOK, "Close");
    UpdateControls();
}

void 
LegoModelDirectoryDialog::UpdateControls()
{
    GetDlgItem(IDC_MODELS)->EnableWindow(
        g_convert->GetModelDirectory()->GetNumModels()
    );
}

BEGIN_MESSAGE_MAP(LegoModelDirectoryDialog, CModalDialog)
    ON_COMMAND(IDC_BROWSE, OnBrowse)
    ON_COMMAND(IDC_MODELS, OnModels)
    ON_EN_CHANGE(IDC_DIRECTORY, OnDirectoryChange)
END_MESSAGE_MAP()

LegoMeshDialog::LegoMeshDialog()
    :
    CModalDialog(IDD_MESH)
{
}

BOOL 
LegoMeshDialog::OnInitDialog()
{
    CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
    LegoU32 n = GetMeshCount3ds(g_convert->GetStudioFile()->GetDatabase());
    for (LegoU32 i = 0; i < n; i++) {
        mesh3ds* studioMesh = NULL;
        GetMeshByIndex3ds(g_convert->GetStudioFile()->GetDatabase(), i, &studioMesh);
        listBox->AddString(studioMesh->name);
        RelMeshObj3ds(&studioMesh);
    }
    UpdateControls();
    return TRUE;
}

void 
LegoMeshDialog::OnSave()
{
    CFileDialog dialog(
        FALSE, 
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Mesh Files (*.msh)|*.msh|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        CWaitCursor cursor;
        convertApp.UpdateStackingChain(this);
        LegoFile* storage = new LegoFile();
        storage->Open(dialog.GetPathName(), LegoFile::c_write);
        CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
        LegoU32 numSelected = listBox->GetSelCount();
        LegoU32* selections = new LegoU32[numSelected];
        listBox->GetSelItems(numSelected, (int*) selections);
        storage->Write(&numSelected, sizeof(numSelected));
        for (LegoU32 i = 0; i < numSelected; i++) {
            CString name;
            listBox->GetText(selections[i], name);
            mesh3ds* studioMesh = NULL;
            GetMeshByName3ds(g_convert->GetStudioFile()->GetDatabase(), (char*) (const char*) name, &studioMesh);
            LegoMesh* legoMesh = g_convert->CreateMesh(g_convert->GetStudioFile()->GetDatabase(), studioMesh, ".");
            legoMesh->Write(storage);
            delete legoMesh;
            RelMeshObj3ds(&studioMesh);
        }
        delete [] selections;
        delete storage;
    }
}

void 
LegoMeshDialog::OnClose()
{
    EndDialog(IDC_CLOSE);
}

void 
LegoMeshDialog::OnSelChange()
{
    UpdateControls();
}

void
LegoMeshDialog::UpdateControls()
{
    GetDlgItem(IDC_SAVE)->EnableWindow(((CListBox*) GetDlgItem(IDC_LIST))->GetSelCount());
}

BEGIN_MESSAGE_MAP(LegoMeshDialog, CModalDialog)
    ON_COMMAND(IDC_SAVE, OnSave)
    ON_COMMAND(IDC_CLOSE, OnClose)
    ON_LBN_SELCHANGE(IDC_LIST, OnSelChange)
END_MESSAGE_MAP()

LegoTextureDialog::LegoTextureDialog()
    :
    CModalDialog(IDD_TEXTURE)
{
}

BOOL 
LegoTextureDialog::OnInitDialog()
{
    CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
    LegoU32 n = GetMaterialCount3ds(g_convert->GetStudioFile()->GetDatabase());
    for (LegoU32 i = 0; i < n; i++) {
        material3ds* studioMaterial = NULL;
        GetMaterialByIndex3ds(g_convert->GetStudioFile()->GetDatabase(), i, &studioMaterial);
        char* name = studioMaterial->texture.map.name;
        if (strlen(name) > 4 && stricmp(name + strlen(name) - 4, ".gif") == 0) {
            int j = listBox->AddString(name);
            listBox->SetItemData(j, i);
        }
        ReleaseMaterial3ds(&studioMaterial);
    }
    UpdateControls();
    return TRUE;
}

void 
LegoTextureDialog::OnSave()
{
    CFileDialog dialog(
        FALSE, 
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Texture Files (*.tex)|*.tex|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        CWaitCursor cursor;
        convertApp.UpdateStackingChain(this);
        LegoFile* storage = new LegoFile();
        storage->Open(dialog.GetPathName(), LegoFile::c_write);
        CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
        LegoU32 numSelected = listBox->GetSelCount();
        LegoU32* selections = new LegoU32[numSelected];
        listBox->GetSelItems(numSelected, (int*) selections);
        storage->Write(&numSelected, sizeof(numSelected));
        for (LegoU32 i = 0; i < numSelected; i++) {
            CString name;
            listBox->GetText(selections[i], name);
            LegoTexture* texture = g_convert->CreateTexture(name);
            if (!texture) {
                g_convert->Message("Unable to read texture %s; skipping...", (const char*) name);
                goto next;
            }
            texture->Write(storage);
next:
            delete texture;
        }
        delete [] selections;
        delete storage;
    }
}

void 
LegoTextureDialog::OnClose()
{
    EndDialog(IDC_CLOSE);
}

void 
LegoTextureDialog::OnSelChange()
{
    UpdateControls();
}

void
LegoTextureDialog::UpdateControls()
{
    GetDlgItem(IDC_SAVE)->EnableWindow(((CListBox*) GetDlgItem(IDC_LIST))->GetSelCount());
}

BEGIN_MESSAGE_MAP(LegoTextureDialog, CModalDialog)
    ON_COMMAND(IDC_SAVE, OnSave)
    ON_COMMAND(IDC_CLOSE, OnClose)
    ON_LBN_SELCHANGE(IDC_LIST, OnSelChange)
END_MESSAGE_MAP()

LegoAnimationDialog::LegoAnimationDialog()
    :
    CModalDialog(IDD_ANIMATION)
{
}

BOOL 
LegoAnimationDialog::OnInitDialog()
{
    CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
    LegoU32 n = GetObjectNodeCount3ds(g_convert->GetStudioFile()->GetDatabase());
    for (LegoU32 i = 0; i < n; i++) {
        kfmesh3ds* studioNode = NULL;
        GetObjectMotionByIndex3ds(g_convert->GetStudioFile()->GetDatabase(), i, &studioNode);
        CString name = studioNode->name;
        if (studioNode->instance[0]) {
            name += ".";
            name += studioNode->instance;
        }
        listBox->AddString(name);
        ReleaseObjectMotion3ds(&studioNode);
    }
    UpdateControls();
    return TRUE;
}

void 
LegoAnimationDialog::OnSave()
{
    CFileDialog dialog(
        FALSE, 
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Animation Files (*.ani)|*.ani|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        CWaitCursor cursor;
        convertApp.UpdateStackingChain(this);
        CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
        LegoU32 numSelected = listBox->GetSelCount();
        LegoU32* selections = new LegoU32[numSelected];
        listBox->GetSelItems(numSelected, (int*) selections);
        LegoTreeNodeInfo* info = new LegoTreeNodeInfo[numSelected];
        LegoU32 i;
        for (i = 0; i < numSelected; i++) {
            CString name;
            listBox->GetText(selections[i], name);
            info[i].SetNodeName(name);
            kfmesh3ds* studioNode = NULL;
            GetObjectMotionByName3ds(g_convert->GetStudioFile()->GetDatabase(), (char*) (const char*) name, &studioNode);
            info[i].SetParentName(studioNode->parent);
            ReleaseObjectMotion3ds(&studioNode);
        }
        LegoAnimBuilder* builder = new LegoAnimBuilder();
        builder->Build(info, numSelected);
        for (i = 0; i < numSelected; i++) {
            if (info[i].GetNode()) {
                kfmesh3ds* studioNode = NULL;
                GetObjectMotionByName3ds(g_convert->GetStudioFile()->GetDatabase(), (char*) info[i].GetNodeName(), &studioNode);
                LegoAnimNodeData* data = g_convert->CreateAnimNodeData(g_convert->GetStudioFile()->GetDatabase(), studioNode);
                info[i].GetNode()->SetData(data);
                ReleaseObjectMotion3ds(&studioNode);
            }
        }
        for (i = 0; i < builder->GetNumTrees(); i++) {
            LegoAnim* anim = (LegoAnim*) builder->GetTree(i);
            anim->CalculateDuration();
        }
        LegoFile* storage = new LegoFile();
        storage->Open(dialog.GetPathName(), LegoFile::c_write);
        LegoU32 numTrees = builder->GetNumTrees();
        storage->Write(&numTrees, sizeof(numTrees));
        for (i = 0; i < builder->GetNumTrees(); i++) {
            builder->GetTree(i)->Write(storage);
        }
        delete storage;
        delete builder;
        delete [] info;
        delete [] selections;
    }
}

void 
LegoAnimationDialog::OnClose()
{
    EndDialog(IDC_CLOSE);
}

void 
LegoAnimationDialog::OnSelChange()
{
    UpdateControls();
}

void
LegoAnimationDialog::UpdateControls()
{
    GetDlgItem(IDC_SAVE)->EnableWindow(((CListBox*) GetDlgItem(IDC_LIST))->GetSelCount());
}

BEGIN_MESSAGE_MAP(LegoAnimationDialog, CModalDialog)
    ON_COMMAND(IDC_SAVE, OnSave)
    ON_COMMAND(IDC_CLOSE, OnClose)
    ON_LBN_SELCHANGE(IDC_LIST, OnSelChange)
END_MESSAGE_MAP()

LegoModelDialog::LegoModelDialog()
    :
    CModalDialog(IDD_MODEL)
{
}

BOOL 
LegoModelDialog::OnInitDialog()
{
    CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
    LegoModelList* modelList = g_convert->GetModelDirectory()->GetModelList();
    for (POSITION pos = modelList->GetHeadPosition(); pos; modelList->GetNext(pos)) {
        LegoModel* model = modelList->GetAt(pos);
        listBox->AddString(model->GetModelName());
    }
    UpdateControls();
    return TRUE;
}

void 
LegoModelDialog::OnSave()
{
    CFileDialog dialog(
        FALSE, 
        NULL, 
        NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        "Model Files (*.mod)|*.mod|All Files (*.*)|*.*||",
        this
    );
    if (dialog.DoModal() == IDOK) {
        CWaitCursor cursor;
        convertApp.UpdateStackingChain(this);
        CListBox* listBox = (CListBox*) GetDlgItem(IDC_LIST);
        LegoU32 numSelected = listBox->GetSelCount();
        LegoU32* selections = new LegoU32[numSelected];
        listBox->GetSelItems(numSelected, (int*) selections);
        CStringList modelList;
        for (LegoU32 i = 0; i < numSelected; i++) {
            CString modelName;
            listBox->GetText(selections[i], modelName);
            modelList.AddTail(modelName);
        }
        delete [] selections;
        g_convert->CreateModelFile(dialog.GetPathName(), modelList);
    }
}

void 
LegoModelDialog::OnClose()
{
    EndDialog(IDC_CLOSE);
}

void 
LegoModelDialog::OnSelChange()
{
    UpdateControls();
}

void
LegoModelDialog::UpdateControls()
{
    GetDlgItem(IDC_SAVE)->EnableWindow(((CListBox*) GetDlgItem(IDC_LIST))->GetSelCount());
}

BEGIN_MESSAGE_MAP(LegoModelDialog, CModalDialog)
    ON_COMMAND(IDC_SAVE, OnSave)
    ON_COMMAND(IDC_CLOSE, OnClose)
    ON_LBN_SELCHANGE(IDC_LIST, OnSelChange)
END_MESSAGE_MAP()

LegoOpenModelDirectoryDialog::LegoOpenModelDirectoryDialog()
    :
    CModalDialog(IDD_OPENMODELDIRECTORY)
{
}

void 
LegoOpenModelDirectoryDialog::OnOK()
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    HTREEITEM item = tree->GetSelectedItem();
    CString path = GetItemPath(item);
    m_name = path.Left(path.GetLength() - 1);
    EndDialog(IDOK);
}

BOOL 
LegoOpenModelDirectoryDialog::OnInitDialog()
{
    InitTree();
    UpdateControls();
    return TRUE;
}

void 
LegoOpenModelDirectoryDialog::OnSelChanged()
{
    UpdateControls();
}

void 
LegoOpenModelDirectoryDialog::OnItemExpanding(HTREEITEM p_item)
{
    CWaitCursor cursor;
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    if (p_item == tree->GetRootItem()) {
        return;
    }
    HTREEITEM item;
    while (item = tree->GetChildItem(p_item)) {
        tree->DeleteItem(item);
    }
    CString path = GetItemPath(p_item);
    path += "*.*";
    HANDLE findHandle;
    WIN32_FIND_DATA findData;
    if ((findHandle = FindFirstFile(path, &findData)) != INVALID_HANDLE_VALUE) {
        path = path.Left(path.GetLength() - 3);
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && findData.cFileName[0] != '.') {
                item = tree->InsertItem(findData.cFileName, p_item);
                tree->SetItemImage(item, m_closedFolder, m_openFolder);
                if (HasSubdirectories(path + findData.cFileName)) {
                    tree->InsertItem("", item);
                }
            }
        } while (FindNextFile(findHandle, &findData));
        FindClose(findHandle);
    }
    tree->SortChildren(p_item);
}

void 
LegoOpenModelDirectoryDialog::OnItemCollapsing(HTREEITEM p_item)
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    if (p_item == tree->GetRootItem()) {
        return;
    }
    HTREEITEM item;
    while (item = tree->GetChildItem(p_item)) {
        tree->DeleteItem(item);
    }
    tree->InsertItem("", p_item);
}

BOOL 
LegoOpenModelDirectoryDialog::OnNotify(WPARAM p_param1, LPARAM p_param2, LRESULT* p_result)
{
    BOOL result = FALSE;
    if (p_param1 == IDC_TREE) {
        NM_TREEVIEW* nmtv = (NM_TREEVIEW*) p_param2;
        switch (nmtv->hdr.code) {
        case TVN_ITEMEXPANDING:
            switch (nmtv->action) {
            case TVE_COLLAPSE:
                OnItemCollapsing(nmtv->itemNew.hItem);
                break;
            case TVE_EXPAND:
                OnItemExpanding(nmtv->itemNew.hItem);
                break;
            }
            *p_result = FALSE;
            result = TRUE;
            break;
        case TVN_SELCHANGED:
            OnSelChanged();
            break;
        }
    }
    return result;
}

void 
LegoOpenModelDirectoryDialog::OnDestroy()
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    CImageList* imageList = tree->SetImageList(NULL, TVSIL_NORMAL);
    delete imageList;
}

void
LegoOpenModelDirectoryDialog::UpdateControls()
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    HTREEITEM item = tree->GetSelectedItem();
    GetDlgItem(IDOK)->EnableWindow(item && item != tree->GetRootItem());
}

void
LegoOpenModelDirectoryDialog::InitTree()
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    CImageList* imageList = CreateImageList();
    tree->SetImageList(imageList, TVSIL_NORMAL);
    HTREEITEM root = tree->InsertItem("My Computer");
    tree->SetItemImage(root, m_computer, m_computer);
    char buffer[105];
    GetLogicalDriveStrings(sizeof(buffer), buffer);
    char* p = buffer;
    char string[5];
    strcpy(string, "( :)");
    while (*p) {
        string[1] = toupper(*p);
        HTREEITEM item = tree->InsertItem(string, root);
        int image;
        switch (GetDriveType(p)) {
        case DRIVE_REMOVABLE:
            image = m_removableDrive;
            break;
        case DRIVE_FIXED:
            image = m_fixedDrive;
            break;
        case DRIVE_REMOTE:
            image = m_remoteDrive;
            break;
        case DRIVE_CDROM:
            image = m_cdROMDrive;
            break;
        default:
            image = m_fixedDrive;
            break;
        }
        tree->SetItemImage(item, image, image);
        tree->InsertItem("", item);
        p += strlen(p) + 1;
    }
    char dir[256];
    GetCurrentDirectory(sizeof(dir), dir);
    ExpandPath(dir);
}

void
LegoOpenModelDirectoryDialog::ExpandPath(char* p_path)
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    HTREEITEM root = tree->GetRootItem();
    tree->Expand(root, TVE_EXPAND);
    char* s = p_path;
    char* t = strchr(s, '\\');
    *t = '\0';
    HTREEITEM parent = FindDrive(s);
    tree->Expand(parent, TVE_EXPAND);
    s = t + 1;
    while (*s) {
        t = strchr(s, '\\');
        if (t) {
            *t = '\0';
        }
        HTREEITEM item = FindDirectory(parent, s);
        if (!item) {
            item = tree->InsertItem(s, parent);
        }
        tree->Expand(item, TVE_EXPAND);
        parent = item;
        if (t) {
            s = t + 1;
        }
        else {
            s += strlen(s);
        }
    }
}

HTREEITEM
LegoOpenModelDirectoryDialog::FindDrive(char* p_drive)
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    HTREEITEM root = tree->GetRootItem();
    HTREEITEM item = tree->GetChildItem(root);
    while (item) {
        CString drive = tree->GetItemText(item);
        if (toupper(drive[1]) == toupper(p_drive[0])) {
            return item;
        }
        item = tree->GetNextSiblingItem(item);
    }
    return NULL;
}

HTREEITEM
LegoOpenModelDirectoryDialog::FindDirectory(HTREEITEM p_parent, char* p_directory)
{
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    HTREEITEM item = tree->GetChildItem(p_parent);
    while (item) {
        CString directory = tree->GetItemText(item);
        if (directory.CompareNoCase(p_directory) == 0) {
            return item;
        }
        item = tree->GetNextSiblingItem(item);
    }
    return NULL;
}

CString 
LegoOpenModelDirectoryDialog::GetItemPath(HTREEITEM p_item)
{
    CString path = "";
    CTreeCtrl* tree = (CTreeCtrl*) GetDlgItem(IDC_TREE);
    for (;;) {
        CString dir = tree->GetItemText(p_item);
        if (dir[0] == '(') {
            path = dir.Mid(1, 2) + "\\" + path;
            break;
        }
        else {
            path = dir + "\\" + path;
        }
        p_item = tree->GetParentItem(p_item);
    }
    return path;
}

LegoBool 
LegoOpenModelDirectoryDialog::HasSubdirectories(const char* p_directory)
{
    LegoBool result = FALSE;
    CString path = p_directory;
    if (path.Right(1) != "\\") {
        path += "\\";
    }
    path += "*.*";
    HANDLE findHandle;
    WIN32_FIND_DATA findData;
    if ((findHandle = FindFirstFile(path, &findData)) != INVALID_HANDLE_VALUE) {
        do {
            if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY && findData.cFileName[0] != '.') {
                result = TRUE;
                break;
            }
        } while (FindNextFile(findHandle, &findData));
        FindClose(findHandle);
    }
    return result;
}

CImageList*
LegoOpenModelDirectoryDialog::CreateImageList()
{
    CImageList* imageList = new CImageList();

    imageList->Create(16, 16, TRUE, 8, 8);

    HICON icon;

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_CDROMDRIVE), 
        IMAGE_ICON, 16, 16, 0
    );
    m_cdROMDrive = imageList->Add(icon);

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_CLOSEDFOLDER), 
        IMAGE_ICON, 16, 16, 0
    );
    m_closedFolder = imageList->Add(icon);

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_COMPUTER), 
        IMAGE_ICON, 16, 16, 0
    );
    m_computer = imageList->Add(icon);

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_FIXEDDRIVE), 
        IMAGE_ICON, 16, 16, 0
    );
    m_fixedDrive = imageList->Add(icon);

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_OPENFOLDER), 
        IMAGE_ICON, 16, 16, 0
    );
    m_openFolder = imageList->Add(icon);

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_REMOTEDRIVE), 
        IMAGE_ICON, 16, 16, 0
    );
    m_remoteDrive = imageList->Add(icon);

    icon = (HICON) LoadImage(
        AfxGetInstanceHandle(), 
        MAKEINTRESOURCE(IDI_REMOVABLEDRIVE), 
        IMAGE_ICON, 16, 16, 0
    );
    m_removableDrive = imageList->Add(icon);

    return imageList;
}

BEGIN_MESSAGE_MAP(LegoOpenModelDirectoryDialog, CModalDialog)
    ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL 
LegoConvertApp::InitInstance()
{
    g_convert = new LegoConvert();
    LegoConvertDialog dialog;
    dialog.DoModal();
    delete g_convert;
    return FALSE;
}

int
LegoConvertApp::ExitInstance()
{
    return 0;
}

void 
LegoConvertApp::UpdateStackingChain(CWnd* p_top)
{
    while (p_top) {
        p_top->UpdateWindow();
        p_top = p_top->GetOwner();
    }
}

