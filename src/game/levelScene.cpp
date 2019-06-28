#include "stdafx.h"
#include "engine/engine.h"
#include "engine/inputManager.h"
#include "levelScene.h"
#include "titleScene.h"
#include "gameScene.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
bool CLevelScene::initV()
{
	if (!CScene::initV()) return false;

	return true;
}

//*********************************************************************
//FUNCTION:
void CLevelScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	if (GET_KEY_STATE(KEY_INPUT_Z) == 1) CEngine::getInstance()->setActiveScene(new CGameScene);
	else if (DxLib::CheckHitKey(KEY_INPUT_X)) CEngine::getInstance()->setActiveScene(new CTitleScene);
}

//*********************************************************************
//FUNCTION:
void CLevelScene::destroyV()
{
	CScene::destroyV();
}