#ifndef _tglVector_h
#define _tglVector_h

#include <stddef.h> // offsetof()
#include "math.h"   // ??? sin() in  RotateAroundY()

namespace Tgl
{


namespace Constant
{
    const double Pi = 3.14159265358979323846;
};

inline
double DegreesToRadians(double degrees)
{
    return Constant::Pi * (degrees / 180.0);
}

inline
double RadiansToDegrees(double radians)
{
    return (radians / Constant::Pi) * 180.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Array<T, N> 

template <class T, int N>
class Array
{
public:
    Array() {}
    Array(const Array& rArray)       { *this = rArray; }
    ~Array() {}

    const T& operator[](int i) const    { return m_elements[i]; };
    T& operator[](int i)                { return m_elements[i]; };

    Array<T, N>& operator=(const Array<T, N>&);
    void operator+=(const Array<T, N>&);

protected:
    T  m_elements[N];
};

//////////////////////////////////////////////////////////////////////////////
//
// Array<T, N> implementation

template <class T, int N>
inline
Array<T, N>& Array<T, N>::operator=(const Array<T, N>& rArray)
{
    int i;

    for (i = 0; i < N; i++)
    {
        m_elements[i] = rArray.m_elements[i];
    }

    return *this;
}

template <class T, int N>
inline
void Array<T, N>::operator+=(const Array<T, N>& rArray)
{
    int i;

    for (i = 0; i < N; i++)
    {
        m_elements[i] += rArray.m_elements[i];
    }
}

//////////////////////////////////////////////////////////////////////////////
//
// DoubleMatrix4

class DoubleMatrix4 : public Array< Array<double, 4>, 4>
{
public:
    DoubleMatrix4() {}
    DoubleMatrix4(const DoubleMatrix4& rMatrix) { *this = rMatrix; }
    DoubleMatrix4(const DoubleMatrix4&, const DoubleMatrix4&);

    void operator*=(const DoubleMatrix4&);
};

//////////////////////////////////////////////////////////////////////////////
//
// DoubleMatrix4 implementation

inline
DoubleMatrix4::DoubleMatrix4(const DoubleMatrix4& rMatrix1,
                             const DoubleMatrix4& rMatrix2)
{
    for (int row = 0; row < 4; row++)
    {
        for (int column = 0; column < 4; column++)
        {
            double  element = 0;

            for (int i = 0; i < 4; i++)
            {
                element += rMatrix1[row][i] * rMatrix2[i][column];
            }

            m_elements[row][column] = element;
        }
    }
}

inline
void DoubleMatrix4::operator*=(const DoubleMatrix4& rMatrix)
{
    DoubleMatrix4   temp(*this, rMatrix);

    // *this = DoubleMatrix4(*this, rMatrix);
    *this = temp;
}

//////////////////////////////////////////////////////////////////////////////
//
// Transformation matrices

class Translation : public DoubleMatrix4
{
public:
    Translation(const double[3]);
    Translation(double x, double y, double z);
protected:
    void Init(double x, double y, double z);
};

class Scale : public DoubleMatrix4
{
public:
    Scale(const double[3]);
    Scale(double x, double y, double z);
    Scale(double);
protected:
    void Init(double x, double y, double z);
};

class RotationX : public DoubleMatrix4
{
public:
    RotationX(double radians);
};

class RotationY : public DoubleMatrix4
{
public:
    RotationY(double radians);
};

//////////////////////////////////////////////////////////////////////////////
//
// Transformation matrices implementation

inline
Translation::Translation(const double vector[3])
{
    Init(vector[0], vector[1], vector[2]); 
}

inline
Translation::Translation(double x, double y, double z)
{
    Init(x, y, z); 
}

inline
void Translation::Init(double x, double y, double z)
{
    m_elements[0][0]   = 1;
    m_elements[0][1]   = 0;
    m_elements[0][2]   = 0;
    m_elements[0][3]   = 0;

    m_elements[1][0]   = 0;
    m_elements[1][1]   = 1;
    m_elements[1][2]   = 0;
    m_elements[1][3]   = 0;

    m_elements[2][0]   = 0;
    m_elements[2][1]   = 0;
    m_elements[2][2]   = 1;
    m_elements[2][3]   = 0;

    m_elements[3][0]   = x;
    m_elements[3][1]   = y;
    m_elements[3][2]   = z;
    m_elements[3][3]   = 1;
}

inline
Scale::Scale(const double vector[3])
{
    Init(vector[0], vector[1], vector[2]); 
}

inline
Scale::Scale(double x, double y, double z)
{
    Init(x, y, z); 
}

inline
Scale::Scale(double scale)
{
    Init(scale, scale, scale); 
}

inline
void
Scale::Init(double x, double y, double z)
{
    m_elements[0][0]   = x;
    m_elements[0][1]   = 0;
    m_elements[0][2]   = 0;
    m_elements[0][3]   = 0;

    m_elements[1][0]   = 0;
    m_elements[1][1]   = y;
    m_elements[1][2]   = 0;
    m_elements[1][3]   = 0;

    m_elements[2][0]   = 0;
    m_elements[2][1]   = 0;
    m_elements[2][2]   = z;
    m_elements[2][3]   = 0;

    m_elements[3][0]   = 0;
    m_elements[3][1]   = 0;
    m_elements[3][2]   = 0;
    m_elements[3][3]   = 1;
}

inline
RotationX::RotationX(double radians)
{
    double  cosRadians = cos(radians);
    double  sinRadians = sin(radians);

    m_elements[0][0]   = 1;
    m_elements[0][1]   = 0;
    m_elements[0][2]   = 0;
    m_elements[0][3]   = 0;

    m_elements[1][0]   = 0;
    m_elements[1][1]   = cosRadians;
    m_elements[1][2]   = -sinRadians;
    m_elements[1][3]   = 0;

    m_elements[2][0]   = 0;
    m_elements[2][1]   = sinRadians;
    m_elements[2][2]   = cosRadians;
    m_elements[2][3]   = 0;

    m_elements[3][0]   = 0;
    m_elements[3][1]   = 0;
    m_elements[3][2]   = 0;
    m_elements[3][3]   = 1;
}

inline
RotationY::RotationY(double radians)
{
    double  cosRadians = cos(radians);
    double  sinRadians = sin(radians);

    m_elements[0][0]   = cosRadians;
    m_elements[0][1]   = 0;
    m_elements[0][2]   = sinRadians;
    m_elements[0][3]   = 0;

    m_elements[1][0]   = 0;
    m_elements[1][1]   = 1;
    m_elements[1][2]   = 0;
    m_elements[1][3]   = 0;

    m_elements[2][0]   = -sinRadians;
    m_elements[2][1]   = 0;
    m_elements[2][2]   = cosRadians;
    m_elements[2][3]   = 0;

    m_elements[3][0]   = 0;
    m_elements[3][1]   = 0;
    m_elements[3][2]   = 0;
    m_elements[3][3]   = 1;
}

//////////////////////////////////////////////////////////////////////////////

}   // namespace Tgl

#endif /* _tglVector_h */
