#include "stdafx.h"
#include "engine.h"
#include "barrageManager.h"
#include "titleScene.h"
#include "helpScene.h"
#include "gameScene.h"
#include "gameoverScene.h"
#include "levelScene.h"

void init()
{
	CHECK_RESULT(DxLib::ChangeWindowMode(TRUE));
	CHECK_RESULT(DxLib::SetGraphMode(WIDTH, HEIGHT, 32));
	CHECK_RESULT(DxLib::SetWindowText("SOB - Lost Doll"));
	CHECK_RESULT(DxLib::SetBackgroundColor(50, 50, 50));

	Engine->registerScene(TITLE_SCENE, new CTitleScene);
	Engine->registerScene(HELP_SCENE, new CHelpScene);
	Engine->registerScene(GAME_SCENE, new CGameScene);
	Engine->registerScene(GAME_OVER_SCENE, new CGameoverScene);
	Engine->registerScene(LEVEL_SCENE, new CLevelScene);

	Engine->setActiveScene(TITLE_SCENE);

	Engine->displayStatus(true);
}

void update()
{
	CBarrageManager::getInstance()->update();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine->registerInitFunc(init);
	Engine->registerUpdateFunc(update);

	return Engine->run();
}