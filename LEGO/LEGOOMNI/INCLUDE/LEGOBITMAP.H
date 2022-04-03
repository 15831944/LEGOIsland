/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOBITMAP_H
#define __LEGOBITMAP_H

#include "MxBitmap.h"

/*
	This derived bitmap class adds the ability to provide bitmap
	data from an external source. Lego Gui bitmaps are already resident
	in memory and will be maintained for the lifetime of the Gui. We
	can avoid duplicate memory usage and the expense of copying the
	image data.
*/


class LegoBitmap : public MxBitmap
{
protected:
	MxBool	m_infoExternal;
	MxBool	m_imageExternal;
public:
	LegoBitmap();
	virtual ~LegoBitmap();
	virtual MxResult Create(BITMAPINFO* p_info, MxU8 *p_image);
	virtual MxResult Create(BITMAPINFO* p_info) {return MxBitmap::Create(p_info);}
    virtual MxResult Create(MxBitmap* p_bitmap) {return MxBitmap::Create(p_bitmap);}


};

#endif // __LEGOBITMAP_H


