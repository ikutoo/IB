#include "stdafx.h"
#include "engine/engine.h"
#include "engine/resourceManager.h"
#include "barrageManager.h"
#include "titleScene.h"

using namespace DxEngine;

void preInit()
{
	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	int WindowWidth = ScreenWidth * 0.8;
	int WindowHeight = WindowWidth * 9.0 / 16.0;

	CHECK_RESULT(DxLib::ChangeWindowMode(true));
	CHECK_RESULT(DxLib::SetGraphMode(WIDTH, HEIGHT, 32));
	CHECK_RESULT(DxLib::SetWindowPosition((ScreenWidth - WindowWidth) / 2, (ScreenHeight - WindowHeight) / 2));
	CHECK_RESULT(DxLib::SetWindowSize(WindowWidth, WindowHeight));
	CHECK_RESULT(DxLib::SetWindowText("SOB - Lost Doll"));
}

void init()
{
	CResourceManager::getInstance()->addFileSearchPath(RES_IMG_ROOT);
	CResourceManager::getInstance()->addFileSearchPath(RES_SND_ROOT);

	CEngine::getInstance()->setActiveScene(new CTitleScene);
	CEngine::getInstance()->displayStatus(true);
}

void update()
{
	CBarrageManager::getInstance()->update();
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CEngine::getInstance()->registerPreInitFunc(preInit);
	CEngine::getInstance()->registerInitFunc(init);
	CEngine::getInstance()->registerUpdateFunc(update);

	return DxEngine::CEngine::getInstance()->run();
}