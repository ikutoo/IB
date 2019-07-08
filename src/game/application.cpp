#include "stdafx.h"
#include "engine/jsonUtil.h"
#include "engine/engine.h"
#include "engine/resourceManager.h"
#include "barrageManager.h"
#include "titleScene.h"

using namespace DxEngine;

void init()
{
	std::vector<std::string> FileSearchPaths = { RES_ROOT, RES_IMG_ROOT, RES_SND_ROOT, RES_SCR_ROOT };
	for (auto& Path : FileSearchPaths) CResourceManager::getInstance()->addFileSearchPath(Path);

	vec2i ScreenSize = { GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) };
	int WindowHeight = ScreenSize.y * 0.8;
	int WindowWidth = WindowHeight * 16.0 / 9.0;

	CJsonReader JsonReader("game.config");

	CEngine::getInstance()->setWindowTitle("SOB - Lost Doll");
	CEngine::getInstance()->setWindowSize(WindowWidth, WindowHeight);
	CEngine::getInstance()->setFullscreen(JsonReader.readBool("fullScreen"));
	CEngine::getInstance()->setGraphSize(GRAPH_SIZE_X, GRAPH_SIZE_Y);

	CEngine::getInstance()->setActiveScene(new CTitleScene);
	CEngine::getInstance()->setShowConsoleHint();
	CEngine::getInstance()->setDisableCNInputHint();
	CEngine::getInstance()->setExpectedFPS(JsonReader.readFloat("fps"));
	if (JsonReader.readBool("displayStatus")) CEngine::getInstance()->setDisplayStatusHint();
}

void update()
{
	CBarrageManager::getInstance()->update();
	CEngine::getInstance()->updateStatus("Bullets Num", CBarrageManager::getInstance()->getNumBullets());
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	CEngine::getInstance()->registerInitFunc(init);
	CEngine::getInstance()->registerUpdateFunc(update);

	return DxEngine::CEngine::getInstance()->run();
}