#ifndef _LegoView1_h
#define _LegoView1_h

#include "TglSurface.h"

class Tgl::Camera;

/////////////////////////////////////////////////////////////////////////////
// LegoView

class LegoView : public TglSurface
{
public:
    LegoView();
	~LegoView();

    BOOL            Create(const CreateStruct&, Tgl::Renderer*);
    void            Destroy();

    Tgl::Group*     GetScene() const;
    Tgl::Camera*    GetCamera() const;

protected:
    Tgl::View*      CreateView(Tgl::Renderer*, Tgl::Device*);

private:
    Tgl::Group*     m_pScene;
    Tgl::Camera*    m_pCamera;
};

/////////////////////////////////////////////////////////////////////////////
// LegoView implementation

inline
Tgl::Group*
LegoView::GetScene() const
{
    return  m_pScene;
}

inline
Tgl::Camera*
LegoView::GetCamera() const
{
    return  m_pCamera;
}

/////////////////////////////////////////////////////////////////////////////
// LegoView1

class LegoView1 : public LegoView
{
public:
    LegoView1();
	~LegoView1();

    BOOL            Create(const TglSurface::CreateStruct&, Tgl::Renderer*);
    void            Destroy();

private:
    Tgl::Light*     m_pSunLight;
    Tgl::Light*     m_pDirectionalLight;
    Tgl::Light*     m_pAmbientLight;
};


#endif /* _LegoView1_h */