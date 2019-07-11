#pragma once
#include <functional>
#include <list>
#include "engine/node.h"

class CBullet;

class CBarrage : public DxEngine::CNode
{
public:
	using TBarrageFunc = std::function<void(CBarrage*, int)>;

	CBarrage(TBarrageFunc vFunc);
	~CBarrage();

	void update();

	void addBullet(CBullet* vBullet);
	void setLiveTime(int vTime) { _LiveTime = vTime; }
	void setOwn2Player(bool vValue) { m_IsOwn2Player = vValue; }

	bool isOwn2Player()  const { return m_IsOwn2Player; }
	int  getNumBullets() const { return m_Bullets.size(); }

protected:
	TBarrageFunc	_BarrageFunc;
	int				_LiveTime = 0;

private:
	std::list<CBullet*> m_Bullets;
	bool				m_IsOwn2Player = false;

	bool __isBulletDead(const CBullet* vBullet) const;

	friend class CBarrageManager;
};