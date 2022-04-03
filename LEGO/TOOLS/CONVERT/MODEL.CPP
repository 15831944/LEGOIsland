#include <afxdlgs.h>
#include <math.h>
#include "model.h"
#include "convert.h"
#include "script.h"
#include "LegoMesh.h"
#include "LegoAnim.h"
#include "LegoStorage.h"
#include "LegoSphere.h"
#include "LegoVector.h"
#include "LegoUtil.h"
#undef TRACE2
#undef TRACE3
#include "vec.h"
extern "C" {
#include "3dsftk.h"
}

LegoModel::LegoModel()
{
    m_lodList = new LegoLODList();
    m_compList = new LegoModelList();
    m_box.SetMin(LegoVertex(888888.0F, 888888.0F, 888888.0F));
    m_box.SetMax(LegoVertex(-888888.0F, -888888.0F, -888888.0F));
    m_haveBounds = FALSE;
}

LegoModel::~LegoModel()
{
    Close();
    delete m_lodList;
    delete m_compList;
}

LegoBool 
LegoModel::Open(const char* p_dir, const char* p_modelName)
{
    CString path;
    path = p_dir;
    path += "\\structure.ini";
    LegoScript script;
    if (!script.Open(path)) {
        return FALSE;
    }
    CStringList keyList;
    script.EnumKeys(p_modelName, keyList);
    CString entry;
    if (keyList.IsEmpty()) {
        entry = p_modelName;
    }
    else {
        for (POSITION pos = keyList.GetHeadPosition(); pos; keyList.GetNext(pos)) {
            CString key = keyList.GetAt(pos);
            script.GetEntry(p_modelName, key, entry);
            CString dummy;
            if (!script.GetEntry(p_modelName, entry, dummy)) {
                break;
            }
        }
        if (!pos) {
            return FALSE;
        }
    }
    return Open(p_dir, p_modelName, entry);
}

LegoBool 
LegoModel::Open(const char* p_dir, const char* p_modelName, const char* p_nodeName)
{
    m_modelName = p_modelName;
    m_nodeName = p_nodeName;
    HANDLE findHandle;
    WIN32_FIND_DATA findData;
    CString path;
    path = p_dir;
    path += "\\";
    path += p_modelName;
    path += "\\";
    path += p_nodeName;
    path += "\\*.3ds";
    if ((findHandle = FindFirstFile(path, &findData)) == INVALID_HANDLE_VALUE) {
        return FALSE;
    }
    do {
        if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            m_lodList->Insert(findData.cFileName);
        }
    } while (FindNextFile(findHandle, &findData));
    FindClose(findHandle);
    path = p_dir;
    path += "\\structure.ini";
    LegoScript script;
    if (!script.Open(path)) {
        return FALSE;
    }
    CStringList keyList;
    script.EnumKeys(p_modelName, keyList);
    for (POSITION pos = keyList.GetHeadPosition(); pos; keyList.GetNext(pos)) {
        CString key = keyList.GetAt(pos);
        CString entry;
        script.GetEntry(p_modelName, key, entry);
        if (entry == p_nodeName) {
            LegoModel* model = new LegoModel();
            if (model->Open(p_dir, p_modelName, key)) {
                m_compList->AddTail(model);
            }
            else {
                delete model;
            }
        }
    }
    return TRUE;
}


void 
LegoModel::Close()
{
    if (m_compList) {
        for (POSITION pos = m_compList->GetHeadPosition(); pos; m_compList->GetNext(pos)) {
            LegoModel* model = m_compList->GetAt(pos);
            delete model;
        }
        m_compList->RemoveAll();
    }
}

