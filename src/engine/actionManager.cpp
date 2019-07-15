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
	for (auto iter = m_Node2ActionMap.begin(); iter != m_Node2ActionMap.end();)
	{
		auto& ActionSet = iter->second;
		for (auto iter2 = ActionSet.begin(); iter2 != ActionSet.end();)
		{
			auto pAction = *iter2;
			pAction->updateV();
			if (pAction->_IsDone)
			{
				SAFE_DELETE(pAction);
				iter2 = ActionSet.erase(iter2);
			}
			else
			{
				iter2++;
			}
		}

		if (ActionSet.empty())
			iter = m_Node2ActionMap.erase(iter);
		else
			iter++;
	}
}