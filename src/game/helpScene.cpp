#include "stdafx.h"
#include "engine/common.h"
#include "engine/engine.h"
#include "engine/resourceManager.h"
#include "helpScene.h"
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

	if (CheckHitKey(KEY_INPUT_X))
	{
		auto pScene = CEngine::getInstance()->popScene();
		CEngine::getInstance()->setActiveScene(pScene);
		CHECK_RESULT(DxLib::PlaySoundFile(LOCATE_FILE("se_cancel_00.wav"), DX_PLAYTYPE_BACK));
	}
}