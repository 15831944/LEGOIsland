// LegoGuiFile.h : header file
//

#ifndef __LEGOGUIFILE_H
#define __LEGOGUIFILE_H

#include "LegoGuiControl.h"

#define MAX_ACTIONS 256
#define MAX_BITMAP_FILES 32768
#define MAX_SOUND_ACTIONS 32768
#define MAX_ACTION_NAMES 32768

class LegoGuiFile
{
// Construction
public:
	LegoGuiFile();
	~LegoGuiFile();
	//}}AFX_VIRTUAL

// Implementation
	void			DoWrite(char *p_infname, char *p_outfname);
protected:
private:
	int				GetNextTok(char **p_inptr);		
	void			InitAction();
	void			ErrBox(char *p_msg);
	BOOL			GetBool(char **p_inptr);
	int				GetInt(char **p_inptr);
	MxCharString	GetString(char **p_inptr);
	void			SkipWhiteSpace(char **p_ptr);
	void			SkipWord(char **p_ptr);
	void			AddAction();
	LegoGuiControl::LegoGuiAction	*FindAction(char *p_name);
	void			WriteAction(LegoGuiControl::LegoGuiAction *p_act, FILE *p_fp);
	void			FreeActionList();
	void			FreeCurrentAction();
	void			FreeBitmapNames();
	void			FreeActionNames();
	void			FreeSoundNames();

	void			GetGui(FILE *p_infp, FILE *p_outfp);
	void			GetControl(char *p_name, FILE *p_infp, FILE *p_outfp);
	MxU8			LookupID(char *p_id);
	void			WriteBitmapArray(FILE *p_outfp);
	void			WriteSoundArray(FILE *p_outfp);
	void			WriteNamedActionArray(FILE *p_outfp);
	void			CopyFile(char *p_name, FILE *p_outfp);
	void			GetFontArray(FILE *p_infp, FILE *p_outfp, int p_tok);
	void			WriteEmptyArray(FILE *p_outfp);
	BOOL			PassOne(FILE *fp);
	BOOL			WriteActionList(FILE *fp);

	int				GetBitmapIndex(MxCharString name);
	int				GetSoundIndex(MxCharString name);
	int				GetNamedActionIndex(MxCharString name);
	void			GetFontBitmapNames(FILE *p_infp, int p_tok);


	enum tok_id {
		e_comment,
		e_none,
		e_defineAction,
		e_loop,
		e_frameTime,
		e_numFrames,
		e_offset,
		e_bitmapFile,
		e_soundAction,
		e_namedAction,
		e_bitmapNoBlt,
		e_endAction,
		e_guiName,
		e_controlName,
		e_camera,
		e_startFont,
		e_endFont,
		e_newFont,
		e_startup,
		e_shutdown,
		e_chainAction,
		e_backgroundBitmapFile,
		e_objectName,
		e_eventMask,
		e_type,
		e_keyLow,
		e_keyHigh,
		e_initToggle,
		e_maxLength,
		e_fontIndex,
		e_releasedState,
		e_selectAction,
		e_selectedState,
		e_releaseAction,
		e_ctrlMessage,
		e_bool,
		e_int,
		e_string,
		e_sysVar,
		e_true,
		e_false,
	};

	struct token {
		tok_id id;
		char *str;
	};

	struct actionItem {
		char *ID;
		LegoGuiControl::LegoGuiActionPtr action;
	};


	LegoGuiControl::LegoGuiActionPtr	currentAction;
	BOOL								actionStarted;
	BOOL								guiStarted;
	BOOL								controlStarted;
	int									offsetIndex;
	int									bitmapIndex;
	char								*currentActionID;
	int									numActions;
	actionItem							actionList[MAX_ACTIONS];
	int									m_numBitmapFiles;
	int									m_numSoundActions;
	int									m_numActionNames;
	MxU8								m_numControls;
	MxCharString						m_bitmapFile[MAX_BITMAP_FILES];
	MxCharString						m_soundAction[MAX_SOUND_ACTIONS];
	MxCharString						m_actionName[MAX_ACTION_NAMES];

};

#endif // __LEGOGUIFILE_H
