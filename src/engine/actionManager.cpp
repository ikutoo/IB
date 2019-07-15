#include "actionManager.h"

using namespace DxEngine;

//*********************************************************
//FUNCTION:
void CActionManager::startAction(CAction* vAction, bool vStopPrevActions)
{
	_ASSERT(vAction);

	if (vStopPrevActions && m_Node2ActionMap.find(vAction->_pTarget) != m_Node2ActionMap.end())
	{
		auto& Actions = m_Node2ActionMap[vAction->_pTarget];
		for (auto& pAction : Actions)
		{
			SAFE_DELETE(pAction);
		}

		Actions.clear();
	}

	m_Node2ActionMap[vAction->_pTarget].emplace_back(vAction);
}

//*********************************************************
//FUNCTION:
void CActionManager::update()
{
	for (auto& e : m_Node2ActionMap)
	{
		for (auto pAction : e.second)
		{
			pAction->updateV();
		}
	}
}