LegoBool
LegoModel::Write(LegoStorage* p_storage, const char* p_dir)
{
    LegoBool ok = FALSE;
    POSITION pos;
    LegoU32 count;
    LegoModel* model;
    LegoSphere sphere;
    LegoFloat d;
    LegoVertex center;
    LegoU32 length;

    length = m_nodeName.GetLength();
    p_storage->Write(&length, sizeof(length));
    p_storage->Write((void*) (const char*) m_nodeName, length);
    
    GetBounds(p_dir);
    center = m_box.GetCenter();
    sphere.SetCenter(center);

	d = (LegoFloat) (sqrt(
		m_box.GetDX() * m_box.GetDX()+ 
		m_box.GetDY() * m_box.GetDY()+
		m_box.GetDZ() * m_box.GetDZ())/2.);

	sphere.SetRadius(d);

    // d = Max(m_box.GetDX(), m_box.GetDY(), m_box.GetDZ()) / 2;
    // sphere.SetRadius((LegoFloat) sqrt(3 * d * d));
    sphere.Write(p_storage);

    if (!WriteLOD(p_storage, p_dir)) {
        goto done;
    }

    count = m_compList->GetCount();
    p_storage->Write(&count, sizeof(count));
    for (pos = m_compList->GetHeadPosition(); pos; m_compList->GetNext(pos)) {
        model = m_compList->GetAt(pos);
        if (!model->Write(p_storage, p_dir)) {
            goto done;
        }
    }

    ok = TRUE;

done:
    return ok;
}

void
LegoModel::GetBounds(const char* p_dir)
{
    if (!m_haveBounds) {
        if (!FindBounds(p_dir)) {
            CalculateBounds(p_dir);
        }
        m_haveBounds = TRUE;
    }
}

LegoBool
LegoModel::FindBounds(const char* p_dir)
{
    LegoBool ok = FALSE;
    LegoU32 i;
    HANDLE findHandle;
    WIN32_FIND_DATA findData;
    CString path;
    dbtype3ds type;
    LegoMesh* legoMesh;
    mesh3ds* studioMesh = NULL;
    file3ds* studioFile = NULL;
    database3ds* database = NULL;

    path = p_dir;
    path += "\\";
    path += m_modelName;
    path += "\\";
    path += m_nodeName;
    path += "\\box\\*.3ds";
    if ((findHandle = FindFirstFile(path, &findData)) == INVALID_HANDLE_VALUE) {
        goto done;
    }
    FindClose(findHandle);
    path = p_dir;
    path += "\\";
    path += m_modelName;
    path += "\\";
    path += m_nodeName;
    path += "\\box\\";
    path += findData.cFileName;
    if (!(studioFile = OpenFile3ds(path, "r"))) {
        goto done;
    }
    InitDatabase3ds(&database);
    CreateDatabase3ds(studioFile, database);
    type = GetDatabaseType3ds(database);
    if (type != MeshFile) {
        goto done;
    }
    if (!GetMeshCount3ds(database)) {
        goto done;
    }
    GetMeshByIndex3ds(database, 0, &studioMesh);
    legoMesh = g_convert->CreateMesh(database, studioMesh, NULL);
    RelMeshObj3ds(&studioMesh);
    for (i = 0; i < legoMesh->GetNumVertices(); i++) {
        m_box.AddVertex(legoMesh->GetVertex(i));
    }
    delete legoMesh;

    ok = TRUE;

done:
    if (database) {
        ReleaseDatabase3ds(&database);
    }
    if (studioFile) {
        CloseFile3ds(studioFile);
    }
    return ok;
}

void
LegoModel::CalculateBounds(const char* p_dir)
{
    LegoBool ok = FALSE;
    LegoU32 i, j;
    POSITION pos;
    CString fileName;
    CString path;
    LegoU32 count;
    dbtype3ds type;
    LegoMesh* legoMesh;
    LegoVertex vertex;
    LegoBox box;
    mesh3ds* studioMesh = NULL;
    file3ds* studioFile = NULL;
    database3ds* database = NULL;

    for (pos = m_lodList->GetHeadPosition(); pos; m_lodList->GetNext(pos)) {
        fileName = m_lodList->GetAt(pos);
        path = p_dir;
        path += "\\";
        path += m_modelName;
        path += "\\";
        path += m_nodeName;
        path += "\\";
        path += fileName;
        if (!(studioFile = OpenFile3ds(path, "r"))) {
            g_convert->Message("Unable to open file %s; skipping...", path);
            goto next;
        }
        InitDatabase3ds(&database);
        CreateDatabase3ds(studioFile, database);
        type = GetDatabaseType3ds(database);
        if (type != MeshFile) {
            g_convert->Message("File %s is not a mesh file; skipping...", path);
            goto next;
        }
        count = GetMeshCount3ds(database);
        for (i = 0; i < count; i++) {
            GetMeshByIndex3ds(database, i, &studioMesh);
            legoMesh = g_convert->CreateMesh(database, studioMesh, NULL);
            RelMeshObj3ds(&studioMesh);
            studioMesh = NULL;
            for (j = 0; j < legoMesh->GetNumVertices(); j++) {
                vertex = legoMesh->GetVertex(j);
                m_box.AddVertex(vertex);
            }
            delete legoMesh;
        }
next:
        if (database) {
            ReleaseDatabase3ds(&database);
            database = NULL;
        }
        if (studioFile) {
            CloseFile3ds(studioFile);
            studioFile = NULL;
        }
    }
}

