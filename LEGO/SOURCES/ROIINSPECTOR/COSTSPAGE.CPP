// CostsPage.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "CostsPage.h"

#include "LegoROI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCostsPage dialog

const int gCostListLODSubItem = 0;
const int gCostListCostSubItem = 1;

IMPLEMENT_DYNCREATE(CCostsPage, CPropertyPage)

CCostsPage::CCostsPage() : CPropertyPage(CCostsPage::IDD)
{
    m_pROI  = 0;

	//{{AFX_DATA_INIT(CCostsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CCostsPage::~CCostsPage()
{
}

void CCostsPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCostsPage)
	DDX_Control(pDX, IDC_LIST1, m_costList);
	DDX_Control(pDX, IDC_COMBO1, m_pixelsCoveredCombo);
	//}}AFX_DATA_MAP

    if (!pDX->m_bSaveAndValidate)
    {
        // updating dialog controls
        
        m_pixelsCoveredCombo.ResetContent();
        m_costList.DeleteAllItems();

        if (m_pROI)
        {
            // update combo box with pixels covered
            if (m_pROI->GetLODCount() > 0)
            {
                const LODObject*    pLOD = m_pROI->GetLOD(0);
                const LegoLOD*      pLegoLOD = static_cast<const LegoLOD*>(pLOD);
                LegoCostInfo*       pCosts = const_cast<LegoLOD*>(pLegoLOD)->GetCosts();
                int                 costCount = const_cast<LegoLOD*>(pLegoLOD)->GetNumCosts();

                for (int i = 0; i < costCount; i++)
                {
                    int     index;
                    CString label;

                    label.Format("%.0f", (double) pCosts[i].GetPixelsCovered());
                    index = m_pixelsCoveredCombo.InsertString(i, label);
                    ASSERT(index >= 0);
                }

                if (costCount > 0)
                {
                    m_pixelsCoveredCombo.SetCurSel(0);
                    UpdateCostList(pCosts[0].GetPixelsCovered());
                }
            }
        }
    }
}

void CCostsPage::UpdateCostList(double pixelsCovered)
{
    m_costList.DeleteAllItems();

    // update list control
    for (int i = 0; i < m_pROI->GetLODCount(); i++)
    {
        const LODObject*    pLOD = m_pROI->GetLOD(i);
        double              cost = pLOD->Cost(pixelsCovered);
	    LV_ITEM             item;
        int                 itemNumber;
        CString             label;

        label.Format("%d", i);
	    item.mask       = LVIF_TEXT | LVIF_PARAM;
	    item.iItem      = i;
 	    item.iSubItem   = gCostListLODSubItem;
	    item.pszText    = (char*) (const char*) label;
        item.lParam     = (LPARAM) pLOD;
        itemNumber      = m_costList.InsertItem(&item);

        label.Format("%.6f", cost);
	    item.mask       = LVIF_TEXT;
	    item.iItem      = itemNumber;
	    item.iSubItem   = gCostListCostSubItem;
	    item.pszText    = (char*) (const char*) label;
        m_costList.SetItem(&item);
    }
}

void CCostsPage::Display(const LegoROI* pROI)
{
    m_pROI = pROI;

    if (GetSafeHwnd())
    {
        UpdateData(FALSE);
    }

	SetModified(FALSE);
}


BEGIN_MESSAGE_MAP(CCostsPage, CPropertyPage)
	//{{AFX_MSG_MAP(CCostsPage)
	ON_WM_SIZE()
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCostsPage message handlers


BOOL CCostsPage::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
    // configure list control
    {
        LV_COLUMN   column;

        // make sure list is in report style
        SetWindowLong(m_costList.GetSafeHwnd(),
                      GWL_STYLE,
                      LVS_REPORT | GetWindowLong(m_costList.GetSafeHwnd(), GWL_STYLE)); 

        column.mask        = LVCF_FMT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_TEXT;
        column.fmt         = LVCFMT_LEFT;

        column.pszText     = _T("LOD");
        column.cx          = m_costList.GetStringWidth(column.pszText) + 15;
        column.iSubItem    = gCostListLODSubItem;
        m_costList.InsertColumn(gCostListLODSubItem, &column);

        column.pszText     = _T("Cost");
        column.cx          = m_costList.GetStringWidth(column.pszText) * 2 + 15;
        column.iSubItem    = gCostListCostSubItem;
        m_costList.InsertColumn(gCostListCostSubItem, &column);
    }
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CCostsPage::OnSize(UINT nType, int cx, int cy) 
{
	CPropertyPage::OnSize(nType, cx, cy);
	
    if (m_costList.GetSafeHwnd())
    {
	    CRect   listRect;
        int     margin;

        // make list fill remainder of dialog
        m_costList.GetWindowRect(&listRect);
        ScreenToClient(&listRect);
        margin = listRect.left;
        m_costList.MoveWindow(listRect.left, listRect.top,
                              cx - listRect.left - margin,
                              cy - listRect.top - margin);

    }
}

void CCostsPage::OnEditchangeCombo1() 
{
    CString text;
    double  pixelsCovered;

    m_pixelsCoveredCombo.GetWindowText(text);
    pixelsCovered = atof(text);
    UpdateCostList(pixelsCovered);
}

void CCostsPage::OnSelchangeCombo1() 
{
    CString text;
    double  pixelsCovered;

    m_pixelsCoveredCombo.GetLBText(m_pixelsCoveredCombo.GetCurSel(), text);
    pixelsCovered = atof(text);
    UpdateCostList(pixelsCovered);
}

int CALLBACK CCostsPage::LODCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    const LODObject*    pLOD1 = reinterpret_cast<const LODObject*>(lParam1);
    const LODObject*    pLOD2 = reinterpret_cast<const LODObject*>(lParam2);
    const LegoROI*      pROI = reinterpret_cast<const LegoROI*>(lParamSort);
    int                 lod1Index = -1;
    int                 lod2Index = -1;

    for (int i = 0; i < pROI->GetLODCount(); i++)
    {
        if (pROI->GetLOD(i) == pLOD1)
        {
            lod1Index = i;
        }
        else if (pROI->GetLOD(i) == pLOD2)
        {
            lod2Index = i;
        }
    }

    ASSERT(lod1Index != -1);
    ASSERT(lod2Index != -1);

    if (lod1Index < lod2Index)
    {
        return -1;
    }
    else if (lod1Index > lod2Index)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CALLBACK CCostsPage::CostCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    const LODObject*    pLOD1 = reinterpret_cast<const LODObject*>(lParam1);
    const LODObject*    pLOD2 = reinterpret_cast<const LODObject*>(lParam2);
    double              pixelsCovered = *reinterpret_cast<double*>(lParamSort);

    if (pLOD1->Cost(pixelsCovered) < pLOD2->Cost(pixelsCovered))
    {
        return -1;
    }
    else if (pLOD1->Cost(pixelsCovered) > pLOD2->Cost(pixelsCovered))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CCostsPage::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    switch (pNMListView->iSubItem)
    {
    case gCostListLODSubItem:
        m_costList.SortItems(LODCmp, reinterpret_cast<LPARAM>(m_pROI));
        break;
    case gCostListCostSubItem:
        {
            CString text;
            double  pixelsCovered;

            m_pixelsCoveredCombo.GetWindowText(text);
            pixelsCovered = atof(text);
            m_costList.SortItems(CostCmp, reinterpret_cast<LPARAM>(&pixelsCovered));
        }
        break;
    default:
        break;
    }
    
	*pResult = 0;
}
