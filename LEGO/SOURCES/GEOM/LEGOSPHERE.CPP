#include "LegoSphere.h"
#include "LegoStorage.h"

LegoResult 
LegoSphere::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = m_center.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_radius, sizeof(m_radius))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoSphere::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = m_center.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_radius, sizeof(m_radius))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