LegoBool 
LegoModel::WriteLOD(LegoStorage* p_storage, const char* p_dir)
{
    LegoBool ok = FALSE;
    LegoU32 i, j, k, l;
    POSITION pos;
    CString fileName;
    CString path;
    LegoU32 count;
    dbtype3ds type;
    LegoMesh* legoMesh;
    LegoU32 numVertices = 0;
    LegoU32 numPolygons = 0;
    LegoFloat polygonArea = 0.0F;
    LegoU32 numCosts = 0;
    LegoFloat vertices[3][3];
    mesh3ds* studioMesh = NULL;
    file3ds* studioFile = NULL;
    database3ds* database = NULL;

    count = m_lodList->GetCount();
    p_storage->Write(&count, sizeof(count));
    for (pos = m_lodList->GetHeadPosition(); pos; m_lodList->GetNext(pos)) {
        fileName = m_lodList->GetAt(pos);
        path = p_dir;
        path += "\\";
        path += m_modelName;
        path += "\\";
        path += m_nodeName;
        path += "\\";
        path += fileName;
        if (!(studioFile = OpenFile3ds(path, "r"))) {
            g_convert->Message("Unable to open file %s; skipping...", path);
            goto next;
        }
        InitDatabase3ds(&database);
        CreateDatabase3ds(studioFile, database);
        type = GetDatabaseType3ds(database);
        if (type != MeshFile) {
            g_convert->Message("File %s is not a mesh file; skipping...", path);
            goto next;
        }
        numVertices = 0;
        numPolygons = 0;
        polygonArea = 0.0F;
        count = GetMeshCount3ds(database);
        for (i = 0; i < count; i++) {
            GetMeshByIndex3ds(database, i, &studioMesh);
            legoMesh = g_convert->CreateMesh(database, studioMesh, NULL);
            RelMeshObj3ds(&studioMesh);
            studioMesh = NULL;
            numVertices += legoMesh->GetNumVertices();
            numPolygons += legoMesh->GetNumFaces();
            for (j = 0; j < legoMesh->GetNumFaces(); j++) {
                for (k = 0; k < 3; k++) {
                    for (l = 0; l < 3; l++) {
                        vertices[k][l] = legoMesh->GetVertex(legoMesh->GetFace(j).GetVertexIndex(k)).GetCoordinate(l);
                    }
                }
                polygonArea += TriangleArea(vertices);
            }
            delete legoMesh;
        }
        polygonArea /= numPolygons;
        p_storage->Write(&numVertices, sizeof(numVertices));
        p_storage->Write(&polygonArea, sizeof(polygonArea));
        p_storage->Write(&numCosts, sizeof(numCosts));
        p_storage->Write(&count, sizeof(count));
        for (i = 0; i < count; i++) {
            GetMeshByIndex3ds(database, i, &studioMesh);
            CString texureDirectory = g_convert->GetModelDirectory()->GetName() + "\\Texture";
            legoMesh = g_convert->CreateMesh(database, studioMesh, texureDirectory);
            RelMeshObj3ds(&studioMesh);
            studioMesh = NULL;
            legoMesh->Write(p_storage);
            delete legoMesh;
        }
next:
        if (database) {
            ReleaseDatabase3ds(&database);
            database = NULL;
        }
        if (studioFile) {
            CloseFile3ds(studioFile);
            studioFile = NULL;
        }
    }

    ok = TRUE;

    return ok;
}

