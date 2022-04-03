#include "stdafx.h"
#include "MeshCost.h"

#include "CostCalculation.h"
#include "Lego3DView.h"         // LegoView
#include "LegoViewWnd.h"
#include "LegoROI.h"
#include "float.h"              // FLT_EPSILON

CostCalculation::CostCalculation()
{
    m_pLegoView                 = 0;
    m_pLegoViewWnd              = 0;
    m_pROIs                     = 0;
    m_roiCount                  = 0;
    m_notificationWnd           = 0;
    m_doneNotificationMsg       = 0;
    m_progressNotificationMsg   = 0;
    m_succeeded                 = TRUE;  
    m_pauseThreadEvent      = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset;;
    m_continueThreadEvent   = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset;;
    m_killThreadEvent       = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset;
    m_threadKilledEvent     = CreateEvent(NULL, FALSE, FALSE, NULL); // auto reset, initially reset;
}

CostCalculation::~CostCalculation()
{
    m_succeeded = FALSE;  
    SetEvent(m_threadKilledEvent);
}

CWinThread*
CostCalculation::CalculateCostInThread(LegoViewWnd* pLegoViewWnd,
                                       LegoView* pLegoView,
                                       LegoROI** pROIs,
                                       int roiCount,
                                       HWND notificationWnd,
                                       UINT doneNotificationMsg,
                                       UINT progressNotificationMsg)
{
    m_pLegoViewWnd              = pLegoViewWnd;
    m_pLegoView                 = pLegoView;
    m_pROIs                     = pROIs;
    m_roiCount                  = roiCount;
    m_notificationWnd           = notificationWnd;
    m_doneNotificationMsg       = doneNotificationMsg;
    m_progressNotificationMsg   = progressNotificationMsg;
    m_succeeded                 = FALSE;  

	ResetEvent(m_pauseThreadEvent);
	ResetEvent(m_continueThreadEvent);
	ResetEvent(m_killThreadEvent);
	ResetEvent(m_threadKilledEvent);

    return AfxBeginThread(ThreadProc1, this);
}

UINT
CostCalculation::ThreadProc1(void* pArg)
{
    CostCalculation*    pCostCalculation = (CostCalculation*) pArg;

    return pCostCalculation->ThreadProc();
}

UINT
CostCalculation::ThreadProc()
{
    m_succeeded = CalculateCost(m_pLegoViewWnd, m_pLegoView, m_pROIs, m_roiCount);

    if (m_notificationWnd)
    {
        CWnd* pNotificationWnd = CWnd::FromHandle(m_notificationWnd);

		pNotificationWnd->PostMessage(m_doneNotificationMsg);
    }

    m_pLegoViewWnd              = 0;
    m_pLegoView                 = 0;
    m_pROIs                     = 0;
    m_roiCount                  = 0;
    m_notificationWnd           = 0;
    m_doneNotificationMsg       = 0;
    m_progressNotificationMsg   = 0;

    if (m_succeeded)
    {
        // thread terminating - calculation finished successfully
        return 0;
    }
    else
    {
        // thread terminating - calculation failed or thread was killed
        SetEvent(m_threadKilledEvent);
        return 1;
    }
}

BOOL
CostCalculation::CalculateCost(LegoViewWnd* pLegoViewWnd,
                               LegoView* pLegoView,
                               LegoROI** pROIs, int roiCount)
{
    BOOL    result;

    for (int i = 0; i < roiCount; i++)
    {
        result = CalculateCost(pLegoViewWnd, pLegoView, pROIs[i]);
        if (!result)
        {
            break;
        }
    }

    return result;
}

BOOL
CostCalculation::CalculateCost(LegoViewWnd* pLegoViewWnd,
                               LegoView* pLegoView,
                               LegoROI* pROI)
{
    if (pROI)
    {
	    const CompoundObject*   pCompoundObject = pROI->GetComp();
        int i;

        for (i = 0; i < pROI->GetLODCount(); i++)
        {
            const LegoLOD*  pLOD = static_cast<const LegoLOD*>(pROI->GetLOD(i));

            // notify window about progress
            if (m_notificationWnd)
            {
                CWnd* pNotificationWnd = CWnd::FromHandle(m_notificationWnd);

				pNotificationWnd->PostMessage(m_progressNotificationMsg,
                                              i,
                                              reinterpret_cast<long>(pROI));
            }

            if (!CalculateCost(pLegoViewWnd, pLegoView,
                               pROI, const_cast<LegoLOD*>(pLOD)))
            {
                return FALSE;
            }
        }

        if (pCompoundObject)
        {
            CompoundObject::const_iterator  iterator = pCompoundObject->begin();

            while (!(iterator == pCompoundObject->end()))
            {
                if (!CalculateCost(pLegoViewWnd, pLegoView,
                                   static_cast<LegoROI*>(*iterator)))
                {
                    return FALSE;
                }
                ++iterator;
            }
        }
    }
    
    return TRUE;
}

