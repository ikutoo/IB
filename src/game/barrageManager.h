#pragma once
#include <list>
#include <functional>
#include <map>
#include "common.h"
#include "barrage.h"

using namespace DxEngine;

class CBarrageManager
{
public:
	SINGLETION(CBarrageManager);

	void startBarrage(CBarrage* vBarrage, CNode* vContainer) { _ASSERTE(vBarrage); vContainer->addChild(vBarrage); m_ActiveBarrages.emplace_back(vBarrage); }
	void stopBarrage(CBarrage* vBarrage) { _ASSERTE(vBarrage); vBarrage->remove(); m_ActiveBarrages.remove(vBarrage); }

	void update();

	void destroy();

	int getNumBullets() const;

private:
	CBarrageManager() = default;
	~CBarrageManager() = default;

	std::list<CBarrage*> m_ActiveBarrages;

	vec2f m_PlayerPosition = {};
};