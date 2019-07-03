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

	while (0 == DxLib::ProcessMessage() && !m_IsMainLoopDone)
	{
		__update();
		__render();
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
	if (!m_pActiveScene->initV()) return false;

	return true;
}

//*********************************************************************
//FUNCTION:
bool CEngine::__init()
{
	for (auto PreInitFunc : m_PreInitFuncs) PreInitFunc();

	CHECK_RESULT(DxLib::DxLib_Init());
	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));

	for (auto InitFunc : m_InitFuncs) InitFunc();

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CEngine::__update()
{
	CInputManager::getInstance()->update();

	int DeltaTime = GetNowCount() - m_TimeCounter;
	m_FPS = 1000.0f / DeltaTime;
	m_TimeCounter = GetNowCount();

	m_pActiveScene->updateV(DeltaTime);

	for (auto UpdateFunc : m_UpdateFuncs) UpdateFunc();
}

//***********************************************************************************************
//FUNCTION:
void CEngine::__render()
{
	CHECK_RESULT(ClearDrawScreen());

	m_pActiveScene->drawV();
	if (m_DisplayStatus) __drawStatus();

	CHECK_RESULT(DxLib::ScreenFlip());
}

//*********************************************************************
//FUNCTION:
void CEngine::__destroy()
{
	m_pActiveScene->destroyV();
	SAFE_DELETE(m_pActiveScene);
	CHECK_RESULT(DxLib::DxLib_End());
}

//*********************************************************************
//FUNCTION:
void CEngine::__drawStatus()
{
	CHECK_RESULT(DxLib::SetFontSize(20));

	char Buf[0xff];
	unsigned int Color = 0x00ff00;
	sprintf(Buf, " FPS: %6.1f \n", m_FPS);
	CHECK_RESULT(DxLib::DrawString(10, 10, Buf, Color));
}

//*********************************************************************
//FUNCTION:
void CEngine::setWindowSize(int vWidth, int vHeight)
{
	m_WindowSize.x = vWidth;
	m_WindowSize.y = vHeight;
	CHECK_RESULT(DxLib::SetWindowSize(vWidth, vHeight));
}

//*********************************************************************
//FUNCTION:
void CEngine::setGraphSize(int vWidth, int vHeight)
{
	m_GraphSize.x = vWidth;
	m_GraphSize.y = vHeight;
	CHECK_RESULT(DxLib::SetGraphMode(vWidth, vHeight, 32));
}