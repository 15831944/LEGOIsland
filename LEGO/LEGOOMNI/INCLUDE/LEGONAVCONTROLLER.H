/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGONAVCONTROLLER_H
#define __LEGONAVCONTROLLER_H

#include "MxCore.h"

//////////////////////////////////////////////////////////////////////////////
//
// LegoMouseController

class LegoNavController : public MxCore
{
public:
    LegoNavController();
	~LegoNavController() { Destroy(); }

	void SetTargets(int p_hPos, int p_vPos, MxBool p_accel);
	void SetControlMax(int p_hMax, int p_vMax);
	void SetTrackDefaultParams(MxBool p_state){ m_trackDefault = p_state; }
	void SetToDefaultParams();
	MxBool CalculateNewPosDir(const Vector3 &p_curPos,
									  const Vector3 &p_curDir,
									  Vector3 &p_newPos,
									  Vector3 &p_newDir);
	double CalculateNewSpeed(const double p_oldSpeed);

	static void GetDefaults(int *p_dz,
							   double *p_lv, double *p_rv,
							   double *p_la, double *p_ra,
							   double *p_ld, double *p_rd,
							   double *p_lmina, double *p_rmina,
							   double *p_rs, MxBool *p_urs);

	static void SetDefaults(int p_dz,
							   double p_lv, double p_rv,
							   double p_la, double p_ra,
							   double p_ld, double p_rd,
							   double p_lmina, double p_rmina,
							   double p_rs, MxBool p_urs);

protected:
	double	CalculateNewVel(double p_targetVel, double p_currentVel, double p_accel, double p_time);
	double	CalculateNewTargetVel(int p_pos, int p_center, double p_max);
	double	CalculateNewAccel(int p_pos, int p_center, double p_max, int p_min);
    void Destroy(MxBool p_fromDestructor);
	void Destroy();

	int     m_hMax;
    int     m_vMax;
	int		m_deadZone;
	double	m_zeroThreshold;
	double	m_linearVel;
	double	m_rotationalVel;
	double	m_targetLinearVel;
	double	m_targetRotationalVel;
	double	m_maxLinearVel;
	double	m_maxRotationalVel;
	double	m_linearAccel;
	double	m_rotationalAccel;
	double	m_maxLinearAccel;
	double	m_maxRotationalAccel;
	double	m_minLinearAccel;
	double	m_minRotationalAccel;
	double	m_maxLinearDeccel;
	double	m_maxRotationalDeccel;
	double	m_rotSensitivity;
	MxBool	m_useRotationalVel;
	MxTime	m_lastTime;
	MxBool	m_trackDefault;


	// one copy of defaults (these can be set by App.)
	static int		m_defdeadZone;
	static double	m_defzeroThreshold;
	static double	m_defmaxLinearVel;
	static double	m_defmaxRotationalVel;
	static double	m_defmaxLinearAccel;
	static double	m_defmaxRotationalAccel;
	static double	m_defminLinearAccel;
	static double	m_defminRotationalAccel;
	static double	m_defmaxLinearDeccel;
	static double	m_defmaxRotationalDeccel;
	static double	m_defrotSensitivity;
	static MxBool	m_defuseRotationalVel;

};

#endif // __LEGOPOVCONTROLLER_H 
