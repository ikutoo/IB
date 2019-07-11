#pragma once
#include <functional>
#include "engine/node.h"

class CBarrage : public DxEngine::CNode
{
public:
	using TBarrageFunc = std::function<void(int, int, int)>;

	CBarrage(TBarrageFunc vFunc);
	~CBarrage();

	void setLiveTime(int vTime) { _LiveTime = vTime; }

	void setOwn2Player(bool vValue) { m_IsOwn2Player = vValue; }
	bool isOwn2Player()  const { return m_IsOwn2Player; }
	void setDestroyAtDeath(bool vValue) { _DestroyAtDeath = vValue; }

private:
	int _LiveTime = 0;
	bool _DestroyAtDeath = true;
	TBarrageFunc _BarrageFunc;

	bool m_IsOwn2Player = false;

	friend class CBarrageManager;
};