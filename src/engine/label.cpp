#include "label.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"
#include "engine.h"

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
	CNode::drawV();
	CHECK_RESULT(DxLib::DrawExtendGraph(_Position.x, _Position.y, _Position.x + m_Size.x, _Position.y + m_Size.y, m_ImageHandle, TRUE));
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
DxEngine::CTextLabel::CTextLabel(const std::string& vText, int vFontSize, int vFontType, int vFontColor, int vEdgeColor, int vFontThickness)
	: m_Text(vText), m_FontSize(vFontSize), m_FontType(vFontType), m_FontColor(vFontColor), m_EdgeColor(vEdgeColor), m_FontThickness(vFontThickness)
{
	auto GraphSize = CEngine::getInstance()->getGraphSize();
	m_TextGraphHandle = DxLib::MakeScreen(GraphSize.x, GraphSize.y, TRUE);
	_ASSERTE(m_TextGraphHandle != -1);
}

//*********************************************************************
//FUNCTION:
CTextLabel::~CTextLabel()
{
	CHECK_RESULT(DxLib::DeleteGraph(m_TextGraphHandle));
}

//*********************************************************************
//FUNCTION:
void DxEngine::CTextLabel::drawV()
{
	CNode::drawV();

	if (m_IsChanged)
	{
		CHECK_RESULT(DxLib::SetDrawBright(_BrightnessColor.x, _BrightnessColor.y, _BrightnessColor.z));
		CHECK_RESULT(DxLib::SetFontSize(m_FontSize));
		CHECK_RESULT(DxLib::SetFontThickness(m_FontThickness));
		CHECK_RESULT(DxLib::ChangeFontType(m_FontType));

		CHECK_RESULT(DxLib::SetDrawScreen(m_TextGraphHandle));
		CHECK_RESULT(DxLib::ClearDrawScreen());
		DxLib::DrawString(_Position.x, _Position.y, m_Text.c_str(), m_FontColor, m_EdgeColor);
		CHECK_RESULT(DxLib::SetDrawScreen(DX_SCREEN_BACK));
	}

	DxLib::DrawGraph(0, 0, m_TextGraphHandle, TRUE);
	m_IsChanged = false;
}