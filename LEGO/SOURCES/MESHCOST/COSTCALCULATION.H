#ifndef _CostCalculation_h
#define _CostCalculation_h

class LegoROI;
class LegoLOD;
class BoundingBox;
class BoundingSphere;
class LegoViewWnd;
class LegoView;

class CostCalculation
{
public:
    CostCalculation();
    ~CostCalculation();

    CWinThread* CalculateCostInThread(LegoViewWnd*,
                                      LegoView*,
                                      LegoROI**,
                                      int roiCount,
                                      HWND notificationWnd,
                                      UINT doneNotificationMsg,
                                      UINT progressNotificationMsg);
    BOOL        CalculateCost(LegoViewWnd*, LegoView*,
                              LegoROI**, int roiCount);

    BOOL        Succeeded() const { return m_succeeded; }
    HANDLE&     PauseThreadEvent()      { return m_pauseThreadEvent; }
    HANDLE&     ContinueThreadEvent()   { return m_continueThreadEvent; }
    HANDLE&     KillThreadEvent()       { return m_killThreadEvent; }
    HANDLE&     ThreadKilledEvent()     { return m_threadKilledEvent; }

protected:
    UINT        ThreadProc();
    static UINT ThreadProc1(void*);

    BOOL        CalculateCost(LegoViewWnd*, LegoView*, LegoROI*);
    BOOL        CalculateCost(LegoViewWnd*, LegoView*, LegoROI*, LegoLOD*);

    BOOL        ContinueCalculateCost();
    BOOL        CalculateCameraPosition(const LegoView*,
                                        double viewAngle,
                                        double& rFrontClippingDistance,
                                        double& rBackClippingDistance,
                                        const BoundingSphere& rBoundingSphere,
                                        double& rPixelsCovered,
                                        const double cameraDirection[3],
                                        const double cameraUp[3],
                                        double cameraPosition[3]);
double          CalculatePixelsCovered(const LegoView*,
                                       double viewAngle,
                                       double frontClippingDistance,
                                       double backClippingDistance,
                                       const BoundingSphere& rWorldBoundingSphere,
                                       const double cameraDirection[3],
                                       const double cameraUp[3],
                                       const double cameraPosition[3]);

private:
    LegoViewWnd*    m_pLegoViewWnd;
    LegoView*       m_pLegoView;
    LegoROI**       m_pROIs;
    int             m_roiCount;
	HWND            m_notificationWnd;
    UINT            m_doneNotificationMsg;
    UINT            m_progressNotificationMsg;
    HANDLE          m_pauseThreadEvent;
    HANDLE          m_continueThreadEvent;
    HANDLE          m_killThreadEvent;
    HANDLE          m_threadKilledEvent;
    BOOL            m_succeeded;
};


#endif
