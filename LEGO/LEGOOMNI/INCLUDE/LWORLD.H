/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LWORLD_H
#define __LWORLD_H

#include "LEntity.h"
class LegoPathController;
class LegoCameraController;

class LegoWorld : public LegoEntity
{
protected:
	LegoPathController* m_pathController;
	LegoCameraController* m_cameraController;
    LegoEntityList* m_entityList;
    void Destroy(MxBool p_fromDestructor);
public:
	LegoWorld();
	virtual ~LegoWorld();
    virtual MxResult Create(const MxChar* p_name);
    virtual void Destroy();
	virtual MxS32 Notify(MxParam& p_param);
    virtual const MxChar* ClassName() { return "LegoWorld"; }
    virtual MxBool IsA(MxCharString p_str) 
    { return (! strcmp(p_str, LegoWorld::ClassName())) || (LegoEntity::IsA(p_str)) ; }

	void ProcessPresenterTree(MxPresenter *p_presenter);

    LegoPathController* CreatePathController();
	LegoPathController* GetPathController() { return m_pathController; }

    LegoCameraController* CreateCameraController();
	LegoCameraController* GetCameraController() { return m_cameraController; }

    void AddEntity(LegoEntity* p_entity) { m_entityList->Append(p_entity); }
    LegoEntityList* GetEntityList() { return m_entityList; }
    LegoEntity* GetEntity(const MxChar* p_entityName);
};

class LegoWorldList : public MxPtrList<LegoWorld> {
protected:
    virtual MxS8 Compare(LegoWorld* p_entity1, LegoWorld* p_entity2) 
					{ return p_entity1 == p_entity2 ? 0 : p_entity1 < p_entity2 ? -1 : 1; }
public:
    LegoWorldList(MxBool p_ownership = FALSE) : MxPtrList<LegoWorld>(p_ownership) {}
    static void Destroy(LegoWorld* p_entity) { delete p_entity; }
};

class LegoWorldListCursor : public MxPtrListCursor<LegoWorld> {
public:
    LegoWorldListCursor(LegoWorldList* p_list) : MxPtrListCursor<LegoWorld>(p_list) {}
};

#endif // __LWORLD_H