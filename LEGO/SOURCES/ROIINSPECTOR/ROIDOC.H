// ROIDoc.h : interface of the CROIDoc class
//
/////////////////////////////////////////////////////////////////////////////

class ROI;
class LegoROI;
class LegoAnim;
class ViewLODListManager;
namespace Tgl
{
    class Renderer;
}

//////////////

class CROIDoc : public CDocument
{
protected: // create from serialization only
	CROIDoc();
	DECLARE_DYNCREATE(CROIDoc)

// Attributes
public:
    int         GetROICount() const { return m_roiCount; }
    LegoROI*    GetROI(int i) const { ASSERT(i < m_roiCount); return m_pROIs[i]; }
    LegoAnim*   GetAnimation(int roiIndex) const;
    int         GetTotalLODCount(const ROI*) const;

// Operations
public:
    BOOL        SetManagers(Tgl::Renderer*, ViewLODListManager*);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROIDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void DeleteContents();
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CROIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CROIDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
    Tgl::Renderer*      m_pRenderer;
    ViewLODListManager* m_pViewLODListManager;
    LegoROI**           m_pROIs;
    int                 m_roiCount;
    LegoAnim*           m_trees;
};

/////////////////////////////////////////////////////////////////////////////
