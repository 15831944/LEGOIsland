/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdMain.h"
#include "TimeAverage.h"
#include "MxTimer.h"
#include "LegoOmni.h"
#include "LegoInputManager.h"
#include "MxVideoManager.h"


TimeAverage::TimeAverage()
{
	Create(FALSE);
}

TimeAverage::TimeAverage(MxBool p_delayedStart)
{
	Create(p_delayedStart);
}


TimeAverage::~TimeAverage()
{
	LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(this);
	LegoOmni::GetInstance()->GetInputManager()->UnRegister(this);
}


void
TimeAverage::Create(MxBool p_delayedStart)
{
	for(int i=0; i<BIN_MAX; i++)
		m_timeBins[i] = 0;

	m_resetAtNextTickle = TRUE;

	if (p_delayedStart)
		LegoOmni::GetInstance()->GetInputManager()->Register(this);
	else
		LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(this);
}

MxResult 
TimeAverage::Tickle()
{
	MxTime currentTime = LegoOmni::GetInstance()->GetTimer()->GetTime();

	if (m_resetAtNextTickle)
	{
		m_minTime = 9999;
		m_maxTime = 0;
		m_sum = 0;
		m_count = 0;
		m_resetAtNextTickle = FALSE;
		m_lastTime = currentTime;
	}
	else
	{
		MxTime deltaTime = currentTime - m_lastTime;
		if (deltaTime < 0)
			deltaTime = 0;
		m_lastTime = currentTime;
		m_sum += deltaTime;
		m_count++;

		if (deltaTime < m_minTime)
			m_minTime = deltaTime;
		if (deltaTime > m_maxTime)
			m_maxTime = deltaTime;

		int binIndex = deltaTime/BIN_INCREMENT;
		if (binIndex >= BIN_MAX)
			binIndex = BIN_MAX-1;

		m_timeBins[binIndex]++;
	}

    return SUCCESS;
}

void 
TimeAverage::Print()
{
	FILE *outfp = fopen("\\FRM_TIME.TXT", "w");

	if (outfp)
	{
		for (int i=0; i<BIN_MAX; i++)
			fprintf(outfp, "%d:\t%d\n", (i+1)*BIN_INCREMENT, m_timeBins[i]);

		fclose(outfp);
	}

	for(int i=0; i<BIN_MAX; i++)
		m_timeBins[i] = 0;
}

MxS32
TimeAverage::Notify(MxParam& p_param)
{
	if (((MxNotificationParam&) p_param).GetNotification() == c_notificationKeyPress)
	{
		MxU8 key = ((LegoEventNotificationParam&)p_param).GetKey();
		if ((key == 's') || (key == 'S'))
		{
			// start collecting information
			LegoOmni::GetInstance()->GetVideoManager()->RegisterPresenter(this);
		}
		else if ((key == 'p') || (key == 'P'))
		{
			// stop collecting information
			LegoOmni::GetInstance()->GetVideoManager()->UnregisterPresenter(this);
			Print();
			m_resetAtNextTickle = TRUE;
		}
	}

	return FALSE;
}


