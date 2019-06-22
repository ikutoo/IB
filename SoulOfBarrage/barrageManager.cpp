#include "stdafx.h"
#include "barrageManager.h"
#include "movePattern.h"

CBarrageManager::CBarrageManager()
{
}

CBarrageManager::~CBarrageManager()
{
}

//*********************************************************************
//FUNCTION:
void CBarrageManager::update()
{
	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end();)
	{
		auto& Bullet = *iter;

		if (__isBulletDead(Bullet))
		{
			__destroyBullet(Bullet);
			iter = m_Bullets.erase(iter);
		}
		else
		{
			TMoveFunc Move = m_MovePatternMap[Bullet.movePattern];
			Move(Bullet);
			Bullet.counter++;

			CHECK_RESULT(DxLib::DrawGraph(Bullet.x, Bullet.y, Bullet.image, TRUE));
			iter++;
		}
	}
}

//*********************************************************************
//FUNCTION:
bool CBarrageManager::__isBulletDead(const SBullet& vBullet) const
{
	if (vBullet.x < 0 || vBullet.x > WIDTH || vBullet.y < 0 || vBullet.y > HEIGHT) return true;

	return false;
}

//*********************************************************************
//FUNCTION:
void CBarrageManager::__destroyBullet(const SBullet& vBullet) const
{
	CHECK_RESULT(DxLib::DeleteGraph(vBullet.image));
}