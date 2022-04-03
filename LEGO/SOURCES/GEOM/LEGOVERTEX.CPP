#include "LegoVertex.h"
#include "LegoStorage.h"

LegoVertex::LegoVertex()
{
    m_coordinates[0] = 0.0F;
    m_coordinates[1] = 0.0F;
    m_coordinates[2] = 0.0F;
}

LegoVertex::LegoVertex(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    m_coordinates[0] = p_x;
    m_coordinates[1] = p_y;
    m_coordinates[2] = p_z;
}

LegoResult 
LegoVertex::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Read(&m_coordinates[0], sizeof(m_coordinates[0]))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_coordinates[1], sizeof(m_coordinates[1]))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_coordinates[2], sizeof(m_coordinates[2]))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoVertex::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Write(&m_coordinates[0], sizeof(m_coordinates[0]))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_coordinates[1], sizeof(m_coordinates[1]))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_coordinates[2], sizeof(m_coordinates[2]))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}
