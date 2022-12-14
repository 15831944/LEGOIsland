// Lego3DView.cpp : implementation file
//

#include "stdafx.h"
#include "Lego3DView.h"
#include "ViewManager.h"

/////////////////////////////////////////////////////////////////////////////
// Lego3DView

Lego3DView::Lego3DView()
{
    m_pViewManager              = 0;
    m_previousRenderTime        = 0;
    m_pPointOfView              = 0;
}

Lego3DView::~Lego3DView()
{
    Destroy();
}

BOOL Lego3DView::Create(const TglSurface::CreateStruct& rCreateStruct,
                        Tgl::Renderer* pRenderer)
{
    double  viewAngle = 45;
    double  frontClippingDistance = 1;
    double  backClippingDistance = 5000;

    if (!LegoView1::Create(rCreateStruct, pRenderer))
    {
        return FALSE;
    }

    assert(GetView());
    GetView()->SetFrustrum(frontClippingDistance, backClippingDistance, viewAngle);

    assert(GetScene());
    assert(!m_pViewManager);
	m_pViewManager = new ViewManager(GetScene(), 0);
    m_pViewManager->SetResolution(GetWidth(), GetHeight());
    m_pViewManager->SetFrustrum(viewAngle, -frontClippingDistance, -backClippingDistance);
    m_previousRenderTime = 0;

    // NOTE: a derived class must inform view manager when it configures
    //       its (Tgl) view: calling Tgl::View::SetFrustrum() should be
    //       accompanied by calling ViewManager::SetFrustrum()

    return TRUE;
}

void
Lego3DView::Destroy()
{
    if (m_pPointOfView)
    {
        m_pPointOfView = 0;
        m_pViewManager->SetPOVSource(0);
    }

    delete m_pViewManager;
    m_pViewManager = 0;

    LegoView1::Destroy();
}

BOOL
Lego3DView::Add(ViewROI& rROI)
{
    assert(m_pViewManager);

    m_pViewManager->Add(rROI);

    return TRUE;
}

BOOL
Lego3DView::Remove(ViewROI& rROI)
{
    assert(m_pViewManager);

    m_pViewManager->Remove(rROI);

    if (m_pPointOfView == &rROI)
    {
        m_pPointOfView = 0;
        m_pViewManager->SetPOVSource(0);
    }

    return TRUE;
}

BOOL
Lego3DView::SetPointOfView(ViewROI& rROI)
{
    Tgl::DoubleMatrix4  transformation;
    Tgl::Result         result;

    m_pPointOfView = &rROI;

    assert(m_pViewManager);
    m_pViewManager->SetPOVSource(m_pPointOfView);

    assert(GetCamera());
    SETMAT4(transformation, rROI.GetLocalTransform());
    result = GetCamera()->SetTransformation(transformation);
    assert(Tgl::Succeeded(result));

    return TRUE;
}

BOOL
Lego3DView::Moved(ViewROI& rROI)
{
    assert(m_pViewManager);

    m_pViewManager->Moved(rROI);

    if (m_pPointOfView == &rROI)
    {
        // move the camera
        Tgl::DoubleMatrix4  transformation;
        Tgl::Result         result;

        assert(GetCamera());

        SETMAT4(transformation, rROI.GetLocalTransform());
        result = GetCamera()->SetTransformation(transformation);
        assert(Tgl::Succeeded(result));
    }

    return TRUE;
}

double
Lego3DView::Render()
{
    assert(m_pViewManager);

    m_pViewManager->Update(m_previousRenderTime);

    m_previousRenderTime = LegoView1::Render();

    return m_previousRenderTime;
}

/*
virtual Tgl::Result  Tgl::View::Pick(unsigned long x, 
                         unsigned long y,
                         const Tgl::Group** ppGroupsToPickFrom,
                         int groupsToPickFromCount,
                         const Tgl::Group**& rppPickedGroups,
                         int& rPickedGroupCount) = 0;
*/

typedef std::map<const Tgl::Group*, const ROI*, std::less<const Tgl::Group*> > Group2ROI;
 
ViewROI* Lego3DView::Pick(unsigned long x, unsigned long y)
{
	const ROIList &visible_rois = m_pViewManager->GetVisibleROIs();
	int n_in=0, n_out;
	const Tgl::Group **groups_in = new const Tgl::Group*[visible_rois.size()];
	const Tgl::Group **groups_out = NULL;
	Group2ROI roi_map;
    ViewROI* viewROI = NULL;

	// generate the list of groups to pick from which is all the geometry
	// groups of all the currently visible ROIs in the view manager.
	// Also, construct a mapping from each group back to it's ROI since that's
	// what we need to return.
	//
	WALK_STL_OBJECT(visible_rois, ROIList, vi)
	{
		ViewROI *vroi = (ViewROI*)(*vi); 
		Tgl::Group *g = vroi->GetGeometry();
		assert(g);
		groups_in[n_in++] = g;
		roi_map[g] = *vi;
	}

	// perform the pick on our TglView passing the visible groups
	//
	Tgl::View *tglview = GetView();
	assert(tglview);
	tglview->Pick(x, y, groups_in, n_in, groups_out, n_out);

	// search the returned group hierarchy from the bottom for the
	// first group which was in groups_in.
	//
	for(int i=n_out-1; i>=0; i--) {
		const Tgl::Group *g = (const Tgl::Group*)(groups_out[i]);
		if(!g) // null entries means group node wasn't in groups_in
			continue;
		Group2ROI::iterator gi = roi_map.find(g);
		if(gi != roi_map.end()) {
			viewROI = (ViewROI*)((*gi).second);
			break;
		}
	}

	// delete the heap allocated arrays.
	//
	delete[] groups_in;
	if(groups_out)
		delete[] groups_out;

    return viewROI;
}


double
Lego3DView::GetTargetRenderingRate() const
{
    double  secondsAllowed;

    assert(m_pViewManager);

    secondsAllowed = m_pViewManager->GetSecondsAllowed();

    return (secondsAllowed ? (1 / secondsAllowed) : HUGE_VAL);
}

