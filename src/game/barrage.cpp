#include "stdafx.h"
#include "barrage.h"
#include "bullet.h"
#include "common.h"

CBarrage::CBarrage(TBarrageFunc vFunc) : _BarrageFunc(vFunc)
{
}

CBarrage::~CBarrage()
{
}

//***********************************************************************************************
//FUNCTION:
void CBarrage::update()
{
	_BarrageFunc(this, _Counter);

	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end();)
	{
		auto pBullet = *iter;

		if (__isBulletDead(pBullet))
		{
			pBullet->remove();
			iter = m_Bullets.erase(iter);
		}
		else
		{
			auto MoveFunc = pBullet->_MoveFunc;
			MoveFunc(pBullet);
			iter++;
		}
	}
}

//***********************************************************************************************
//FUNCTION:
void CBarrage::addBullet(CBullet* vBullet)
{
	_ASSERTE(vBullet);
	vBullet->setOwn2Player(m_IsOwn2Player);
	m_Bullets.emplace_back(vBullet);
	this->addChild(vBullet);
}

//*********************************************************************
//FUNCTION:
bool CBarrage::__isBulletDead(const CBullet* vBullet) const
{
	float Offset = max(vBullet->getSize().x, vBullet->getSize().y) / 2;
	if (intersects(vBullet->getWorldPosition(), rectf{ BORDER_L - Offset, BORDER_U - Offset, BORDER_W + 2 * Offset, BORDER_H + 2 * Offset })) return false;
	return true;
}