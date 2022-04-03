#include <memory.h>
#include <string.h>
#include "LegoStorage.h"

LegoMemory::LegoMemory(void* p_buffer)
{
    m_buffer = (LegoU8*) p_buffer;
    m_position = 0;
}

LegoResult 
LegoMemory::Read(void* p_buffer, LegoU32 p_size)
{
    memcpy(p_buffer, m_buffer + m_position, p_size);
    m_position += p_size;
    return SUCCESS;
}

LegoResult 
LegoMemory::Write(void* p_buffer, LegoU32 p_size)
{
    memcpy(m_buffer + m_position, p_buffer, p_size);
    m_position += p_size;
    return SUCCESS;
}

LegoFile::LegoFile()
{
    m_file = NULL;
}

LegoFile::~LegoFile()
{
    if (m_file) {
        fclose(m_file);
    }
}

LegoResult 
LegoFile::Read(void* p_buffer, LegoU32 p_size)
{
    if (!m_file) {
        return FAILURE;
    }
    if (fread(p_buffer, 1, p_size, m_file) != p_size) {
        return FAILURE;
    }
    return SUCCESS;
}

LegoResult 
LegoFile::Write(void* p_buffer, LegoU32 p_size)
{
    if (!m_file) {
        return FAILURE;
    }
    if (fwrite(p_buffer, 1, p_size, m_file) != p_size) {
        return FAILURE;
    }
    return SUCCESS;
}

LegoResult 
LegoFile::GetPosition(LegoU32& p_position)
{
    if (!m_file) {
        return FAILURE;
    }
    LegoU32 position = ftell(m_file);
    if (position == -1) {
        return FAILURE;
    }
    p_position = position;
    return SUCCESS;
}

LegoResult 
LegoFile::SetPosition(LegoU32 p_position)
{
    if (!m_file) {
        return FAILURE;
    }
    if (fseek(m_file, p_position, SEEK_SET) != 0) {
        return FAILURE;
    }
    return SUCCESS;
}

LegoResult 
LegoFile::Open(const char* p_name, LegoU32 p_mode)
{
    if (m_file) {
        fclose(m_file);
    }
    char mode[3];
    mode[0] = '\0';
    if (p_mode & c_read) {
        strcat(mode, "r");
    }
    if (p_mode & c_write) {
        strcat(mode, "w");
    }
    strcat(mode, "b");
    if (!(m_file = fopen(p_name, mode))) {
        return FAILURE;
    }
    return SUCCESS;
}

LegoResult 
LegoFile::Close()
{
    if (m_file) {
        fclose(m_file);
        m_file = NULL;
    }
    return SUCCESS;
}


