/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __PATHCTRL_H
#define __PATHCTRL_H

#include "MxList.h"
#include "Paths.h"
#include "MxGeometry3D.h"
#include "PathStruc.h"

class LegoSpacePresenter;

class LegoPathController
{
protected:
	LegoPathLinkPtr	m_links;
	LegoPathNodePtr	m_nodes;
	LegoCorridorPtr	m_corridors;
	MxS32			m_numLinks;
	MxS32			m_numNodes;
	MxS32			m_numCorridors;

public:
	LegoPathController();
	~LegoPathController();
	void	Init();
	MxS32	Create();
	MxS32	Create(MxCharString p_fileName);
	MxS32	Create(LegoPaths * p_rawData, const Mx3DPointDouble & p_location);
	void	AddPresenter(LegoSpacePresenter* p_spacePresenter, MxS32 p_nodeId);
	void	HandleEndOfLink(LegoSpacePresenter* p_spacePresenter);
	void	MovePresenter(LegoSpacePresenter* p_spacePresenter);

friend class LegoPathStructPresenter;
};

#endif  // __PATHCTRL_H