// LegoGuiFile.cpp : implementation file
//

#include "stdafx.h"
#include "LegoGui.h"
#include "LegoGuiControl.h"
#include "LegoGuiFile.h"

LegoGuiFile::LegoGuiFile()
{
	actionStarted = FALSE;
	guiStarted = FALSE;
	controlStarted = FALSE;
	currentActionID = NULL;
	currentAction = NULL;
	numActions = 0;
	memset(actionList, 0, sizeof(actionList));
}

LegoGuiFile::~LegoGuiFile()
{
	FreeActionList();
	FreeCurrentAction();
	FreeBitmapNames();
	FreeActionNames();
	FreeSoundNames();
}

void LegoGuiFile::DoWrite(char *p_infname, char *p_outfname)
{
	FILE *infp, *outfp, *pass1_outfp;
	BOOL done = FALSE;
	char inbuf[1024];
	char *inptr;
	char *actLstFname;
	int tok;
	long guiLenLoc;

	
	infp = fopen(p_infname, "r");
	if (!infp)
	{
		ErrBox("Can't open input file.");
		return;
	}

	if (!PassOne(infp))
	{
		ErrBox("Can't build bitmap/action lists (PassOne).");
		return;
	}
	rewind(infp);

	// make .act filename from output filename
	actLstFname = inbuf;	// just using this buffer
	strcpy(actLstFname, p_outfname);
	char *ptr = strrchr(actLstFname, '.');
	if (ptr)
		*ptr = '\0';
	strcat (actLstFname, ".act");

	pass1_outfp = fopen(actLstFname, "w");
	if (!pass1_outfp)
	{
		fclose(infp);
		ErrBox("Can't open action list file for output (PassOne).");
		return;
	}

	if (!WriteActionList(pass1_outfp))
	{
		ErrBox("Can't write bitmap/action lists (PassOne).");
		fclose (pass1_outfp);
		fclose(infp);
		return;
	}
	fclose (pass1_outfp);

	outfp = fopen(p_outfname, "wb");
	if (!outfp)
	{
		fclose(infp);
		ErrBox("Can't open output file.");
		return;
	}

	do 
	{
		if (fgets(inbuf, 1024, infp) == NULL)
		{
			done = TRUE;
			break;
		}
		inptr = inbuf;
		tok = GetNextTok(&inptr);
		switch(tok)
		{
			case e_none:
				break;
			case e_defineAction:
				// action items are built up ahead of time, so the order of
				// elements is not critical.
				InitAction();
				currentActionID = GetString(&inptr);   // allocates space
				break;
			case e_loop:
				if (actionStarted)
					currentAction->looping = GetBool(&inptr);
				break;
			case e_frameTime:
				if (actionStarted)
					currentAction->frameTime = GetInt(&inptr);
				break;
			case e_numFrames:
				if (actionStarted)
					currentAction->numFrames = GetInt(&inptr);
				break;
			case e_offset:
				if (actionStarted)
				{
					if (currentAction->offsetArray == NULL)
					{
						currentAction->offsetArray =
						 new LegoGuiControl::LegoGuiScreenCoord[currentAction->numFrames];
						offsetIndex = 0;
					}
					if (offsetIndex < currentAction->numFrames)
					{
						currentAction->offsetArray[offsetIndex].x = GetInt(&inptr);
						currentAction->offsetArray[offsetIndex].y = GetInt(&inptr);
						offsetIndex++;
					}
					else
						ErrBox("Too many offsets");
				}
				break;
			case e_bitmapFile:
				if (actionStarted)
				{
					if (currentAction->bitmapArray == NULL)
					{
						currentAction->bitmapArray =
						 new MxS16[currentAction->numFrames];
						bitmapIndex = 0;
					}
					if (bitmapIndex < currentAction->numFrames)
					{
						MxCharString str = GetString(&inptr);
						currentAction->bitmapArray[bitmapIndex] = GetBitmapIndex(str);
						delete str;
						bitmapIndex++;
					}
					else
						ErrBox("Too many bitmaps in action.");
				}
				break;
			case e_soundAction:
				if (actionStarted)
				{
					MxCharString str = GetString(&inptr);
					currentAction->soundActionIdx = GetSoundIndex(str);
					delete str;
				}
			case e_namedAction:
				if (actionStarted)
				{
					MxCharString str = GetString(&inptr);
					currentAction->actionNameIdx =	GetNamedActionIndex(str);
					delete str;
				}
				break;
			case e_bitmapNoBlt:
				if (actionStarted)
					currentAction->bitmapNoBlt = GetBool(&inptr);
				break;
			case e_ctrlMessage:
				if (actionStarted)
				{
					LegoGuiControl::LegoGuiMessagePtr message =
										new LegoGuiControl::LegoGuiMessage;
					message->SetTarget(GetString(&inptr));
					int type = GetNextTok(&inptr);
					switch (type)
					{
						case e_bool:
							message->SetType(LegoGuiControl::e_boolMsg);
							message->SetValue((MxBool)GetBool(&inptr));
							break;
						case e_int:
							message->SetType(LegoGuiControl::e_intMsg);
							message->SetValue((MxS32)GetInt(&inptr));
							break;
						case e_string:
							message->SetType(LegoGuiControl::e_stringMsg);
							message->SetValue((MxCharString)GetString(&inptr));
							break;
						case e_sysVar:
							message->SetType(LegoGuiControl::e_sysVarMsg);
							message->SetValue((MxCharString)GetString(&inptr));
							break;
					}
					currentAction->messageList.Append(message);
				}
				break;
			case e_endAction:
				if (actionStarted)
					AddAction();
				break;
			case e_guiName:
			{
				char *guiName = GetString(&inptr);
				if (!guiName || guiStarted)
				{
					ErrBox("Gui Name error");
				}
				else
				{
					// save current file location for length
					guiLenLoc = ftell(outfp);
					// write dummy length
					MxU32 len = 0;
					fwrite(&len, sizeof(len), 1, outfp);

					// write version tag
					fwrite(GUI_VERSION_ID, strlen(GUI_VERSION_ID)+1, 1, outfp);
					fwrite(GUI_VERSION, strlen(GUI_VERSION)+1, 1, outfp);

					fwrite(guiName, strlen(guiName)+1, 1, outfp);
					delete guiName;

					// do the gui state machine
					GetGui(infp, outfp);
					
					// replace length
					long curLoc = ftell(outfp);
					fseek(outfp, (long)guiLenLoc, SEEK_SET);
					MxU32 guiLen = curLoc - guiLenLoc - sizeof(guiLen);
					fwrite(&guiLen, sizeof(guiLen), 1, outfp);
					fseek(outfp, 0l, SEEK_END);
				}
				break;
			}
			case e_comment:
				break;
		}

	}
	while (!done);
}

