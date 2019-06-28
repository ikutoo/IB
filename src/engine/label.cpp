#include "label.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

DxEngine::CImageLabel::CImageLabel(const std::string& vImageFile) : m_ImageFile(vImageFile)
{
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERT(m_ImageHandle != -1);
	CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
}

DxEngine::CImageLabel::~CImageLabel()
{
	CResourceManager::getInstance()->deleteImage(m_ImageFile);
}

//*********************************************************************
//FUNCTION:
void DxEngine::CImageLabel::drawV()
{
	CHECK_RESULT(DxLib::DrawGraph(_Position.x, _Position.y, m_ImageHandle, TRUE));
	CNode::drawV();
}