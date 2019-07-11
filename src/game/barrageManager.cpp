#include "stdafx.h"
#include "engine/node.h"
#include "barrageManager.h"
#include "barrage.h"
#include "math.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CBarrageManager::update()
{
	for (auto iter = m_ActiveBarrages.begin(); iter != m_ActiveBarrages.end();)
	{
		auto pBarrage = *iter;

		if (pBarrage->_LiveTime > 0 && pBarrage->_Counter > pBarrage->_LiveTime)
		{
			pBarrage->remove();
			iter = m_ActiveBarrages.erase(iter);
		}
		else
		{
			pBarrage->update();
			iter++;
		}
	}
}

//*********************************************************************
//FUNCTION:
void CBarrageManager::destroy()
{
	for (auto pBarrage : m_ActiveBarrages) pBarrage->remove();
	m_ActiveBarrages.clear();
}

//***********************************************************************************************
//FUNCTION:
int CBarrageManager::getNumBullets() const
{
	int Count = 0;
	for (auto pBarrage : m_ActiveBarrages)
		Count += pBarrage->getNumBullets();
	return Count;
}