BOOL
LegoGuiFile::PassOne(FILE *infp)
{
	BOOL result = TRUE;

	// scan file looking for bitmap filenames and Omni action names.

	BOOL done = FALSE;
	char inbuf[1024];
	char *inptr;
	int tok;

	m_numBitmapFiles = 0;
	m_numSoundActions = 0;
	m_numActionNames = 0;
	m_numControls = 0;

	do 
	{
		if (fgets(inbuf, 1024, infp) == NULL)
		{
			done = TRUE;
			break;
		}
		inptr = inbuf;
		tok = GetNextTok(&inptr);
		switch(tok)
		{
			case e_controlName:
				m_numControls++;
				break;
			case e_backgroundBitmapFile:
			case e_bitmapFile:
				if (m_numBitmapFiles < MAX_BITMAP_FILES)
				{
					MxCharString str = GetString(&inptr);
					if (str)
					{
						if (GetBitmapIndex(str) == -1)
							m_bitmapFile[m_numBitmapFiles++] = str;
						else
							delete str;
					}
				}
				break;
			case e_soundAction:
				if (m_numSoundActions < MAX_SOUND_ACTIONS)
				{
					MxCharString str = GetString(&inptr);
					if (str)
					{
						if (GetSoundIndex(str) == -1)
							m_soundAction[m_numSoundActions++] = str;
						else
							delete str;
					}
				}
				break;
			case e_namedAction:
				if (m_numActionNames < MAX_ACTION_NAMES)
				{
					MxCharString str = GetString(&inptr);
					if (str)
					{
						if (GetNamedActionIndex(str) == -1)
							m_actionName[m_numActionNames++] = str;
						else
							delete str;
					}
				}
				break;
			case e_startFont:
				GetFontBitmapNames(infp, e_endFont);
				break;
		}
	}
	while (!done);
	return result;
}

BOOL
LegoGuiFile::WriteActionList(FILE *fp)
{
	int i;
	BOOL result = TRUE;

	// write bitmap names
	fprintf(fp, "\tBITMAP FILES:\n");
	for (i=0; i<m_numBitmapFiles; i++)
	{
		fprintf(fp, "%s\n", m_bitmapFile[i]);
	}
	fprintf(fp, "\n");

	// write sound actions
	fprintf(fp, "\tSOUND ACTIONS:\n");
	for (i=0; i<m_numSoundActions; i++)
	{
		fprintf(fp, "%s\n", m_soundAction[i]);
	}
	fprintf(fp, "\n");

	// write named actions
	fprintf(fp, "\tNAMED ACTIONS:\n");
	for (i=0; i<m_numActionNames; i++)
	{
		fprintf(fp, "%s\n", m_actionName[i]);
	}
	fprintf(fp, "\n");

	return result;
}

int
LegoGuiFile::GetBitmapIndex(MxCharString name)
{
	int i;

	
	if (name)
	{
		for (i=0; i<m_numBitmapFiles; i++)
		{
			if (!strcmp(m_bitmapFile[i], name))
				return i;
		}
	}
	return -1;
}

int
LegoGuiFile::GetSoundIndex(MxCharString name)
{
	int i;

	if (name)
	{
		for (i=0; i<m_numSoundActions; i++)
		{
			if (!strcmp(m_soundAction[i], name))
				return i;
		}
	}
	return -1;
}

int
LegoGuiFile::GetNamedActionIndex(MxCharString name)
{
	int i;

	if (name)
	{
		for (i=0; i<m_numActionNames; i++)
		{
			if (!strcmp(m_actionName[i], name))
				return i;
		}
	}

	return -1;
}

