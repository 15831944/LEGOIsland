/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "TGL.h"
#include "Lego3DView.h"
#include "ViewManager.h" 
#include "vec.h"
#include "MxTickleManager.h"
#include "MxTimer.h"
#include "LegoOmni.h"
#include "LegoNavController.h"

//////////////////////////////////////////////////////////////////////

#ifndef M_PI
#		define M_PI 3.1416
#endif
#ifdef DTOR
#       undef DTOR
#endif
#       define DTOR(angle) ((angle) * M_PI / 180.)

//////////////////////////////////////////////////////////////////////

int		LegoNavController::m_defdeadZone = 50;
double	LegoNavController::m_defzeroThreshold = 0.001;
double	LegoNavController::m_defmaxLinearVel = 10.0;
double	LegoNavController::m_defmaxRotationalVel = 20.0;
double	LegoNavController::m_defmaxLinearAccel = 8.0;
double	LegoNavController::m_defmaxRotationalAccel = 30.0;
double	LegoNavController::m_defminLinearAccel = 4.0;
double	LegoNavController::m_defminRotationalAccel = 15.0;
double	LegoNavController::m_defmaxLinearDeccel = 10.0;
double	LegoNavController::m_defmaxRotationalDeccel = 30.0;
double	LegoNavController::m_defrotSensitivity = 0.2;
MxBool	LegoNavController::m_defuseRotationalVel = FALSE;

//////////////////////////////////////////////////////////////////////

LegoNavController::LegoNavController() 
{
	SetToDefaultParams();
	m_lastTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
}


void
LegoNavController::Destroy()
{
}

void
LegoNavController::SetControlMax(int p_hMax, int p_vMax)
{
    m_hMax = p_hMax;
    m_vMax = p_vMax;
}

void
LegoNavController::SetToDefaultParams()
{
	m_deadZone = m_defdeadZone;
	m_zeroThreshold = m_defzeroThreshold;
	m_maxRotationalAccel = m_defmaxRotationalAccel;
	m_maxLinearAccel = m_defmaxLinearAccel;
	m_minRotationalAccel = m_defminRotationalAccel;
	m_minLinearAccel = m_defminLinearAccel;
	m_maxRotationalDeccel = m_defmaxRotationalDeccel;
	m_maxLinearDeccel = m_defmaxLinearDeccel;
	m_maxRotationalVel = m_defmaxRotationalVel;
	m_maxLinearVel = m_defmaxLinearVel;
	m_useRotationalVel = m_defuseRotationalVel;
	m_rotSensitivity = m_defrotSensitivity;
}

void
LegoNavController::GetDefaults(int *p_dz,
							   double *p_lv, double *p_rv,
							   double *p_la, double *p_ra,
							   double *p_ld, double *p_rd,
							   double *p_lmina, double *p_rmina,
							   double *p_rs, MxBool *p_urs)
{
	*p_dz = m_defdeadZone;
	*p_lv = m_defmaxLinearVel;
	*p_rv = m_defmaxRotationalVel;
	*p_la = m_defmaxLinearAccel;
	*p_ra = m_defmaxRotationalAccel;
	*p_ld = m_defmaxLinearDeccel;
	*p_rd = m_defmaxRotationalDeccel;
	*p_lmina = m_defminLinearAccel;
	*p_rmina = m_defminRotationalAccel;
	*p_rs = m_defrotSensitivity;
	*p_urs = m_defuseRotationalVel;
}

void
LegoNavController::SetDefaults(int p_dz,
							   double p_lv, double p_rv,
							   double p_la, double p_ra,
							   double p_ld, double p_rd,
							   double p_lmina, double p_rmina,
							   double p_rs, MxBool p_urs)
{
	m_defdeadZone = p_dz;
	m_defmaxLinearVel = p_lv;
	m_defmaxRotationalVel = p_rv;
	m_defmaxLinearAccel = p_la;
	m_defmaxRotationalAccel = p_ra;
	m_defmaxLinearDeccel = p_ld;
	m_defmaxRotationalDeccel = p_rd;
	m_defminLinearAccel = p_lmina;
	m_defminRotationalAccel = p_rmina;
	m_defrotSensitivity = p_rs;
	m_defuseRotationalVel = p_urs;
}

