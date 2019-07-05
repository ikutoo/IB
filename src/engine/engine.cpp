#include "engine.h"
#include <DXLib/DxLib.h>
#include "inputManager.h"
#include "scene.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
int CEngine::run()
{
	if (!__init()) return EXIT_FAILURE;

	CCPUTimer Timer;
	while (0 == DxLib::ProcessMessage() && !m_IsMainLoopDone)
	{
		Timer.start();

		__update();
		__render();

		while (1000.0 / m_ExpectedFPS - Timer.getTimestamp() > 0.0) {};

		Timer.stop();
	}

	__destroy();

	return EXIT_SUCCESS;
}

//***********************************************************************************************
//FUNCTION:
bool CEngine::setActiveScene(CScene* vScene)
{
	_ASSERT(vScene);

	if (m_pActiveScene)
	{
		m_pActiveScene->destroyV();
		SAFE_DELETE(m_pActiveScene);
	}

	m_pActiveScene = vScene;

	if (!m_IsInitialized) return true;
	if (!m_pActiveScene->initV()) return false;

	return true;
}

//*********************************************************************
//FUNCTION:
bool CEngine::__init()
{
	for (auto InitFunc : m_InitFuncs) InitFunc();

	__allocConsoleIfNeccessary();
	__initWindowInfo();

	CHECK_RESULT(DxLib::DxLib_Init());
	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));

	if (!m_pActiveScene->initV()) return false;

	m_Timer.start();

	m_IsInitialized = true;
	DxLib::LogFileAdd("Success to initialize DxEngine.\n");

	return m_IsInitialized;
}

//***********************************************************************************************
//FUNCTION:
void CEngine::__update()
{
	CInputManager::getInstance()->update();

	double DeltaTime = __updateFPS();

	m_pActiveScene->updateV(DeltaTime);
	for (auto UpdateFunc : m_UpdateFuncs) UpdateFunc();
}

//***********************************************************************************************
//FUNCTION:
void CEngine::__render()
{
	CHECK_RESULT(ClearDrawScreen());

	m_pActiveScene->drawV();
	if (m_DisplayStatusHint) __drawStatus();

	CHECK_RESULT(DxLib::ScreenFlip());
}

//*********************************************************************
//FUNCTION:
void CEngine::__destroy()
{
	m_Timer.stop();

	m_pActiveScene->destroyV();
	SAFE_DELETE(m_pActiveScene);
	CHECK_RESULT(DxLib::DxLib_End());

	DxLib::LogFileAdd("Success to destroy DxEngine.\n");

	__freeConsoleIfNecessary();
}

//*********************************************************************
//FUNCTION:
void CEngine::__drawStatus()
{
	unsigned int Color = 0x00ff00;
	CHECK_RESULT(DxLib::SetFontSize(20));
	int y = 10;

	for (auto & iter : m_AppStatusMap)
	{
		char Buf[0xff];
		sprintf(Buf, " %s: %6.1f \n", iter.first.c_str(), iter.second);
		CHECK_RESULT(DxLib::DrawString(10, y, Buf, Color));
		y += 20;
	}
}

//***********************************************************************************************
//FUNCTION:
bool CEngine::__initWindowInfo()
{
	CHECK_RESULT(DxLib::SetWindowSize(m_DisplayInfo.WindowSize.x, m_DisplayInfo.WindowSize.y));
	CHECK_RESULT(DxLib::SetGraphMode(m_GraphSize.x, m_GraphSize.y, 32));

	m_DisplayInfo.ScreenSize = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	m_DisplayInfo.WindowPosition.x = (m_DisplayInfo.ScreenSize.x - m_DisplayInfo.WindowSize.x) / 2;
	m_DisplayInfo.WindowPosition.y = (m_DisplayInfo.ScreenSize.y - m_DisplayInfo.WindowSize.y) / 2;

	CHECK_RESULT(DxLib::ChangeWindowMode(!m_DisplayInfo.IsFullscreen));
	CHECK_RESULT(DxLib::SetWindowPosition(m_DisplayInfo.WindowPosition.x, m_DisplayInfo.WindowPosition.y));
	CHECK_RESULT(DxLib::SetWindowText(m_DisplayInfo.WindowTitle.c_str()));

	return true;
}

//***********************************************************************************************
//FUNCTION:
double DxEngine::CEngine::__updateFPS()
{
	double t = m_Timer.getTimestamp();
	double DeltaTime = t - m_CurrentTime;
	m_CurrentTime = t;

	m_FPS = 1000.0f / DeltaTime;

	updateStatus("FPS", m_FPS);

	return DeltaTime;
}

//***********************************************************************************************
//FUNCTION:
void DxEngine::CEngine::__allocConsoleIfNeccessary()
{
#ifdef _DEBUG
	if (m_ShowConsoleHint)
	{
		AllocConsole();
		freopen("CONIN$", "r", stdin);
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
	}
#endif
}

//***********************************************************************************************
//FUNCTION:
void DxEngine::CEngine::__freeConsoleIfNecessary()
{
#ifdef _DEBUG
	if (m_ShowConsoleHint)
	{
		FreeConsole();
	}
#endif
}