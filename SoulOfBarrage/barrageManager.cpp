#include "stdafx.h"
#include "barrageManager.h"
#include "bullet.h"
#include "barrage.h"
#include "math.h"
#include "node.h"

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
void CBarrageManager::registerBulletType(int vBulletType, const char* vImageFile)
{
	if (m_BulletType2ImageMap.find(vBulletType) != m_BulletType2ImageMap.end()) return;

	auto ImageHandle = LoadGraph(vImageFile);
	_ASSERTE(ImageHandle != -1);

	m_BulletType2ImageMap[vBulletType] = ImageHandle;
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
	for (auto iter = m_BulletType2ImageMap.begin(); iter != m_BulletType2ImageMap.end(); ++iter)
	{
		CHECK_RESULT(DxLib::DeleteGraph(iter->second));
	}

	m_pContainer->removeAllChilds();

	m_Bullets.clear();
	m_ActiveBarrages.clear();
	m_BulletType2ImageMap.clear();
}

//*********************************************************************
//FUNCTION:
bool CBarrageManager::__isBulletDead(const CBullet* vBullet) const
{
	if (intersects(vBullet->_Position, rectf{ -100, -100, WIDTH + 100, HEIGHT + 100 })) return false;
	return true;
}