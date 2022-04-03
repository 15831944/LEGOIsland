/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoTestTimer.h"
#include "MxTimer.h"
#include "LegoOmni.h"
#include "LegoInputManager.h"



LegoTestTimer::LegoTestTimer(int p_numTimers, int p_interval, int p_maxTime, int p_type)
{
	m_enable = FALSE;
	m_keyRegistered = FALSE;

	if (p_interval > 0)
	{
		m_numTimers = p_numTimers;
		m_interval = p_interval;
		m_numBins = p_maxTime/m_interval;
		m_lastTime = new int [m_numTimers];
		m_totalTime = new int [m_numTimers];
		m_timers = new int *[m_numTimers];
		for (int i=0; i<m_numTimers; i++)
		{
			m_lastTime[i] = -1;
			m_timers[i] = new int [m_numBins];
			for (int j=0; j<m_numBins; j++)
				m_timers[i][j] = 0;
		}
		
	}
	else
	{
		m_numTimers = 0;
		m_interval = 0;
		m_numBins = 0;
		m_lastTime = NULL;
		m_totalTime = NULL;
		m_timers = NULL;
	}
}


LegoTestTimer::~LegoTestTimer()
{
	if (m_keyRegistered && LegoOmni::GetInstance()->GetInputManager())
		LegoOmni::GetInstance()->GetInputManager()->UnRegister(this);
	m_enable = FALSE;
	if (m_numTimers)
	{
		delete [] m_lastTime;
		delete [] m_totalTime;
		for (int i=0; i< m_numTimers; i++)
		{
			delete [] m_timers[i];
		}
		delete [] m_timers;
	}
}


void 
LegoTestTimer::Tick(int p_timer)
{
	if (m_enable)
	{
		MxTime currentTime = LegoOmni::GetInstance()->GetTimer()->GetTime();
		int previousTimer = p_timer ? p_timer-1: 0;

		if (m_lastTime[p_timer] == -1)
		{
			m_lastTime[p_timer] = currentTime;
			m_totalTime[p_timer] = 0;
			for(int bin=0; bin<m_numBins; bin++)
				m_timers[p_timer][bin] = 0;
		}
		else
		{
			MxTime deltaTime = currentTime - m_lastTime[previousTimer];
			if (deltaTime < 0)
				deltaTime = 0;
			m_lastTime[p_timer] = currentTime;

			int binIndex = deltaTime/m_interval;
			if (binIndex >= m_numBins)
				binIndex = m_numBins-1;

			m_timers[p_timer][binIndex]++;
			m_totalTime[p_timer] += deltaTime;
		}
	}
	else if (!m_keyRegistered)
	{
		LegoOmni::GetInstance()->GetInputManager()->Register(this);
		m_keyRegistered = TRUE;
	}

}

void 
LegoTestTimer::Print()
{
	FILE *outfp = fopen("\\TEST_TIME.TXT", "w");

	if (outfp)
	{
		int t;
		fprintf(outfp, "timer");
		for (t=0; t<m_numTimers; t++)
			fprintf(outfp, "%8d ", t);

		fprintf(outfp, "\n");

		for (int i=0; i<m_numBins; i++)
		{
			fprintf(outfp, "%3d: ", (i+1)*m_interval);
			
			for (int j=0; j<m_numTimers; j++)
			{
				fprintf(outfp, "%8d ", m_timers[j][i]);
			}
			fprintf(outfp, "\n");
		}

		fprintf(outfp, "ttime");
		for (t=0; t<m_numTimers; t++)
			fprintf(outfp, "%8d ", m_totalTime[t]);

		fclose(outfp);
	}

	ResetAtNextTick();
}

void 
LegoTestTimer::ResetAtNextTick()
{
	for(int i=0; i<m_numTimers; i++)
		m_lastTime[i] = -1;
}


MxS32
LegoTestTimer::Notify(MxParam& p_param)
{
	if (((MxNotificationParam&) p_param).GetNotification() == c_notificationKeyPress)
	{
		MxU8 key = ((LegoEventNotificationParam&)p_param).GetKey();
		if ((key == 's') || (key == 'S'))
		{
			// start collecting information
			ResetAtNextTick();
			m_enable = TRUE;
		}
		else if ((key == 'p') || (key == 'P'))
		{
			// stop collecting information
			m_enable = FALSE;
			Print();
		}
	}

	return FALSE;
}


