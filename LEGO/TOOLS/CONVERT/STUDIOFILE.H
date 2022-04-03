#ifndef __STUDIOFILE
#define __STUDIOFILE

#include <stdio.h>
#include "LegoTypes.h"

extern "C" {
#include "3dsftk.h"
}

class LegoStudioFile {
public:
    LegoStudioFile();
    LegoBool Open(const char* p_name);
    void Close();
    file3ds* GetFile() { return m_file; }
    database3ds* GetDatabase() { return m_database; }
    LegoU32 GetNumMeshes();
    LegoU32 GetNumTextures();
    LegoU32  GetNumAnimations();
protected:
    file3ds* m_file;
    database3ds* m_database;
};

#endif // __STUDIOFILE

