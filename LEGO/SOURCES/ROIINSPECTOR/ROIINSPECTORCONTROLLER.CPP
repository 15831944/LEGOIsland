#include "stdafx.h"
#include "ROIInspectorController.h"
#include "ROIInspectorROI.h"
#include "std.h"    // min

#ifndef M_PI
#	define M_PI		3.14159265358979323846
#endif
#ifndef DTOR
#	define DTOR(deg) ((deg) * M_PI / 180.0)
#endif
#ifndef RTOD
#	define RTOD(rad) ((rad) * 180.0 / M_PI)
#endif
#ifndef ABS
#define ABS(n) (((n) > 0) ? (n) : -(n))
#endif

ROIInspectorController::ROIInspectorController()
{
    m_pROI = 0;
}

void ROIInspectorController::LeftDrag(int x, int y)
{
    if (m_pROI && IsButtonDown())
    {
        double  multiplier = .007;
        double  deltaRotateY = multiplier * (x - ButtonX());
        double  deltaRotateX = multiplier * (y - ButtonY());
        Vector3 rotation;

        rotation[0] = m_pROI->GetRotation()[0] + deltaRotateX;
        rotation[1] = m_pROI->GetRotation()[1] + deltaRotateY;
        rotation[2] = m_pROI->GetRotation()[2];

        m_pROI->Rotate(rotation);
#if 0
        TRACE("ROIInspectorController::LeftDrag(): Rotate[%.2f, %.2f, %.2f]\n",
                (double) RTOD(m_pROI->GetRotation()[0]),
                (double) RTOD(m_pROI->GetRotation()[1]),
                (double) RTOD(m_pROI->GetRotation()[2]));
#endif
    }

    MouseController::LeftDrag(x, y); // stores new cursor position
}

void ROIInspectorController::RightDrag(int x, int y)
{
    if (m_pROI && IsButtonDown())
    {
        double  multiplier = .008;
        double  delta = multiplier * (y - ButtonY());
        
        m_pROI->Scale(std::max(m_pROI->GetScale() + delta, 0.0));

#if 0
        TRACE("ROIInspectorController::RightDrag(): Scale[%.2f]\n",
                (double) m_pROI->GetScale());
#endif
    }

    MouseController::RightDrag(x, y); // stores new cursor position
}
