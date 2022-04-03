#ifndef __LEGOCONTAINER
#define __LEGOCONTAINER

#include "MxString.h"
#include "MxHashTable.h"
#include "LegoTexture.h"
#include "LegoROI.h"

template <class T>
class LegoContainerInfo {
protected:
    MxString m_name;
    T* m_object;
public:
    LegoContainerInfo() { m_object = NULL; }
    LegoContainerInfo(const MxChar* p_name) { m_name = p_name; }
    LegoContainerInfo(const MxChar* p_name, T* p_object) { m_name = p_name; m_object = p_object; }
    MxString& GetName() { return m_name; }
    T* GetObject() { return m_object; }
    void SetObject(T* p_object) { m_object = p_object; }
};

template <class T>
class LegoContainer : protected MxHashTable<LegoContainerInfo<T>*> {
protected:
    MxBool m_ownership;
    static void Destroy(LegoContainerInfo<T>* p_info) { delete p_info; }
    virtual MxS8 Compare(LegoContainerInfo<T>* p_info1, LegoContainerInfo<T>* p_info2);
    virtual MxU32 Hash(LegoContainerInfo<T>* p_info);
public:
    LegoContainer() { m_ownership = TRUE; SetDestroy(Destroy); }
    ~LegoContainer();
    LegoBool GetOwnership() { return m_ownership; }
    void SetOwnership(LegoBool p_ownership) { m_ownership = p_ownership; }
    void Add(const MxChar* p_name, T* p_info);
    T* Find(const MxChar* p_name);
};

class LegoTextureContainer : public LegoContainer<LegoTexture> {
};

template <class T>
inline
LegoContainer<T>::~LegoContainer()
{
    if (m_ownership) {
        MxHashTableCursor<LegoContainerInfo<T>*> cursor(this);
        LegoContainerInfo<T>* info;
        while (cursor.Next(info)) {
            delete info->GetObject();
        }
    }
}

template <class T>
inline MxS8 
LegoContainer<T>::Compare(LegoContainerInfo<T>* p_info1, LegoContainerInfo<T>* p_info2)
{
    return p_info1->GetName().Compare(p_info2->GetName());
}

template <class T>
inline MxU32 
LegoContainer<T>::Hash(LegoContainerInfo<T>* p_info)
{
    const MxChar* name = p_info->GetName();
    MxU32 value = 0;
    for (int i = 0; name[i]; i++) {
        value += name[i];
    }
    return value;
}

template <class T>
inline void 
LegoContainer<T>::Add(const MxChar* p_name, T* p_object)
{
    MxHashTableCursor<LegoContainerInfo<T>*> cursor(this);
    LegoContainerInfo<T>* info = new LegoContainerInfo<T>(p_name, p_object);
    if (cursor.Find(info)) {
        delete info;
        cursor.GetElement(info);
        if (m_ownership) {
            delete info->GetObject();
        }
        info->SetObject(p_object);
    }
    else {
        MxHashTable<LegoContainerInfo<T>*>::Add(info);
    }
}

template <class T>
inline T* 
LegoContainer<T>::Find(const MxChar* p_name)
{
    T* object = NULL;
    MxHashTableCursor<LegoContainerInfo<T>*> cursor(this);
    LegoContainerInfo<T>* info = new LegoContainerInfo<T>(p_name);
    MxBool found = cursor.Find(info);
    delete info;
    if (found) {
        cursor.GetElement(info);
        object = info->GetObject();
    }
    return object;
}


#endif // __LEGOCONTAINER

