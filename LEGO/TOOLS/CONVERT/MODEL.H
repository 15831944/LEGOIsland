#ifndef __MODEL_H
#define __MODEL_H

#include <afxwin.h>
#include <afxtempl.h>
#include "LegoTypes.h"
#include "LegoBox.h"

class LegoStorage;
class LegoLODList;
class LegoModelList;
class LegoAnim;
class LegoTreeNode;
class LegoAnimNodeData;
class LegoBox;
class LegoVertex;

class LegoModel {
public:
    LegoModel();
    virtual ~LegoModel();
    CString& GetModelName() { return m_modelName; }
    CString& GetNodeName() { return m_nodeName; }
    LegoBox& GetBox() { return m_box; }
    LegoModelList* GetCompList() { return m_compList; }
    LegoBool Open(const char* p_dir, const char* p_modelName);
    LegoBool Open(const char* p_dir, const char* p_modelName, const char* p_nodeName);
    void Close();
    LegoBool Write(LegoStorage* p_storage, const char* p_dir);
protected:
    void GetBounds(const char* p_dir);
    LegoBool FindBounds(const char* p_dir);
    void CalculateBounds(const char* p_dir);
    LegoBool WriteLOD(LegoStorage* p_storage, const char* p_dir);
    LegoFloat TriangleArea(LegoFloat p_vertices[][3]);
    CString m_modelName;
    CString m_nodeName;
    LegoBox m_box;
    LegoBool m_haveBounds;
    LegoLODList* m_lodList;
    LegoModelList* m_compList;
};

class LegoLODList : public CStringList {
public:
    void Insert(const char* p_fileName);
};

class LegoModelList : public CList<LegoModel*, LegoModel*> {
};

class LegoModelDirectory {
public:
    LegoModelDirectory();
    virtual ~LegoModelDirectory();
    CString& GetName() { return m_name; }
    LegoModelList* GetModelList() { return m_modelList; }
    LegoBool Open(const char* p_name);
    void Close();
    LegoBool Write(LegoStorage* p_storage, LegoModel* p_model);
    LegoU32  GetNumModels();
    LegoModel* GetModel(const char* p_modelName);
protected:
    LegoAnim* CreateAnim(LegoModel* p_model);
    LegoBool MatchAnimToModel(LegoAnim* p_anim, LegoModel* p_model);
    LegoBool MatchAnimToModel(LegoTreeNode* p_animNode, LegoModel* p_model);
    CString m_name;
    LegoModelList* m_modelList;
};


#endif // __MODEL_H

