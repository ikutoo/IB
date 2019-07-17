#include "action.h"
#include <algorithm>
#include "engine.h"

using namespace DxEngine;

//************************************************************
//FUNCTION:
CMoveTo::CMoveTo(CNode* vTarget, vec2f vFrom, vec2f vTo, float vTimeInMS, float vDelayTimeInMS, TInterpFunc vInterpFunc)
	: m_VecFrom(vFrom), m_VecTo(vTo), m_TimeInMS(vTimeInMS), m_DelayTime(vDelayTimeInMS), m_InterpFunc(vInterpFunc)
{
	_ASSERT(vTarget);
	_pTarget = vTarget;

	m_TotalFrameCount = std::max(1, int(vTimeInMS * CEngine::getInstance()->getFPS() / 1000));
	m_DelayFrameCount = std::max(0, int(vDelayTimeInMS * CEngine::getInstance()->getFPS() / 1000));
}

//************************************************************
//FUNCTION:
void CMoveTo::updateV()
{
	if (m_DelayFrameCount > 0) { m_DelayFrameCount--; return; }

	if (m_CurrentFrame >= m_TotalFrameCount)
	{
		if (_DestroyTargetOnDone) SAFE_DELETE(_pTarget);
		_IsDone = true;
		return;
	}

	m_CurrentFrame++;

	float t = m_InterpFunc((float)m_CurrentFrame / m_TotalFrameCount);
	vec2 Pos = m_VecFrom + (m_VecTo - m_VecFrom) * t;

	_pTarget->setPosition(Pos);
}

//************************************************************
//FUNCTION:
CActionSequence::CActionSequence(CNode* vTarget, const std::vector<CAction*>& vActionSequence) : m_ActionSequence(vActionSequence)
{
	_ASSERTE(vTarget);
	_pTarget = vTarget;
}

//************************************************************
//FUNCTION:
CActionSequence::~CActionSequence()
{
	for (auto pAction : m_ActionSequence) SAFE_DELETE(pAction);
}

//************************************************************
//FUNCTION:
void CActionSequence::updateV()
{
	if (_IsDone) return;

	_ASSERT(m_CurrentActionIndex < m_ActionSequence.size());
	auto pAction = m_ActionSequence[m_CurrentActionIndex];
	_ASSERT(pAction);

	pAction->updateV();

	if (pAction->isDone())
	{
		m_CurrentActionIndex++;
	}

	if (m_CurrentActionIndex == m_ActionSequence.size())
	{
		if (_DestroyTargetOnDone) SAFE_DELETE(_pTarget);
		_IsDone = true;
	}
}