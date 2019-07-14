#include "stdafx.h"
#include "playerAlice.h"
#include "engine/jsonUtil.h"
#include "barragePattern.h"
#include "barrage.h"

using namespace DxEngine;

namespace
{
	const int MAX_DOLL_NUM = 5;

	const std::vector<vec2f> DOLL_POS_5a = { {0, -96}, {-128, -32}, {128, -32}, {-256, 32}, {256, 32} };
	const std::vector<vec2f> DOLL_POS_5b = { {0, -96}, {-12, -64}, {12, -64}, {-24, -32}, {24, -32} };
}

//***********************************************************************************
//FUNCTION:
CPlayerAlice::CPlayerAlice(const std::string& vConfigFile) : CPlayer(vConfigFile)
{
	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		auto pDoll = new CSprite;
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
	__updateBarrage();
	__updateAnimation();
}

//***********************************************************************************
//FUNCTION:
void CPlayerAlice::__updateBarrage()
{
	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		if (m_State & PLAYER_STATE_LOW_SPEED)
			m_Dolls[i]->setPosition(DOLL_POS_5b[i]);
		else
			m_Dolls[i]->setPosition(DOLL_POS_5a[i]);

		m_Barrages[i]->setPosition(m_Dolls[i]->getWorldPosition());
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
}