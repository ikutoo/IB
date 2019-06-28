#pragma once
#include "common.h"

#define GET_KEY_STATE(keyCode) CInputManager::getInstance()->getKeyState(keyCode)
#define CHECK_HIT_KEY(keyCode) CInputManager::getInstance()->checkHitKey(keyCode)

namespace DxEngine
{
	class CInputManager
	{
	public:
		SINGLETION(CInputManager);

		void update();

		int getKeyState(unsigned char vKeyCode) const { return m_KeyState[vKeyCode]; }
		bool checkHitKey(unsigned char vKeyCode) const { return 1 == m_KeyState[vKeyCode]; }

	private:
		CInputManager() = default;
		~CInputManager() = default;

		int m_KeyState[256] = {};
	};
}