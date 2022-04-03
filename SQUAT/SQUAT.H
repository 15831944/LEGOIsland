
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                     *
 *                       SIMPLE QUATERNION LIBRARY                     *
 *                       version 1.0.1                                 *
 *                       by Daniel Green                               *
 *                       Mindscape, Inc.                               *
 *                       January 1996                                  *
 *                                                                     *
 * DESCRIPTION                                                         *
 *    Implements a quaternion class called "SQuat".                    *
 *    A quaternion represents a rotation about an axis.                *
 *    Squats can be concatenated together via the '*' and '*='         *
 *    operators.                                                       *
 *                                                                     *
 *    SQuats operate in a left handed coordinate system (i.e. positive *
 *    Z is coming out of the screen). The direction of a rotation by   *
 *    a positive value follows the right-hand-rule meaning that if the *
 *    thumb of your right hand is pointing along the axis of rotation, *
 *    the rotation is in the direction that your fingers curl.         *
 *                                                                     *
 *    Simple 3D vector and matrix classes are also defined mostly as   *
 *    ways to get 3D data into and out of quaternions. Methods for     *
 *    matrix multiplication, inversion, etc. are purposely not         *
 *    implemented because they are fully covered in vec.h the vector   *
 *    macro library which will work with these vector and matrix       *
 *    classes and with any other objects that can be indexed into.     *
 *                                                                     *
 *    The GetAxis and GetRotation methods extract the current axis and *
 *    rotation in radians.  A rotation matrix can also be extracted    *
 *    via the Matrix3 constructor which takes a SQuat argument.        *
 *    A SQuat can also be initialized from a rotation matrix and       *
 *    thereby extract its axis of rotation and amount.                 *
 *                                                                     *
 *    The GetHomoAxis and GetHomoRoation methods return the raw values *
 *    stored in a SQuat which have no useful geometric interpretation  *
 *    and are probably only useful to the application programmer       *
 *    wanting to archive and restore SQuats as quickly as possible.    *
 *    When reconstructing a SQuat from homogenous values, use the      *
 *    five-value constructor and pass a non-zero "homo-vals" flag.     *
 *    Otherwise, that flag should always be allowed to default to      *
 *    zero.                                                            *
 *                                                                     *
 * BUGS                                                                *
 *    None known.                                                      *
 *                                                                     *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef SQUAT
#define SQUAT

#define DTOR(d) ((d) * 3.1415926535 / 180)

/*
 * A simple array of three doubles that can be indexed into.
 */
class Vector3 {
public:
	Vector3();
	Vector3(double x, double y, double z);
	const double &operator[](long i) const { return elements[i]; }
	      double &operator[](long i)       { return elements[i]; }
	double Length() const;
	Vector3 Normal() const;
private:
	double elements[3];
};


class SQuat {
public:
	SQuat(const Vector3 &, double);
	SQuat(const SQuat &);
	SQuat(const class Matrix3 &);
	SQuat(double x, double y, double z, double r, int homo_vals = 0);
	SQuat  operator *  (const SQuat &) const;
	SQuat& operator *= (const SQuat &);
	double GetRotation() const;
	void GetAxis(Vector3 &v) const; // fastest way to extraxt axis
	Vector3 GetAxis() const; // for convienience. Only a touch slower
	double GetHomoRotation() const;
	void GetHomoAxis(Vector3 &v) const;
private:
	void InitFromVector(const Vector3 &, double);
	Vector3 axis;
	double rot;
};


class Matrix3 {
public:
	Matrix3();
	Matrix3(const Vector3 &, const Vector3 &, const Vector3 &); 
	Matrix3(const Matrix3 &);
	Matrix3(const SQuat &);
	const Vector3 &operator[](long i) const { return rows[i]; }
	      Vector3 &operator[](long i)       { return rows[i]; }
private:
	Vector3 rows[3];
};

#endif
