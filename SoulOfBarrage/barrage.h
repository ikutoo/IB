#pragma once
#include <functional>
#include "node.h"

class CBarrage : public DxEngine::CNode
{
public:
	using TBarrageFunc = std::function<void(int, int, int)>;

	CBarrage(TBarrageFunc vFunc);
	~CBarrage();

	void setLiveTime(int vTime) { _LiveTime = vTime; }

private:
	int _LiveTime = 0;

	TBarrageFunc _BarrageFunc;

	friend class CBarrageManager;
};