BOOL
CostCalculation::CalculateCost(LegoViewWnd* pLegoViewWnd,
                               LegoView* pLegoView,
                               LegoROI* pROI, LegoLOD* pLOD)
{
    LegoCostInfo*           pCostInfo;
    const int               costCount = 11;
    int                     rotationCount = 20;
    Tgl::Group*             pTopLevelGroup;
    const BoundingBox&      rWorldBoundingBox = pROI->GetWorldBoundingBox();
    Tgl::Translation        translation(-pROI->GetWorldBoundingSphere().Center()[0],
                                        -pROI->GetWorldBoundingSphere().Center()[1],
                                        -pROI->GetWorldBoundingSphere().Center()[2]);
    int                     width = pLegoView->GetDevice()->GetWidth();
    int                     height = pLegoView->GetDevice()->GetHeight();
    Tgl::Result             tglResult;
    BOOL                    result;
    double                  cameraDirection[3] = { 0, 0, -1 };
    double                  cameraUp[3] = { 0, 1, 0 };
    double                  cameraPosition[3] = { 0, 1.5 / 16, 0 };

    pCostInfo = new LegoCostInfo[costCount];

    // figure out camera's positions (z translations)
    BoundingSphere          boundingSphere = pROI->GetWorldBoundingSphere();
    
    // the bounding sphere's world coordinates will be at origin
    ZEROVEC3(boundingSphere.Center());

    // assemble scene:

    // 0 - create toplevel group in scene
    pTopLevelGroup = pLegoView->GetRenderer()->CreateGroup(pLegoView->GetScene());
    ASSERT(pTopLevelGroup);

    // 1 - remove any LOD geometry that may exist in ROI geometry
    ASSERT(pROI->GetGeometry());
    pROI->GetGeometry()->RemoveAll();

    // 2 - add LOD geometry to ROI geometry
    ASSERT(pLOD->GetGeometry());
    tglResult = pROI->GetGeometry()->Add(pLOD->GetGeometry());
    ASSERT(Tgl::Succeeded(tglResult));

    // 3 - add ROI geometry to toplevel group
    tglResult = pTopLevelGroup->Add(pROI->GetGeometry());
    ASSERT(Tgl::Succeeded(tglResult));

    // 4 - orient camera
#if 0
    tglResult = pLegoView->GetCamera()->SetOrientation(cameraDirection, cameraUp);
    ASSERT(Tgl::Succeeded(tglResult));
#endif

    for (int i = 0; i < costCount; i++)
    {
        double  viewAngle = 45;
        double  frontClippingDistance = 1;
        double  backClippingDistance = 5000;
        double  pixelsCovered;
        double  renderTime = 0;

        pixelsCovered = (i == 0) ? 1 : ((width * height * i * i) / ((costCount - 1) * (costCount - 1)));

        // figure out camera position
        if (!CalculateCameraPosition(pLegoView,
                                     viewAngle,
                                     frontClippingDistance,
                                     backClippingDistance,
                                     boundingSphere,
                                     pixelsCovered,
                                     cameraDirection,
                                     cameraUp,
                                     cameraPosition))
        {
            result = FALSE;
            goto done;
        }

#if 0
        TRACE("Position.z: %8.4f, PixelsCovered: %6.0f, Front:%8.4f, Back:%8.4f\n",
                cameraPosition[2], pixelsCovered, frontClippingDistance, backClippingDistance);
#endif
        // adjust frustrum (CalculateCameraPosition() may change clipping planes)
        tglResult = pLegoView->GetView()->SetFrustrum(frontClippingDistance, backClippingDistance, viewAngle);
        ASSERT(Tgl::Succeeded(tglResult));

        // position camera
#if 0
        tglResult = pLegoView->GetCamera()->SetPosition(cameraPosition);
        ASSERT(Tgl::Succeeded(tglResult));
#else
        {
            Tgl::DoubleMatrix4  transformation;
            Matrix4             transform;

            CalcLocalTransform(cameraPosition, cameraDirection, cameraUp, transform);
            SETMAT4(transformation, transform);
            tglResult = pLegoView->GetCamera()->SetTransformation(transformation);
            ASSERT(Tgl::Succeeded(tglResult));
        }
#endif
        // render mesh once to avoid "renderer noice"
        // let LegoViewWnd render so window is cleared and updated
        // Note: timing does not include time to clear and blt the 
        // rendered image to screen
        tglResult = pTopLevelGroup->SetTransformation(translation);
        ASSERT(Tgl::Succeeded(tglResult));
        pLegoViewWnd->Render();

        for (int j = 0; j < rotationCount; j++)
        {
            Tgl::DoubleMatrix4  transformation;

            // translate and rotate mesh  
            transformation  = translation;
            transformation *= Tgl::RotationY(Tgl::DegreesToRadians(360 * (j / (double) rotationCount)));

            tglResult = pTopLevelGroup->SetTransformation(transformation);
            ASSERT(Tgl::Succeeded(tglResult));

            renderTime += pLegoViewWnd->Render();

            // cancel if we are asked to
		    if (!ContinueCalculateCost())
            {
                result = FALSE;
                goto done;
            }
        }

        pCostInfo[i].SetCost((LegoFloat) (renderTime / rotationCount));
        pCostInfo[i].SetPixelsCovered(pixelsCovered);
    }

    result = TRUE;

done:
    // disassemble scene:

    // 1 - remove top level group from scene 
    pLegoView->GetScene()->Remove(pTopLevelGroup);

    // 2 - remove ROI geometry from scene
    tglResult = pTopLevelGroup->Remove(pROI->GetGeometry());
    ASSERT(Tgl::Succeeded(tglResult));

    // 3 - remove LOD geometry from ROI geometry
    tglResult = pROI->GetGeometry()->Remove(pLOD->GetGeometry());
    ASSERT(Tgl::Succeeded(tglResult));

    // 4 - delete toplevel group
    delete pTopLevelGroup;
    pTopLevelGroup = 0;

    if (result)
    {
        delete [] pLOD->GetCosts();

        pLOD->SetCosts(pCostInfo);
        pLOD->SetNumCosts(costCount);
    }
    else
    {
        delete [] pCostInfo;
    }

    return result;
}

