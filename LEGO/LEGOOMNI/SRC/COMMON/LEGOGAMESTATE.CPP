/*   
    This unpublished source code contains trade secrets and
    copyrighted materials which are the property of Mindscape, Inc.
    Unauthorized use, copying or distribution is a violation of U.S.
    and international laws and is strictly prohibited.
*/

#include "StdLego.h"
#include "MxVariableTable.h"
#include "LegoOmni.h"
#include "LegoGameState.h"


LegoGameState::LegoGameState()
{
	m_name = new MxVariable(CURRENT_PLAYER_VARIABLE, DEFAULT_PLAYER_NAME);
	LegoOmni::GetInstance()->GetVariableTable()->SetVariable(m_name);
}

LegoGameState::~LegoGameState()
{
}

void
LegoGameState::SetPlayerName(MxCharString p_name)
{
	m_name->SetValue(p_name);
}

const MxChar*
LegoGameState::GetPlayerName()
{
	return m_name->GetValue();
}

MxResult
LegoGameState::Save(MxCharString p_name)
{
	return SUCCESS;
}

MxResult
LegoGameState::Load(MxCharString p_name)
{
	return SUCCESS;
}