void
LegoGuiFile::InitAction()
{
	FreeCurrentAction();
	currentAction = new LegoGuiControl::LegoGuiAction;
	currentAction->looping = FALSE;
	currentAction->frameTime = -1;
	currentAction->numFrames = 1;
	currentAction->offsetArray = NULL;
	currentAction->bitmapArray = NULL;
	currentAction->soundActionIdx = -1;
	currentAction->actionNameIdx = -1;
	currentAction->actionNameIdx = -1;
	currentAction->bitmapNoBlt = FALSE;

	actionStarted = TRUE;
}

int
LegoGuiFile::GetNextTok(char **inptr)
{
	static token tok_strings[] = {
		{e_comment, "//"},
		{e_defineAction, "DEFINE_ACTION"},
		{e_loop,"LOOP"},
		{e_frameTime,"FRAME_TIME"},
		{e_numFrames,"NUM_FRAMES"},
		{e_offset,"OFFSET"},
		{e_bitmapFile,"BITMAP_FILE"},
		{e_soundAction,"SOUND_ACTION"},
		{e_namedAction,"NAMED_ACTION"},
		{e_bitmapNoBlt,"BITMAP_NO_BLT"},
		{e_endAction,"END_ACTION"},
		{e_guiName,"GUI_NAME"},
		{e_controlName,"CONTROL_NAME"},
		{e_camera,"CAMERA"},
		{e_startFont,"START_FONT"},
		{e_endFont,"END_FONT"},
		{e_newFont,"NEW_FONT"},
		{e_startup,"STARTUP"},
		{e_shutdown,"SHUTDOWN"},
		{e_chainAction,"CHAINACTION"},
		{e_backgroundBitmapFile,"BACKGROUND_BITMAP_FILE"},
		{e_objectName,"OBJECT_NAME"},
		{e_eventMask,"EVENT_MASK"},
		{e_type,"TYPE"},
		{e_keyLow,"KEYRANGE_LOW"},
		{e_keyHigh,"KEYRANGE_HIGH"},
		{e_initToggle,"INIT_STATE"},
		{e_maxLength,"MAXLENGTH"},
		{e_fontIndex,"FONTINDEX"},
		{e_releasedState,"RELEASED_STATE"},
		{e_selectAction,"SELECT_ACTION"},
		{e_selectedState,"SELECTED_STATE"},
		{e_releaseAction,"RELEASE_ACTION"},
		{e_ctrlMessage,"CTRL_MESSAGE"},
		{e_true,"TRUE"},
		{e_false,"FALSE"},
		{e_bool, "BOOL"},
		{e_int, "INT"},
		{e_string, "STRING"},
		{e_sysVar, "SYSTEM_VARIABLE"},
		{e_none,"NONE"},
	};

	char *locptr = *inptr;

	// skip white space	(include comma's)
	while (*locptr && (*locptr == ' ' || *locptr == '\t' || *locptr == ','))
		locptr++;

	if (!*locptr)
	{
		*inptr = locptr;
		return e_comment;
	}
	
	for (int i=0; i<(sizeof(tok_strings)/sizeof(token)); i++)
	{
		if (!_strnicmp(tok_strings[i].str, locptr, strlen(tok_strings[i].str)))
		{
			*inptr = locptr + strlen(tok_strings[i].str);
			return tok_strings[i].id;
		}
	}

	*inptr = locptr + 1;
	return e_comment;
}



BOOL
LegoGuiFile::GetBool(char **inptr)
{
	char *savePtr = *inptr;
	int state;

	int tok = GetNextTok(inptr);
	switch (tok)
	{
		case e_true:
			state = 1;
			break;
		case e_false:
			state = 0;
			break;
		default:
			state = 0;
			*inptr = savePtr;
			ErrBox("Bad BOOL value");
			break;
	}
	return state;
}

int
LegoGuiFile::GetInt(char **inptr)
{
	int value = 0;

	SkipWhiteSpace(inptr);

	// single quotes indicate an ascii character code
	unsigned char c;
	if (sscanf(*inptr, "'%c'", &c) == 1)
	{
		value = c;
		SkipWord(inptr);
	}
	else if (sscanf(*inptr, "0x%x", &value) == 1) // hex
		SkipWord(inptr);
	else if (sscanf(*inptr, "0X%x", &value) == 1) // hex
		SkipWord(inptr);
	else if (sscanf(*inptr, "%d", &value) == 1)	// decimal
		SkipWord(inptr);
	else if (GetNextTok(inptr) == e_none)
		value = -1;
	else
		ErrBox("Bad Int value");

	return value;
}

MxCharString
LegoGuiFile::GetString(char **inptr)
{
	MxCharString str = NULL;
	char buf[1024];

	SkipWhiteSpace(inptr);

	if (sscanf(*inptr, "%s", buf) == 1)
	{
		SkipWord(inptr);
		if (_stricmp(buf, "NONE"))
		{
			str = new char[strlen(buf)+1];
			strcpy(str, buf);
		}
	}

	return str;
}

void
LegoGuiFile::SkipWhiteSpace(char **ptr)
{
	// include comma's in white space
	while (**ptr && (**ptr == ' ' || **ptr == '\t' || **ptr == ','))
		(*ptr)++;
}

void
LegoGuiFile::SkipWord(char **ptr)
{
	// include comma's in white space
	while (**ptr && **ptr != ' ' && **ptr != '\t' && **ptr != ',')
		(*ptr)++;
}

