/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/


#ifndef __LEGOGUI_H
#define __LEGOGUI_H

// Omni includes
#include "MxCore.h"
#include "MxList.h"
#include "MxGeometry.h"
#include "MxBitmapMacros.h"
#include "MxTimer.h"
#include "MxAtom.h"

// LegoOmni includes
#include "LegoGuiBase.h"
#include "LegoGuiControl.h"

#define GUI_VERSION_ID "GUI_VERSION"
#define GUI_VERSION "1.1"
#define GUI_OLD_VERSION "0.0"

#define EXIT_MESSAGE "EXIT"

class LegoGui : public LegoGuiBase
{
// local types
private:

// exported types
public:

	enum LegoGuiState {
			e_idle = 0,
			e_starting,
			e_waiting,
			e_active,
			e_ending,
			e_complete,
	};

// local member functions
private:
protected:
//	LegoGui();
	void			StartControls();
	void			EndControls();
	void			DoShutDown();
	void			DoStartUp();


// exported member functions
public:
	LegoGui();
	~LegoGui();

	MxResult		Create();
	void			ParseGuiData(MxU8Ptr p_data);
	MxU32			MakeControlId(MxCharString p_str);
	static MxU32	MakeGuiId(MxCharString p_str);
	static MxResult	FillDataArrayIndexes(MxS16Ptr p_num, MxU8Ptr **p_array, MxU8Ptr *p_data);
	static MxResult	FillStringArrayIndexes(MxS16Ptr p_num, MxU8Ptr **p_array, MxU8Ptr *p_data);
	LegoGuiState	GetState() { return m_state; }
	BITMAPINFO		*GetBitmapInfo(MxS16 p_index);
	MxU8			*GetBitmapImage(MxS16 p_index);
	BITMAPINFO		*GetBGBitmapInfo() {  return GetBitmapInfo(m_backgroundBitmapIdx); }
	MxU8			*GetBGBitmapImage() { return GetBitmapImage(m_backgroundBitmapIdx); }
	MxS16			GetFontBitmapIndex(MxU8 p_ccode, MxU8 p_font);
	MxResult		Tickle();
	MxPoint32		&GetLoc() { return m_locXY; }
	MxS32			GetX() { return m_locXY.GetX(); }
	MxS32			GetY() { return m_locXY.GetY(); }
	MxTimer			*GetTimer() { return m_timer; }
	MxS32			Notify(MxParam& p_param);
	MxS32			IsHit(MxS32 p_x, MxS32 p_y) { return TRUE; }
	LegoGuiBase		*FindControl(MxCharString p_name);
	void			SetBaseDisplayZ(MxS32 p_z) { m_nextDisplayZ = m_baseDisplayZ = p_z; }
	MxS32			GetBaseDisplayZ() { return m_baseDisplayZ; }
	MxS32			GetNextDisplayZ() { return --m_nextDisplayZ; }
	MxCharString	GetSoundActionName(MxS16 p_index);
	MxCharString	GetNamedActionName(MxS16 p_index);
	MxCharString	GetGuiName() { return m_guiName; }
	void			CheckForExitMessage(MxCharString p_target, MxCharString p_msg);
	MxCore			*GetMouseCapture() { return m_mouseCaptureControl; }
	void			BeginCaptureMouse(MxCore *p_control);
	void			EndCaptureMouse();
	void			SetSourceId(MxAtomId& p_sourceId) { m_sourceId = p_sourceId; }
	MxAtomId&		GetSourceId() { return m_sourceId; }
	

// Attributes
private:
	MxCharString		m_guiName;
	MxCharString		m_cameraName;
	MxU8				m_numControls;
	LegoGuiControlList	m_controlList;
	MxS16				m_numBitmaps;
	MxS16				m_numSounds;
	MxS16				m_numNamedActions;
	MxS16				m_numFonts;
	MxU8Ptr				*m_bitmapPool;
	MxU8Ptr				*m_soundPool;
	MxU8Ptr				*m_namedActionPool;
	MxU8Ptr				*m_fontPool;
	MxCharString		m_startUp;
	MxCharString		m_shutDown;
	MxCharString		m_chainAction;
	MxBool				m_startUpDone;
	MxBool				m_shutDownDone;
	MxS16				m_backgroundBitmapIdx;
	LegoGuiState		m_state;
	MxBool				m_advanceState;
	MxBool				m_exitMessageFound;
	MxPoint32			m_locXY;
	MxTimer				*m_timer;
	static LegoGui		*m_gui;
	MxS32				m_nextDisplayZ;
	MxS32				m_baseDisplayZ;
	MxCore				*m_mouseCaptureControl;
	MxAtomId			m_sourceId;
};



#endif // __LEGOGUI_H
