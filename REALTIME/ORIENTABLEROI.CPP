
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                       *
 *                       ORIENTABLE ROI                                  *
 *                       by Daniel Green                                 *
 *                       Mindscape, Inc.                                 *
 *                       May 1996                                        *
 *                                                                       *
 * DESCRIPTION                                                           *
 *     This file contains the implementation of the OrientableROI class. *
 *     Currently it only contains a constructor since that is the only   *
 *     method that couldn't easily be inlined without introducing a      *
 *     dependancy on vec.h                                               *
 *                                                                       *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "realtime.h"
#include "vec.h"

using namespace std;

OrientableROI::OrientableROI()
{
	FILLVEC3(world_bounding_box.Min(), 888888.8);
	FILLVEC3(world_bounding_box.Max(), -888888.8);
	ZEROVEC3(world_bounding_sphere.Center());
	world_bounding_sphere.Radius() = 0.0;
	ZEROVEC3(world_velocity);
}



