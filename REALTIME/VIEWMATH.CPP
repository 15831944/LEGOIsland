
#include <math.h>
#include "viewmath.h"
#include "vec.h"

extern "C" {
#include "pcube.h"
}

//#define DTOR(angle) ((angle) * M_PI / 180.)

// The following macro from Jon Wood, Dept of Communication and Neuroscience
// Keele University, Staffordshire, England
// coa34@keele.ac.uk
//
#define CLOCKWISE( x1, y1, x2, y2, x3, y3 ) \
    ( ((x1) - (x2)) * ((y1) - (y3)) <= ((x1) - (x3)) * ((y1) - (y2)) )


/*
    Parallel projection matrix that transforms the box
	[cam_x0..cam_x1]x[cam_y0..cam_y1]x[cam_z0..cam_z1]
    into the box
	[scr_x0..scr_x1]x[scr_y0..scr_y1]x[scr_z0..scr_z1]
    This gem curtsey of Don Hatch.
*/
static void ParallelProjection(double parallelmat[4][4],
				    double cam_x0, double cam_x1,
				    double cam_y0, double cam_y1,
				    double cam_z0, double cam_z1,
				    double scr_x0, double scr_x1,
				    double scr_y0, double scr_y1,
				    double scr_z0, double scr_z1)
{
	IDENTMAT4(parallelmat);
	parallelmat[0][0] = (scr_x1-scr_x0) / (cam_x1-cam_x0);
	parallelmat[0][3] = (scr_x0*cam_x1 - scr_x1*cam_x0) / (cam_x1-cam_x0);

	parallelmat[1][1] = (scr_y1-scr_y0) / (cam_y1-cam_y0);
	parallelmat[1][3] = (scr_y0*cam_y1 - scr_y1*cam_y0) / (cam_y1-cam_y0);

	parallelmat[2][2] = (scr_z1-scr_z0) / (cam_z1-cam_z0);
	parallelmat[2][3] = (scr_z0*cam_z1 - scr_z1*cam_z0) / (cam_z1-cam_z0);
}


/*
    Perspective matrix that transforms
	    [-fovx/2..fovx/2]x[-fovy/2..fovy/2]x[-phar..-neer]
	 to [x0..x1]x[y0..y1]x[z0..z1]
    (do the w-divide to x,y,and z, as usual to get screen coords)
    This gem curtsey of Don Hatch.
*/
static void PerspectiveProjection(double perspectivemat[4][4],
				    double fovx,
				    double fovy,
				    double neer,
				    double phar,
				    double x0, double x1,
				    double y0, double y1,
				    double z0, double z1)
{
	IDENTMAT4(perspectivemat);
	perspectivemat[0][0] = (x1-x0)/2 / tan(DTOR(fovx)/2.0);
	perspectivemat[0][2] = (x0+x1)/2;

	perspectivemat[1][1] = (y1-y0)/2 / tan(DTOR(fovy)/2.0);
	perspectivemat[1][2] = (y0+y1)/2;

	perspectivemat[2][2] = (z0*-phar - z1*-neer) / (-neer - -phar);
	perspectivemat[2][3] = (z1-z0) * neer * phar / (-neer - -phar);

	perspectivemat[3][2] = -1.0;
	perspectivemat[3][3] =  0.0;
}

extern void build_orthographic_mat(double pmat[4][4],
			double width, double height,
			double neer, double phar)
{
	ParallelProjection(pmat,
		-width/2.,  width/2.,
		-height/2., height/2., 
		-phar, -neer,
		-.5, .5,
		-.5, .5,
		-.5, .5);
}


extern void build_perspective_mat(double pmat[4][4],
			double fovy, double view_aspect_ratio,
			double neer, double phar)
{
	PerspectiveProjection(pmat,
		fovy * view_aspect_ratio,
		fovy,
		neer, phar,
		-.5, .5,
		-.5, .5,
		-.5, .5);
}



static int hexahedron_inside_unit_box(const double hexa[8][3])
{
	register int i, j;
	for(i=0; i<8; i++)
		for(j=0; j<3; j++)
			if((-.5 > hexa[i][j]) || (hexa[i][j] > .5))
				return 0;
	return 1;
}


static const int BoxFaces[6][4] = {
	{0,2,3,1},  // Back
	{1,3,7,5},  // Right
	{5,7,6,4},  // Front
	{4,6,2,0},  // Left
	{0,1,5,4},  // Bottom
	{2,6,7,3},  // Top
};


