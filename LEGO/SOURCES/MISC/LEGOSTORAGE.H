#ifndef __LEGOSTORAGE_H
#define __LEGOSTORAGE_H

#include <stdio.h>
#include "LegoTypes.h"

class LegoStorage {
public:
    virtual LegoResult Read(void* p_buffer, LegoU32 p_size) = 0;
    virtual LegoResult Write(void* p_buffer, LegoU32 p_size) = 0;
    virtual LegoResult GetPosition(LegoU32& p_position) = 0;
    virtual LegoResult SetPosition(LegoU32 p_position) = 0;
};

class LegoMemory : public LegoStorage {
public:
    LegoMemory(void* p_buffer);
    virtual LegoResult Read(void* p_buffer, LegoU32 p_size);
    virtual LegoResult Write(void* p_buffer, LegoU32 p_size);
    virtual LegoResult GetPosition(LegoU32& p_position) { p_position = m_position; return SUCCESS; }
    virtual LegoResult SetPosition(LegoU32 p_position) { m_position = p_position; return SUCCESS; }
protected:
    LegoU8* m_buffer;
    LegoU32 m_position;
};

class LegoFile : public LegoStorage {
public:
    enum {
        c_read = 1,
        c_write = 2,
    };
    LegoFile();
    virtual ~LegoFile();
    virtual LegoResult Read(void* p_buffer, LegoU32 p_size);
    virtual LegoResult Write(void* p_buffer, LegoU32 p_size);
    virtual LegoResult GetPosition(LegoU32& p_position);
    virtual LegoResult SetPosition(LegoU32 p_position);
    LegoResult Open(const char* p_name, LegoU32 p_mode);
    LegoResult Close();
protected:
    FILE* m_file;
};

#endif // __LEGOSTORAGE_H

