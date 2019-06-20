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

		ASSERT_SUCCESS(ScreenFlip());
	}

	__destroy();

	return EXIT_SUCCESS;
}

//*********************************************************************
//FUNCTION:
bool CApplication::__init()
{
	ASSERT_SUCCESS(ChangeWindowMode(TRUE));
	ASSERT_SUCCESS(SetGraphMode(WIDTH, HEIGHT, 32));
	ASSERT_SUCCESS(SetWindowText("IB"));
	ASSERT_SUCCESS(SetBackgroundColor(50, 50, 50));

	ASSERT_SUCCESS(DxLib_Init());
	ASSERT_SUCCESS(SetDrawScreen(DX_SCREEN_BACK));

	ASSERT_SUCCESS(SetMouseDispFlag(FALSE));

	CDirector::getInstance()->registerScene(TITLE_SCENE, new CTitleScene);
	CDirector::getInstance()->registerScene(HELP_SCENE, new CHelpScene);
	CDirector::getInstance()->registerScene(GAME_SCENE, new CGameScene);
	CDirector::getInstance()->registerScene(GAME_OVER_SCENE, new CGameoverScene);

	_ASSERT(CDirector::getInstance()->setActiveScene(TITLE_SCENE));

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
	ASSERT_SUCCESS(DxLib_End());
}