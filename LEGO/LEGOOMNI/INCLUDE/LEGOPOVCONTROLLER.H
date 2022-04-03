/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOPOVCONTROLLER_H
#define __LEGOPOVCONTROLLER_H

#include "MxCore.h"

class Lego3DView;
class LegoEntity;
class LegoNavController;

//////////////////////////////////////////////////////////////////////////////
//
// LegoMouseController

class LegoMouseController : public MxCore
{
public:
    LegoMouseController();
	~LegoMouseController();

	virtual void LeftDown(int, int);
	virtual void LeftDrag(int, int);
	virtual void LeftUp(int, int);
	virtual void RightDown(int, int);
	virtual void RightDrag(int, int);
	virtual void RightUp(int, int);

	BOOL        IsButtonDown() const { return m_isButtonDown; }
	double      ButtonX() const { return m_buttonX; }
	double      ButtonY() const { return m_buttonY; }

private:
	BOOL        m_isButtonDown;
	double      m_buttonX;
	double      m_buttonY;
};

//////////////////////////////////////////////////////////////////////////////
//
// LegoPointOfViewController

class LegoPointOfViewController : public LegoMouseController
{
public:
    LegoPointOfViewController() ;
	~LegoPointOfViewController() {}
	MxResult Create(Lego3DView* p_lego3DView); 
    virtual void Destroy();
	virtual MxResult Tickle();

	void    LeftDown(int x, int y);
	void    LeftDrag(int x, int y);
	void    LeftUp(int x, int y)
		{ LegoMouseController::LeftUp(x, y);     AffectPointOfView(); }
	void    RightDown(int x, int y)
		{ LegoMouseController::RightDown(x, y);  AffectPointOfView(); }
	void    RightDrag(int x, int y)
		{ LegoMouseController::RightDrag(x, y);  AffectPointOfView(); }
	void    RightUp(int x, int y)
		{ LegoMouseController::RightUp(x, y);    AffectPointOfView(); }

	void    OnViewSize(int width, int height);

	void SetEntity(LegoEntity* p_entity);
	LegoEntity* GetEntity() {return m_entity;}


protected:
	void AffectPointOfView();
    Lego3DView* m_lego3DView;
	LegoEntity* m_entity;
	double m_entityOffsetUp;
	LegoNavController *m_nav;

private:
};

#endif // __LEGOPOVCONTROLLER_H 
