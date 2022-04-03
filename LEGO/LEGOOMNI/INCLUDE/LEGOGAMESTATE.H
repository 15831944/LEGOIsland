/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#ifndef __LEGOGAMESTATE_H
#define __LEGOGAMESTATE_H

#include "MxCore.h"

class MxVariable;

#define CURRENT_PLAYER_VARIABLE "CurrentPlayer"
#define DEFAULT_PLAYER_NAME "SHIFTY"

class LegoGameState : public MxCore {
protected:
	MxVariable	*m_name;
public:
	LegoGameState();
	~LegoGameState();
	void			SetPlayerName(MxCharString p_name);
	const MxChar	*GetPlayerName();
	MxResult		Save(MxCharString p_name);
	MxResult		Load(MxCharString p_name);
};

#endif // __LEGOGAMESTATE_H

