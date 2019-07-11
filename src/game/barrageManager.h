#pragma once
#include <list>
#include <set>
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

	void addBullet(CBullet* vBullet, bool vOwn2Player = false);

	void startBarrage(CBarrage* vBarrage, bool vOwn2Player = false);
	void stopBarrage(CBarrage* vBarrage);

	void update();

	void destroy();

	int getNumBullets() const { return m_Bullets.size(); }

	void setPlayerPosition(vec2f vPosition) { m_PlayerPosition = vPosition; }
	const vec2f& getPlayerPosition() const { return m_PlayerPosition; }

private:
	CBarrageManager() = default;
	~CBarrageManager() = default;

	std::list<CBullet*> m_Bullets;
	std::set<CBarrage*> m_ActiveBarrages;

	DxEngine::CNode* m_pContainerEm = nullptr;
	DxEngine::CNode* m_pContainerPy = nullptr;

	vec2f m_PlayerPosition = {};

	bool __isBulletDead(const CBullet* vBullet) const;
};