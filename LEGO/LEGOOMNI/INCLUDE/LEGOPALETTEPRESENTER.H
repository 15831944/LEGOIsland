#ifndef __LEGOPALETTEPRESENTER
#define __LEGOPALETTEPRESENTER

#include "MxVideoPresenter.h"

class MxPalette;

class LegoPalettePresenter : public MxVideoPresenter {
protected:
    MxPalette* m_palette;
    void Init();
    void Destroy(MxBool p_fromDestructor);
    MxResult CreatePalette(MxDSChunk* p_chunk);
    virtual void StartingTickle();
    virtual void StreamingTickle();
public:
    LegoPalettePresenter();
    ~LegoPalettePresenter();
    virtual MxResult Create();
    virtual void Destroy();
	virtual MxResult Tickle();
    virtual MxResult PutData();
    static const MxChar* HandlerClassName() { return "LegoPalettePresenter"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
};

#endif // __LEGOPALETTEPRESENTER

