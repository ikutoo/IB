#include "scene.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
bool DxEngine::CScene::init()
{
	if (m_IsIntialized) return true;

	if (!_initV()) return false;

	m_IsIntialized = true;
	return m_IsIntialized;
}

//*********************************************************************
//FUNCTION:
void DxEngine::CScene::update(double vDeltaTime)
{
	if (!m_IsIntialized) return;

	CNode::updateV(vDeltaTime);
	_updateV(vDeltaTime);
}

//*********************************************************************
//FUNCTION:
void DxEngine::CScene::destroy()
{
	if (!m_IsIntialized || m_IsCached) return;

	_destroyV();

	m_IsIntialized = false;
	delete this;
}