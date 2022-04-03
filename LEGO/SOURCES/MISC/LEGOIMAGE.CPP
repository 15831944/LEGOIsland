#include "LegoImage.h"
#include "LegoStorage.h"

LegoPaletteEntry::LegoPaletteEntry()
{
    m_red = 0;
    m_green = 0;
    m_blue = 0;
}

LegoPaletteEntry::LegoPaletteEntry(LegoU8 p_red, LegoU8 p_green, LegoU8 p_blue)
{
    m_red = p_red;
    m_green = p_green;
    m_blue = p_blue;
}

LegoResult 
LegoPaletteEntry::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Read(&m_red, sizeof(m_red))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_green, sizeof(m_green))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_blue, sizeof(m_blue))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoPaletteEntry::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Write(&m_red, sizeof(m_red))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_green, sizeof(m_green))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_blue, sizeof(m_blue))) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoImage::LegoImage()
{
    m_width = 0;
    m_height = 0;
    m_bits = NULL;
}

LegoImage::LegoImage(LegoU32 p_width, LegoU32 p_height)
{
    m_width = p_width;
    m_height = p_height;
    m_bits = new LegoU8[m_width * m_height];
}

LegoImage::~LegoImage()
{
    if (m_bits) {
        delete [] m_bits;
    }
}

LegoResult 
LegoImage::Read(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Read(&m_width, sizeof(m_width))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Read(&m_height, sizeof(m_height))) != SUCCESS) {
        return result;
    }
    for (LegoU32 i = 0; i < 256; i++) {
        if ((result = m_palette[i].Read(p_storage)) != SUCCESS) {
            return result;
        }
    }
    if (m_bits) {
        delete [] m_bits;
    }
    m_bits = new LegoU8[m_width * m_height];
    if ((result = p_storage->Read(m_bits, m_width * m_height)) != SUCCESS) {
        return result;
    }
    return SUCCESS;
}

LegoResult 
LegoImage::Write(LegoStorage* p_storage)
{
    LegoResult result;
    if ((result = p_storage->Write(&m_width, sizeof(m_width))) != SUCCESS) {
        return result;
    }
    if ((result = p_storage->Write(&m_height, sizeof(m_height))) != SUCCESS) {
        return result;
    }
    for (LegoU32 i = 0; i < 256; i++) {
        if ((result = m_palette[i].Write(p_storage)) != SUCCESS) {
            return result;
        }
    }
    if (m_bits) {
        if ((result = p_storage->Write(m_bits, m_width * m_height)) != SUCCESS) {
            return result;
        }
    }
    return SUCCESS;
}


