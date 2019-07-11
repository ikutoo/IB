#pragma once
#include <list>
#include <functional>
#include <map>
#include "common.h"
#include "barrage.h"
#include "bullet.h"

using namespace DxEngine;

class CBarrageManager
{
public:
	SINGLETION(CBarrageManager);

	bool init(DxEngine::CNode* vContainerEm, DxEngine::CNode* vContainerPy);

	void addBulletEm(CBullet* vBullet, float vLocalZ = 0.0f) { _ASSERTE(vBullet); m_Bullets.emplace_back(vBullet); m_pContainerEm->addChild(vBullet, vLocalZ); }
	void addBulletPy(CBullet* vBullet, float vLocalZ = 0.0f) { _ASSERTE(vBullet); m_Bullets.emplace_back(vBullet); m_pContainerPy->addChild(vBullet, vLocalZ); vBullet->setOwn2Player(true); }

	void startBarrageEm(CBarrage* vBarrage, float vLocalZ = 0.0f) { _ASSERTE(vBarrage); m_ActiveBarrages.emplace_back(vBarrage); m_pContainerEm->addChild(vBarrage, vLocalZ); }
	void startBarragePy(CBarrage* vBarrage, float vLocalZ = 0.0f) { _ASSERTE(vBarrage); m_ActiveBarrages.emplace_back(vBarrage); m_pContainerPy->addChild(vBarrage, vLocalZ); vBarrage->setOwn2Player(true); }

	void update();

	void destroy();

	int getNumBullets() const { return m_Bullets.size(); }

	void setPlayerPosition(vec2f vPosition) { m_PlayerPosition = vPosition; }
	const vec2f& getPlayerPosition() const { return m_PlayerPosition; }

private:
	CBarrageManager() = default;
	~CBarrageManager() = default;

	std::list<CBullet*> m_Bullets;
	std::list<CBarrage*> m_ActiveBarrages;

	DxEngine::CNode* m_pContainerEm = nullptr;
	DxEngine::CNode* m_pContainerPy = nullptr;

	vec2f m_PlayerPosition = {};

	bool __isBulletDead(const CBullet* vBullet) const;
};