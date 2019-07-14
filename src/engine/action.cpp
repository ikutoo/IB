#include "action.h"
#include <algorithm>
#include "engine.h"

using namespace DxEngine;

//************************************************************
//FUNCTION:
CMoveTo::CMoveTo(CNode* vTarget, vec2f vFrom, vec2f vTo, float vTimeInMS, TInterpFunc vInterpFunc)
	: m_pTarget(vTarget), m_VecFrom(vFrom), m_VecTo(vTo), m_TimeInMS(vTimeInMS), m_InterpFunc(vInterpFunc)
{
	_ASSERT(vTarget);

	m_TotalFrameCount = std::min(1, int(vTimeInMS / CEngine::getInstance()->getFPS()));
}

//************************************************************
//FUNCTION:
void CMoveTo::updateV()
{
	if (m_CurrentFrame >= m_TotalFrameCount) return;
	m_CurrentFrame++;

	float t = m_InterpFunc((float)m_CurrentFrame / m_TotalFrameCount);
	vec2 Pos = m_VecFrom + (m_VecTo - m_VecFrom) * t;

	m_pTarget->setPosition(Pos);
}