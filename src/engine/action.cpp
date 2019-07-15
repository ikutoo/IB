#include "action.h"
#include <algorithm>
#include "engine.h"

using namespace DxEngine;

//************************************************************
//FUNCTION:
CMoveTo::CMoveTo(CNode* vTarget, vec2f vFrom, vec2f vTo, float vTimeInMS, float vDelayTime, TInterpFunc vInterpFunc)
	: m_VecFrom(vFrom), m_VecTo(vTo), m_TimeInMS(vTimeInMS), m_DelayTime(vDelayTime), m_InterpFunc(vInterpFunc)
{
	_ASSERT(vTarget);
	_pTarget = vTarget;

	m_TotalFrameCount = std::max(1, int(vTimeInMS / CEngine::getInstance()->getFPS()));
}

//************************************************************
//FUNCTION:
void CMoveTo::updateV()
{
	if (m_CurrentFrame >= m_TotalFrameCount) { _IsDone = true;  return; }
	m_CurrentFrame++;

	float t = m_InterpFunc((float)m_CurrentFrame / m_TotalFrameCount);
	vec2 Pos = m_VecFrom + (m_VecTo - m_VecFrom) * t;

	_pTarget->setPosition(Pos);
}