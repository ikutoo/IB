#include "stdafx.h"
#include "gameScene.h"
#include "barrageManager.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
}

//*********************************************************************
//FUNCTION:
bool CGameScene::initV()
{
	if (!CScene::initV()) return false;

	__loadResource();

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__drawUI();
	__drawBarrage();
	__drawPlayer();
}

//*********************************************************************
//FUNCTION:
void CGameScene::__drawUI()
{

}

//*********************************************************************
//FUNCTION:
void CGameScene::__drawBarrage()
{
	
}

//*********************************************************************
//FUNCTION:
void CGameScene::__drawPlayer()
{

}

//*********************************************************************
//FUNCTION:
void CGameScene::__loadResource()
{

}