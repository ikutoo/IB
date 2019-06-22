#include "stdafx.h"
#include "engine.h"
#include "director.h"
#include "titleScene.h"
#include "helpScene.h"
#include "gameScene.h"
#include "gameoverScene.h"

//*********************************************************************
//FUNCTION:
int CEngine::run()
{
	if (!__init()) return EXIT_FAILURE;

	while (true)
	{
		if (0 != DxLib::ProcessMessage()) break;



		CDirector::getInstance()->update();

		if (0 != DxLib::ClearDrawScreen()) break;
		CHECK_RESULT(DxLib::ScreenFlip());
	}

	__destroy();

	return EXIT_SUCCESS;
}

//*********************************************************************
//FUNCTION:
bool CEngine::__init()
{
	CHECK_RESULT(DxLib::ChangeWindowMode(TRUE));
	CHECK_RESULT(DxLib::SetGraphMode(WIDTH, HEIGHT, 32));
	CHECK_RESULT(DxLib::SetWindowText("SOB - Lost Doll"));
	CHECK_RESULT(DxLib::SetBackgroundColor(50, 50, 50));

	CHECK_RESULT(DxLib::DxLib_Init());
	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));

	CHECK_RESULT(DxLib::SetMouseDispFlag(FALSE));

	CDirector::getInstance()->registerScene(TITLE_SCENE, new CTitleScene);
	CDirector::getInstance()->registerScene(HELP_SCENE, new CHelpScene);
	CDirector::getInstance()->registerScene(GAME_SCENE, new CGameScene);
	CDirector::getInstance()->registerScene(GAME_OVER_SCENE, new CGameoverScene);

	if (!CDirector::getInstance()->setActiveScene(TITLE_SCENE)) return false;
	CDirector::getInstance()->displayFPS(true);

	return true;
}

//*********************************************************************
//FUNCTION:
void CEngine::__destroy()
{
	CHECK_RESULT(DxLib::DxLib_End());
}

//*********************************************************************
//FUNCTION:
void CEngine::__handleEvents()
{
	
}

//*********************************************************************
//FUNCTION:
void CEngine::__update()
{

}

//*********************************************************************
//FUNCTION:
void CEngine::__render()
{

}