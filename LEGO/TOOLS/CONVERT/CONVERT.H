#ifndef __CONVERT_H
#define __CONVERT_H

#include <stdio.h>
#include "LegoTypes.h"
#include "LegoColor.h"

extern "C" {
#include "3dsftk.h"
}

class LegoScript;
class LegoStudioFile;
class LegoModelDirectory;
class LegoMesh;
class LegoTexture;
class LegoAnimNodeData;

class LegoConvert {
public:
    LegoConvert();
    virtual ~LegoConvert();
    LegoScript* GetScript()  {return m_script; }
    LegoStudioFile* GetStudioFile() { return m_studioFile; }
    LegoModelDirectory* GetModelDirectory() { return m_modelDirectory; }
    LegoBool OpenScript(const char* p_fileName);
    LegoBool OpenStudioFile(const char* p_fileName);
    LegoBool OpenModelDirectory(const char* p_fileName);
    LegoBool CreateModelFile(const char* p_fileName, CStringList& p_modelList);
    LegoMesh* CreateMesh(database3ds* p_database, mesh3ds* p_studioMesh, const char* p_textureDirectory);
    LegoTexture* CreateTexture(const char* p_fileName);
    LegoAnimNodeData* CreateAnimNodeData(database3ds* p_database, kfmesh3ds* p_studioNode);
    void Message(const char* p_format, ...);
protected:
    enum {
        c_frameRate = 10,
    };
    LegoColor GetMeshColor(database3ds* p_database, mesh3ds* p_studioMesh);
    LegoU8 GetMeshShading(database3ds* p_database, mesh3ds* p_studioMesh);
    LegoBool GetMeshTextureFileName(database3ds* p_database, mesh3ds* p_studioMesh, CString& p_name);
    LegoBool IsPowerOf2(LegoU32 p_val);
    LegoScript* m_script;
    LegoStudioFile* m_studioFile;
    LegoModelDirectory* m_modelDirectory;
};

extern LegoConvert* g_convert;

#endif // __CONVERT_H


