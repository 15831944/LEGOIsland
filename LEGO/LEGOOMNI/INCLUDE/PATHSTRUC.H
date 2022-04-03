/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __PATHSTRUCT_H
#define __PATHSTRUCT_H

#include "MxList.h"
//#include "Paths.h"
#include "MxGeometry3D.h"
#include "LegoSpacePresenter.h"

// Special path structure id values
#define NOT_A_PATHNODE  (-1)
#define NOT_A_PATHLINK  NOT_A_PATHNODE
#define NOT_A_CORRIDOR  NOT_A_PATHNODE

// Change this value to "drive on left" (-1) or "drive on right" (1).
#define CORRIDOR_HANDEDNESS 1

// Corridor admission flag values
#define PATH_DIRECTION_BITS			0x70000000
#define PATH_DIRECTION_FORWARD		0x10000000
#define PATH_DIRECTION_BACKWARD		0x20000000
#define PATH_DIRECTION_ANY			0x30000000

#define PATH_PRIVILEGE_BITS			0x0F000000
#define PATH_PRIVILEGE_USER			0x01000000

#define PATH_TRAVELER_BITS			0x00FFFFFF
#define PATH_TRAVELER_PEDESTRIAN	0x00000001
#define PATH_TRAVELER_VEHICLE		0x00000002

const MxDouble ACTOR_PROXIMITY_DISTANCE = 30;

class LegoPathLink;
typedef LegoPathLink * LegoPathLinkPtr;

class LegoPathNode;
typedef LegoPathNode * LegoPathNodePtr;

class LegoCorridor;
typedef LegoCorridor * LegoCorridorPtr;

#define PATH_NAME_LEN	10

class LegoPathLink
{
protected:	
	MxChar				m_name[PATH_NAME_LEN+1];
	MxS32				m_id; // unique path link identifier
	LegoSpacePresenterList	m_residents; // SpacePresenter objects at this location
	MxS32				m_numNodes;
	LegoPathNodePtr *	m_nodes; // nodes connected to this link
	MxS32				m_numCorridors;
	LegoCorridorPtr *	m_corridors; // corridors connected to this link
	Mx3DPointDouble			m_vector;    // unit vector parallel to link
	Mx3DPointDouble			m_upVector;  // perpendicular and normal to surface
	Mx3DPointDouble			m_outVector; // perpendicular and on surface
	MxDouble				m_length;

public:	
	LegoPathLink();
	virtual ~LegoPathLink();
	void SetId(MxS32 p_id) {m_id = p_id;}
	MxS32 GetId() {return m_id;}
	void SetName(const MxChar * p_name) {
				strncpy(m_name, p_name, PATH_NAME_LEN);
				m_name[PATH_NAME_LEN] = 0;
	}
	const MxChar *GetName() { return m_name; }
	
	virtual void SetNodes(LegoPathNodePtr * p_nodes, MxS32 p_numNodes);
	LegoPathNodePtr * GetNodes() {return m_nodes;}

	void SetCorridors(LegoCorridorPtr * p_corridors, MxS32 p_numCorridors);
	LegoCorridorPtr * GetCorridors() {return m_corridors;}

	MxBool SelectCorridor(MxS32 p_direction, MxS32 p_type, LegoCorridorPtr & p_corridorPtr);
	virtual void AddPresenter(LegoSpacePresenter* p_spacePresenter);
	virtual void RemovePresenter(LegoSpacePresenter* p_spacePresenter);

	virtual void AdjustMoveVector(LegoSpacePresenter* p_spacePresenter, Mx3DPointDouble &p_vector);
	virtual void CheckProximity(LegoSpacePresenter* p_spacePresenter, BOOL p_checkNodes);
	virtual MxBool AtEndOfLink(LegoSpacePresenter* p_spacePresenter, 
							   LegoPathNodePtr & p_newNodePtr,
							   LegoPathLinkPtr & p_newLinkPtr,
							   LegoCorridorPtr & p_newCorridorPtr);
	MxBool IsOriginNode(LegoPathNodePtr p_node) {return p_node == m_nodes[0];}
	MxDouble GetLength() {return m_length;}
	Mx3DPointDouble GetVector() {return m_vector;}
	Mx3DPointDouble GetUpVector() {return m_upVector;}
	Mx3DPointDouble GetOutVector() {return m_outVector;}

//friend class CTestView;
friend class LegoPathStructPresenter;
};