static void get_hexa_face3(const double hexa[8][3], int q, double face[4][3])
{
	register int v;
	for(v=0; v<4; v++)
		SET3(face[v], hexa[BoxFaces[q][v]]);
}


static void get_hexa_face4(const double hexa[8][4], int q, double face[4][4])
{
	register int v;
	for(v=0; v<4; v++)
		SET4(face[v], hexa[BoxFaces[q][v]]);
}


extern void get_box_verts(double verts[8][4],
			const double bll[3], const double fur[3])
{
	int i;
	for(i=0; i<8; i++)
		verts[i][3] = 1.0;

	verts[0][0] = bll[0];
	verts[0][1] = bll[1];
	verts[0][2] = bll[2];

	verts[1][0] = fur[0];
	verts[1][1] = bll[1];
	verts[1][2] = bll[2];

	verts[2][0] = bll[0];
	verts[2][1] = fur[1];
	verts[2][2] = bll[2];

	verts[3][0] = fur[0];
	verts[3][1] = fur[1];
	verts[3][2] = bll[2];

	verts[4][0] = bll[0];
	verts[4][1] = bll[1];
	verts[4][2] = fur[2];

	verts[5][0] = fur[0];
	verts[5][1] = bll[1];
	verts[5][2] = fur[2];

	verts[6][0] = bll[0];
	verts[6][1] = fur[1];
	verts[6][2] = fur[2];

	verts[7][0] = fur[0];
	verts[7][1] = fur[1];
	verts[7][2] = fur[2];
}


static int hexahedron_clipped(const double hexa[8][3], double normals[6][3])
{
	register int q;
	for(q=0; q<6; q++) {
		double face[4][3];
		get_hexa_face3(hexa, q, face);
		if(fast_polygon_intersects_cube(4, ARRAY3 face, normals[q], 0, 0))
			return 1;
	}
	return 0;
}


static int hexahedron_contains_origin(const double hexa[8][3])
{
	register int q;
	for(q=0; q<6; q++) {
		// the determinant of the first three vertices in each
		// face will always be positive if the origin is inside
		// the box.
		//
		double determinant = VXVXV3(
					hexa[BoxFaces[q][0]],
					hexa[BoxFaces[q][1]],
					hexa[BoxFaces[q][2]]);
		if(determinant > 0.0)
			return 0;
	}
	return 1;
}

static void compute_hexa_normals(const double hexa[8][3], double normals[6][3])
{
	for(int i=0; i<6; i++) {
		double e01[3], e03[3]; // edges from vert 0->1 and vert 0->3
		double len;
		VMV3(e01, hexa[BoxFaces[i][1]], hexa[BoxFaces[i][0]]);
		VMV3(e03, hexa[BoxFaces[i][3]], hexa[BoxFaces[i][0]]);
		len = sqrt(NORMSQRD3(e01));
		VDS3(e01, e01, len);
		len = sqrt(NORMSQRD3(e03));
		VDS3(e03, e03, len);
		VXV3(normals[i], e03, e01);
		len = sqrt(NORMSQRD3(normals[i]));
		VDS3(normals[i], normals[i], len);
	}
}

static ViewIntersectionType test_hexahedra_intersect_unit_box(
		const double hexa[8][3])
{
	// Quick test to see if the unit box is completely contained
	// by the hexahedron
	//
	if(hexahedron_inside_unit_box(hexa))
		return HEXA_CONTAINED;

	// Quick (but not definitive) test to see if hexahedron is
	// completely outside the unit box
	//
	if(0 == trivial_vertex_tests(8, hexa, 1))
		return HEXA_OUTSIDE;

	// Complete test to see whether any part of the *surfaces* of
	// the hexahedra and view volume intersect
	//
	double hexa_normals[6][3];
	compute_hexa_normals(hexa, hexa_normals);
	if(hexahedron_clipped(hexa, hexa_normals))
		return HEXA_CLIPPED;
	
	// If any point within the unit box (i.e. the origin) is inside
	// the hexahedron, then the whole unit box must also be contained.
	//
	if(hexahedron_contains_origin(hexa))
		return HEXA_CONTAINS_BOX;

	// All possible intersections (should) have been eliminated.
	//
	return HEXA_OUTSIDE;
}


