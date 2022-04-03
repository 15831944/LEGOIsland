#ifndef __SCRIPT_H
#define __SCRIPT_H

#include <afxwin.h>
#include "LegoTypes.h"

class LegoScript {
public:
    LegoBool Open(const char* p_fileName);
    void Close();
    LegoBool Run();
    LegoBool IsOpen() { return m_fileName != ""; }
    LegoU32 EnumSections(CStringList& p_list);
    LegoU32 EnumKeys(const char* p_section, CStringList& p_list);
    LegoU32 GetEntry(const char* p_section, const char* p_key, CString& p_result);
protected:
    LegoBool ProcessMeshes();
    LegoBool ProcessTextures();
    LegoBool ProcessAnimations();
    LegoBool ProcessModels();
    LegoU32 ParseList(const char* p_string, CStringList& p_list);
    LegoU32 Delimiters(const char* p_string);
    LegoU32 Token(const char* p_string);
    CString m_fileName;
};


#endif // __SCRIPT_H

