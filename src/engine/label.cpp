#include "label.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
DxEngine::CImageLabel::CImageLabel(const std::string& vImageFile) : m_ImageFile(vImageFile)
{
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERT(m_ImageHandle != -1);
	CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
}

//*********************************************************************
//FUNCTION:
DxEngine::CImageLabel::~CImageLabel()
{
	CResourceManager::getInstance()->deleteImage(m_ImageFile);
}

//*********************************************************************
//FUNCTION:
void DxEngine::CImageLabel::drawV()
{
	CHECK_RESULT(DxLib::DrawExtendGraph(_Position.x, _Position.y, _Position.x + m_Size.x, _Position.y + m_Size.y, m_ImageHandle, TRUE));
	CNode::drawV();
}

//*********************************************************************
//FUNCTION:
void DxEngine::CImageLabel::setImageFile(const std::string& vImageFile)
{
	if (vImageFile == m_ImageFile) return;
	CResourceManager::getInstance()->deleteImage(m_ImageFile);
	m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
	_ASSERT(m_ImageHandle != -1);
	m_ImageFile = vImageFile;
}

//*********************************************************************
//FUNCTION:
DxEngine::CTextLabel::CTextLabel(const std::string& vText, int vFontSize, int vFontType, int vFontColor, int vEdgeColor)
	: m_Text(vText), m_FontSize(vFontSize), m_FontType(vFontType), m_FontColor(vFontColor), m_EdgeColor(vEdgeColor)
{
}

//*********************************************************************
//FUNCTION:
void DxEngine::CTextLabel::drawV()
{
	DxLib::SetFontSize(m_FontSize);
	DxLib::ChangeFontType(m_FontType);
	DxLib::DrawString(_Position.x, _Position.y, m_Text.c_str(), m_FontColor, m_EdgeColor);
	CNode::drawV();
}