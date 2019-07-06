#include "stdafx.h"
#include "engine/graphics2d.h"
#include "gameScene.h"
#include "barrageManager.h"
#include "barragePattern.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
bool CGameScene::initV()
{
	if (!CScene::initV()) return false;

	CHECK_RESULT(DxLib::SetBackgroundColor(0, 0, 0));

	CBarrageManager::getInstance()->init(this);

	__initUI();

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
bool CGameScene::__initUI()
{
	m_pBgSprite = new CSprite("bg_01.png");
	m_pBgSprite->setBrightness({ 100, 100, 100 });
	this->addChild(m_pBgSprite, 1);

	m_pChSprite = new CSprite("alice_01.png");
	m_pChSprite->setPosition(-50, 250);
	this->addChild(m_pChSprite, 1);

	float PosX = 1500;
	m_pScoreDesc = new CTextLabel("SCORE:", 40, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_pScoreDesc->setPosition(PosX, 100);
	this->addChild(m_pScoreDesc, 1);

	m_pPlayerDesc = new CTextLabel("PLAYER", 30, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_pPlayerDesc->setPosition(PosX, 400);
	this->addChild(m_pPlayerDesc, 1);

	m_pBombDesc = new CTextLabel("BOMB", 30, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_pBombDesc->setPosition(PosX, 450);
	this->addChild(m_pBombDesc, 1);

	m_pPowerDesc = new CTextLabel("POWER", 30, DX_FONTTYPE_ANTIALIASING_EDGE, 0xffff00);
	m_pPowerDesc->setPosition(PosX, 500);
	this->addChild(m_pPowerDesc, 1);

	m_pScoreValue = new CTextLabel("000000", 40, DX_FONTTYPE_ANTIALIASING);
	m_pScoreValue->setPosition(PosX + 200, m_pScoreDesc->getPosition().y);
	this->addChild(m_pScoreValue, 1);

	m_pPlayerValue = new CTextLabel("000", 30, DX_FONTTYPE_ANTIALIASING);
	m_pPlayerValue->setPosition(PosX + 200, m_pPlayerDesc->getPosition().y);
	this->addChild(m_pPlayerValue, 1);

	m_pBombValue = new CTextLabel("000", 30, DX_FONTTYPE_ANTIALIASING);
	m_pBombValue->setPosition(PosX + 200, m_pBombDesc->getPosition().y);
	this->addChild(m_pBombValue, 1);

	m_pPowerValue = new CTextLabel("000", 30, DX_FONTTYPE_ANTIALIASING);
	m_pPowerValue->setPosition(PosX + 200, m_pPowerDesc->getPosition().y);
	this->addChild(m_pPowerValue, 1);

	return true;
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