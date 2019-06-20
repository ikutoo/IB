#include "stdafx.h"
#include "gameScene01.h"

CGameScene01::CGameScene01()
{
}

CGameScene01::~CGameScene01()
{
}

//***********************************************************************************************
//FUNCTION:
void CGameScene01::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	DrawString(500, 500, "this is game scene 01.", 0xffffff);
}