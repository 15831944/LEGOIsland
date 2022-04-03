#ifndef __LEGOMATRIX_H
#define __LEGOMATRIX_H

#include "LegoVector.h"

template <class T, LegoU32 r, LegoU32 c>
class LegoMatrix {
public:
    const LegoVector<T, c>& operator[](LegoU32 p_i) const { return m_rows[p_i]; }
    LegoVector<T, c>& operator[](LegoU32 p_i) { return m_rows[p_i]; }
protected:
    LegoVector<T, c> m_rows[r];
};

class LegoMatrixF2x2 : public LegoMatrix<LegoFloat, 2, 2> {
};

class LegoMatrixF3x3 : public LegoMatrix<LegoFloat, 3, 3> {
};

class LegoMatrixF4x4 : public LegoMatrix<LegoFloat, 4, 4> {
public:
    void SetTranslation(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z);
    void SetRotation(LegoFloat p_a, LegoFloat p_x, LegoFloat p_y, LegoFloat p_z);
    void SetScale(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z);
    void ApplyTranslation(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z);
    void ApplyRotation(LegoFloat p_a, LegoFloat p_x, LegoFloat p_y, LegoFloat p_z);
    void ApplyScale(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z);
};


#endif // __LEGOMATRIX_H

