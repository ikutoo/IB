#include "node.h"
#include <algorithm>
#include <DXLib/DxLib.h>
#include "common.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
void CNode::drawV()
{
	if (_IsPaused || !_IsVisible) return;

	DxLib::SetDrawBright(_BrightnessColor.x, _BrightnessColor.y, _BrightnessColor.z);

	_Childs.sort([](const CNode* l, const CNode* r) {return l->getLocalZ() < r->getLocalZ(); });
	for (auto pChild : _Childs) pChild->drawV();
}

//*********************************************************************
//FUNCTION:
void CNode::updateV(double vDeltaTime)
{
	if (_IsPaused) return;

	_Counter++;
	for (auto pChild : _Childs) pChild->updateV(vDeltaTime);
}

//***********************************************************************************************
//FUNCTION:
void CNode::removeAllChilds(bool vDestroyChilds)
{
	auto Childs = _Childs;
	if (vDestroyChilds) { for (auto pChild : Childs) { pChild->setParent(nullptr); SAFE_DELETE(pChild); } }
	_Childs.clear();
}

//***********************************************************************************************
//FUNCTION:
void CNode::removeChild(CNode* vNode, bool vDestroyChild /*= true*/)
{
	_Childs.remove(vNode);
	vNode->setParent(nullptr);
	if (vDestroyChild) SAFE_DELETE(vNode);
}

//*********************************************************************
//FUNCTION:
CNode* CNode::findChild(const std::string& vName)
{
	for (auto pChild : _Childs)
	{
		if (pChild->getName() == vName) return pChild;
	}
	return nullptr;
}

//***********************************************************************************************
//FUNCTION:
void CNode::addChild(CNode* vNode, float vLocalZ)
{
	_ASSERT(vNode);
	if (vLocalZ != 0.0) vNode->setLocalZ(vLocalZ);
	vNode->setParent(this);
	_Childs.emplace_back(vNode);
}

//***********************************************************************************************
//FUNCTION:
vec2f CNode::getWorldPosition() const
{
	return _Parent ? _Parent->getWorldPosition() + _Position : _Position;
}

//***********************************************************************************************
//FUNCTION:
vec2f CNode::getWorldScale() const
{
	return _Parent ? vec2f{ _Parent->getWorldScale().x * _Scale.x,_Parent->getWorldScale().y * _Scale.y } : _Scale;
}

//***********************************************************************************************
//FUNCTION:
float CNode::getWorldRotation() const
{
	return _Parent ? _Parent->getWorldRotation() + _Rotation : _Rotation;
}