void
LegoGuiFile::ErrBox(char *msg)
{
	AfxMessageBox(msg);
}


LegoGuiControl::LegoGuiAction *
LegoGuiFile::FindAction(char *name)
{
	for (int i=0; i<numActions; i++)
	{
		if (!_stricmp(name, actionList[i].ID))
			return actionList[i].action;
	}
	return NULL;
}

void
LegoGuiFile::AddAction()
{
	for (int i=0; i<numActions; i++)
	{
		if (!_stricmp(currentActionID, actionList[i].ID))
		{
			ErrBox("duplicate action.");
			return;
		}
	}
	if (numActions < MAX_ACTIONS)
	{
		actionList[numActions].ID = currentActionID;
		currentActionID = NULL;
		actionList[numActions].action = currentAction;
		numActions++;
		currentAction = NULL;
		actionStarted = FALSE;
	}
}

void
LegoGuiFile::WriteAction(LegoGuiControl::LegoGuiAction *action, FILE *fp)
{
	int i;

	fwrite( &(action->looping), sizeof(action->looping), 1, fp);
	fwrite( &(action->frameTime), sizeof(action->frameTime), 1, fp);
	fwrite( &(action->numFrames), sizeof(action->numFrames), 1, fp);
	for (i=0; i<action->numFrames; i++)
	{
		fwrite( &(action->offsetArray[i].x), sizeof(MxS16), 1, fp);
		fwrite( &(action->offsetArray[i].y), sizeof(MxS16), 1, fp);
	}
	for (i=0; i<action->numFrames; i++)
		fwrite( &(action->bitmapArray[i]), sizeof(action->bitmapArray[i]), 1, fp);
	fwrite(&(action->soundActionIdx), sizeof(action->soundActionIdx), 1, fp);
	fwrite(&(action->actionNameIdx), sizeof(action->actionNameIdx), 1, fp);
	fwrite( &(action->bitmapNoBlt), sizeof(action->bitmapNoBlt), 1, fp);

	// write message list for this action
	LegoGuiControl::LegoGuiMessagePtr message;
	MxU8 numMsg = (MxU8)action->messageList.GetNumElements();
	fwrite(&numMsg, sizeof(numMsg), 1, fp);
	LegoGuiControl::LegoGuiMessageListCursor cursor(&(action->messageList));
	while (cursor.Next(message))
	{
		fwrite(message->GetTarget(), strlen(message->GetTarget())+1, 1, fp);
		MxU8 msgType = (MxU8)message->GetType();
		fwrite(&msgType, sizeof(msgType), 1, fp);
		switch (message->GetType())
		{
			case LegoGuiControl::e_boolMsg:
			{
				MxBool bval = message->GetBoolValue();
				fwrite(&bval, sizeof(bval), 1, fp);
				break;
			}
			case LegoGuiControl::e_intMsg:
			{
				MxS32 ival = message->GetIntValue();
				fwrite(&ival, sizeof(ival), 1, fp);
				break;
			}
			case LegoGuiControl::e_stringMsg:
			case LegoGuiControl::e_sysVarMsg:
			{
				MxCharString sval = message->GetStringValue();
				fwrite(sval, strlen(sval)+1, 1, fp);
				break;
			}
		}
	}
}

void
LegoGuiFile::FreeActionList()
{
	for (int i=0; i<numActions; i++)
	{
		if (actionList[i].ID)
			delete actionList[i].ID;
		if (actionList[i].action)
		{
			if (actionList[i].action->offsetArray)
				delete actionList[i].action->offsetArray;
			if (actionList[i].action->bitmapArray)
				delete actionList[i].action->bitmapArray;
			delete actionList[i].action;
		}
	}
}

void
LegoGuiFile::FreeCurrentAction()
{
	if (currentActionID)
		delete currentActionID;
	currentActionID = NULL;
	if (currentAction)
	{
		if (currentAction->offsetArray)
			delete currentAction->offsetArray;
		if (currentAction->bitmapArray)
			delete currentAction->bitmapArray;
		delete currentAction;
		currentAction = NULL;
	}
}

void
LegoGuiFile::FreeBitmapNames()
{
	for (int i=0; i<m_numBitmapFiles; i++)
		delete m_bitmapFile[i];
}

void
LegoGuiFile::FreeActionNames()
{
	for (int i=0; i<m_numActionNames; i++)
		delete m_actionName[i];
}

void
LegoGuiFile::FreeSoundNames()
{
	for (int i=0; i<m_numSoundActions; i++)
		delete m_soundAction[i];
}


