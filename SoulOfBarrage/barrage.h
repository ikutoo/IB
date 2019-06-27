#pragma once
#include "node.h"

class CBarrage : public DxEngine::CNode
{
public:
	CBarrage();
	~CBarrage();

private:
	int m_BarragePattern = -1;
	int m_LiveTime = 0;
};