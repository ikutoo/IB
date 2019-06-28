#include "stdafx.h"
#include "engine/engine.h"
#include "engine/resourceManager.h"
#include "barrageManager.h"
#include "titleScene.h"

using namespace DxEngine;

void preInit()
{
	CHECK_RESULT(DxLib::ChangeWindowMode(true));
	CHECK_RESULT(DxLib::SetGraphMode(WIDTH, HEIGHT, 32));
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