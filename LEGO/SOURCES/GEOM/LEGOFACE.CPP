#include "LegoFace.h"
#include "LegoStorage.h"

LegoFace::LegoFace()
{
}

LegoFace::LegoFace(LegoU32* p_vertexIndices)
{
    for (int i = 0; i < 3; i++) {
        m_vertexIndices[i] = p_vertexIndices[i];
    }
}

LegoResult 
LegoFace::Read(LegoStorage* p_storage)
{
    LegoResult result;
    for (int i = 0; i < 3; i++) {
        if ((result = p_storage->Read(&m_vertexIndices[i], sizeof(m_vertexIndices[i]))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

LegoResult 
LegoFace::Write(LegoStorage* p_storage)
{
    LegoResult result;
    for (int i = 0; i < 3; i++) {
        if ((result = p_storage->Write(&m_vertexIndices[i], sizeof(m_vertexIndices[i]))) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}

