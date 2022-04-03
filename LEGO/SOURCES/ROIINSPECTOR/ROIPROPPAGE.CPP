// ROIPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "ROIPropPage.h"

#include "LegoROI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROIPropPage property page

IMPLEMENT_DYNCREATE(CROIPropPage, CPropertyPage)

CROIPropPage::CROIPropPage() : CPropertyPage(CROIPropPage::IDD)
{
    m_psp.pszIcon   = MAKEINTRESOURCE(IDI_ROI);
    m_psp.dwFlags   |= PSP_USEICONID;

	//{{AFX_DATA_INIT(CROIPropPage)
	m_name = _T("");
	m_lodCount = _T("");
	m_partsCount = _T("");
	m_translation = _T("");
	m_direction = _T("");
	m_up    = _T("");
	m_boundingSphereCenter = _T("");
	m_boundingSphereRadius = _T("");
	m_boundingBoxMin = _T("");
	m_boundingBoxMax = _T("");
	//}}AFX_DATA_INIT
}

CROIPropPage::~CROIPropPage()
{
}

void CROIPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CROIPropPage)
	DDX_Text(pDX, IDC_ROINAME, m_name);
	DDX_Text(pDX, IDC_STATIC2, m_lodCount);
	DDX_Text(pDX, IDC_STATIC3, m_partsCount);
	DDX_Text(pDX, IDC_STATIC4, m_translation);
	DDX_Text(pDX, IDC_STATIC5, m_direction);
	DDX_Text(pDX, IDC_STATIC6, m_up   );
	DDX_Text(pDX, IDC_STATIC7, m_boundingSphereCenter);
	DDX_Text(pDX, IDC_STATIC8, m_boundingSphereRadius);
	DDX_Text(pDX, IDC_STATIC9, m_boundingBoxMin);
	DDX_Text(pDX, IDC_STATIC10, m_boundingBoxMax);
	//}}AFX_DATA_MAP
}

void CROIPropPage::Display(const LegoROI* pROI)
{
    if (pROI)
    {
        const Matrix4&          rLocalTransform = pROI->GetLocalTransform();
        const Vector4&          rTranslation = rLocalTransform[3];
        const Vector4&          rDirection = rLocalTransform[2];
        const Vector4&          rUp = rLocalTransform[1];
        const BoundingSphere&   rBoundingSphere = pROI->GetWorldBoundingSphere();
        const BoundingBox&      rBoundingBox = pROI->GetWorldBoundingBox();
        CString                 label;

	    m_name                  = pROI->GetName();

        label.Format("%d", (int) pROI->GetLODCount());
	    m_lodCount              = label;

        label.Format("%d", (int) (pROI->GetComp() ? pROI->GetComp()->size() : 0));
	    m_partsCount            = label;

        label.Format("[% .4f, % .4f, % .4f]", EXPAND3(rTranslation));
	    m_translation           = label;

        label.Format("[% .4f, % .4f, % .4f]", EXPAND3(rDirection));
	    m_direction             = label;

        label.Format("[% .4f, % .4f, % .4f]", EXPAND3(rUp));
	    m_up                    = label;

        label.Format("[% .4f, % .4f, % .4f]", EXPAND3(rBoundingSphere.Center()));
	    m_boundingSphereCenter  = label;

        label.Format("%.4f", rBoundingSphere.Radius());
	    m_boundingSphereRadius  = label;

        label.Format("[% .4f, % .4f, % .4f]", EXPAND3(rBoundingBox.Min()));
	    m_boundingBoxMin        = label;

        label.Format("[% .4f, % .4f, % .4f]", EXPAND3(rBoundingBox.Max()));
	    m_boundingBoxMax        = label;
    }
    else
    {
	    m_name                  = _T("");
	    m_lodCount              = _T("");
	    m_partsCount            = _T("");
	    m_translation           = _T("");
	    m_direction             = _T("");
	    m_up                    = _T("");
	    m_boundingSphereCenter  = _T("");
	    m_boundingSphereRadius  = _T("");
	    m_boundingBoxMin        = _T("");
	    m_boundingBoxMax        = _T("");
    }

    UpdateData(FALSE);
	SetModified(FALSE);
}


BEGIN_MESSAGE_MAP(CROIPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CROIPropPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROIPropPage message handlers
