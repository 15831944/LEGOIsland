// ROITreeCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ROIInspector.h"
#include "ROITreeCtrl.h"
#include "LegoROI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CROITreeCtrl

CROITreeCtrl::CROITreeCtrl()
{
    m_shortNamesEnabled         = TRUE;
    m_shortNameSeparator    = '\\';
}

CROITreeCtrl::~CROITreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CROITreeCtrl, CTreeCtrl)
	//{{AFX_MSG_MAP(CROITreeCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CROITreeCtrl message handlers

BOOL CROITreeCtrl::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	BOOL    result;
	
    dwStyle |= TVS_SHOWSELALWAYS | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT;

	result = CTreeCtrl::Create(dwStyle, rect, pParentWnd, nID);

    if (result)
    {
    	HICON       hIcon;
    
        // create image list, add bitmaps and attach it to tree control
        int iconCount = 4;

	    m_imageList.Create(16, 16, FALSE, iconCount, 0);
	    hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_ROI));
	    m_roiImageIndex = m_imageList.Add(hIcon);
	    hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_LODLIST));
	    m_lodListImageIndex = m_imageList.Add(hIcon);
	    hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_LOD));
	    m_lodImageIndex = m_imageList.Add(hIcon);
	    hIcon = ::LoadIcon(AfxGetResourceHandle(), MAKEINTRESOURCE(IDI_PARTS));
	    m_partsImageIndex = m_imageList.Add(hIcon);
	    ASSERT(m_imageList.GetImageCount() == iconCount);
	    
        SetImageList(&m_imageList, TVSIL_NORMAL);
    }

    return result;
}

void CROITreeCtrl::EnableShortNames(BOOL useShortNames, int shortNameSeparator)
{
    if ((m_shortNamesEnabled != useShortNames) ||
        (m_shortNameSeparator != shortNameSeparator))
    {
        m_shortNamesEnabled     = useShortNames;
        m_shortNameSeparator    = shortNameSeparator;
    }
}

const BOOL cExpandInsertedItems = FALSE;

void CROITreeCtrl::Insert(const LegoROI& rROI)
{
    InsertROIItems(rROI, TVI_ROOT);
}

void CROITreeCtrl::InsertROIItems(const LegoROI& rROI, HTREEITEM hParentItem)
{
    HTREEITEM   hROIItem;

    // add item for roi
    hROIItem = InsertROIItem(rROI, hParentItem);

    // Insert subitem for LODList
    InsertLODListItems(rROI, hROIItem);

    // Insert subitem for Parts
    InsertPartsItems(rROI, hROIItem);

    if (cExpandInsertedItems)
    {
        Expand(hROIItem, TVE_EXPAND);
    }
}


void CROITreeCtrl::InsertLODListItems(const LegoROI& rROI, HTREEITEM hParentItem)
{
    const LODListBase*  pLODList = rROI.GetLODs();

    if (pLODList)
    {
        const ViewLODList*  pViewLODList = static_cast<const ViewLODList*>(pLODList);
        HTREEITEM           hLODListItem;

        // Insert item for LODList
        hLODListItem = InsertLODListItem(rROI, *pViewLODList, hParentItem);

        // Insert subitem for each LOD
        for (int i = 0; i < (int) pViewLODList->Size(); i++)
        {
            const ViewLOD*  pLOD = (*pViewLODList)[i];
            const LegoLOD*  pLegoLOD = static_cast<const LegoLOD*>(pLOD);

            InsertLODItem(rROI, *pLegoLOD, i, hLODListItem);
        }

        if (cExpandInsertedItems)
        {
            Expand(hLODListItem, TVE_EXPAND);
        }
    }
}

void CROITreeCtrl::InsertPartsItems(const LegoROI& rROI, HTREEITEM hParentItem)
{
    const CompoundObject*   pParts = rROI.GetComp();

    if (pParts)
    {
        CompoundObject::const_iterator  iterator;
        HTREEITEM                       hPartsItem;

        // Insert item for Parts
        hPartsItem = InsertPartsItem(rROI, pParts, hParentItem);

        // Insert subitem for each Part
        for (iterator = pParts->begin();
             !(iterator == pParts->end());
             ++iterator)
        {
            const ROI*      pPart = *iterator;
            const LegoROI*  pLegoPart = static_cast< const LegoROI*>(pPart);

            InsertROIItems(*pLegoPart, hPartsItem);
        }

        if (cExpandInsertedItems)
        {
            Expand(hPartsItem, TVE_EXPAND);
        }
    }
}

