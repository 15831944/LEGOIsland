#ifndef _Controller_h
#define _Controller_h

class Lego3DView;

//////////////////////////////////////////////////////////////////////////////
//
// Controller

class Controller {
public:
    Controller() {}
	virtual ~Controller() = 0;
};

inline Controller::~Controller() {}

//////////////////////////////////////////////////////////////////////////////
//
// MouseController

class MouseController : public Controller
{
public:
    MouseController();
	~MouseController();

	virtual void LeftDown(int, int);
	virtual void LeftDrag(int, int);
	virtual void LeftUp(int, int);
	virtual void RightDown(int, int);
	virtual void RightDrag(int, int);
	virtual void RightUp(int, int);

	int         IsButtonDown() const { return m_isButtonDown; }
	double      ButtonX() const { return m_buttonX; }
	double      ButtonY() const { return m_buttonY; }

private:
	int         m_isButtonDown;
	double      m_buttonX;
	double      m_buttonY;
};

//////////////////////////////////////////////////////////////////////////////
//
// PointOfViewController

class PointOfViewController : public MouseController
{
public:
    PointOfViewController(Lego3DView& rLego3DView) : m_rLego3DView(rLego3DView) {}
	~PointOfViewController() {}

	void    LeftDown(int x, int y)
		{ MouseController::LeftDown(x, y);   AffectPointOfView(); }
	void    LeftDrag(int x, int y)
		{ MouseController::LeftDrag(x, y);   AffectPointOfView(); }
	void    LeftUp(int x, int y)
		{ MouseController::LeftUp(x, y);     AffectPointOfView(); }
	void    RightDown(int x, int y)
		{ MouseController::RightDown(x, y);  AffectPointOfView(); }
	void    RightDrag(int x, int y)
		{ MouseController::RightDrag(x, y);  AffectPointOfView(); }
	void    RightUp(int x, int y)
		{ MouseController::RightUp(x, y);    AffectPointOfView(); }

	void    OnViewSize(int width, int height);

protected:
	void    AffectPointOfView();

private:
    Lego3DView& m_rLego3DView;
	int         dev_center_x;
    int         dev_center_y;
};

#endif /* _Controller_h */
