#ifndef _ROIInspectorController_h
#define _ROIInspectorController_h

#include "Controller.h"
#include "tgl.h"        // Tgl::DoubleMatrix4

class ROIInspectorROI;

class ROIInspectorController : public MouseController
{
public:
    ROIInspectorController();

    void    SetROI(ROIInspectorROI* pROI) { m_pROI = pROI; }

	void    LeftDrag(int, int);
	void    RightDrag(int, int);

private:
    ROIInspectorROI*    m_pROI;
};

#endif /* _ROIInspectorController_h */
