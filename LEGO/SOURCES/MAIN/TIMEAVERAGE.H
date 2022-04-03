/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __TIMEAVERAGE_H
#define __TIMEAVERAGE_H

// Omni header files
#include "MxPresenter.h"

#define MAX_FRAME_TIME 1000
#define BIN_MAX 100
#define BIN_INCREMENT (MAX_FRAME_TIME/BIN_MAX)

class TimeAverage : public MxPresenter {
protected:
	MxTime	m_minTime;
	MxTime	m_maxTime;
	MxTime	m_lastTime;
	MxTime	m_sum;
	int		m_count;
	MxBool	m_resetAtNextTickle;
	int		m_timeBins[BIN_MAX];

public:
	TimeAverage(MxBool);
	TimeAverage();
	virtual ~TimeAverage();
	void Create(MxBool p_delayedStart);
	virtual MxResult Tickle();
	virtual void EndAction() {};
	virtual MxResult StartAction(MxStreamController* p_controller, MxDSAction* p_action) { return SUCCESS; }
	virtual void Destroy() {}
	virtual MxResult Create() { return SUCCESS; }


	void	ResetAtNextTickle() { m_resetAtNextTickle = TRUE; }
	MxTime	GetMin() { return m_minTime; }
	MxTime	GetMax() { return m_maxTime; }
	MxTime	GetAverage() { return m_count ? m_sum/m_count : 0; }
	void	Print();
	MxS32	Notify(MxParam& p_param);


    static const MxChar* HandlerClassName() { return "TimeAverage"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
};


#endif // __TIMEAVERAGE_H

