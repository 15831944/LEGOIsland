/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "LegoBitmap.h"

/*
	This derived bitmap class adds the ability to provide bitmap
	data from an external source. Lego Gui bitmaps are already resident
	in memory and will be maintained for the lifetime of the Gui. We
	can avoid duplicate memory usage and the expense of copying the
	image data.
*/

LegoBitmap::LegoBitmap()
{
	m_infoExternal = FALSE;
	m_imageExternal = FALSE;
}

LegoBitmap::~LegoBitmap()
{

    if (m_info && !m_infoExternal) {
        delete [] (MxU8*) m_info;
    }

    if (m_image && !m_imageExternal) {
        delete [] m_image;
    }

	m_info = NULL;
	m_image = NULL;
}

MxResult 
LegoBitmap::Create(BITMAPINFO* p_info, MxU8 *p_image)
{
    MxResult result = FAILURE;

	if (p_info && p_image)
	{
		m_info = p_info;
		m_infoExternal = TRUE;
		m_image = p_image;
		m_imageExternal = TRUE;

		m_header = &m_info->bmiHeader;
		m_clut = m_info->bmiColors;

		result = SUCCESS;
	}
    return result;
}

