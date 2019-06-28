#pragma once
#include <list>
#include <functional>
#include <map>
#include "common.h"
#include "barrage.h"
#include "bullet.h"

class CBarrageManager
{
public:
	SINGLETION(CBarrageManager);

	bool init(DxEngine::CNode* vContainer);

	void addBullet(CBullet* vBullet) { _ASSERTE(vBullet); m_Bullets.emplace_back(vBullet); m_pContainer->addChild(vBullet); }

	void startBarrage(CBarrage* vBarrage) { _ASSERTE(vBarrage); m_ActiveBarrages.emplace_back(vBarrage); m_pContainer->addChild(vBarrage); }

	void update();

	void destroy();

	int getNumBullets() const { return m_Bullets.size(); }

private:
	CBarrageManager() = default;
	~CBarrageManager() = default;

	std::list<CBullet*> m_Bullets;
	std::list<CBarrage*> m_ActiveBarrages;

	DxEngine::CNode* m_pContainer = nullptr;

	bool __isBulletDead(const CBullet* vBullet) const;
};