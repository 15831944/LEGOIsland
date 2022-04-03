#ifndef _Lego3DView_h
#define _Lego3DView_h

#include "LegoView1.h"

class ViewROI;
class ViewManager;


/////////////////////////////////////////////////////////////////////////////
// Lego3DView

class Lego3DView : public LegoView1
{
public:
    Lego3DView();
	~Lego3DView();

    BOOL            Create(const CreateStruct&, Tgl::Renderer*);
    void            Destroy();

    BOOL            Add(ViewROI&);
    BOOL            Remove(ViewROI&);
    BOOL            Moved(ViewROI&);
    BOOL            SetPointOfView(ViewROI&);

    double          Render();

    ViewROI*        Pick(unsigned long x, unsigned long y);

    ViewROI*        GetPointOfView();
    ViewManager*    GetViewManager();
    double          GetTargetRenderingRate() const;

private:
    ViewManager*    m_pViewManager;
    double          m_previousRenderTime;

    ViewROI*        m_pPointOfView;
};

/////////////////////////////////////////////////////////////////////////////
//
// Lego3DView implementation

inline
ViewManager*    
Lego3DView::GetViewManager() 
{ 
    return m_pViewManager;
}

inline
ViewROI*
Lego3DView::GetPointOfView()
{
    return m_pPointOfView;
}

#endif /* _Lego3DView_h */