HTREEITEM CROITreeCtrl::InsertROIItem(const LegoROI& rROI,
                                      HTREEITEM hParentItem)
{
	TV_INSERTSTRUCT insertStruct;
    const char*     pItemName;

    if (m_shortNamesEnabled)
    {
        pItemName = strrchr(rROI.GetName(), m_shortNameSeparator);
        if (pItemName)
        {
            pItemName++;
        }
        else
        {
            pItemName = rROI.GetName();
        }
    }
    else
    {
        pItemName = rROI.GetName();
    }

    insertStruct.item.mask              = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	insertStruct.item.pszText           = const_cast<char*>(pItemName);
	insertStruct.item.cchTextMax        = strlen(insertStruct.item.pszText);
	insertStruct.item.iImage            = m_roiImageIndex;
	insertStruct.item.iSelectedImage    = m_roiImageIndex;
    insertStruct.item.lParam            = reinterpret_cast<DWORD>(&rROI);
	insertStruct.hInsertAfter           = TVI_LAST;
	insertStruct.hParent                = hParentItem;
	
	return InsertItem(&insertStruct);
}

HTREEITEM CROITreeCtrl::InsertLODListItem(const LegoROI& rROI,
                                          const ViewLODList& rLODList,
                                          HTREEITEM hParentItem)
{
    CString itemLabel;

    itemLabel.Format("LODs (%d)", (int) rLODList.Size());

    return InsertItem(itemLabel, m_lodListImageIndex, m_lodListImageIndex, hParentItem, TVI_LAST);
}

HTREEITEM CROITreeCtrl::InsertPartsItem(const LegoROI& rROI,
                                        const CompoundObject* pParts,
                                        HTREEITEM hParentItem)
{
    CString itemLabel;

    itemLabel.Format("Parts (%d)", (int) pParts->size());

    return InsertItem(itemLabel, m_partsImageIndex, m_partsImageIndex, hParentItem, TVI_LAST);
}

HTREEITEM CROITreeCtrl::InsertLODItem(const LegoROI& rROI,
                                      const LegoLOD& rLOD,
                                      int lodNumber,
                                      HTREEITEM hParentItem)
{
	TV_INSERTSTRUCT insertStruct;
    CString         itemLabel;
    const char*     pItemName;

    if (m_shortNamesEnabled)
    {
        pItemName = strrchr(rROI.GetName(), m_shortNameSeparator);
        if (pItemName)
        {
            pItemName++;
        }
        else
        {
            pItemName = rROI.GetName();
        }
    }
    else
    {
        pItemName = rROI.GetName();
    }

    itemLabel.Format("%s:%d (%ld vertices)", 
                     pItemName,
                     lodNumber,
                     (long) rLOD.GetNumVertices());

	insertStruct.item.mask              = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	insertStruct.item.pszText           = (char*) (const char*) itemLabel;
	insertStruct.item.cchTextMax        = strlen(insertStruct.item.pszText);
	insertStruct.item.iImage            = m_lodImageIndex;
	insertStruct.item.iSelectedImage    = m_lodImageIndex;
    insertStruct.item.lParam            = reinterpret_cast<DWORD>(&rLOD);
	insertStruct.hInsertAfter           = TVI_LAST;
	insertStruct.hParent                = hParentItem;
	
	return InsertItem(&insertStruct);
}

void CROITreeCtrl::GetSelection(const LegoROI*& rpSelectedROI,
                                const LegoLOD*& rpSelectedLOD) const
{
    HTREEITEM   hSelectedItem = GetSelectedItem();

    rpSelectedROI   = 0;
    rpSelectedLOD   = 0;

    if (hSelectedItem)
    {
        HTREEITEM   roiItem;
        HTREEITEM   lodItem;
        int         itemImageIndex = -1;
        int         selectedItemImageIndex;

        GetItemImage(hSelectedItem, itemImageIndex, selectedItemImageIndex);

        if (itemImageIndex == m_roiImageIndex)
        {
            roiItem = hSelectedItem;
            lodItem = 0;
        }
        else if (itemImageIndex == m_lodListImageIndex)
        {
            roiItem = GetParentItem(hSelectedItem);
            lodItem = 0;
        }
        else if (itemImageIndex == m_partsImageIndex)
        {
            roiItem = GetParentItem(hSelectedItem);
            lodItem = 0;
        }
        else if (itemImageIndex == m_lodImageIndex)
        {
            HTREEITEM   lodListItem = GetParentItem(hSelectedItem);
            
            roiItem = GetParentItem(lodListItem);
            lodItem = hSelectedItem;
        }

        if (roiItem)
        {
            rpSelectedROI   = reinterpret_cast<const LegoROI*>(GetItemData(roiItem));
        }

        if (lodItem)
        {
            rpSelectedLOD   = reinterpret_cast<const LegoLOD*>(GetItemData(lodItem));
        }
    }
}
