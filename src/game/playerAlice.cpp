#include "stdafx.h"
#include "playerAlice.h"
#include <DXLib/DxLib.h>
#include "engine/jsonUtil.h"
#include "engine/actionManager.h"
#include "engine/inputManager.h"
#include "barragePattern.h"
#include "barrage.h"

using namespace DxEngine;

namespace
{
	const int MAX_DOLL_NUM = 5;
	const int MAX_SHOOT_MODE = 5;
}

//***********************************************************************************
//FUNCTION:
CPlayerAlice::CPlayerAlice(const std::string& vConfigFile) : CPlayer(vConfigFile)
{
	m_InitialDollPosSet.resize(MAX_SHOOT_MODE);
	__calculateInitialDollPos();

	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		auto pDoll = new CSprite;
		pDoll->setPosition(m_InitialDollPosSet[m_CurrentShootMode][i]);
		this->addChild(pDoll, 1.0);
		m_Dolls.emplace_back(pDoll);

		auto pBarrage = new CBarrage(CBarragePattern::playerBarrage00);
		pBarrage->setDestroyAtDeath(false);
		m_Barrages.emplace_back(pBarrage);
	}

	CJsonReader JsonReader(vConfigFile);
	m_DollAnimation = JsonReader.readAnimation("doll_anm");
}

//***********************************************************************************
//FUNCTION:
CPlayerAlice::~CPlayerAlice()
{

}

//***********************************************************************************
//FUNCTION:
void CPlayerAlice::updateV(double vDeltaTime)
{
	CPlayer::updateV(vDeltaTime);
	__updateAnimation();
}

//***********************************************************************************
//FUNCTION:
void CPlayerAlice::__calculateInitialDollPos()
{
	m_InitialDollPosSet[0] = { {0, -96}, {128, -32}, {256, 32}, {-256, 32}, {-128, -32} };

	float Theta = 0.0;
	for (int i = 0; i < MAX_DOLL_NUM; ++i, Theta += PI * 2.0 / MAX_DOLL_NUM)
	{
		m_InitialDollPosSet[1].emplace_back(vec2f{ 64 * sin(Theta), -64 * cos(Theta) });
		m_InitialDollPosSet[2].emplace_back(vec2f{ 0.0f, -60.0f });
		m_InitialDollPosSet[3].emplace_back(vec2f{ -64.0f * (i + 1), 0.0f });
		m_InitialDollPosSet[4].emplace_back(vec2f{ 64.0f * (i + 1), 0.0f });
	}
}

//***********************************************************************************
//FUNCTION:
void CPlayerAlice::__changeShootingMode()
{
	m_CurrentShootMode++;
	if (m_CurrentShootMode >= MAX_SHOOT_MODE) m_CurrentShootMode = 0;

	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		CActionManager::getInstance()->startAction(new CMoveTo(m_Dolls[i], m_Dolls[i]->getPosition(), m_InitialDollPosSet[m_CurrentShootMode][i], 800));
	}
}

//***********************************************************************************
//FUNCTION:
void CPlayerAlice::__updateAnimation()
{
	for (auto pDoll : m_Dolls)
	{
		pDoll->setImageFile(m_DollAnimation.ImageFile, m_DollAnimation.forward());
		pDoll->setAnchor(pDoll->getSize() / 2);
	}

	if (CHECK_HIT_KEY(KEY_INPUT_X)) { __changeShootingMode(); }

	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		m_Barrages[i]->setPosition(m_Dolls[i]->getWorldPosition());
	}
}