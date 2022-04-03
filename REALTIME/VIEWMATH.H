#ifndef _VIEWMATH_
#define _VIEWMATH_

/*
			    VIEW MATH
			    by Daniel Green

This module contains a set of routines that handle most of the hairy math
involved in simple projective geometry and view/bounding volume handling
enough so to allow the construction of a typical rendering (or rendering-like)
application.

Notice that the the hierarchical z-buffer algorithm begins with just such a
normal graphics pipeline but adds some additional visibility tests to display
nodes that would otherwise be visible in the view volume.  This module was
designed to also be useful in those more usual situations that do not need the
hzbuffer functionality.  In those cases the routine test_box_against_hzb would
not be called, and test_box_visible could be passed a null hzbuffer pointer.

Each method is described below.  Note that two macros are defined at the end
which should be used to cast non-const 2d arrays into const 2d arrays when
calling methods here that call for them.  It shouldn't be needed, but the
Watcom compiler won't accept them otherwise.

*/

#ifndef M_PI
#	define M_PI		3.14159265358979323846
#endif
#ifndef DTOR
#	define DTOR(deg) ((deg) * M_PI / 180.0)
#endif
#ifndef RTOD
#	define RTOD(rad) ((rad) * 180.0 / M_PI)
#endif
#ifndef SQR
#	define SQR(a) ((a) * (a))
#endif
#ifndef MAX
#	define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
#ifndef MIN
#	define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif


typedef enum {
	HEXA_ERROR,
	HEXA_OUTSIDE,
	HEXA_CONTAINED,
	HEXA_CONTAINS_BOX,
	HEXA_CLIPPED,         // either front clipped or otherwise
	HEXA_FRONT_CLIPPED,
	HEXA_BACK_OR_SIDE_CLIPPED,
} ViewIntersectionType;


// Returns into the given matrix a viewing matrix which transforms the given
// volume of space into the cube of length 1.0 centered at the origin.
// The resulting matrix operates on column vectors.
//
extern void build_orthographic_mat(double pmat[4][4],
		double width, double height,
		double neer, double phar);


// Returns into the given matrix a viewing matrix which transforms the given
// volume of space into homogenious coordinates.  For transformed homogenious
// column vectors with positive W values, the point X/W, Y/W, Z/W will lie
// within the cube of length 1.0 centered at the origin if the untransformed
// point is within the given volume.
//
extern void build_perspective_mat(double pmat[4][4],
		double fovy, double view_aspect_ratio,
		double neer, double phar);


// This routine tells how a given box intersects a given view volume.
// The box is described by its back-lower-left and front-upper-right corners.
// The view volume is described by its eight corners in the following order:
//	bll, blr, bul, bur, fll, flr, ful, fur.
// Note that although it's refered to as a "view" volume, these corners really
// describe a general hexahedron and this routine can also be used for
// applications outside of view volume bounds checking.
//
// The returned enumerated value tells the exact nature of the intersection
// between the two bodies.  I.e. whether they do not intersect at all, one body
// completely contains the other, or whether their surfaces intersect (each
// clips the other).  When their surfaces intersect this routine distinguishes
// between the cases where the front face of the view volume is one of the
// affected faces is involved in the clipping, and when it is not.  That extra
// information is needed by the hierarchical z-buffer algorithm.  The
// HEXA_CLIPPED and HEXA_ERROR values are only used internally and should never
// be returned by this routine.
//
extern ViewIntersectionType test_box_intersect_view(
		const double bll[3], const double fur[3],
		const double viewbox[8][3]);


// Returns the world-space corners of an orthographic view volume
// given a camera transformation matrix and orthographic viewing parameters.
// The order of the returned corners are:
//	bll, blr, bul, bur, fll, flr, ful, fur.
//
extern void get_ortho_view_corners(double viewbox[8][3],
		const double cam_xfm[4][4],
		double xmin, double xmax,
		double ymin, double ymax,
		double neer, double phar);


// Returns the world-space corners of a perspective view volume
// given a camera transformation matrix and perspective viewing parameters.
// The order of the returned corners are:
//	bll, blr, bul, bur, fll, flr, ful, fur.
//
extern void get_persp_view_corners(double viewbox[8][3],
		const double cam_xfm[4][4],
		double fovx, double fovy,
		double neer, double phar);

// Returns the corners of a bounding box.
// Note: fills a 4-vector coordinate with the fourth entry always 1.0
//
extern void get_box_verts(double verts[8][4],
			const double bll[3], const double fur[3]);

// These macros are used to work around a bug in the Watcom 9.5 compiler
// which won't allow non-const two-dimensional arrays to be passed to a
// routine expecting a const array.  Works fine for one-dimensional arrays.
//
#define ARRAY3 (const double (*)[3])
#define ARRAY4 (const double (*)[4])

#endif