void
LegoGuiFile::GetGui(FILE *infp, FILE *outfp)
{
	BOOL guiDone = FALSE;
	BOOL skipCase = FALSE;
	char *inptr;
	char inbuf[1024];
	int tok;

	int gState = e_camera;

	do
	{
		do
		{
			if (fgets(inbuf, 1024, infp) == NULL)
			{
				guiDone = TRUE;
				ErrBox("EOF in GUI definition");
				break;
			}
			inptr = inbuf;
			tok = GetNextTok(&inptr);
		}
		while (tok == e_comment);

#ifdef ALL_FIELDS_REQUIRED
		if (tok != gState)
		{
			char msg[100];
			sprintf(msg, "Bad GUI item order. Got %d Expected %d", tok, gState);
			ErrBox(msg);
			guiDone = TRUE;
			break;
		}
#endif // ALL_FIELDS_REQUIRED

		switch (gState)
		{
			case e_camera:
			{
				if (tok != gState)
				{
					char msg[100];
					sprintf(msg, "Bad GUI item order. Got %d Expected %d", tok, gState);
					ErrBox(msg);
					guiDone = TRUE;
					break;
				}
				char *camName = GetString(&inptr);
				if (camName)
				{
					fwrite(camName, strlen(camName)+1, 1, outfp);
					delete camName;
				}
				else
					fwrite("", 1, 1, outfp);

				WriteBitmapArray(outfp);
				WriteSoundArray(outfp);
				WriteNamedActionArray(outfp);
				gState = e_startFont;
				break;
			}
			case e_startFont:
				if (tok != gState)
				{
					// write empty array
					WriteEmptyArray(outfp);
					skipCase = TRUE;
				}
				else
					GetFontArray(infp, outfp, e_endFont);
			case e_endFont:
				gState = e_startup;
				if (!skipCase)
					break;
				skipCase = FALSE;
			case e_startup:
			{
				if (tok == gState)
				{
					char *str = GetString(&inptr);
					if (str)
					{
						fwrite(str, strlen(str)+1, 1, outfp);
						delete str;
					}
					else
						fwrite("", 1, 1, outfp);
					gState = e_shutdown;
					break;
				}
				else
				{
					fwrite("", 1, 1, outfp);
					gState = e_shutdown;
					// fall through
				}
			}
			case e_shutdown:
			{
				if (tok == gState)
				{
					char *str = GetString(&inptr);
					if (str)
					{
						fwrite(str, strlen(str)+1, 1, outfp);
						delete str;
					}
					else
						fwrite("", 1, 1, outfp);
					gState = e_chainAction;
					break;
				}
				else
				{
					fwrite("", 1, 1, outfp);
					gState = e_chainAction;
					// fall through
				}
			}
			case e_chainAction:
			{
				if (tok == gState)
				{
					char *str = GetString(&inptr);
					if (str)
					{
						fwrite(str, strlen(str)+1, 1, outfp);
						delete str;
					}
					else
						fwrite("", 1, 1, outfp);
					gState = e_backgroundBitmapFile;
					break;
				}
				else
				{
					fwrite("", 1, 1, outfp);
					gState = e_backgroundBitmapFile;
					// fall through
				}
			}
			case e_backgroundBitmapFile:
			{
				if (tok != gState)
				{
					char msg[100];
					sprintf(msg, "Bad GUI item order. Got %d Expected %d", tok, gState);
					ErrBox(msg);
					guiDone = TRUE;
					break;
				}
				else
				{
					MxCharString str = GetString(&inptr);
					MxS16 idx = GetBitmapIndex(str);
					delete str;
					fwrite(&idx, sizeof(idx), 1, outfp);
					fwrite(&m_numControls, sizeof(m_numControls), 1, outfp);
					gState = e_controlName;
					break;
				}
			}
			case e_controlName:
			{
				if (tok != gState)
				{
					char msg[100];
					sprintf(msg, "Bad GUI item order. Got %d Expected %d", tok, gState);
					ErrBox(msg);
					guiDone = TRUE;
					break;
				}
				else
				{
					char *controlName = GetString(&inptr);
					if (controlName == NULL)
					{
						ErrBox("Invalid control name.");
						guiDone = TRUE;
					}
					else
					{
						GetControl(controlName, infp, outfp);
						delete controlName;
						if (--m_numControls == 0)
						{
							guiDone = TRUE;
						}
					}
					break;
				}
			}
		}
	}
	while (!guiDone);

}