void
LegoNavController::SetTargets(int p_hPos, int p_vPos, MxBool p_accel)
{
	if (m_trackDefault)
		SetToDefaultParams();

	if(p_accel)
	{
		m_targetRotationalVel = CalculateNewTargetVel(p_hPos, m_hMax/2, m_maxRotationalVel);
		m_targetLinearVel = CalculateNewTargetVel(m_vMax - p_vPos, m_vMax/2, m_maxLinearVel);
		m_rotationalAccel = CalculateNewAccel(p_hPos, m_hMax/2, m_maxRotationalAccel, m_minRotationalAccel);
		m_linearAccel = CalculateNewAccel(m_vMax - p_vPos, m_vMax/2, m_maxLinearAccel, m_minLinearAccel);
	}
	else
	{
		m_targetRotationalVel = 0;
		m_targetLinearVel = 0;
		m_linearAccel = m_maxLinearDeccel;
		m_rotationalAccel = m_maxRotationalDeccel;
	}
}


double
LegoNavController::CalculateNewTargetVel(int p_pos, int p_center, double p_max)
{
	double newVel;
	int diff = p_pos - p_center;

	if (diff > m_deadZone)
		newVel = (diff - m_deadZone) * p_max / (p_center - m_deadZone);
	else if (diff < -m_deadZone)
		newVel = (diff + m_deadZone) * p_max / (p_center - m_deadZone);
	else
		newVel = 0.0;

	return newVel;
}



double
LegoNavController::CalculateNewAccel(int p_pos, int p_center, double p_max, int p_min)
{
	double newAccel;
	int diff = p_pos - p_center;

	diff = Abs(diff);
	diff = Max(diff, p_min);
	newAccel = diff * p_max / p_center;

	return newAccel;
}


double
LegoNavController::CalculateNewVel(	double p_targetVel,
									double p_currentVel,
									double p_accel,
									double p_time)
{
	double newVel = p_currentVel;

	double velDiff = p_targetVel - p_currentVel;
	int vSign = velDiff > 0 ? 1: -1;
	if (Abs(velDiff) > m_zeroThreshold)
	{
		double deltaVel = p_accel * p_time;
		newVel = p_currentVel + (deltaVel * vSign);

		// clamp to target vel
		if (vSign > 0)
			newVel = Min(newVel, p_targetVel);
		else
			newVel = Max(newVel, p_targetVel);
	}

	return newVel;
}

double
LegoNavController::CalculateNewSpeed(const double p_oldSpeed)
{
	MxTime currentTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
	double deltaTime = (currentTime - m_lastTime) / 1000.0;
	m_lastTime = currentTime;

	m_linearVel = CalculateNewVel(	m_targetLinearVel,
									p_oldSpeed,
									m_linearAccel,
									deltaTime);

	return m_linearVel;
}

MxBool
LegoNavController::CalculateNewPosDir(const Vector3 &p_curPos,
									  const Vector3 &p_curDir,
									  Vector3 &p_newPos,
									  Vector3 &p_newDir)
{
	MxBool changed = FALSE;

	MxTime currentTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
	double deltaTime = (currentTime - m_lastTime) / 1000.0;
	m_lastTime = currentTime;

	if(m_useRotationalVel)
		m_rotationalVel = CalculateNewVel(	m_targetRotationalVel,
											m_rotationalVel,
											m_rotationalAccel,
											deltaTime);
	else
		m_rotationalVel = m_targetRotationalVel;

	m_linearVel = CalculateNewVel(	m_targetLinearVel,
									m_linearVel,
									m_linearAccel,
									deltaTime);

	if ((Abs(m_rotationalVel) > m_zeroThreshold) ||
		(Abs(m_linearVel) > m_zeroThreshold))
	{
		double      rot_mat[3][3];
		Vector3     delta_pos, new_dir, new_pos;

		VXS3(delta_pos, p_curDir, m_linearVel * deltaTime);
		VPV3(p_newPos, p_curPos, delta_pos);

		double delta_rad;
		if (m_useRotationalVel)
			delta_rad = DTOR(m_rotationalVel * deltaTime);
		else
			delta_rad = DTOR(m_rotationalVel * m_rotSensitivity);

		IDENTMAT3(rot_mat);
		rot_mat[0][0] = rot_mat[2][2] = cos(delta_rad);
		rot_mat[0][2] = rot_mat[2][0] = sin(delta_rad);
		rot_mat[0][2] *= -1.0f;
		VXM3(p_newDir, p_curDir, rot_mat);

		changed = TRUE;
	}

	return changed;
}
