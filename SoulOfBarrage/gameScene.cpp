#include "stdafx.h"
#include "gameScene.h"
#include "barrageManager.h"
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

	CBarrageManager::getInstance()->init(this);

	CBarrageManager::getInstance()->registerBulletType(1, LOCATE_IMAGE("bullet01.png"));

	return true;
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::updateV(double vDeltaTime)
{
	CScene::updateV(vDeltaTime);

	__updateBarrage();

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
void CGameScene::__updateBarrage()
{
	if (m_Counter == 100)
	{
		CBarrage* pBarrage = new CBarrage(CBarragePattern::barragePattern001);
		pBarrage->setPosition(WIDTH / 2, HEIGHT / 2);
		pBarrage->setLiveTime(3000);
		CBarrageManager::getInstance()->startBarrage(pBarrage);
	}
}