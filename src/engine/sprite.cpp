#include "sprite.h"
#include <DXLib/DxLib.h>
#include "common.h"
#include "resourceManager.h"

using namespace DxEngine;

CSprite::CSprite(const std::string& vImageFile) : m_ImageFile(vImageFile)
{
	if (!vImageFile.empty())
	{
		m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
		_ASSERTE(m_ImageHandle != -1);
		CHECK_RESULT(DxLib::GetGraphSize(m_ImageHandle, &m_Size.x, &m_Size.y));
	}
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
		CHECK_RESULT(DxLib::DrawRotaGraphFast3(_Position.x, _Position.y, m_Anchor.x, m_Anchor.y, _Scale.x, _Scale.y, _Rotation, m_ImageHandle, TRUE, m_IsFliped));
	}
}

////*********************************************************************
//FUNCTION:
void CSprite::setImageFile(const std::string& vImageFile)
{
	if (vImageFile == m_ImageFile) return;

	CResourceManager::getInstance()->deleteImage(m_ImageFile);

	if (vImageFile.empty())
	{
		m_ImageHandle = -1;
	}
	else
	{
		m_ImageHandle = CResourceManager::getInstance()->loadImage(vImageFile);
		_ASSERT(m_ImageHandle != -1);
	}

	m_ImageFile = vImageFile;
}