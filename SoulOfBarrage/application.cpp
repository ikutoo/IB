#include "stdafx.h"
#include "engine.h"
#include "barrageManager.h"
#include "titleScene.h"

void preInit()
{
	CHECK_RESULT(DxLib::ChangeWindowMode(true));
	CHECK_RESULT(DxLib::SetGraphMode(WIDTH, HEIGHT, 32));
	CHECK_RESULT(DxLib::SetWindowText("SOB - Lost Doll"));
	CHECK_RESULT(DxLib::SetBackgroundColor(50, 50, 50));
}

void init()
{
	Engine->setActiveScene(new CTitleScene);
	Engine->displayStatus(true);
}

void update()
{
	CBarrageManager::getInstance()->update();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Engine->registerPreInitFunc(preInit);
	Engine->registerInitFunc(init);
	Engine->registerUpdateFunc(update);

	return Engine->run();
}