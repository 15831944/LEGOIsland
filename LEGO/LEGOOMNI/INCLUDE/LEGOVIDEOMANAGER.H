#ifndef __LEGOVIDEOMANAGER
#define __LEGOVIDEOMANAGER

#include "MxVideoManager.h"
#include "Tgl.h"

class Lego3DManager;
class LegoROI;
class LegoTestTimer;

class LegoVideoManager : public MxVideoManager {
protected:
    Tgl::Renderer* m_renderer;
    Lego3DManager* m_3dManager;
    LegoROI* m_viewROI;
	LegoTestTimer* m_testTimer;
public:
    LegoVideoManager();
    virtual ~LegoVideoManager();
    virtual MxResult Create(MxVideoParam& p_param, MxTime p_tickleInterval = 100, MxBool p_createThread = FALSE);
    virtual void Destroy();
    virtual MxResult Tickle();
	virtual MxPresenter *GetPresenterAt(MxS32 p_x, MxS32 p_y);
    Tgl::Renderer* GetRenderer() { return m_renderer; }
    Lego3DManager* Get3DManager() { return m_3dManager; }
	LegoROI* GetViewROI() {return m_viewROI;}
};


#endif // __LEGOVIDEOMANAGER