void
LegoGuiFile::GetControl(char *p_name, FILE *p_infp, FILE *p_outfp)
{
	BOOL controlDone = FALSE;
	long controlLenLoc;
	char *inptr;
	char inbuf[1024];
	int tok;
	MxU8 keyLow = 0;


	// save current file location for length
	controlLenLoc = ftell(p_outfp);
	// write dummy length
	MxU32 len = 0;
	fwrite(&len, sizeof(len), 1, p_outfp);
	// gui control name
	fwrite(p_name, strlen(p_name)+1, 1, p_outfp);

	int cState = e_objectName;


	do
	{
		do
		{
			if (fgets(inbuf, 1024, p_infp) == NULL)
			{
				controlDone = TRUE;
				ErrBox("EOF in CONTROL definition");
				break;
			}
			inptr = inbuf;
			tok = GetNextTok(&inptr);
		}
		while (tok == e_comment);

#ifdef ALL_FIELDS_REQUIRED
		if (tok != cState)
		{
			ErrBox("Bad order in CONTROL definition");
			controlDone = TRUE;
			break;
		}
#endif // ALL_FIELDS_REQUIRED

		switch (cState)
		{
			case e_objectName:
			{
				if (tok == cState)
				{
					char *objName = GetString(&inptr);
					if (objName == NULL)
					{
						ErrBox("Invalid object name.");
						controlDone = TRUE;
					}
					else
					{
						fwrite(objName, strlen(objName)+1, 1, p_outfp);
						delete objName;
						cState = e_eventMask;
					}
					break;
				}
				else
				{
					// write empty string
					fwrite("", 1, 1, p_outfp);
					// fall through to next state
 					cState = e_eventMask;
				}

			}
			case e_eventMask:
			{
				char *str;
				MxU8 mask = 0;
				if (tok == cState)
				{
					while (str = GetString(&inptr))
					{
						mask |= LookupID(str);
						delete str;
					}
					fwrite(&mask, sizeof(mask), 1, p_outfp);
					cState = e_keyLow;
					break;
				}
				else
				{
					fwrite(&mask, sizeof(mask), 1, p_outfp);
					// fall through to next state
					cState = e_keyLow;
				}
			}
			case e_keyLow:
			{
				if (tok == cState)
				{
					keyLow = GetInt(&inptr);
					fwrite(&keyLow, sizeof(keyLow), 1, p_outfp);
					cState = e_keyHigh;
					break;
				}
				else
				{
					fwrite(&keyLow, sizeof(keyLow), 1, p_outfp);
					// fall through to next state
					cState = e_keyHigh;
				}
			}
			case e_keyHigh:
			{
				MxU8 data = keyLow;
				if (tok == cState)
				{
					data = GetInt(&inptr);
					fwrite(&data, sizeof(data), 1, p_outfp);
					cState = e_sysVar;
					break;
				}
				else
				{
					fwrite(&data, sizeof(data), 1, p_outfp);
					// fall through to next state
					cState = e_sysVar;
				}
			}
			case e_sysVar:
			{
				if (tok == cState)
				{
					char *varName = GetString(&inptr);
					if (varName)
					{
						fwrite(varName, strlen(varName)+1, 1, p_outfp);
						delete varName;
					}
					else
					{
						fwrite("", 1, 1, p_outfp);
					}
					cState = e_type;
					break;
				}
				else
				{
					fwrite("", 1, 1, p_outfp);
					// fall through to next state
 					cState = e_type;
				}
			}
			case e_type:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				char *str = GetString(&inptr);
				MxU8 type = LookupID(str);
				fwrite(&type, sizeof(type), 1, p_outfp);
				delete str;
				switch (type)
				{
					case LegoGuiControl::e_pushbutton:
						cState = e_releasedState;
						break;
					case LegoGuiControl::e_toggle:
						cState = e_initToggle;
						break;
					case LegoGuiControl::e_string:
						cState = e_maxLength;
						break;
					case LegoGuiControl::e_radio:
					case LegoGuiControl::e_slider:
						ErrBox("Control type not implemented");
				}
				break;
			}
			case e_initToggle:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				MxBool isRadio = FALSE;
				fwrite(&isRadio, sizeof(isRadio), 1, p_outfp);

				MxBool tState = GetBool(&inptr);
				fwrite(&tState, sizeof(tState), 1, p_outfp);

				cState = e_releasedState;
				break;
			}
			case e_maxLength:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				MxU8 len = GetInt(&inptr);
				fwrite(&len, sizeof(len), 1, p_outfp);

				cState = e_fontIndex;
				break;
			}
			case e_fontIndex:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				MxU8 font = GetInt(&inptr);
				fwrite(&font, sizeof(font), 1, p_outfp);

				cState = e_releasedState;
				break;
			}
			case e_releasedState:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				char *name = GetString(&inptr);
				LegoGuiControl::LegoGuiAction *act = FindAction(name);
				if (!act)
				{
					char msg[256];
					sprintf(msg, "Can't find Action: %s", name);
					ErrBox(msg);
					controlDone = TRUE;
					break;
				}
				WriteAction(act, p_outfp);
				delete name;
				cState = e_selectAction;
			}
				break;
			case e_selectAction:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				char *name = GetString(&inptr);
				LegoGuiControl::LegoGuiAction *act = FindAction(name);
				if (!act)
				{
					char msg[256];
					sprintf(msg, "Can't find Action: %s", name);
					ErrBox(msg);
					controlDone = TRUE;
					break;
				}
				WriteAction(act, p_outfp);
				delete name;
				cState = e_selectedState;
				break;
			}
			case e_selectedState:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				char *name = GetString(&inptr);
				LegoGuiControl::LegoGuiAction *act = FindAction(name);
				if (!act)
				{
					char msg[256];
					sprintf(msg, "Can't find Action: %s", name);
					ErrBox(msg);
					controlDone = TRUE;
					break;
				}
				WriteAction(act, p_outfp);
				delete name;
				cState = e_releaseAction;
				break;
			}
			case e_releaseAction:
			{
				if (tok != cState)
				{
					ErrBox("Bad order in CONTROL definition");
					controlDone = TRUE;
					break;
				}
				char *name = GetString(&inptr);
				LegoGuiControl::LegoGuiAction *act = FindAction(name);
				if (!act)
				{
					char msg[256];
					sprintf(msg, "Can't find Action: %s", name);
					ErrBox(msg);
					controlDone = TRUE;
					break;
				}
				WriteAction(act, p_outfp);
				delete name;
				controlDone = TRUE;
				break;
			}
		}
	}
	while (!controlDone);

	long curLoc = ftell(p_outfp);
	fseek(p_outfp, (long)controlLenLoc, SEEK_SET);
	MxU32 controlLen = curLoc - controlLenLoc - sizeof(controlLen);
	fwrite(&controlLen, sizeof(controlLen), 1, p_outfp);
	fseek(p_outfp, 0l, SEEK_END);
}

