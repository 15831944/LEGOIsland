#ifndef __LEGOBOX_H
#define __LEGOBOX_H

#include "LegoVertex.h"

class LegoBox {
public:
    void AddVertex(LegoVertex& p_vertex);
    LegoVertex& GetMin() { return m_min; }
    void SetMin(LegoVertex& p_min) { m_min = p_min; }
    LegoVertex& GetMax() { return m_max; }
    void SetMax(LegoVertex& p_max) { m_max = p_max; }
    LegoVertex GetCenter() { return LegoVertex((m_min.GetX() + m_max.GetX()) / 2, (m_min.GetY() + m_max.GetY()) / 2, (m_min.GetZ() + m_max.GetZ()) / 2); }
    LegoFloat GetDX() { return m_max.GetX() - m_min.GetX(); }
    LegoFloat GetDY() { return m_max.GetY() - m_min.GetY(); }
    LegoFloat GetDZ() { return m_max.GetZ() - m_min.GetZ(); }
    LegoBool IsEmpty() { return m_min.IsOrigin() && m_max.IsOrigin(); }
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
    void operator |=(LegoBox& p_box);
protected:
    LegoVertex m_min;
    LegoVertex m_max;
};


#endif // __LEGOBOX_H

