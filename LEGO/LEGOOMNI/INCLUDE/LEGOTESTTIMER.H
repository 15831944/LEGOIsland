/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOTESTTIMER_H
#define __LEGOTESTTIMER_H

// Omni header files
#include "MxCore.h"

class LegoTestTimer : public MxCore {
protected:
	int		**m_timers;
	int		*m_lastTime;
	int		*m_totalTime;
	int		m_numTimers;
	int		m_numBins;
	int		m_interval;
	MxBool	m_enable;
	MxBool	m_keyRegistered;

public:
	LegoTestTimer(int p_numTimers, int p_interval, int p_maxTime, int p_type);
	~LegoTestTimer();

	void	Tick(int p_timer);
	void	ResetAtNextTick();
	void	Print();

	MxS32	Notify(MxParam& p_param);
    static const MxChar* HandlerClassName() { return "LegoTestTimer"; }
    virtual const MxChar* ClassName() { return HandlerClassName(); }
};


#endif // __LEGOTESTTIMER_H