MxU8
LegoGuiFile::LookupID(char *p_id)
{
	struct intId {
		MxU8	id;
		char	*name;
	};

	static intId internalIds[] = {
		{LegoGuiControl::e_pushbutton, "PUSHBUTTON"},
		{LegoGuiControl::e_toggle, "TOGGLE"},
		{LegoGuiControl::e_radio, "RADIO"},
		{LegoGuiControl::e_slider, "SLIDER"},
		{LegoGuiControl::e_string, "STRING"},
		{e_none, "NONE"},
		{LegoGuiControl::c_buttonUp, "BUTTON_UP"},
		{LegoGuiControl::c_buttonDown, "BUTTON_DOWN"},
		{LegoGuiControl::c_drag, "DRAG"},
	};

	// first check canned ID's
	for (int i=0; i<(sizeof(internalIds)/sizeof(intId)) ; i++)
	{
		if (!_strnicmp(p_id, internalIds[i].name, strlen(internalIds[i].name)))
			return internalIds[i].id;
	}

	// now search external ID's
	// stub
	return 1;
}

void
LegoGuiFile::WriteNamedActionArray(FILE *p_outfp)
{
	MxS16 num = m_numActionNames;

	// save current file location for length
	int saveLenLoc = ftell(p_outfp);
	// write dummy length
	MxU32 len = 0;
	fwrite(&len, sizeof(len), 1, p_outfp);

	// write count
	fwrite(&num, sizeof(num), 1, p_outfp);

	for (int i=0; i<num; i++)
	{
		fwrite(m_actionName[i], strlen(m_actionName[i])+1, 1, p_outfp);
	}

	// replace length
	long curLoc = ftell(p_outfp);
	fseek(p_outfp, (long)saveLenLoc, SEEK_SET);
	len = curLoc - saveLenLoc - sizeof(len);
	fwrite(&len, sizeof(len), 1, p_outfp);
	fseek(p_outfp, 0l, SEEK_END);
}

void
LegoGuiFile::WriteSoundArray(FILE *p_outfp)
{
	MxS16 num = m_numSoundActions;

	// save current file location for length
	int saveLenLoc = ftell(p_outfp);
	// write dummy length
	MxU32 len = 0;
	fwrite(&len, sizeof(len), 1, p_outfp);

	// write count
	fwrite(&num, sizeof(num), 1, p_outfp);

	for (int i=0; i<num; i++)
	{
		fwrite(m_soundAction[i], strlen(m_soundAction[i])+1, 1, p_outfp);
	}

	// replace length
	long curLoc = ftell(p_outfp);
	fseek(p_outfp, (long)saveLenLoc, SEEK_SET);
	len = curLoc - saveLenLoc - sizeof(len);
	fwrite(&len, sizeof(len), 1, p_outfp);
	fseek(p_outfp, 0l, SEEK_END);
}

void
LegoGuiFile::WriteBitmapArray(FILE *p_outfp)
{
	int i;
	MxS16 num = m_numBitmapFiles;

	// save current file location for length
	int saveLenLoc = ftell(p_outfp);
	// write dummy length
	MxU32 len = 0;
	fwrite(&len, sizeof(len), 1, p_outfp);

	// write count
	fwrite(&num, sizeof(num), 1, p_outfp);

	for (i=0; i<num; i++)
	{
		CopyFile(m_bitmapFile[i], p_outfp);
	}

	// replace length
	long curLoc = ftell(p_outfp);
	fseek(p_outfp, (long)saveLenLoc, SEEK_SET);
	len = curLoc - saveLenLoc - sizeof(len);
	fwrite(&len, sizeof(len), 1, p_outfp);
	fseek(p_outfp, 0l, SEEK_END);
}

