#include <string.h>
#include "StudioFile.h"

LegoStudioFile::LegoStudioFile()
{
    m_file = NULL;
    m_database = NULL;
}

LegoBool 
LegoStudioFile::Open(const char* p_name)
{
    LegoBool ok = FALSE;
    dbtype3ds type = Unknown;

    if (!(m_file = OpenFile3ds(p_name, "r"))) {
        goto done;
    }
    InitDatabase3ds(&m_database);
    CreateDatabase3ds(m_file, m_database);
    type = GetDatabaseType3ds(m_database);
    if (type != MeshFile) {
        goto done;
    }

    ok = TRUE;

done:
    if (!ok) {
        if (m_file) {
            CloseFile3ds(m_file);
            m_file = NULL;
        }
        if (m_database) {
            ReleaseDatabase3ds(&m_database);
            m_database = NULL;
        }
    }
    return ok;
}

void 
LegoStudioFile::Close()
{
    if (m_database) {
        ReleaseDatabase3ds(&m_database);
        m_database = NULL;
    }
    if (m_file) {
        CloseFile3ds(m_file);
        m_file = NULL;
    }
}

LegoU32 
LegoStudioFile::GetNumMeshes()
{
    LegoU32 result = 0;
    if (m_database) {
        result = GetMeshCount3ds(m_database);
    }
    return result;
}

LegoU32 
LegoStudioFile::GetNumTextures()
{
    LegoU32 result = 0;
    if (m_database) {
        LegoU32 n = GetMaterialCount3ds(m_database);
        for (LegoU32 i = 0; i < n; i++) {
            material3ds* studioMaterial = NULL;
            GetMaterialByIndex3ds(m_database, i, &studioMaterial);
            char* name = studioMaterial->texture.map.name;
            if (strlen(name) > 4 && stricmp(name + strlen(name) - 4, ".gif") == 0) {
                result++;
            }
            ReleaseMaterial3ds(&studioMaterial);
        }

    }
    return result;
}

LegoU32 
LegoStudioFile::GetNumAnimations()
{
    LegoU32 result = 0;
    if (m_database) {
        result = GetObjectNodeCount3ds(m_database);
    }
    return result;
}

