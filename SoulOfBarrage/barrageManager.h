#pragma once
#include <list>
#include <functional>
#include <map>
#include "common.h"

class CBarrageManager
{
public:
	using TMoveFunc = std::function<void(SBullet&)>;
	using TBarrageFunc = std::function<void(int)>;

	SINGLETION(CBarrageManager);

	void addBullet(const SBullet& vBullet) { m_Bullets.emplace_back(std::move(vBullet)); }
	void registerMovePattern(int vPatternID, TMoveFunc vFunc) { m_MovePatternMap[vPatternID] = vFunc; }
	void registerBarragePattern(int vPatternID, TBarrageFunc vFunc) { m_BarragePatternMap[vPatternID] = vFunc; }

	void update();

private:
	CBarrageManager();
	~CBarrageManager();

	std::list<SBullet> m_Bullets;
	std::map<int, TMoveFunc> m_MovePatternMap;
	std::map<int, TBarrageFunc> m_BarragePatternMap;

	bool __isBulletDead(const SBullet& vBullet) const;
	void __destroyBullet(const SBullet& vBullet) const;
};