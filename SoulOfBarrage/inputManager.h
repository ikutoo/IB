#pragma once
#include "commonMicro.h"

#define GET_KEY_STATE(keyCode) CInputManager::getInstance()->getKeyState(keyCode)

namespace DxEngine
{
	class CInputManager
	{
	public:
		SINGLETION(CInputManager);

		void update();

		int getKeyState(unsigned char vKeyCode) const { return m_KeyState[vKeyCode]; }

	private:
		CInputManager() = default;
		~CInputManager() = default;

		int m_KeyState[256] = {};
	};
}