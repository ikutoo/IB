#pragma once
#include <list>
#include <functional>
#include <map>
#include "common.h"

class CBullet;
class CBarrage;

class CBarrageManager
{
public:
	using TMoveFunc = std::function<void(SBullet&)>;
	using TBarrageFunc = std::function<void(int, int, int)>;

	SINGLETION(CBarrageManager);

	bool init();

	void addBullet(const SBullet& vBullet) { m_Bullets.emplace_back(std::move(vBullet)); }
	void registerMovePattern(int vMovePattern, TMoveFunc vMoveFunc) { m_ID2MoveFuncMap[vMovePattern] = vMoveFunc; }
	void registerBarragePattern(int vBarragePattern, TBarrageFunc vBarrageFunc) { m_ID2BarrageFuncMap[vBarragePattern] = vBarrageFunc; }
	void registerBulletType(int vBulletType, const char* vImageFile);

	void startBarrage(const SBarrage& vBarrage) { m_ActiveBarrages.emplace_back(vBarrage); }

	void update();

	void destroy();

	int getNumBullets() const { return m_Bullets.size(); }

private:
	CBarrageManager();
	~CBarrageManager();

	std::list<SBullet> m_Bullets;
	std::list<SBarrage> m_ActiveBarrages;
	std::map<int, int> m_BulletType2ImageMap;
	std::map<int, TMoveFunc> m_ID2MoveFuncMap;
	std::map<int, TBarrageFunc> m_ID2BarrageFuncMap;

	bool __isBulletDead(const SBullet& vBullet) const;
};