BOOL
CostCalculation::ContinueCalculateCost()
{
    // cancel if we are asked to
    if (WaitForSingleObject(m_killThreadEvent, 0) == WAIT_OBJECT_0)
    {
         return FALSE;
    }

    // pause if we are asked to
    if (WaitForSingleObject(m_pauseThreadEvent, 0) == WAIT_OBJECT_0)
    {
        HANDLE  handles[] = { m_continueThreadEvent, m_killThreadEvent };
        DWORD   index;

        // wait for continue or kill event
        index = WaitForMultipleObjects(sizeof(handles)/sizeof(handles[0]),
                                       handles,
                                       FALSE,
                                       INFINITE);

        if (handles[index - WAIT_OBJECT_0] == m_killThreadEvent)
        {
            return FALSE;
        }
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////////
//

class FooROI : public ViewROI
{
public:
    FooROI(Tgl::Renderer* pRenderer)
    : ViewROI(pRenderer, 0)
    {
    }

    void update_world_bounding_volumes()
    {
    }
};

BOOL
CostCalculation::CalculateCameraPosition(const LegoView* pLegoView,
                                         double viewAngle,
                                         double& rFrontClippingDistance,
                                         double& rBackClippingDistance,
                                         const BoundingSphere& rWorldBoundingSphere,
                                         double& rPixelsCovered,
                                         const double cameraDirection[3],
                                         const double cameraUp[3],
                                         double cameraPosition[3])
{
    // given a bounding sphere, calculate camera positions
    // (and direction and up)
    // also given: camera direction, camera up
    // also: all camera x positions == 0, y positions == 1.5/16
    // also: assuming cameraDirection is negative z...
    // also: adjust clipping planes to ensure bounding sphere is within clipping planes
    ASSERT(fabs(cameraDirection[0]) <= FLT_EPSILON);
    ASSERT(fabs(cameraDirection[1]) <= FLT_EPSILON);
    ASSERT(fabs(cameraDirection[2] - -1) <= FLT_EPSILON);

    // set up a RealtimeView to give us projected sizes
    FooROI          rvScene(pLegoView->GetRenderer());
    FooROI          rvPointOfView(pLegoView->GetRenderer());
    RealtimeView    realtimeView(rvScene);
    double          deltaZ = rWorldBoundingSphere.Radius();
    double          desiredPixelsCovered = rPixelsCovered;
    double          pixelsCoveredEpsilon = desiredPixelsCovered / 100;
    int             width = pLegoView->GetDevice()->GetWidth();
    int             height = pLegoView->GetDevice()->GetHeight();

    double          frontClippingDistance;
    double          backClippingDistance;
    BOOL            hasClippingDistancesDecreased = FALSE;
    BOOL            hasClippingDistancesIncreased = FALSE;

    Matrix4         cameraLocalTransform;

    realtimeView.SetPOVSource(&rvPointOfView);
    realtimeView.SetResolution(width, height);

    do
    {
        frontClippingDistance   = rFrontClippingDistance;
        backClippingDistance    = rBackClippingDistance;
        cameraPosition[2]       = rWorldBoundingSphere.Center()[2];
        rPixelsCovered          = HUGE_VAL;

        realtimeView.SetFOV(viewAngle, frontClippingDistance, backClippingDistance);

        do
        {
            if (rPixelsCovered > desiredPixelsCovered)
            {
                // with this camera position we have too many pixels covered
                // move camera away from bounding sphere center
                cameraPosition[2] += deltaZ;
            }
            else
            {
                // with this camera position we have too few pixels covered
                // move camera closer to bounding sphere center
                cameraPosition[2] -= deltaZ;
                deltaZ /= 2;
            }

            CalcLocalTransform(cameraPosition,
                               cameraDirection,
                               cameraUp,
                               cameraLocalTransform);
            rvPointOfView.SetLocalTransform(cameraLocalTransform);

            rPixelsCovered = realtimeView.ProjectedSize(rWorldBoundingSphere) * width * height;

        } while (fabs(rPixelsCovered - desiredPixelsCovered) > pixelsCoveredEpsilon);

        // if bounding sphere doesn't fit within clipping planes,
        // then adjust clipping planes and calculate camera position again
        if ((rWorldBoundingSphere.Center()[2] + rWorldBoundingSphere.Radius()) >= (cameraPosition[2] - frontClippingDistance))
        {
            rFrontClippingDistance /= 10;
            rBackClippingDistance  /= 10;
            hasClippingDistancesDecreased = TRUE;
        }

        if ((rWorldBoundingSphere.Center()[2] - rWorldBoundingSphere.Radius()) <= (cameraPosition[2] - backClippingDistance))
        {
            rFrontClippingDistance *= 10;
            rBackClippingDistance  *= 10;
            hasClippingDistancesIncreased = TRUE;
        }

        if (hasClippingDistancesDecreased && hasClippingDistancesIncreased)
        {
            AfxMessageBox("Bounding Sphere does not fit within clipping planes");
            ASSERT(0);  // can be ignored...
            return FALSE;
        }

    } while (frontClippingDistance != rFrontClippingDistance);

    return TRUE;
}

double
CostCalculation::CalculatePixelsCovered(const LegoView* pLegoView,
                                        double viewAngle,
                                        double frontClippingDistance,
                                        double backClippingDistance,
                                        const BoundingSphere& rWorldBoundingSphere,
                                        const double cameraDirection[3],
                                        const double cameraUp[3],
                                        const double cameraPosition[3])
{
    // given a bounding sphere and camera position, direction and up, calculate
    // pixels covered

    FooROI          scene(pLegoView->GetRenderer());
    FooROI          pointOfView(pLegoView->GetRenderer());
    RealtimeView    realtimeView(scene);
    int             width = pLegoView->GetDevice()->GetWidth();
    int             height = pLegoView->GetDevice()->GetHeight();
    Matrix4         cameraLocalTransform;

    realtimeView.SetPOVSource(&pointOfView);
    realtimeView.SetResolution(width, height);
    realtimeView.SetFOV(viewAngle, frontClippingDistance, backClippingDistance);

    CalcLocalTransform(cameraPosition,
                       cameraDirection,
                       cameraUp,
                       cameraLocalTransform);
    pointOfView.SetLocalTransform(cameraLocalTransform);

    return realtimeView.ProjectedSize(rWorldBoundingSphere) * width * height;
}



