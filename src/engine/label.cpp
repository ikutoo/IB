#include "label.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

DxEngine::CImageLabel::CImageLabel(const char* vImageFile)
{
	m_ImageHandle = CResourceManager::getInstance()->getImageHandle(vImageFile);
	_ASSERT(m_ImageHandle != -1);
	CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
}

DxEngine::CImageLabel::~CImageLabel()
{
}

//*********************************************************************
//FUNCTION:
void DxEngine::CImageLabel::drawV()
{
	CHECK_RESULT(DxLib::DrawGraph(_Position.x, _Position.y, m_ImageHandle, TRUE));
	CNode::drawV();
}