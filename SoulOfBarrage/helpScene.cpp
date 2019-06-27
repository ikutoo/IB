#include "stdafx.h"
#include "helpScene.h"
#include "titleScene.h"
#include "engine.h"
#include "common.h"

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

	if (CheckHitKey(KEY_INPUT_X)) Engine->setActiveScene(new CTitleScene);
}