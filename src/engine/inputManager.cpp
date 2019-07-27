#include "inputManager.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CInputManager::update()
{
	//update XInput state
	m_PrevXInputState = m_XInputState;
	GetJoypadXInputState(DX_INPUT_PAD1, &m_XInputState);

	//update key state
	char KeyState[256];
	CHECK_RESULT(DxLib::GetHitKeyStateAll(KeyState));

	for (int i = 0; i < 256; i++)
	{
		m_PrevKeyState[i] = m_KeyState[i];
		KeyState[i] == 1 ? m_KeyState[i]++ : m_KeyState[i] = 0;
	}
}