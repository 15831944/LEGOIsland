/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __PATHS_H
#define __PATHS_H

#include "MxRawData.h"
#include "PathStruc.h"

// -------------------------------------------------------------------
// MxPaths is an interface to data from *.pth files.  These files 
// contain all the geometry and data used to instantiate the
// Path Controller.

typedef MxU8 LegoPathsData;

class LegoPaths : public MxRawData <LegoPathsData> {
public:
    virtual const MxChar* ClassName() { return "LegoPaths"; }
	MxResult	ParseData(LegoPathsData *p_frameData,
						  MxS32 & p_numLinks, LegoPathLinkPtr & p_links,
						  MxS32 & p_numNodes, LegoPathNodePtr & p_nodes,
						  MxS32 & p_numCorridors, LegoCorridorPtr & p_corridors);
};

#endif // __PATHS_H


