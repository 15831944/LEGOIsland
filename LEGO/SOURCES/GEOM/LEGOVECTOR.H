#ifndef __LEGOVECTOR_H
#define __LEGOVECTOR_H

#include "LegoTypes.h"

template <class T, LegoU32 d>
class LegoVector {
public:
    T operator[](LegoU32 p_i) const { return m_elements[p_i]; }
    T& operator[](LegoU32 p_i) { return m_elements[p_i]; }
protected:
    T m_elements[d];
};

class LegoVectorF2 : public LegoVector<LegoFloat, 2> {
};

class LegoVectorF3 : public LegoVector<LegoFloat, 3> {
};

class LegoVectorF4 : public LegoVector<LegoFloat, 4> {
};

#endif // __LEGOVECTOR_H

