#include "LegoTexture.h"
#include "LegoImage.h"
#include "LegoStorage.h"

LegoTexture::LegoTexture()
{
    m_image = new LegoImage();
}

LegoTexture::LegoTexture(LegoU32 p_width, LegoU32 p_height)
{
    m_image = new LegoImage(p_width, p_height);
}

LegoTexture::~LegoTexture()
{
    delete m_image;
}

LegoResult 
LegoTexture::Read(LegoStorage* p_storage)
{
    return m_image->Read(p_storage);
}

LegoResult 
LegoTexture::Write(LegoStorage* p_storage)
{
    return m_image->Write(p_storage);
}

