#include "stdafx.h"
#include "application.h"
#include "director.h"
#include "titleScene.h"
#include "helpScene.h"
#include "gameScene.h"
#include "gameoverScene.h"

//*********************************************************************
//FUNCTION:
int CApplication::run()
{
	if (!__init()) return EXIT_FAILURE;

	while (0 == __processLoop())
	{
		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		CDirector::getInstance()->update();

		CHECK_RESULT(ScreenFlip());
	}

	__destroy();

	return EXIT_SUCCESS;
}

//*********************************************************************
//FUNCTION:
bool CApplication::__init()
{
	CHECK_RESULT(ChangeWindowMode(TRUE));
	CHECK_RESULT(SetGraphMode(WIDTH, HEIGHT, 32));
	CHECK_RESULT(SetWindowText("Soul of Barrage - Ô­µã"));
	CHECK_RESULT(SetBackgroundColor(50, 50, 50));

	CHECK_RESULT(DxLib_Init());
	CHECK_RESULT(SetDrawScreen(DX_SCREEN_BACK));

	CHECK_RESULT(SetMouseDispFlag(FALSE));

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
int CApplication::__processLoop()
{
	if (0 != ProcessMessage()) return -1;
	if (0 != ClearDrawScreen()) return -1;

	return 0;
}

//*********************************************************************
//FUNCTION:
void CApplication::__destroy()
{
	CHECK_RESULT(DxLib_End());
}