LegoFloat 
LegoModel::TriangleArea(LegoFloat p_vertices[][3])
{
    LegoVectorF3 vectors[2], cross;
    VMV3(vectors[0], p_vertices[1], p_vertices[0]);
    VMV3(vectors[1], p_vertices[2], p_vertices[0]);
    VXV3(cross, vectors[0], vectors[1]);
    return (LegoFloat) sqrt(NORMSQRD3(cross)) / 2.0F;
}

    LegoModelDirectory::LegoModelDirectory()
{
    m_modelList = new LegoModelList();
}

void 
LegoLODList::Insert(const char* p_fileName)
{
    POSITION pos;
    for (pos = GetHeadPosition(); pos && GetAt(pos) > p_fileName; GetNext(pos));
    if (pos) {
        InsertBefore(pos, p_fileName);
    }
    else {
        AddTail(p_fileName);
    }
}


LegoModelDirectory::~LegoModelDirectory()
{
    Close();
    delete m_modelList;
}

LegoBool 
LegoModelDirectory::Open(const char* p_name)
{
    m_name = p_name;
    CString path;
    path = m_name;
    path += "\\structure.ini";
    LegoScript script;
    if (!script.Open(path)) {
        return FALSE;
    }
    CStringList sectionList;
    script.EnumSections(sectionList);
    for (POSITION pos = sectionList.GetHeadPosition(); pos; sectionList.GetNext(pos)) {
        LegoModel* model = new LegoModel();
        if (model->Open(m_name, sectionList.GetAt(pos))) {
            m_modelList->AddTail(model);
        }
        else {
            delete model;
        }
    }
    return TRUE;
}

void 
LegoModelDirectory::Close()
{
    if (m_modelList) {
        for (POSITION pos = m_modelList->GetHeadPosition(); pos; m_modelList->GetNext(pos)) {
            LegoModel* model = m_modelList->GetAt(pos);
            delete model;
        }
        m_modelList->RemoveAll();
    }
}

LegoBool 
LegoModelDirectory::Write(LegoStorage* p_storage, LegoModel* p_model)
{
    LegoBool ok = FALSE;
    LegoAnim* anim = NULL;
    
    if (!(anim = CreateAnim(p_model))) {
        g_convert->Message("Unable to create animation");
        goto done;
    }
    anim->Write(p_storage);
    if (!p_model->Write(p_storage, m_name)) {
        g_convert->Message("Unable to write model");
        goto done;
    }

    ok = TRUE;

done:
    if (anim) {
        delete anim;
    }
    return ok;
}

LegoU32 
LegoModelDirectory::GetNumModels()
{
    return m_modelList->GetCount();
}

LegoModel* 
LegoModelDirectory::GetModel(const char* p_modelName)
{
    for (POSITION pos = m_modelList->GetHeadPosition(); pos; m_modelList->GetNext(pos)) {
        LegoModel* model = m_modelList->GetAt(pos);
        if (stricmp(model->GetModelName(), p_modelName) == 0) {
            return model;
        }
    }
    return NULL;
}

