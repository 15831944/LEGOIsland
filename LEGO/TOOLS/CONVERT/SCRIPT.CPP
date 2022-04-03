#include "Script.h"
#include "Convert.h"

LegoBool 
LegoScript::Open(const char* p_fileName)
{
    LegoBool ok = FALSE;

    FILE* file;
    if (!(file = fopen(p_fileName, "r"))) {
        goto done;
    }
    fclose(file);
    m_fileName = p_fileName;

    ok = TRUE;

done:
    return ok;
}

void 
LegoScript::Close()
{
    m_fileName = "";
}

LegoBool
LegoScript::Run()
{
    LegoBool ok = TRUE;
    ok = ProcessMeshes() && ok;
    ok = ProcessTextures() && ok;
    ok = ProcessAnimations() && ok;
    ok = ProcessModels() && ok;
    return ok;
}

LegoBool 
LegoScript::ProcessMeshes()
{
    return FALSE;
}

LegoBool 
LegoScript::ProcessTextures()
{
    return FALSE;
}

LegoBool 
LegoScript::ProcessAnimations()
{
    return FALSE;
}

LegoBool
LegoScript::ProcessModels()
{
    LegoBool ok = FALSE;
    CStringList modelFileList;
    POSITION pos;

    CString modelDirectory;
    if (!GetEntry("Settings", "ModelDirectory", modelDirectory)) {
        goto done;
    }
    if (!g_convert->OpenModelDirectory(modelDirectory)) {
        goto done;
    }
    EnumKeys("Models", modelFileList);
    for (pos = modelFileList.GetHeadPosition(); pos; modelFileList.GetNext(pos)) {
        const char* modelFile = modelFileList.GetAt(pos);
        CString string;
        GetEntry("Models", modelFile, string);
        CStringList modelList;
        ParseList(string, modelList);
        g_convert->CreateModelFile(modelFile, modelList);
    }

    ok = TRUE;

done:
    return ok;
}

LegoU32
LegoScript::EnumSections(CStringList& p_list)
{
    char buffer[512];
    LegoU32 n = GetPrivateProfileString(
        NULL,
        NULL,
        "",
        buffer,
        sizeof(buffer),
        m_fileName
    );
    if (!n) {
        return n;
    }
    n = 0;
    char* p = buffer;
    while (*p) {
        p_list.AddTail(p);
        p += strlen(p) + 1;
    }
    return n;
}

LegoU32
LegoScript::EnumKeys(const char* p_section, CStringList& p_list)
{
    char buffer[512];
    LegoU32 n = GetPrivateProfileString(
        p_section,
        NULL,
        "",
        buffer,
        sizeof(buffer),
        m_fileName
    );
    if (!n) {
        return n;
    }
    n = 0;
    char* p = buffer;
    while (*p) {
        p_list.AddTail(p);
        p += strlen(p) + 1;
    }
    return n;
}

LegoU32
LegoScript::GetEntry(const char* p_section, const char* p_key, CString& p_result)
{
    char buffer[512];
    LegoU32 n = GetPrivateProfileString(
        p_section,
        p_key,
        "",
        buffer,
        sizeof(buffer),
        m_fileName
    );
    p_result = buffer;
    return n;
}

LegoU32
LegoScript::ParseList(const char* p_string, CStringList& p_list)
{
    const char* p = p_string;
    LegoU32 n = 0;
    LegoU32 c;
    for (;;) {
        p += Delimiters(p);
        if (!(c = Token(p))) {
            break;
        }
        p_list.AddTail(CString(p, c));
        p += c;
        n++;
    }
    return n;
}

LegoU32
LegoScript::Delimiters(const char* p_string)
{
    const char* p = p_string;
    while (*p && (isspace(*p) || *p == ',')) {
        p++;
    }
    return p - p_string;
}

LegoU32
LegoScript::Token(const char* p_string)
{
    const char* p = p_string;
    while (*p && !isspace(*p) && *p != ',') {
        p++;
    }
    return p - p_string;
}