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

	const std::vector<vec2f> DOLL_POS_5a = { {0, -96}, {-128, -32}, {128, -32}, {-256, 32}, {256, 32} };
	const std::vector<vec2f> DOLL_POS_5b = { {0, -60}, {-57, -18}, {57, -18}, {-35, 48}, {35, 48} };
}

//***********************************************************************************
//FUNCTION:
CPlayerAlice::CPlayerAlice(const std::string& vConfigFile) : CPlayer(vConfigFile)
{
	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		auto pDoll = new CSprite;
		pDoll->setPosition(DOLL_POS_5a[i]);
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
void CPlayerAlice::__updateAnimation()
{
	for (auto pDoll : m_Dolls)
	{
		pDoll->setImageFile(m_DollAnimation.ImageFile, m_DollAnimation.forward());
		pDoll->setAnchor(pDoll->getSize() / 2);
	}

	if (CHECK_HIT_KEY(KEY_INPUT_LSHIFT))
	{
		for (int i = 0; i < MAX_DOLL_NUM; ++i)
		{
			CActionManager::getInstance()->startAction(new CMoveTo(m_Dolls[i], m_Dolls[i]->getPosition(), DOLL_POS_5b[i], 800));
		}
	}
	else if (CHECK_RELEASE_KEY(KEY_INPUT_LSHIFT))
	{
		for (int i = 0; i < MAX_DOLL_NUM; ++i)
		{
			CActionManager::getInstance()->startAction(new CMoveTo(m_Dolls[i], m_Dolls[i]->getPosition(), DOLL_POS_5a[i], 800));
		}
	}

	for (int i = 0; i < MAX_DOLL_NUM; ++i)
	{
		m_Barrages[i]->setPosition(m_Dolls[i]->getWorldPosition());
	}
}