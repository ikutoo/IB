#include "stdafx.h"
#include "inputManager.h"
#include "levelScene.h"
#include "titleScene.h"
#include "gameScene.h"
#include "engine.h"

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

	if (DxLib::CheckHitKey(KEY_INPUT_Z)) Engine->setActiveScene(new CGameScene);
	else if (DxLib::CheckHitKey(KEY_INPUT_X)) Engine->setActiveScene(new CTitleScene); //HACK: fix bug
}

//*********************************************************************
//FUNCTION:
void CLevelScene::destroyV()
{
	CScene::destroyV();
}