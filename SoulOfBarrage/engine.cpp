#include "stdafx.h"
#include "engine.h"
#include "inputManager.h"
#include "scene.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
int CEngine::run()
{
	if (!__init()) return EXIT_FAILURE;

	while (0 == DxLib::ProcessMessage())
	{
		CInputManager::getInstance()->update();

		CHECK_RESULT(ClearDrawScreen());

		__update();
		__render();

		CHECK_RESULT(DxLib::ScreenFlip());
	}

	__destroy();

	return EXIT_SUCCESS;
}

//***********************************************************************************************
//FUNCTION:
bool CEngine::setActiveScene(int vSceneID)
{
	if (m_ID2SceneMap.find(vSceneID) == m_ID2SceneMap.end()) return false;

	if (m_pActiveScene) m_pActiveScene->destroyV();
	m_pActiveScene = m_ID2SceneMap[vSceneID];
	if (!m_pActiveScene->initV()) return false;

	return true;
}

//*********************************************************************
//FUNCTION:
bool CEngine::__init()
{
	CHECK_RESULT(DxLib::DxLib_Init());
	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));

	for (auto InitFunc : m_ExtraInitFuncs) InitFunc();

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CEngine::__update()
{
	int deltaTime = GetNowCount() - m_TimeCounter;
	m_FPS = 1000.0 / deltaTime;
	m_TimeCounter = GetNowCount();

	for (auto UpdateFunc : m_ExtraUpdateFuncs) UpdateFunc();
}

//***********************************************************************************************
//FUNCTION:
void CEngine::__render()
{
	if (m_DisplayStatus) __drawStatus();
	m_pActiveScene->updateV(0.0);
}

//*********************************************************************
//FUNCTION:
void CEngine::__destroy()
{
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