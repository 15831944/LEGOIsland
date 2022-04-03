/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoOmni.h"

#include "Paths.h"
#include "PathStruc.h"

static MxS32 FindNodeId(LegoPathNodePtr p_nodes, MxS32 p_numNodes, MxChar* p_name)
{
	for(int i=0; i<p_numNodes; i++)
		if(!strcmp(p_nodes[i].GetName(), p_name))
			return i;
	return NOT_A_PATHNODE;

}

static MxS32 FindCorridorId(LegoCorridorPtr p_corridors, MxS32 p_numCorridors, MxChar* p_name)
{
	for(int i=0; i<p_numCorridors; i++)
		if(!strcmp(p_corridors[i].GetName(), p_name))
			return i;
	return NOT_A_CORRIDOR;

}


// -------------------------------------------------------------------
// LegoPaths is an interface to data from *.pth files.  These files 
// contain all the geometry and data used to instantiate the
// Path Controller.
MxResult LegoPaths::ParseData(LegoPathsData *p_frameData,
							MxS32 & p_numLinks, LegoPathLinkPtr & p_links,
						    MxS32 & p_numNodes, LegoPathNodePtr & p_nodes,
							MxS32 & p_numCorridors, LegoCorridorPtr & p_corridors)
{
	MxResult result = FAILURE;

	enum {  // parser modes
		NonMode,	
		InLinks,
		InNodes,
		InCorridors,
		InCorridorLinks,
		InIntersectionLinks,
	} mode = NonMode;
	enum {  // parser states
		NonState,	
		NeedName,
		NeedNode1,
		NeedNode2,
		NeedLocationX,
		NeedLocationY,
		NeedLocationZ,
		NeedNormalX,
		NeedNormalY,
		NeedNormalZ,
		NeedOffset,
		NeedWidth,
		NeedAdmissionFlags,
		NeedLink,
		NeedCorridor,
		EndState,
	} state = NonState;

	char seps[]   = " ,\t\n\r";
	char *token;

	p_numNodes = p_numLinks = p_numCorridors = 0;

	LegoPathLinkPtr links = new LegoPathLink[1000];
	LegoPathNodePtr nodes = new LegoPathNode[1000];
	LegoCorridorPtr corridors = new LegoCorridor[100];

	// nodes connected to current link (reused for each link)
	LegoPathNodePtr * nodePtrs = new LegoPathNodePtr[20];
	MxS32 nodePtrCount;
	// corridors connected to current link (reused for each link)
	LegoCorridorPtr * corridorPtrs = new LegoCorridorPtr[20];
	MxS32 corridorPtrCount;

	// links connected to each node (remembers all nodes)
	struct NodeLinkPtrs {
		int				linkPtrCount;
		LegoPathLinkPtr	linkPtrs[20];
	};
	NodeLinkPtrs * nodeLinkPtrs = new NodeLinkPtrs[1000];
	memset(nodeLinkPtrs, 0, 1000*sizeof(NodeLinkPtrs));

	MxS32		nodeId, corridorId;
	Mx3DPointDouble location, normal;

	if(!links || !nodes || !corridors)
		goto done;

	if(!nodeLinkPtrs || !nodePtrs || !corridorPtrs)
		goto done;

	token = strtok( (char*)p_frameData, seps );
	while( token != NULL )
	{
		// first check for token that changes mode
		if(!_stricmp(token, "links"))
		{
			mode = InLinks;
			state = NeedName;
		}
		else if(!_stricmp(token, "nodes"))
		{
			mode = InNodes;
			state = NeedName;
		}
		else if(!_stricmp(token, "corridors"))
		{
			mode = InCorridors;
			state = NeedName;
		}
		else if(!_stricmp(token, "corridorLinks"))
		{
			mode = InCorridorLinks;
			state = NeedName;
		}
		else if(!_stricmp(token, "intersectionLinks"))
		{
			mode = InIntersectionLinks;
			state = NeedName;
		}
		// process according to current mode
		else switch(mode)
		{
		case InLinks:
			switch(state)
			{
			case NeedName:
				state = NeedNode1;
				links[p_numLinks].SetName(token);
				links[p_numLinks].SetId(p_numLinks);
				nodePtrCount = 0;
				corridorPtrCount = 0;
				break;
			case NeedNode1:
				state = NeedNode2;
				nodeId = FindNodeId(nodes,p_numNodes,token);
				if(nodeId != NOT_A_PATHNODE)
				{
					nodePtrs[nodePtrCount] = &nodes[nodeId];
					nodePtrCount++;
					nodeLinkPtrs[nodeId].linkPtrs[nodeLinkPtrs[nodeId].linkPtrCount] = &links[p_numLinks];
					nodeLinkPtrs[nodeId].linkPtrCount++;
				}
				break;
			case NeedNode2:
				state = NeedCorridor;
				nodeId = FindNodeId(nodes,p_numNodes,token);
				if(nodeId != NOT_A_PATHNODE)
				{
					nodePtrs[nodePtrCount] = &nodes[nodeId];
					nodePtrCount++;
					nodeLinkPtrs[nodeId].linkPtrs[nodeLinkPtrs[nodeId].linkPtrCount] = &links[p_numLinks];
					nodeLinkPtrs[nodeId].linkPtrCount++;
				}
				break;
			case NeedCorridor:
				if(!strcmp(token,";"))
				{
					state = NeedName; // get ready for next one
					links[p_numLinks].SetNodes(nodePtrs, nodePtrCount);
					links[p_numLinks].SetCorridors(corridorPtrs, corridorPtrCount);
					p_numLinks++;
					break;
				}
				corridorId = FindCorridorId(corridors,p_numCorridors,token);
				if(corridorId != NOT_A_CORRIDOR)
				{
					corridorPtrs[corridorPtrCount] = &corridors[corridorId];
					corridorPtrCount++;
				}
				break;
			}
			break;
		case InNodes:
			switch(state)
			{
			case NeedName:
				state = NeedLocationX;
				nodes[p_numNodes].SetName(token);
				nodes[p_numNodes].SetId(p_numNodes);
				break;
			case NeedLocationX:
				state = NeedLocationY;
				location.SetX(strtod(token,NULL));
				break;
			case NeedLocationY:
				state = NeedLocationZ;
				location.SetY(strtod(token,NULL));
				break;
			case NeedLocationZ:
				state = EndState;
				location.SetZ(strtod(token,NULL));
				break;
			case EndState: // eats up the ';'
				if(!strcmp(token,";"))
				{
					state = NeedName; // get ready for next one
					// scale coordinates for fixed-point representation
					nodes[p_numNodes].SetLocation(location);
					p_numNodes++;
				}
				break;
			}
			break;
		case InCorridors:
			switch(state)
			{
			case NeedName:
				state = NeedOffset;
				corridors[p_numCorridors].SetName(token);
				corridors[p_numCorridors].SetId(p_numCorridors);
				break;
			case NeedOffset:
				state = NeedWidth;
				corridors[p_numCorridors].SetOffset(strtod(token,NULL));
				break;
			case NeedWidth:
				state = NeedAdmissionFlags;
				corridors[p_numCorridors].SetWidth(strtod(token,NULL));
				break;
			case NeedAdmissionFlags:
				state = EndState;
				corridors[p_numCorridors].SetAdmissionFlags(strtol(token,NULL,0));
				break;
			case EndState: // eats up the ';'
				if(!strcmp(token,";"))
				{
					state = NeedName; // get ready for next one
					p_numCorridors++;
				}
				break;
			}
			break;
		case InCorridorLinks: // variable number of same type fields
			break;
		case InIntersectionLinks: // variable number of same type fields
			break;
		}

		token = strtok( NULL, seps );
	}
	result = SUCCESS;
done:
	if(SUCCESS == result)
	{
		//  for each node, record the list of attached links
		for(int i=0; i<p_numNodes; i++)
			nodes[i].SetLinks(nodeLinkPtrs[i].linkPtrs, nodeLinkPtrs[i].linkPtrCount);
	}
	else
	{
		if(links)
			delete [] links;
		links = NULL;
		p_numLinks = 0;
		if(nodes)
			delete [] nodes;
		nodes = NULL;
		p_numNodes = 0;
		if(corridors)
			delete [] corridors;
		corridors = NULL;
		p_numCorridors = 0;
	}

	// delete the temporaries
	if(nodePtrs)
		delete [] nodePtrs;
	if(corridorPtrs)
		delete [] corridorPtrs;
	if(nodeLinkPtrs)
		delete [] nodeLinkPtrs;

	// assign the results
	p_links = links;
	p_nodes = nodes;
	p_corridors = corridors;

	return result;
}	
