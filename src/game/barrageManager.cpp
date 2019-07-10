#include "stdafx.h"
#include "engine/node.h"
#include "barrageManager.h"
#include "bullet.h"
#include "barrage.h"
#include "math.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
bool CBarrageManager::init(DxEngine::CNode* vContainer)
{
	_ASSERTE(vContainer);
	m_pContainer = vContainer;

	return true;
}

//*********************************************************************
//FUNCTION:
void CBarrageManager::update()
{
	for (auto iter = m_ActiveBarrages.begin(); iter != m_ActiveBarrages.end();)
	{
		auto pBarrage = *iter;

		if (pBarrage->_Counter > pBarrage->_LiveTime)
		{
			m_pContainer->removeChild(pBarrage);
			iter = m_ActiveBarrages.erase(iter);
		}
		else
		{
			auto pBarrageFunc = pBarrage->_BarrageFunc;
			pBarrageFunc(pBarrage->_Position.x, pBarrage->_Position.y, pBarrage->_Counter);
			iter++;
		}
	}

	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end();)
	{
		auto pBullet = *iter;

		if (__isBulletDead(pBullet))
		{
			m_pContainer->removeChild(pBullet);
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

//*********************************************************************
//FUNCTION:
void CBarrageManager::destroy()
{
	m_pContainer->removeAllChilds();

	m_Bullets.clear();
	m_ActiveBarrages.clear();
}

//*********************************************************************
//FUNCTION:
bool CBarrageManager::__isBulletDead(const CBullet* vBullet) const
{
	float Offset = max(vBullet->getSize().x, vBullet->getSize().y) / 2;
	if (intersects(vBullet->_Position, rectf{ BORDER_L - Offset, BORDER_U - Offset, BORDER_W + 2 * Offset, BORDER_H + 2 * Offset })) return false;
	return true;
}