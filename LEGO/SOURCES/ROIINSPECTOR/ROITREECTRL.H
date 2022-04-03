// ROITreeCtrl.h : header file
//

class LegoROI;
class LegoLOD;
class ViewLODList;

/////////////////////////////////////////////////////////////////////////////
// CROITreeCtrl window

class CROITreeCtrl : public CTreeCtrl
{
// Construction
public:
	CROITreeCtrl();

// Attributes
public:

// Operations
public:
    void    Insert(const LegoROI&);
    void    GetSelection(const LegoROI*&, const LegoLOD*&) const;

    void    EnableShortNames(BOOL enableShortNames, int shortNameSeparator);
    BOOL    ShortNamesEnabled() const { return m_shortNamesEnabled; }
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CROITreeCtrl)
	public:
	//}}AFX_VIRTUAL

    BOOL Create( DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID );

// Implementation
public:
	virtual ~CROITreeCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CROITreeCtrl)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
    void        InsertROIItems(const LegoROI&, HTREEITEM hParentItem);
    void        InsertLODListItems(const LegoROI&, HTREEITEM hParentItem);
    void        InsertPartsItems(const LegoROI&, HTREEITEM hParentItem);
    HTREEITEM   InsertROIItem(const LegoROI&, HTREEITEM hParentItem);
    HTREEITEM   InsertLODListItem(const LegoROI&, const ViewLODList&, HTREEITEM hParentItem);
    HTREEITEM   InsertPartsItem(const LegoROI&, const CompoundObject* pParts, HTREEITEM hParentItem);
    HTREEITEM   InsertLODItem(const LegoROI&, const LegoLOD&, int lodNumber, HTREEITEM hParentItem);

private:
    CImageList  m_imageList;
    int         m_roiImageIndex;
    int         m_lodListImageIndex;
    int         m_lodImageIndex;
    int         m_partsImageIndex;

    BOOL        m_shortNamesEnabled;
    int         m_shortNameSeparator;
};

/////////////////////////////////////////////////////////////////////////////
