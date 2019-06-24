#include "stdafx.h"
#include "application.h"
#include "director.h"
#include "titleScene.h"
#include "helpScene.h"
#include "gameScene.h"
#include "gameoverScene.h"
#include "levelScene.h"

//*********************************************************************
//FUNCTION:
int CApplication::run()
{
	if (!__init()) return EXIT_FAILURE;

	while (0 == __processLoop())
	{
		CDirector::getInstance()->update();

		CHECK_RESULT(DxLib::ScreenFlip());
	}

	__destroy();

	return EXIT_SUCCESS;
}

//*********************************************************************
//FUNCTION:
bool CApplication::__init()
{
	CHECK_RESULT(DxLib::ChangeWindowMode(TRUE));
	CHECK_RESULT(DxLib::SetGraphMode(WIDTH, HEIGHT, 32));
	CHECK_RESULT(DxLib::SetWindowText("SOB - Lost Doll"));
	CHECK_RESULT(DxLib::SetBackgroundColor(50, 50, 50));

	CHECK_RESULT(DxLib::DxLib_Init());
	CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));

	CDirector::getInstance()->registerScene(TITLE_SCENE, new CTitleScene);
	CDirector::getInstance()->registerScene(HELP_SCENE, new CHelpScene);
	CDirector::getInstance()->registerScene(GAME_SCENE, new CGameScene);
	CDirector::getInstance()->registerScene(GAME_OVER_SCENE, new CGameoverScene);
	CDirector::getInstance()->registerScene(LEVEL_SCENE, new CLevelScene);

	if (!CDirector::getInstance()->setActiveScene(TITLE_SCENE)) return false;
	CDirector::getInstance()->displayStatus(true);

	return true;
}

//*********************************************************************
//FUNCTION:
int CApplication::__processLoop()
{
	if (0 != DxLib::ProcessMessage()) return -1;
	if (0 != DxLib::ClearDrawScreen()) return -1;

	return 0;
}

//*********************************************************************
//FUNCTION:
void CApplication::__destroy()
{
	CHECK_RESULT(DxLib::DxLib_End());
}