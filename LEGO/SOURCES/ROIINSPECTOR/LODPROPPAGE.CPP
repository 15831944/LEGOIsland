// LODPropPage.cpp : implementation file
//

#include "stdafx.h"
#include "roiinspector.h"
#include "LODPropPage.h"

#include "LegoROI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int gCostListSampleSubItem = 0;
const int gCostListPixelsCoveredSubItem = 1;
const int gCostListCostSubItem = 2;
const int gCostListEstimatedCost1SubItem = 3;

/////////////////////////////////////////////////////////////////////////////
// CLODPropPage property page

IMPLEMENT_DYNCREATE(CLODPropPage, CPropertyPage)

CLODPropPage::CLODPropPage() : CPropertyPage(CLODPropPage::IDD)
{
    m_psp.pszIcon   = MAKEINTRESOURCE(IDI_LOD);
    m_psp.dwFlags   |= PSP_USEICONID;

    m_pLOD = 0;

	//{{AFX_DATA_INIT(CLODPropPage)
	m_vertixCount = _T("");
	m_costCount = _T("");
	//}}AFX_DATA_INIT
}

CLODPropPage::~CLODPropPage()
{
}

void CLODPropPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLODPropPage)
	DDX_Control(pDX, IDC_LIST1, m_costList);
	DDX_Text(pDX, IDC_STATIC1, m_vertixCount);
	DDX_Text(pDX, IDC_STATIC2, m_costCount);
	//}}AFX_DATA_MAP

    if (!pDX->m_bSaveAndValidate)
    {
        // updating dialog controls
        
        m_costList.DeleteAllItems();

        if (m_pLOD)
        {
            int             costCount = const_cast<LegoLOD*>(m_pLOD)->GetNumCosts();
            LegoCostInfo*   pCosts = const_cast<LegoLOD*>(m_pLOD)->GetCosts();
            CString         label;

            for (int i = 0; i < costCount; i++)
            {
                double  pixelsCovered;
	            double  cost;
                double  estimatedCost1;
                LV_ITEM item;
                int     itemNumber;

                pixelsCovered   = pCosts[i].GetPixelsCovered();
                cost            = pCosts[i].GetCost();
                estimatedCost1  = (0.1 * pCosts[i].GetPixelsCovered() / (640 * 480)) +
                                  (0.03 * m_pLOD->GetNumVertices() / 80);

                label.Format("%d", i);
	            item.mask       = LVIF_TEXT | LVIF_PARAM;
	            item.iItem      = i;
 	            item.iSubItem   = gCostListSampleSubItem;
	            item.pszText    = (char*) (const char*) label;
                item.lParam     = (LPARAM) &pCosts[i];
                itemNumber      = m_costList.InsertItem(&item);

                label.Format("%.0f", (double) pixelsCovered);
	            item.mask       = LVIF_TEXT;
	            item.iItem      = itemNumber;
	            item.iSubItem   = gCostListPixelsCoveredSubItem;
	            item.pszText    = (char*) (const char*) label;
                m_costList.SetItem(&item);

                label.Format("%.6f", (double) cost);
	            item.mask       = LVIF_TEXT;
	            item.iItem      = itemNumber;
	            item.iSubItem   = gCostListCostSubItem;
	            item.pszText    = (char*) (const char*) label;
                m_costList.SetItem(&item);

                label.Format("%.6f", (double) estimatedCost1);
	            item.mask       = LVIF_TEXT;
	            item.iItem      = itemNumber;
	            item.iSubItem   = gCostListEstimatedCost1SubItem;
	            item.pszText    = (char*) (const char*) label;
                m_costList.SetItem(&item);
            }
        }
    }
}

void CLODPropPage::Display(const LegoLOD* pLOD)
{
    m_pLOD = pLOD;

    if (pLOD)
    {
        CString label;

        label.Format("%d", (int) pLOD->GetNumVertices());
	    m_vertixCount   = label;

        label.Format("%d", const_cast<LegoLOD*>(pLOD)->GetNumCosts());
	    m_costCount     = label;

        // cannot fill list here, as it may not yet exist
        // list is filled in DoDataExchange() in response to UpdateData(FALSE)
        // below
    }
    else
    {
        m_vertixCount   = _T("");
        m_costCount     = _T("");
    }

    if (GetSafeHwnd())
    {
        UpdateData(FALSE);
    }
	SetModified(FALSE);
}

