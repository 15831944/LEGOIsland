/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#ifndef __LEGOGUIBASE_H
#define __LEGOGUIBASE_H



class LegoGuiBase	: public MxCore
{
public:
	static MxU8 GetU8(MxU8Ptr *p_data);
	static MxS8 GetS8(MxU8Ptr *p_data);
	static MxU16 GetU16(MxU8Ptr *p_data);
	static MxS16 GetS16(MxU8Ptr *p_data);
	static MxU32 GetU32(MxU8Ptr *p_data);
	static MxS32 GetS32(MxU8Ptr *p_data);
	static MxBool GetBool(MxU8Ptr *p_data);
	static MxTime GetTime(MxU8Ptr *p_data);
	static MxCharString GetString(MxU8Ptr *p_data);
};

#endif // __LEGOGUIBASE_H
