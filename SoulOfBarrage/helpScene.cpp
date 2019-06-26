#include "stdafx.h"
#include "helpScene.h"
#include "engine.h"

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

	DrawString(500, 500, "this is help scene", 0xffffff);

	if (CheckHitKey(KEY_INPUT_X)) Engine->setActiveScene(TITLE_SCENE);
}