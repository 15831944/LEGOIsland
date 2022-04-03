#include "LegoTextureVertex.h"
#include "LegoStorage.h"

LegoTextureVertex::LegoTextureVertex()
{
    m_coordinates[0] = 0.0F;
    m_coordinates[1] = 0.0F;
}

LegoTextureVertex::LegoTextureVertex(LegoFloat p_u, LegoFloat p_v)
{
    m_coordinates[0] = p_u;
    m_coordinates[1] = p_v;
}

LegoResult 
LegoTextureVertex::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Read(&m_coordinates[0], sizeof(m_coordinates[0]))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_coordinates[1], sizeof(m_coordinates[1]))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoTextureVertex::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Write(&m_coordinates[0], sizeof(m_coordinates[0]))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_coordinates[1], sizeof(m_coordinates[1]))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}


