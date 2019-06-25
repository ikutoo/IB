#include "stdafx.h"
#include "barrageManager.h"

CBarrageManager::CBarrageManager()
{
}

CBarrageManager::~CBarrageManager()
{
}

//*********************************************************************
//FUNCTION:
bool CBarrageManager::init()
{
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
		auto& Barrage = *iter;

		if (Barrage.counter > Barrage.liveTime)
		{
			iter = m_ActiveBarrages.erase(iter);
		}
		else
		{
			TBarrageFunc GenBarrage = m_ID2BarrageFuncMap[Barrage.barragePattern];
			GenBarrage(Barrage.x, Barrage.y, Barrage.counter);
			Barrage.counter++;
			iter++;
		}
	}

	for (auto iter = m_Bullets.begin(); iter != m_Bullets.end();)
	{
		auto& Bullet = *iter;

		if (__isBulletDead(Bullet))
		{
			iter = m_Bullets.erase(iter);
		}
		else
		{
			TMoveFunc Move = m_ID2MoveFuncMap[Bullet.movePattern];
			Move(Bullet);
			Bullet.counter++;

			CHECK_RESULT(DxLib::DrawGraph(Bullet.x, Bullet.y, m_BulletType2ImageMap[Bullet.bulletType], TRUE));
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

	m_Bullets.clear();
	m_ActiveBarrages.clear();
	m_BulletType2ImageMap.clear();
	m_ID2BarrageFuncMap.clear();
	m_ID2MoveFuncMap.clear();
}

//*********************************************************************
//FUNCTION:
bool CBarrageManager::__isBulletDead(const SBullet& vBullet) const
{
	if (vBullet.x < -100 || vBullet.x > WIDTH + 100 || vBullet.y < -100 || vBullet.y > HEIGHT + 100) return true;

	return false;
}