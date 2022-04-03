#ifndef _ViewLODList_h
#define _ViewLODList_h

#include "std.h"
#include "assert.h"
#include "LODList.h"

class ViewLOD;
class ViewLODListManager;

//////////////////////////////////////////////////////////////////////////////
// ViewLODList
//
// An ViewLODList is an LODList that is shared among instances of the "same ROI".
//
// ViewLODLists are managed (created and destroyed) by ViewLODListManager.
//

class ViewLODList : public LODList<ViewLOD>
{
    friend ViewLODListManager;

protected:
   	ViewLODList(size_t capacity);
    ~ViewLODList();

public:
    int         AddRef();
    int         Release();

#ifdef _DEBUG
    void        Dump(void (*pTracer)(const char*, ...)) const;
#endif

private:
    int         m_refCount;
};

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODList implementation

inline
ViewLODList::ViewLODList(size_t capacity)
: LODList<ViewLOD>(capacity), m_refCount(0)
{
}

inline
ViewLODList::~ViewLODList()
{
    assert(m_refCount == 0);
}

inline
int
ViewLODList::AddRef()
{
    return ++m_refCount; 
}

inline
int
ViewLODList::Release()
{
    assert(m_refCount > 0);
    return --m_refCount;
}

//////////////////////////////////////////////////////////////////////////////
//

// ??? for now, until we have symbol management
typedef const char* ROIName;
struct ROINameComparator
{
    bool operator() (const ROIName& rName1, const ROIName& rName2) const
	{
		return strcmp((const char*) rName1, (const char*) rName2) > 0;
	}
};

//////////////////////////////////////////////////////////////////////////////
//
// ViewLODListManager
//
// ViewLODListManager manages creation and sharing of ViewLODLists.
// It stores ViewLODLists under a name, the name of the ROI where
// the ViewLODList belongs.

class ViewLODListManager
{

    typedef std::map< ROIName, ViewLODList*, ROINameComparator > ViewLODListMap;

public:
    ViewLODListManager();
    virtual ~ViewLODListManager();

    // ??? should LODList be const

    // creates an LODList with room for lodCount LODs for a named ROI
    // returned LODList has a refCount of 1, i.e. caller must call Release()
    // when it no longer holds on to the list
    ViewLODList*    Create(const ROIName&, int lodCount);

    // returns an LODList for a named ROI
    // returned LODList's refCount is increased, i.e. caller must call Release()
    // when it no longer holds on to the list
    ViewLODList*    Lookup(const ROIName&) const;

#ifdef _DEBUG
    void            Dump(void (*pTracer)(const char*, ...)) const;
#endif

private:
    ViewLODListMap  m_map;
};

#endif /* _ViewLODList_h */