class LegoPathLinkList : public MxPtrList<LegoPathLink> {
protected:
	MxS8 Compare(LegoPathLinkPtr p_element1, LegoPathLinkPtr p_element2) 
			{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoPathLinkList(MxBool p_ownership=FALSE) : MxPtrList<LegoPathLink>(p_ownership) {}
};

class LegoPathLinkListCursor : public MxPtrListCursor<LegoPathLink> {
public:
    LegoPathLinkListCursor(LegoPathLinkList* p_list) : MxPtrListCursor<LegoPathLink>(p_list) {}
};

class LegoPathNode
{
protected:	
	MxChar				m_name[PATH_NAME_LEN+1];
	MxS32				m_id; // unique path node identifier
	LegoSpacePresenterList	m_residents; // SpacePresenter objects at this location
	MxS32				m_numLinks;
	LegoPathLinkPtr *	m_links; // links connected to this node
	Mx3DPointDouble			m_location; // location in world space

public:
	LegoPathNode();
	virtual ~LegoPathNode();
	void SetId(MxS32 p_id) {m_id = p_id;}
	MxS32 GetId() {return m_id;}
	void SetName(const MxChar * p_name) {
				strncpy(m_name, p_name, PATH_NAME_LEN);
				m_name[PATH_NAME_LEN] = 0;
	}
	const MxChar *GetName() { return m_name; }
	void SetLocation(const Mx3DPointDouble & p_point) {m_location = p_point;}
	Mx3DPointDouble & GetLocation() {return m_location;}
	virtual void SetLinks(LegoPathLinkPtr * p_links, MxS32 p_numLinks);
	MxBool SelectLink(const Mx3DPointDouble & p_direction, LegoPathLinkPtr & linkPtr);
	void AddPresenter(LegoSpacePresenter* p_spacePresenter, MxBool p_setLocation=FALSE);
	void RemovePresenter(LegoSpacePresenter* p_spacePresenter);
	void CheckProximity(LegoSpacePresenter* p_spacePresenter);
//friend class CTestView;
friend class LegoPathStructPresenter;
};

class LegoPathNodeList : public MxPtrList<LegoPathNode> {
protected:
	MxS8 Compare(LegoPathNodePtr p_element1, LegoPathNodePtr p_element2) 
			{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoPathNodeList(MxBool p_ownership) : MxPtrList<LegoPathNode>(p_ownership) {}
};

class LegoPathNodeListCursor : public MxPtrListCursor<LegoPathNode> {
public:
    LegoPathNodeListCursor(LegoPathNodeList* p_list) : MxPtrListCursor<LegoPathNode>(p_list) {}
};

class LegoCorridor
{
protected:	
	MxChar	m_name[PATH_NAME_LEN+1];
	MxS32	m_id; // unique corridor identifier
	MxDouble	m_offset;
	MxDouble	m_width;
	MxU32	m_admissionFlags;

public:	
	LegoCorridor() {}
	~LegoCorridor() {}
	void SetId(MxS32 p_id) {m_id = p_id;}
	MxS32 GetId() {return m_id;}
	
	void SetName(const MxChar * p_name) {
				strncpy(m_name, p_name, PATH_NAME_LEN);
				m_name[PATH_NAME_LEN] = 0;
	}
	const MxChar *GetName() { return m_name; }

	void SetOffset(MxDouble p_offset) {m_offset = p_offset;}
	MxDouble GetOffset() {return m_offset;}
	
	void SetWidth(MxDouble p_width) {m_width = p_width;}
	MxDouble GetWidth() {return m_width;}

	void SetAdmissionFlags(MxU32 p_admissionFlags) {m_admissionFlags = p_admissionFlags;}
	MxU32 GetAdmissionFlags() {return m_admissionFlags;}

friend class LegoPathStructPresenter;
};

#endif  // __PATHSTRUCT_H