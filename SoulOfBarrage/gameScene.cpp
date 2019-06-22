#include "stdafx.h"
#include "gameScene.h"
#include "barrageManager.h"
#include "movePattern.h"
#include "barragePattern.h"

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

	CBarrageManager::getInstance()->init();

	CBarrageManager::getInstance()->registerBarragePattern(1, barrage_pattern::barragePattern001);

	CBarrageManager::getInstance()->registerMovePattern(1, move_pattern::movePattern001);

	CBarrageManager::getInstance()->registerBulletType(1, LOCATE_IMAGE("bullet01.png"));

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

	m_Counter++;
}

//*********************************************************************
//FUNCTION:
void CGameScene::destroyV()
{
	CBarrageManager::getInstance()->destroy();
	CScene::destroyV();
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
	if (m_Counter == 100)
		CBarrageManager::getInstance()->startBarrage(SBarrage{ WIDTH / 2, HEIGHT / 2, 1, 0, 3000 });
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