LegoAnim*
LegoModelDirectory::CreateAnim(LegoModel* p_model)
{
    LegoAnim* anim = NULL;
    LegoU32 i;
    CString path;
    CString name;
    LegoU32 count;
    LegoU32 n;
    dbtype3ds type;
    LegoTreeNodeInfo* info;
    LegoAnimBuilder* builder = NULL;
    file3ds* studioFile = NULL;
    database3ds* database = NULL;
    kfmesh3ds* studioNode = NULL;

    path = m_name;
    path += "\\";
    path += p_model->GetModelName();
    path += "\\anim\\neutral.3ds";
    studioFile = OpenFile3ds(path, "r");
    if (!studioFile) {
        g_convert->Message("Unable to open file %s...", path);
        goto done;
    }
    InitDatabase3ds(&database);
    CreateDatabase3ds(studioFile, database);
    type = GetDatabaseType3ds(database);
    if (type != MeshFile) {
        g_convert->Message("File %s is not a mesh file", path);
        goto done;
    }
    count = GetObjectNodeCount3ds(database);
    info = new LegoTreeNodeInfo[count];
    n = 0;
    for (i = 0; i < count; i++) {
        GetObjectMotionByIndex3ds(database, i, &studioNode);
        if (strcmp(studioNode->name, "$$$DUMMY") == 0) {
            name = studioNode->name;
            name += ".";
            name += studioNode->instance;
            info[n].SetNodeName(name);
            info[n].SetParentName(studioNode->parent);
            n++;
        }
        ReleaseObjectMotion3ds(&studioNode);
        studioNode = NULL;
    }
    builder = new LegoAnimBuilder();
    builder->Build(info, n);
    for (i = 0; i < n; i++) {
        if (info[i].GetNode()) {
            GetObjectMotionByName3ds(database, info[i].GetNodeName(), &studioNode);
            LegoAnimNodeData* data = g_convert->CreateAnimNodeData(database, studioNode);
            info[i].GetNode()->SetData(data);
            ReleaseObjectMotion3ds(&studioNode);
            studioNode = NULL;
        }
    }
    delete [] info;
    if (builder->GetNumTrees() != 1) {
        g_convert->Message("File contains %d animation trees (expected 1)", builder->GetNumTrees());
        goto done;
    }
    anim = (LegoAnim*) builder->GetTree(0);
    builder->SetNumTrees(0);

done:
    if (builder) {
        delete builder;
    }
    if (database) {
        ReleaseDatabase3ds(&database);
    }
    if (studioFile) {
        CloseFile3ds(studioFile);
    }
    return anim;
}

LegoBool
LegoModelDirectory::MatchAnimToModel(LegoAnim* p_anim, LegoModel* p_model)
{
    LegoTreeNode* animNode;
    LegoAnimNodeData* animNodeData;

    if (!(animNode = p_anim->GetRoot())) {
        g_convert->Message("Cannot locate neutral.3ds root animation");
	    return FALSE;
    }
    if (!(animNodeData = (LegoAnimNodeData*) animNode->GetData())) {
        g_convert->Message("Cannot locate neutral.3ds animation data");
        return FALSE;
    }
    if (stricmp(animNodeData->GetName(), p_model->GetNodeName()) != 0) {
        g_convert->Message("Neutral.3ds animation name(%s) mismatches model name(%s)",
					animNodeData->GetName(),
					p_model->GetNodeName());
        return FALSE;
    }
    return MatchAnimToModel(animNode, p_model);
}

LegoBool
LegoModelDirectory::MatchAnimToModel(LegoTreeNode* p_animNode, LegoModel* p_model)
{
    LegoU32 i, j;
    POSITION pos;
    LegoModelList* compList = p_model->GetCompList();

    if (p_animNode->GetNumChildren() != (LegoU32) compList->GetCount()) {
        g_convert->Message("Neutral.3ds kid count (%d) of (%s) mismatches model kid count(%d)",
					p_animNode->GetNumChildren(),
					p_model->GetNodeName(),
					(LegoU32) compList->GetCount())
					;
        return FALSE;
    }
    for (pos = compList->GetHeadPosition(), i = 0; pos; compList->GetNext(pos), i++) {
        LegoModel* model = compList->GetAt(pos);
        const char* modelName = strrchr(model->GetNodeName(), '\\');
        if (modelName) {
            modelName++;
        }
        else {
            modelName = model->GetNodeName();
        }
        for (j = i; j < p_animNode->GetNumChildren(); j++) {
            LegoAnimNodeData* data = (LegoAnimNodeData*) p_animNode->GetChild(j)->GetData();
            if (stricmp(modelName, data->GetName()) == 0) {
                break;
            }
        }
        if (j >= p_animNode->GetNumChildren()) {
  	      g_convert->Message("Neutral.3ds model name (%s) does not exist in model directory",
					model->GetNodeName())
					;
            return FALSE;
        }
        Swap(p_animNode->GetChildren()[i], p_animNode->GetChildren()[j]);
        if (!MatchAnimToModel(p_animNode->GetChild(i), model)) {
            return FALSE;
        }
    }
    return TRUE;
}