void
LegoGuiFile::GetFontArray(FILE *p_infp, FILE *p_outfp, int p_tok)
{
	int saveLenLoc;
	MxS16 numFonts = 0;
	int saveCountLoc;

	int saveFMLenLoc;
	MxU8 numChars = 0;
	int saveCCountLoc;

	BOOL done = FALSE;
	char inbuf[1024];
	char *inptr;
	int nextTok;
	MxU8 ccode;
	MxS16 cindex;

	// save current file location for length
	saveLenLoc = ftell(p_outfp);
	// write dummy length
	MxU32 len = 0;
	fwrite(&len, sizeof(len), 1, p_outfp);
	// save location for count
	saveCountLoc = ftell(p_outfp);
	// write dummy count
	fwrite(&numFonts, sizeof(numFonts), 1, p_outfp);

	do
	{
		if (fgets(inbuf, 1024, p_infp) == NULL)
		{
			ErrBox("EOF while reading files");
			done = TRUE;
		}
		inptr = inbuf;
		if ((nextTok = GetNextTok(&inptr)) == p_tok)
			done = TRUE;
		else if (nextTok == e_newFont)
		{
			// starting a new fontmap
			if (numChars)
			{
				// replace length of previous fontmap
				long curLoc = ftell(p_outfp);
				fseek(p_outfp, (long)saveFMLenLoc, SEEK_SET);
				len = curLoc - saveFMLenLoc - sizeof(len);
				fwrite(&len, sizeof(len), 1, p_outfp);

				//replace count of previous fontmap
				fseek(p_outfp, (long)saveCCountLoc, SEEK_SET);
				fwrite(&numChars, sizeof(numChars), 1, p_outfp);
				fseek(p_outfp, 0l, SEEK_END);
			}
			numFonts++;
			numChars = 0;
			// save location for length of next fontmap
			saveFMLenLoc = ftell(p_outfp);
			// write dummy length
			fwrite(&len, sizeof(len), 1, p_outfp);

			// save location for count of character entries
			saveCCountLoc = ftell(p_outfp);
			// write dummy count
			fwrite(&numChars, sizeof(numChars), 1, p_outfp);
		}
		else	// another code/filename pair
		{
			inptr = inbuf;
			SkipWhiteSpace(&inptr);
			// single character codes are in quotes
			// hex starts with 0x
			// otherwise it must be decimal
			int iccode = 0;
			if (*inptr == '\'')	// check for quoted character
				iccode = *++inptr;
			else if (sscanf(inptr, "0x%x", &iccode) != 1) // then hex
				sscanf(inptr, "%d", &iccode);	  // then decimal
			ccode = (MxU8)iccode;

			// now get the bitmap index
			SkipWord(&inptr);
			MxCharString str = GetString(&inptr);
			cindex = GetBitmapIndex(str);
			delete str;

			// write binary file data
			numChars++;
			fwrite(&ccode, sizeof(ccode), 1, p_outfp);
			fwrite(&cindex, sizeof(cindex), 1, p_outfp);
		}
	}
	while (!done);

	if (numChars)
	{
		// replace length of pending fontmap
		long curLoc = ftell(p_outfp);
		fseek(p_outfp, (long)saveFMLenLoc, SEEK_SET);
		len = curLoc - saveFMLenLoc - sizeof(len);
		fwrite(&len, sizeof(len), 1, p_outfp);

		//replace count of pending fontmap
		fseek(p_outfp, (long)saveCCountLoc, SEEK_SET);
		fwrite(&numChars, sizeof(numChars), 1, p_outfp);
		fseek(p_outfp, 0l, SEEK_END);
	}

	// replace length
	long curLoc = ftell(p_outfp);
	fseek(p_outfp, (long)saveLenLoc, SEEK_SET);
	len = curLoc - saveLenLoc - sizeof(len);
	fwrite(&len, sizeof(len), 1, p_outfp);
	//replace count
	fseek(p_outfp, (long)saveCountLoc, SEEK_SET);
	fwrite(&numFonts, sizeof(numFonts), 1, p_outfp);
	fseek(p_outfp, 0l, SEEK_END);
}

void
LegoGuiFile::GetFontBitmapNames(FILE *p_infp, int p_tok)
{
	BOOL done = FALSE;
	char inbuf[1024];
	char *inptr;
	int nextTok;

	do
	{
		if (fgets(inbuf, 1024, p_infp) == NULL)
		{
			ErrBox("EOF while reading files");
			done = TRUE;
		}
		inptr = inbuf;
		if ((nextTok = GetNextTok(&inptr)) == p_tok)
			done = TRUE;
		else if (nextTok != e_newFont)
		{
			inptr = inbuf;
			SkipWhiteSpace(&inptr);

			// skip char code and get the bitmap filename
			SkipWord(&inptr);

			if (m_numBitmapFiles < MAX_BITMAP_FILES)
			{
				MxCharString str = GetString(&inptr);
				if (GetBitmapIndex(str) == -1)
					m_bitmapFile[m_numBitmapFiles++] = str;
				else
					delete str;
			}
		}
	}
	while (!done);
}

void
LegoGuiFile::CopyFile(char *p_name, FILE *p_outfp)
{
	long len;
	BOOL done = FALSE;
	char *buf[1024];

	// can't have trailing white space
	char *ptr = p_name;
	while (*ptr && *ptr != ' ' && *ptr != '\t' &&
						*ptr != 0x0a && *ptr != 0x0d)
		ptr++;
	*ptr = '\0';

	// Try filename as is
	FILE *infp = fopen(p_name, "rb");

	if (!infp)
	{
		// Try adding ".bmp" to name
		int len = strlen(p_name) + 5;
		char *nameBuf = new char[len];
		sprintf(nameBuf, "%s.bmp", p_name);
		infp = fopen(nameBuf, "rb");
	}

	if (!infp)
	{
		ErrBox("Can't open bitmap file");
		return;
	}

	fseek(infp, 0l, SEEK_END);
	MxU32 fileSize = ftell(infp);
	fseek(infp, 0l, SEEK_SET);
	fwrite(&fileSize, sizeof(fileSize), 1, p_outfp);	// we need the file length
	do
	{
		len = fread(buf, 1, sizeof(buf), infp);
		if (len)
		{
			fwrite(buf, 1, len, p_outfp);
		}
		else
			done = TRUE;
	}
	while (!done);
}

void
LegoGuiFile::WriteEmptyArray(FILE *p_outfp)
{
	// write length
	MxU32 len = sizeof(MxS16);
	fwrite(&len, sizeof(len), 1, p_outfp);

	// write count
	MxS16 num = 0;
	fwrite(&num, sizeof(num), 1, p_outfp);
}


