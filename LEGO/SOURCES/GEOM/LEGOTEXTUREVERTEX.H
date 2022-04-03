#ifndef __LEGOTEXTUREVERTEX
#define __LEGOTEXTUREVERTEX

#include "LegoTypes.h"

class LegoStorage;

class LegoTextureVertex {
public:
    LegoTextureVertex();
    LegoTextureVertex(LegoFloat p_u, LegoFloat p_v);
    LegoFloat GetCoordinate(LegoU32 p_i) { return m_coordinates[p_i]; }
    void SetCoordinate(LegoU32 p_i, LegoFloat p_coordinate) { m_coordinates[p_i] = p_coordinate; }
    LegoFloat GetU() { return m_coordinates[0]; }
    void SetU(LegoFloat p_u) { m_coordinates[0] = p_u; }
    LegoFloat GetV() { return m_coordinates[1]; }
    void SetV(LegoFloat p_v) { m_coordinates[1] = p_v; }
    LegoResult Read(LegoStorage* p_storage);
    LegoResult Write(LegoStorage* p_storage);
protected:
    LegoFloat m_coordinates[2];
};

#endif // __LEGOTEXTUREVERTEX

