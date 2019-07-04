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

	CHECK_RESULT(DxLib::SetBackgroundColor(255, 255, 255));

	CBarrageManager::getInstance()->init(this);

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
		pBarrage->setPosition(GRAPH_SIZE_X / 2, GRAPH_SIZE_Y / 2);
		pBarrage->setLiveTime(3000);
		CBarrageManager::getInstance()->startBarrage(pBarrage);
	}
}

//***********************************************************************************************
//FUNCTION:
void CGameScene::drawV()
{
	int BoxSize = 1000;
	int x = (GRAPH_SIZE_X - BoxSize) / 2;
	int y = (GRAPH_SIZE_Y - BoxSize) / 2;
	DxLib::DrawBox(x, y, x + BoxSize, y + BoxSize, 0x000000, TRUE);

	CScene::drawV();
}