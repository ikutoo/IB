#include "inputManager.h"
#include <DXLib/DxLib.h>

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CInputManager::update()
{
	char KeyState[256];
	CHECK_RESULT(DxLib::GetHitKeyStateAll(KeyState));

	for (int i = 0; i < 256; i++)
	{
		m_PrevKeyState[i] = m_KeyState[i];
		KeyState[i] == 1 ? m_KeyState[i]++ : m_KeyState[i] = 0;
	}
}