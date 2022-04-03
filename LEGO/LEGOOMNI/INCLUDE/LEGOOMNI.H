/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOOMNI_H
#define __LEGOOMNI_H

#include "MxMain.h"
#include "LWorld.h"

class LegoVideoManager;
class LegoInputManager;
class ViewLODListManager;
class LegoTextureContainer;

class LegoOmni : public MxOmni { 
protected:
    ViewLODListManager* m_viewLODListManager;
	LegoInputManager *m_inputManager;
    LegoTextureContainer* m_textureContainer;
    LegoWorldList* m_worldList;
    LegoOmni();
    virtual ~LegoOmni();
    virtual void Init();
public:
	virtual void Destroy();
    virtual MxResult Create(MxOmniCreateParam& p_param);
	static void CreateInstance();
    static LegoOmni* GetInstance();
	LegoInputManager *GetInputManager() { return m_inputManager; }
    ViewLODListManager* GetViewLODListManager() { return m_viewLODListManager; }
    LegoTextureContainer* GetTextureContainer() { return m_textureContainer; }
    
    void AddWorld(LegoWorld* p_world) { m_worldList->Append(p_world); }
    LegoWorldList* GetWorldList() { return m_worldList; }
    LegoWorld* GetWorld(const MxChar* p_worldName);
};


#endif // __LEGOOMNI_H

