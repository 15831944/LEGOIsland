#include "ViewManager.h"
#include "ViewLODList.h"

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODList
//

#ifdef _DEBUG
void
ViewLODList::Dump(void (*pTracer)(const char*, ...)) const
{
    int i;

    pTracer("   ViewLODList<0x%x>: Capacity=%d, Size=%d, RefCount=%d\n",
            (void*) this, (int) Capacity(), (int) Size(), m_refCount);

    for (i = 0; i < (int) Size(); i++)
    {
        const ViewLOD* pLOD = (*this)[i];

        pTracer("      [%d]: ViewLOD<0x%x>: Vertices=%d, Cost(1000)=%.4f\n", 
                i, (void*) pLOD, pLOD->NVerts(), pLOD->Cost(1000));
    }
}
#endif

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODListManager
//

ViewLODListManager::ViewLODListManager()
{
    // ??? how to configure map for size
}

ViewLODListManager::~ViewLODListManager()
{
	ViewLODListMap::iterator    iterator;

    // delete all ViewLODLists
    for (iterator = m_map.begin(); !(iterator == m_map.end()); ++iterator)
    {
        const ROIName&  rROIName = (*iterator).first;
        ViewLODList*    pLODList = (*iterator).second;

        // LODList's refCount should be 0
        assert(pLODList->m_refCount == 0);

        // ???who pops and deletes LODObjects
        while (pLODList->Size() > 0)
        {
            delete const_cast<ViewLOD*>(pLODList->PopBack());
        }

        delete pLODList;
        // ??? for now
        delete [] const_cast<char*>(rROIName);
    }

    // ??? correct way of "emptying" map
    m_map.erase(m_map.begin(), m_map.end());

    assert(m_map.begin() == m_map.end());
}

ViewLODList*
ViewLODListManager::Create(const ROIName& rROIName, int lodCount)
{
    // returned ViewLODList has a refCount of 1, i.e. caller must call Release()
    // when it no longer holds on to the list

    ViewLODList*    pLODList;
    int             refCount;
    char*           pROIName;

    assert(!Lookup(rROIName));

    pLODList    = new ViewLODList(lodCount);
    refCount    = pLODList->AddRef();
    assert(refCount == 1);

    pROIName = new char[strlen(rROIName) + 1];
    strcpy(pROIName, rROIName);

    m_map[pROIName] = pLODList;

    // NOTE: Lookup() adds a refCount
    assert((Lookup(rROIName) == pLODList) && (pLODList->Release() == 1));

    return pLODList;
}

ViewLODList*
ViewLODListManager::Lookup(const ROIName& rROIName) const
{
    // returned ViewLODList's refCount is increased, i.e. caller must call Release()
    // when it no longer holds on to the list

	ViewLODListMap::const_iterator  iterator = m_map.find(rROIName);
    ViewLODList*                    pLODList = 0;

    if(!(iterator == m_map.end()))
    {
        pLODList = (*iterator).second;

        assert(pLODList);
        pLODList->AddRef();
    }

    return pLODList;
}

#ifdef _DEBUG
void
ViewLODListManager::Dump(void (*pTracer)(const char*, ...)) const
{
	ViewLODListMap::const_iterator  iterator;
    int                             i;

    pTracer("ViewLODListManager<0x%x>: size=%d, max_size=%d\n",
            (void*)this, (int) m_map.size(), (int) m_map.max_size());

    for (iterator = m_map.begin(), i = 0; !(iterator == m_map.end()); ++iterator, i++)
    {
        const ROIName&  rName = (*iterator).first;
        ViewLODList* const& rpLODList = (*iterator).second;

        pTracer("ViewLODListManager[%d]: ROI=\"%s\", ViewLODList=0x%x\n",
                i, (const char*) rName, (void*) rpLODList);
        rpLODList->Dump(pTracer);
    }
}
#endif

