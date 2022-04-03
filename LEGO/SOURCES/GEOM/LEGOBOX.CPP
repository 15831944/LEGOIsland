#include "LegoBox.h"
#include "LegoUtil.h"

void 
LegoBox::AddVertex(LegoVertex& p_vertex)
{
    if (p_vertex.GetX() < m_min.GetX()) {
        m_min.SetX(p_vertex.GetX());
    }
    if (p_vertex.GetX() > m_max.GetX()) {
        m_max.SetX(p_vertex.GetX());
    }
    if (p_vertex.GetY() < m_min.GetY()) {
        m_min.SetY(p_vertex.GetY());
    }
    if (p_vertex.GetY() > m_max.GetY()) {
        m_max.SetY(p_vertex.GetY());
    }
    if (p_vertex.GetZ() < m_min.GetZ()) {
        m_min.SetZ(p_vertex.GetZ());
    }
    if (p_vertex.GetZ() > m_max.GetZ()) {
        m_max.SetZ(p_vertex.GetZ());
    }
}

LegoResult 
LegoBox::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = m_min.Read(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = m_max.Read(p_storage)) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoBox::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = m_min.Write(p_storage)) != SUCCESS) {
        return result;
    }
    if ((result = m_max.Write(p_storage)) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

void 
LegoBox::operator |=(LegoBox& p_box)
{
    m_min.SetX(Min(m_min.GetX(), p_box.GetMin().GetX()));
    m_min.SetY(Min(m_min.GetY(), p_box.GetMin().GetY()));
    m_min.SetZ(Min(m_min.GetZ(), p_box.GetMin().GetZ()));
    m_max.SetX(Max(m_max.GetX(), p_box.GetMax().GetX()));
    m_max.SetY(Max(m_max.GetY(), p_box.GetMax().GetY()));
    m_max.SetZ(Max(m_max.GetZ(), p_box.GetMax().GetZ()));
}
