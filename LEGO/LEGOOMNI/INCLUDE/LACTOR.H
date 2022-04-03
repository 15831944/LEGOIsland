/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LACTOR_H
#define __LACTOR_H

#include "LEntity.h"

class LegoActor : public LegoEntity
{
protected:
	MxS32		m_proximityCount;
    void Destroy(MxBool p_fromDestructor);

public:
	LegoActor();
	virtual ~LegoActor();
    virtual MxResult Create(const MxChar* p_name, LegoWorld* p_world);
    virtual void Destroy();
    virtual const MxChar* ClassName() { return "LegoActor"; }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoActor::ClassName())) || (LegoEntity::IsA(p_str)) ; }

	virtual MxResult Tickle();
	
	virtual void OnActorProximityEvent(LegoActor* p_otherActor);
	virtual void OnNodeProximityEvent(MxS32 p_nodeId);
};

class LegoActorList : public MxPtrList<LegoActor> {
protected:
    virtual MxS8 Compare(LegoActor* p_entity1, LegoActor* p_entity2) 
			{ return p_entity1 == p_entity2 ? 0 : p_entity1 < p_entity2 ? -1 : 1; }
public:
    LegoActorList(MxBool p_ownership = FALSE) : MxPtrList<LegoActor>(p_ownership) {}
    static void Destroy(LegoActor* p_entity) { delete p_entity; }
};

class LegoActorListCursor : public MxPtrListCursor<LegoActor> {
public:
    LegoActorListCursor(LegoActorList* p_list) : MxPtrListCursor<LegoActor>(p_list) {}
};

// m_stateFlag values (bit field)
const MxS32 ACTOR_PROXIMITY_EVENT_FLAG = 1;
const MxS32 NODE_PROXIMITY_EVENT_FLAG = 2;

#endif // __LACTOR_H