#include "stdafx.h"
#include "gameScene.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	DrawString(500, 500, "this is game scene.", 0xffffff);
}