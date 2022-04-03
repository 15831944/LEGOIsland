
/*
                        TOWN.CPP
                        by Daniel Green
                        Mindscape, Inc
                        July - 1995

    This file contains the implementations of the Lego Town object
    and the Controller classes. As they grow, they should be broken out
    into separate implementation files, but currently are here
    deliniated into different sections.
 */

#include "stdafx.h"
#include "town.h"
#include "vec.h"

using namespace std;
using namespace Tgl;

Town::Town()
{
    Tgl::DoubleMatrix4  transformation;
    Matrix4             transform;
    double              direction[3];
    double              up[3];
    double              position[3];

    // Build the entire RL version of the town in the given
    // town description file,
    // and store the top level frame in m_pScene
    //
    
    m_pRenderer     = CreateRenderer();
    m_pScene        = m_pRenderer->CreateGroup();
    m_pSun          = 0;

    // City Planner's view
    direction[0] = 0, direction[1] = -1, direction[2] = 0;
    up[0] = 0, up[1] = 0, up[2] = 1;
    position[0] = 0, position[1] = 100, position[2] = 0;
    m_pCityPlanner = m_pRenderer->CreateGroup(m_pScene);
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pCityPlanner->SetTransformation(transformation);

    // Kid's eye view
    direction[0] = -1, direction[1] = -1, direction[2] = 1;
    up[0] = -1, up[1] = 1, up[2] = 1;
    position[0] = 200, position[1] = 200, position[2] = 200;
    m_pKidsEye = m_pRenderer->CreateGroup(m_pScene);
    CalcLocalTransform(position, direction, up, transform);
    SETMAT4(transformation, transform);
    m_pKidsEye->SetTransformation(transformation);

    // The first-person player is part of the town. It is one of
    // the town folk. The player_camera is the frame defining that
    // person's head
    //
}

Town::~Town()
{
    // ??? who destroys hierarchy
    delete m_pSun;
    delete m_pScene;
    delete m_pCityPlanner;
    delete m_pKidsEye;
    delete m_pRenderer;
}

void Town::Tickle()
{
}

//////////////////////////////////////////////////////////////////////

void LegoCitizen::update_world_data(const Matrix4& parent2world)
{
    DoubleMatrix4   transformation;
    Matrix4         transform;
    Result          result;

    LegoMovable::update_world_data(parent2world);

    // move & orient head
    // ??? head is in world space
    CalcLocalTransform(GetWorldPosition(),
                       GetWorldDirection(),
                       GetWorldUp(), 
                       transform);
    SETMAT4(transformation, transform);

    result = GetHead()->SetTransformation(transformation);
    assert(Succeeded(result));
}

//////////////////////////////////////////////////////////////////////

LegoMovable::LegoMovable(Renderer* pRenderer, ViewLODList* lods) : LegoROI(pRenderer, lods)
{
}

void LegoMovable::Tickle()
{
    // compute new position and orientation and attempt to set them
    // in the town
}

//////////////////////////////////////////////////////////////////////

LegoCitizen::LegoCitizen(Renderer* pRenderer, ViewLODList* lods)
: LegoMovable(pRenderer, lods)
{
    m_pHead     = pRenderer->CreateCamera();

    // Add rest of body (avitar) below

    // Currently hardcoding car parts for something to see
    Group*  pBody = pRenderer->CreateGroup(geometry);
    Group*  pDash = 0; //read_unit_object("car.xof", pRenderer);

    if (pDash)
    {
        DoubleMatrix4   transformation;

        transformation =  Tgl::Scale(3);
        transformation *= Tgl::RotationY(Tgl::DegreesToRadians(180));
        transformation *= Tgl::Translation(0, -0.8, 2);

        pDash->SetTransformation(transformation);

        pBody->Add(pDash);
        delete pDash;
    }

    delete pBody;
}

//////////////////////////////////////////////////////////////////////

MouseController::MouseController()
{
    m_isButtonDown  = 0;
}

MouseController::~MouseController()
{
}

void MouseController::LeftDown(int x, int y)
{
    m_isButtonDown = 1;
    m_buttonX = x;
    m_buttonY = y;
}

void MouseController::LeftUp(int x, int y)
{
    m_isButtonDown = 0;
    m_buttonX = x;
    m_buttonY = y;
}

void MouseController::LeftDrag(int x, int y)
{
    m_buttonX = x;
    m_buttonY = y;
}

void MouseController::RightDown(int x, int y)
{
    m_isButtonDown = 1;
    m_buttonX = x;
    m_buttonY = y;
}

void MouseController::RightUp(int x, int y)
{
    m_isButtonDown = 0;
    m_buttonX = x;
    m_buttonY = y;
}

void MouseController::RightDrag(int x, int y)
{
    m_buttonX = x;
    m_buttonY = y;
}

//////////////////////////////////////////////////////////////////////

EditorController::EditorController(Group* pScene)
{
    m_pScene            = pScene;
    m_pCurrentObject    = 0;
}

EditorController::~EditorController()
{
}

