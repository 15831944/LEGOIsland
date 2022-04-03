#include "LegoMatrix.h"
#include "vec.h"

#pragma warning(disable: 4244)

void 
LegoMatrixF4x4::SetTranslation(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    IDENTMAT4(m_rows);
    m_rows[0][3] = p_x;
    m_rows[1][3] = p_y;
    m_rows[2][3] = p_z;
}

void 
LegoMatrixF4x4::SetRotation(LegoFloat p_a, LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    LegoFloat s = sin(p_a);
    LegoFloat c = cos(p_a);
    LegoFloat x2 = p_x * p_x;
    LegoFloat y2 = p_y * p_y;
    LegoFloat z2 = p_z * p_z;
    LegoFloat xy = p_x * p_y;
    LegoFloat xz = p_x * p_z;
    LegoFloat yz = p_y * p_z;
    IDENTMAT4(m_rows);
    m_rows[0][0] = x2 + (1.0F - x2) * c;
    m_rows[0][1] = xy * (1.0F - c) - p_z * s;
    m_rows[0][2] = xz * (1.0F - c) + p_y * s;
    m_rows[1][0] = xy * (1.0F - c) + p_z * s;
    m_rows[1][1] = y2 + (1.0F - y2) * c;
    m_rows[1][2] = yz * (1.0F - c) - p_x * s;
    m_rows[2][0] = xz * (1.0F - c) - p_y * s;
    m_rows[2][1] = yz * (1.0F - c) + p_x * s;
    m_rows[2][2] = z2 + (1.0F - z2) * c;
}

void 
LegoMatrixF4x4::SetScale(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    IDENTMAT4(m_rows);
    m_rows[0][0] = p_x;
    m_rows[1][1] = p_y;
    m_rows[2][2] = p_z;
}

void 
LegoMatrixF4x4::ApplyTranslation(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    LegoMatrixF4x4 m;
    m.SetTranslation(p_x, p_y, p_z);
    MXM4d(m_rows, m_rows, m);
}

void 
LegoMatrixF4x4::ApplyRotation(LegoFloat p_a, LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    LegoMatrixF4x4 m;
    m.SetRotation(p_a, p_x, p_y, p_z);
    MXM4d(m_rows, m_rows, m);
}

void 
LegoMatrixF4x4::ApplyScale(LegoFloat p_x, LegoFloat p_y, LegoFloat p_z)
{
    LegoMatrixF4x4 m;
    m.SetScale(p_x, p_y, p_z);
    MXM4d(m_rows, m_rows, m);
}
