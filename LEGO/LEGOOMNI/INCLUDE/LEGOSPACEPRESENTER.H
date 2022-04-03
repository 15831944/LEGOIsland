/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOSPACEPRESENTER_H
#define __LEGOSPACEPRESENTER_H

#include "MxPresenter.h"
#include "MxGeometry3D.h"
#include "LegoEntityPresenter.h"

class LegoPathLink;
class LegoPathNode;
class LegoCorridor;
class LegoWorld;
class LegoActor;

class LegoSpacePresenter : public LegoEntityPresenter {
protected:
	void Init();

public:
	LegoSpacePresenter();
	virtual ~LegoSpacePresenter();
    virtual MxResult Create(LegoEntity* p_entity);
    static const MxChar* HandlerClassName() { return "LegoSpacePresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoSpacePresenter::ClassName())) || (LegoEntityPresenter::IsA(p_str)) ; }

	virtual MxResult Move();

	void OnActorProximityEvent(LegoSpacePresenter * p_actorPresenter);
	void OnNodeProximityEvent(MxS32 p_nodeId);

protected:
	// path and space controller friends, state variables and methods
	friend class LegoPathController;
	friend class LegoPathLink;
	friend class LegoPathNode;

	enum {
		e_linkTransition = 101,
	};
	LegoPathNode * m_nodePtr;
	LegoPathLink * m_linkPtr;
	LegoCorridor * m_corridorPtr;
	MxDouble	m_linkDistance, m_outDistance;
	MxS32	m_numTransitionSteps, m_currentTransitionStep;
	Mx3DPointDouble m_oldLocation;
	Mx3DPointDouble m_oldDirection;
	Mx3DPointDouble m_newLocation;
	Mx3DPointDouble m_newDirection;
	LegoPathLink * m_newLinkPtr;
	LegoCorridor * m_newCorridorPtr;
	MxU32 m_pathTravelerType;

	MxResult RegularMove();
	MxResult LinkTransitionMove();

	void  SetPathNodePtr(LegoPathNode * p_nodePtr) {m_nodePtr = p_nodePtr;}
	LegoPathNode * GetPathNodePtr() {return m_nodePtr;}
	
	void  SetPathLinkPtr(LegoPathLink * p_linkPtr) {m_linkPtr = p_linkPtr;}
	LegoPathLink * GetPathLinkPtr() {return m_linkPtr;}
	
	void  SetCorridorPtr(LegoCorridor * p_corridorPtr) {m_corridorPtr = p_corridorPtr;}
	LegoCorridor * GetCorridorPtr() {return m_corridorPtr;}
	
	void  SetLinkDistance(MxDouble p_val) {m_linkDistance = p_val;}
	MxDouble GetLinkDistance() {return m_linkDistance;}
	
	void  SetOutDistance(MxDouble p_val) {m_outDistance = p_val;}
	MxDouble GetOutDistance() {return m_outDistance;}
	
	void  SetNumTransitionSteps(MxS32 p_val) {m_numTransitionSteps = p_val;}
	MxS32 GetNumTransitionSteps() {return m_numTransitionSteps;}
	
	void  SetCurrentTransitionStep(MxS32 p_val) {m_currentTransitionStep = p_val;}
	MxS32 GetCurrentTransitionStep() {return m_currentTransitionStep;}

public:
	void  SetPathTravelerType(MxU32 p_val) {m_pathTravelerType = p_val;}
	MxU32 GetPathTravelerType() {return m_pathTravelerType;}
	MxBool SetLinkTransition(const Mx3DPointDouble & p_newLocation, 
						   const Mx3DPointDouble & p_newDirection,
						   MxDouble p_newLinkDistance, 
						   MxDouble p_newOutDistance,
						   LegoPathLink * p_newLinkPtr,
						   LegoCorridor * p_newCorridorPtr);
};

typedef LegoSpacePresenter * LegoSpacePresenterPtr;

class LegoSpacePresenterList : public MxPtrList<LegoSpacePresenter> {
protected:
	MxS8 Compare(LegoSpacePresenterPtr p_element1, LegoSpacePresenterPtr p_element2) 
				{ return p_element1 == p_element2 ? 0 : p_element1 < p_element2 ? -1 : 1; }
public:
    LegoSpacePresenterList(MxBool p_ownership=FALSE) : MxPtrList<LegoSpacePresenter>(p_ownership) {}
};

class LegoSpacePresenterListCursor : public MxPtrListCursor<LegoSpacePresenter> {
public:
    LegoSpacePresenterListCursor(LegoSpacePresenterList* p_list) : MxPtrListCursor<LegoSpacePresenter>(p_list) {}
};


#endif // __LEGOSPACEPRESENTER_H