void EditorController::LeftDrag(int x, int y)
{
    if (m_pCurrentObject && IsButtonDown())
    {
        double              drag_dir[3];
        static const double y_dir[] = {0,1,0};
        static const double rot_sf = .5; 
        double              axis[3];
        double              degrees;


        drag_dir[0] = x - ButtonX();
        drag_dir[1] = 0;
        drag_dir[2] = y - ButtonY();
        VXV3(axis, drag_dir, y_dir);

        degrees = sqrt(NORMSQRD3(drag_dir)) * rot_sf;
        assert(0);
#if 0
        m_pCurrentObject->AddRotation(CombineAfter, -axis[0], -axis[1], -axis[2], DTOR(degrees));
#endif
    }

    MouseController::LeftDrag(x, y); // stores new cursor position
}

void EditorController::RightDrag(int x, int y)
{
    if (m_pCurrentObject && IsButtonDown())
    {
        double  xdiff = x-ButtonX();
        double  ydiff = y-ButtonY();
        double  max_diff = (ABS(xdiff) > ABS(ydiff)) ? xdiff : ydiff;
        double  scaleFactor;

        scaleFactor = max_diff > 0 ? 1.1 : 0.9;
        assert(0);
#if 0
        m_pCurrentObject->AddScale(CombineAfter, scaleFactor, scaleFactor, scaleFactor);
#endif
    }

    MouseController::RightDrag(x, y); // stores new cursor position
}

void EditorController::SetCurrentObject(Group* pObject)
{
    if (find(m_pObjects.begin(), m_pObjects.end(), pObject) != m_pObjects.end())
    {
        m_pCurrentObject = pObject;
    }
}

void EditorController::Remove(Group* pObject)
{
    vector<Group*>::iterator iter = find(m_pObjects.begin(), m_pObjects.end(), pObject);

    if (iter != m_pObjects.end())
    {
        if (pObject == m_pCurrentObject)
        {
            // select next
            if ((iter + 1) != m_pObjects.end())
            {
                m_pCurrentObject = *(iter + 1);
            }
            else if (iter != m_pObjects.begin())
            {
                m_pCurrentObject = *(iter - 1);
            }
            else
            {
                m_pCurrentObject = 0;
            }
        }

        m_pScene->Remove(pObject);
        delete pObject;
        m_pObjects.erase(iter);
    }
}

void EditorController::RemoveAll()
{
    vector<Group*>::iterator iter = m_pObjects.begin();

    while (iter != m_pObjects.end())
    {
        Group* pObject = *iter;

        m_pScene->Remove(pObject);
        delete pObject;
        ++iter;
    }
    m_pObjects.erase(m_pObjects.begin(), m_pObjects.end());
    m_pCurrentObject = 0;
}

//////////////////////////////////////////////////////////////////////

CitizenController::CitizenController(LegoCitizen* pCitizen) 
{
    Vector3 pos, dir, up;

    pos[0]  = 0;
    pos[1]  = 10;
    //pos[2] = 4;
    pos[2]  = -100;
    dir[0]  = sin(DTOR(45./2));
    dir[1]  = 0;
    dir[2]  = cos(DTOR(45./2));
    up[0]   = 0;
    up[1]   = 1;
    up[2]   = 0;

    m_pCitizen = pCitizen;

    //assert(cur_player);
	Matrix4 xfm;
	CalcLocalTransform(pos, dir, up, xfm);
	m_pCitizen->SetLocalTransform(xfm);
}

CitizenController::~CitizenController()
{
}

void CitizenController::OnViewSize(int width, int height)
{
    dev_center_x = width/2;
    dev_center_y = height/2;
}

void CitizenController::AffectCitizen()
{
    if(IsButtonDown() && m_pCitizen)
    {
        int       x_diff = ButtonX() - dev_center_x;
        int       y_diff = ButtonY() - dev_center_y;
        double    trans_sf = .03; // tunes translate sensitivity
        double    deg_sf = .5;	 // tunes rotate sensitivity
        double    window_degs = 10;
        double    degs_per_pixel = window_degs / dev_center_x * deg_sf;
        double    delta_deg = degs_per_pixel * x_diff;
        double    rot_mat[3][3];
        Vector3   delta_pos, new_dir, new_pos;
        double    step_dist = -y_diff * trans_sf;

        Vector3 cur_pos(m_pCitizen->GetWorldPosition());
        Vector3 cur_dir(m_pCitizen->GetWorldDirection());
        
        IDENTMAT3(rot_mat);
        rot_mat[0][0] = rot_mat[2][2] = cos(DTOR(delta_deg));
        rot_mat[0][2] = rot_mat[2][0] = sin(DTOR(delta_deg));
        rot_mat[0][2] *= -1.0f;
        VXM3(new_dir, cur_dir, rot_mat);
        
        VXS3(delta_pos, new_dir, step_dist);
        VPV3(new_pos, cur_pos, delta_pos);

		Matrix4 new_mat;
		CalcLocalTransform(new_pos, new_dir, m_pCitizen->GetWorldUp(), new_mat);
		m_pCitizen->SetLocalTransform(new_mat);
    }
}

 //////////////////////////////////////////////////////////////////////

/*
 * some RLBox utilities
 */
static void get_box_center(const float min[3],
                           const float max[3],
                           Vector3 &center)
{
    center[0] = (max[0] + min[0]) / 2;
    center[1] = (max[1] + min[1]) / 2;
    center[2] = (max[2] + min[2]) / 2;
}

static double get_box_max_dim(const float min[3], const float max[3])
{
    double  xdim = max[0] - min[0];
    double  ydim = max[1] - min[1];
    double  zdim = max[2] - min[2];

    return MAX(xdim, MAX(ydim, zdim));
}
