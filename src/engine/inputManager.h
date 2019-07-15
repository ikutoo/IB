#pragma once
#include "common.h"

#define GET_KEY_STATE(keyCode) CInputManager::getInstance()->getKeyState(keyCode)
#define CHECK_HIT_KEY(keyCode) CInputManager::getInstance()->checkHitKey(keyCode)
#define CHECK_RELEASE_KEY(keyCode) CInputManager::getInstance()->checkReleaseKey(keyCode)

namespace DxEngine
{
	class CInputManager
	{
	public:
		SINGLETION(CInputManager);

		void update();

		int getKeyState(unsigned char vKeyCode) const { return m_KeyState[vKeyCode]; }
		bool checkHitKey(unsigned char vKeyCode) const { return 1 == m_KeyState[vKeyCode]; }
		bool checkReleaseKey(unsigned char vKeyCode) const { return (m_KeyState[vKeyCode] == 0) && (m_PrevKeyState[vKeyCode] != 0); }

	private:
		CInputManager() = default;
		~CInputManager() = default;

		int m_PrevKeyState[256] = {};
		int m_KeyState[256] = {};
	};
}