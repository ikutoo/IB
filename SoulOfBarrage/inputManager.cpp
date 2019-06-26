#include "stdafx.h"
#include "inputManager.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CInputManager::update()
{
	char KeyState[256];
	GetHitKeyStateAll(KeyState);

	for (int i = 0; i < 256; i++)
	{
		KeyState[i] == 1 ? m_KeyState[i]++ : m_KeyState[i] = 0;
	}
}