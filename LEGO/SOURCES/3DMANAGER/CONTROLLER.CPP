#include "stdafx.h"
#include "Controller.h"
#include "Lego3DView.h"
#include "ViewManager.h" 
#include "vec.h"

//////////////////////////////////////////////////////////////////////

#ifndef M_PI
#		define M_PI 3.1416
#endif
#ifdef DTOR
#       undef DTOR
#endif
#       define DTOR(angle) ((angle) * M_PI / 180.)

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

void PointOfViewController::OnViewSize(int width, int height)
{
    dev_center_x = width/2;
    dev_center_y = height/2;
}

void PointOfViewController::AffectPointOfView()
{
    ViewROI*    pPointOfView = m_rLego3DView.GetPointOfView();

    if(IsButtonDown() && pPointOfView)
    {
        int     x_diff = ButtonX() - dev_center_x;
        int     y_diff = ButtonY() - dev_center_y;
        double  trans_sf = .03; // tunes translate sensitivity
        double  deg_sf = .5;	 // tunes rotate sensitivity
        double  window_degs = 10;
        double  degs_per_pixel = window_degs / dev_center_x * deg_sf;
        double  delta_deg = degs_per_pixel * x_diff;
        double  rot_mat[3][3];
        Vector3 delta_pos, new_dir, new_pos;
        double  step_dist = -y_diff * trans_sf;

        Vector3 cur_pos(pPointOfView->GetWorldPosition());
        Vector3 cur_dir(pPointOfView->GetWorldDirection());
        
        IDENTMAT3(rot_mat);
        rot_mat[0][0] = rot_mat[2][2] = cos(DTOR(delta_deg));
        rot_mat[0][2] = rot_mat[2][0] = sin(DTOR(delta_deg));
        rot_mat[0][2] *= -1.0f;
        VXM3(new_dir, cur_dir, rot_mat);
        
        VXS3(delta_pos, new_dir, step_dist);
        VPV3(new_pos, cur_pos, delta_pos);

		Matrix4 new_mat;
		CalcLocalTransform(new_pos, new_dir, pPointOfView->GetWorldUp(), new_mat);
		pPointOfView->SetLocalTransform(new_mat);

        m_rLego3DView.Moved(*pPointOfView);
    }
}