BEGIN_MESSAGE_MAP(CLODPropPage, CPropertyPage)
	//{{AFX_MSG_MAP(CLODPropPage)
	ON_WM_SIZE()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLODPropPage message handlers

BOOL CLODPropPage::OnInitDialog() 
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

        column.pszText     = _T("Sample");
        column.cx          = m_costList.GetStringWidth(column.pszText) + 15;
        column.iSubItem    = gCostListSampleSubItem;
        m_costList.InsertColumn(column.iSubItem, &column);

        column.pszText     = _T("Pixels Covered");
        column.cx          = m_costList.GetStringWidth(column.pszText) + 15;
        column.iSubItem    = gCostListPixelsCoveredSubItem;
        m_costList.InsertColumn(column.iSubItem, &column);

        column.pszText     = _T("Cost");
        column.cx          = m_costList.GetStringWidth(column.pszText) * 2 + 15;
        column.iSubItem    = gCostListCostSubItem;
        m_costList.InsertColumn(column.iSubItem, &column);

        column.pszText     = _T("Est. Cost 1");
        column.cx          = m_costList.GetStringWidth(column.pszText) * 2 + 15;
        column.iSubItem    = gCostListEstimatedCost1SubItem;
        m_costList.InsertColumn(column.iSubItem, &column);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLODPropPage::OnSize(UINT nType, int cx, int cy) 
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

int CALLBACK SampleCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    LegoCostInfo*   pCostInfo1 = reinterpret_cast<LegoCostInfo*>(lParam1);
    LegoCostInfo*   pCostInfo2 = reinterpret_cast<LegoCostInfo*>(lParam2);

    if (pCostInfo1 < pCostInfo2)
    {
        return -1;
    }
    else if (pCostInfo1 > pCostInfo2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CALLBACK CLODPropPage::PixelsCoveredCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    LegoCostInfo*   pCostInfo1 = reinterpret_cast<LegoCostInfo*>(lParam1);
    LegoCostInfo*   pCostInfo2 = reinterpret_cast<LegoCostInfo*>(lParam2);

    if (pCostInfo1->GetPixelsCovered() < pCostInfo2->GetPixelsCovered())
    {
        return -1;
    }
    else if (pCostInfo1->GetPixelsCovered() > pCostInfo2->GetPixelsCovered())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CALLBACK CLODPropPage::CostCmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    LegoCostInfo*   pCostInfo1 = reinterpret_cast<LegoCostInfo*>(lParam1);
    LegoCostInfo*   pCostInfo2 = reinterpret_cast<LegoCostInfo*>(lParam2);

    if (pCostInfo1->GetCost() < pCostInfo2->GetCost())
    {
        return -1;
    }
    else if (pCostInfo1->GetCost() > pCostInfo2->GetCost())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int CALLBACK CLODPropPage::EstimatedCost1Cmp(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    LegoCostInfo*   pCostInfo1 = reinterpret_cast<LegoCostInfo*>(lParam1);
    LegoCostInfo*   pCostInfo2 = reinterpret_cast<LegoCostInfo*>(lParam2);

    // EstimatedCost1 grows with pixelsCovered

    if (pCostInfo1->GetPixelsCovered() < pCostInfo2->GetPixelsCovered())
    {
        return -1;
    }
    else if (pCostInfo1->GetPixelsCovered() > pCostInfo2->GetPixelsCovered())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CLODPropPage::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    switch (pNMListView->iSubItem)
    {
    case gCostListSampleSubItem:
        m_costList.SortItems(SampleCmp, 0);
        break;
    case gCostListPixelsCoveredSubItem:
        m_costList.SortItems(PixelsCoveredCmp, 0);
        break;
    case gCostListCostSubItem:
        m_costList.SortItems(CostCmp, 0);
        break;
    case gCostListEstimatedCost1SubItem:
        m_costList.SortItems(EstimatedCost1Cmp, 0);
        break;
    default:
        break;
    }
    
	*pResult = 0;
}
