#pragma once
#include <DXLib/DxLib.h>
#include "common.h"

#define IS_KEY_PRESSED(keyCode) CInputManager::getInstance()->isKeyPressed(keyCode)
#define CHECK_HIT_KEY(keyCode) CInputManager::getInstance()->checkHitKey(keyCode)
#define CHECK_RELEASE_KEY(keyCode) CInputManager::getInstance()->checkReleaseKey(keyCode)

#define IS_JOYPAD_BUTTON_PRESSED(xInput) CInputManager::getInstance()->isJoypadButtonPressed(xInput)
#define CHECK_HIT_JOYPAD_BUTTON(xInput) CInputManager::getInstance()->checkHitJoypadButton(xInput)
#define CHECK_RELEASE_JOYPAD_BUTTON(xInput) CInputManager::getInstance()->checkReleaseJoypadButton(xInput)

namespace DxEngine
{
	//TODO: 使用回调机制是否会更好？
	class CInputManager
	{
	public:
		SINGLETION(CInputManager);

		void update();

		bool isKeyPressed(unsigned char vKeyCode) const { return m_KeyState[vKeyCode]; }
		bool checkHitKey(unsigned char vKeyCode) const { return 1 == m_KeyState[vKeyCode]; }
		bool checkReleaseKey(unsigned char vKeyCode) const { return (m_KeyState[vKeyCode] == 0) && (m_PrevKeyState[vKeyCode] != 0); }

		bool isJoypadButtonPressed(unsigned char vXInput) const { return m_XInputState.Buttons[vXInput]; }
		bool checkHitJoypadButton(unsigned char vXInput) const { return (m_XInputState.Buttons[vXInput] == 1) && (m_PrevXInputState.Buttons[vXInput] == 0); }
		bool checkReleaseJoypadButton(unsigned char vXInput) const { return (m_XInputState.Buttons[vXInput] == 0) && (m_PrevXInputState.Buttons[vXInput] == 1); }

	private:
		CInputManager() = default;
		~CInputManager() = default;

		int m_PrevKeyState[256] = {};
		int m_KeyState[256] = {};

		XINPUT_STATE m_PrevXInputState = {};
		XINPUT_STATE m_XInputState = {};
	};
}