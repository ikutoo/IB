#include "stdafx.h"
#include "engine/engine.h"
#include "helpScene.h"
#include "titleScene.h"
#include "common.h"

using namespace DxEngine;

CHelpScene::CHelpScene()
{
}

CHelpScene::~CHelpScene()
{
}

//***********************************************************************************************
//FUNCTION:
void CHelpScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	if (CheckHitKey(KEY_INPUT_X)) CEngine::getInstance()->setActiveScene(new CTitleScene);
}