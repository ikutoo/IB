#include "sprite.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

CSprite::CSprite(const std::string& vImageFile, const recti& vRect)
{
	setImageFile(vImageFile, vRect);
}

CSprite::~CSprite()
{
	if (!m_ImageFile.empty())
	{
		CResourceManager::getInstance()->deleteImage(m_ImageFile);
	}
}

//*********************************************************************
//FUNCTION:
void CSprite::drawV()
{
	CNode::drawV();

	if (m_ImageHandle != -1)
	{
		if (m_Rect.w != 0)
		{
			CHECK_RESULT(DxLib::DrawRectRotaGraphFast3(_Position.x, _Position.y, m_Rect.x, m_Rect.y, m_Rect.w, m_Rect.h, m_Anchor.x, m_Anchor.y, _Scale.x, _Scale.y, _Rotation, m_ImageHandle, TRUE, m_IsFliped));
		}
		else
		{
			CHECK_RESULT(DxLib::DrawRotaGraphFast3(_Position.x, _Position.y, m_Anchor.x, m_Anchor.y, _Scale.x, _Scale.y, _Rotation, m_ImageHandle, TRUE, m_IsFliped));
		}
	}
}

//*********************************************************************
//FUNCTION:
vec2i CSprite::getSize() const
{
	return vec2i{ (int)(m_Size.x * _Scale.x), (int)(m_Size.y * _Scale.y) };
}

////*********************************************************************
//FUNCTION:
void CSprite::setImageFile(const std::string& vImageFile, const recti& vRect)
{
	if (vImageFile == m_ImageFile) return;

	CResourceManager::getInstance()->deleteImage(m_ImageFile);

	if (!vImageFile.empty())
	{
		m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
		_ASSERTE(m_ImageHandle != -1);

		if (vRect.w != 0)
			m_Size = { vRect.w, vRect.h };
		else
			CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
	}
	else
	{
		m_ImageHandle = -1;
	}

	m_Rect = vRect;
	m_ImageFile = vImageFile;
}