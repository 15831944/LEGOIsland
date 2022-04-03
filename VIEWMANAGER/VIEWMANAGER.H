

/*
				VIEWMANAGER.H
				by Daniel Green
				Mindscape, Inc.
				March - 1996

	This file describes some classes derived from realtime classes
	introducing and managing TGL graphical features.
*/

#ifndef _VIEWMANAGER_H
#define _VIEWMANAGER_H

#include "tgl.h"
#include "realtime.h"
#include "ViewLODList.h"

class ViewLODListManager;

// vec.h defines TRACE2 and TRACE3 which conflicts w/ MFC's
// definitions
#ifdef TRACE2
#undef TRACE2
#endif
#ifdef TRACE3
#undef TRACE3
#endif
#include "vec.h"

//////////////////////////////////////////////////////////////////////////////
// ViewLOD
//

class ViewLOD : public LODObject
{
public:
    ViewLOD(Tgl::Renderer* pRenderer) 
    : m_numPolys(0), m_meshGroup(pRenderer->CreateGroup()) {}
	virtual double Cost(double pixels_covered) const
	{
		// below is a *very* simplistic cost function.
		// the area divided by full screen is fraction of screen.
		// dividing that by 10 is assuming that it takes a tenth
		// of a second to paint the full screen.
		return  pixels_covered / (640*480) / 10 * m_numPolys/5.0;
	}
    virtual ~ViewLOD() { delete m_meshGroup; }
	virtual double AveragePolyArea() const
		{ return 2 * 3.14159 * 10.0 / m_numPolys; };
	virtual int NVerts() const { return m_numPolys * 2; }
    Tgl::Group* GetGeometry() { return m_meshGroup; }
    const Tgl::Group* GetGeometry() const { return m_meshGroup; }
protected:
	int m_numPolys;
	Tgl::Group* m_meshGroup;
};


/*
	ViewROI objects represent view objects, collections of view objects,
	etc. Basically, anything which can be placed in a scene and manipilated
	by the view manager is a ViewROI.
*/

class ViewROI : public RelativeROI
{
public:
    ViewROI(Tgl::Renderer* pRenderer, ViewLODList* lodList)
    {
        SetLODList(lodList);
		geometry = pRenderer->CreateGroup();
	}
	~ViewROI() 
    {
        // SetLODList() will decrease refCount of LODList
        SetLODList(0);
        delete geometry; 
    }
	void SetLODList(ViewLODList* lodList) 
    {
        // ??? inherently type unsafe - kind of... because, now, ROI
        //     does not expose SetLODs() ...
        // solution: create pure virtual LODListBase* ROI::GetLODList()
        // and let derived ROI classes hold the LODList
        
        if (lods)
        {
            reinterpret_cast<ViewLODList*>(lods)->Release(); 
        }

        lods = lodList;

        if (lods)
        {
            reinterpret_cast<ViewLODList*>(lods)->AddRef(); 
        }
    }
	virtual double IntrinsicImportance() const { return .5; } // for now
	virtual Tgl::Group* GetGeometry() { return geometry; }
	virtual const Tgl::Group* GetGeometry() const { return geometry; }
protected:
	Tgl::Group* geometry;
	void update_world_data(const Matrix4& parent2world)
	{
		RelativeROI::update_world_data(parent2world);
		if (geometry)
		{
			Tgl::DoubleMatrix4 tgl_mat;
			SETMAT4(tgl_mat, local2world);
			Tgl::Result result = geometry->SetTransformation(tgl_mat);
			//assert(Tgl::Succeeded(result));
		}
	}
};


/*
	A simple container ROI for ViewROIs.
	Used only by the ViewManager below.
	Will be changed later to be an R-tree node when large numbers
	of vrois need to be managed.
*/
class TreeNode : public OrientableROI
{
public:
	TreeNode()
    {
        comp = new CompoundObject; 
    }
	~TreeNode() 
    {
        // for now, make sure client has removed all rois
        assert(comp->size() == 0);
        delete comp;
        comp = 0;
    }
	void Add(ViewROI &vroi);
	void Moved(ViewROI &vroi);
	void Remove(ViewROI &vroi);
	double IntrinsicImportance() const { return 1; }
protected:
	void update_world_bounding_volumes() {} // stubbed out since local2world won't change
};

class ViewManager
{
public:
	ViewManager(Tgl::Group* scene, const OrientableROI* point_of_view);
	virtual ~ViewManager();
    void    AddTestROIs(Tgl::Renderer*, ViewLODListManager*); // for testing only
	void    Add(ViewROI &vroi);
	void    Moved(ViewROI &vroi);
	void    Remove(ViewROI &vroi);
	void    Update(double secondsUsedLastFrame);
	void    SetResolution(int width, int height)
			{ rt_view.SetResolution(width, height); }
	void    SetFrustrum(double fov, double front, double back)
			{ rt_view.SetFOV(fov, front, back); }
	void	SetPOVSource(const OrientableROI* point_of_view);
    void    SetSecondsAllowed(double secondsAllowed)
            { seconds_allowed = secondsAllowed; }
    double  GetSecondsAllowed() { return  seconds_allowed; }
#ifdef _DEBUG
    double  GetSecondsUsedLastFrame() { return  seconds_used_last_frame; }
#endif
	const ROIList& GetVisibleROIs() const { return visible_rois; } 
private:
	Tgl::Group*     scene; // top of graphical R-tree
	TreeNode        roi_root; // top of ROI R-tree
	RealtimeView    rt_view;
	ROIList         visible_rois;
	IntList         visible_lod_indices;
    double          seconds_allowed;
#ifdef _DEBUG
    double          seconds_used_last_frame;
#endif
};

#endif /* _VIEWMANAGER_H */