// Returns the world-space corners of a perspective view volume.
//
extern void get_persp_view_corners(double viewbox[8][3],
			const double cam_xfm[4][4],
			double fovx, double fovy,
			double neer, double phar)
{
	double wcs_corner[4];
	double ccs_corner[4];
	ccs_corner[3] = 1.0;
	double tan_half_x = tan(DTOR(fovx)/2);
	double tan_half_y = tan(DTOR(fovy)/2);

	// bll corner
	//
	ccs_corner[0] = -phar * tan_half_x;
	ccs_corner[1] = -phar * tan_half_y;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[0], wcs_corner);

	// blr corner
	//
	ccs_corner[0] =  phar * tan_half_x;
	ccs_corner[1] = -phar * tan_half_y;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[1], wcs_corner);

	// bul corner
	//
	ccs_corner[0] = -phar * tan_half_x;
	ccs_corner[1] =  phar * tan_half_y;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[2], wcs_corner);

	// bur corner
	//
	ccs_corner[0] =  phar * tan_half_x;
	ccs_corner[1] =  phar * tan_half_y;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[3], wcs_corner);

	// fll corner
	//
	ccs_corner[0] = -neer * tan_half_x;
	ccs_corner[1] = -neer * tan_half_y;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[4], wcs_corner);

	// flr corner
	//
	ccs_corner[0] =  neer * tan_half_x;
	ccs_corner[1] = -neer * tan_half_y;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[5], wcs_corner);

	// ful corner
	//
	ccs_corner[0] = -neer * tan_half_x;
	ccs_corner[1] =  neer * tan_half_y;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[6], wcs_corner);

	// fur corner
	//
	ccs_corner[0] =  neer * tan_half_x;
	ccs_corner[1] =  neer * tan_half_y;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[7], wcs_corner);

}


// Returns the world-space corners of an orthographic view volume.
//
extern void get_ortho_view_corners(double viewbox[8][3],
			const double cam_xfm[4][4],
			double xmin, double xmax,
			double ymin, double ymax,
			double neer, double phar)
{
	double wcs_corner[4];
	double ccs_corner[4];
	ccs_corner[3] = 1.0;

	// bll corner
	//
	ccs_corner[0] = xmin;
	ccs_corner[1] = ymin;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[0], wcs_corner);

	// blr corner
	//
	ccs_corner[0] = xmax;
	ccs_corner[1] = ymin;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[1], wcs_corner);

	// bul corner
	//
	ccs_corner[0] = xmin;
	ccs_corner[1] = ymax;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[2], wcs_corner);

	// bur corner
	//
	ccs_corner[0] = xmax;
	ccs_corner[1] = ymax;
	ccs_corner[2] = -phar;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[3], wcs_corner);

	// fll corner
	//
	ccs_corner[0] = xmin;
	ccs_corner[1] = ymin;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[4], wcs_corner);

	// flr corner
	//
	ccs_corner[0] = xmax;
	ccs_corner[1] = ymin;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[5], wcs_corner);

	// ful corner
	//
	ccs_corner[0] = xmin;
	ccs_corner[1] = ymax;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[6], wcs_corner);

	// fur corner
	//
	ccs_corner[0] = xmax;
	ccs_corner[1] = ymax;
	ccs_corner[2] = -neer;
	MXV4(wcs_corner, cam_xfm, ccs_corner);
	SET3(viewbox[7], wcs_corner);
}



extern ViewIntersectionType test_box_intersect_view(
			const double bll[3], const double fur[3],
			const double viewbox[8][3])
{
	double npc_box[8][3];
	ViewIntersectionType intersection = HEXA_ERROR;
	int i, j;

	// Transform the view box by the same tramsform that would take
	// the given box to the unit box.
	//
	double centroid[3], size[3];
	for(j=0; j<3; j++) {
		centroid[j] = (fur[j] + bll[j]) / 2.0;
		size[j] = fur[j] - bll[j];
	}
	for(i=0; i<8; i++)
		for(j=0; j<3; j++)
			npc_box[i][j] = (viewbox[i][j] - centroid[j]) / size[j];

	// Find out how the transformed viewbox intersects the unit box
	//
	intersection = test_hexahedra_intersect_unit_box(ARRAY3 npc_box);

	return intersection;
}



static int test_front_facing(const double f[][3])
{
	double vec0[2], vec1[2], determinant;
	VMV2(vec0, f[1], f[0]);  // vector from first vertex to second
	VMV2(vec1, f[2], f[1]);  // vector from second vertex to third
	determinant = VXV2(vec0, vec1);
	return (determinant > 0.0);
}	

