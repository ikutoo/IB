#pragma once
#include <map>
#include "node.h"

namespace DxEngine
{
	class CSprite : public CNode
	{
	public:
		CSprite(const std::string& vImageFile);
		virtual ~CSprite();

		void drawV() override;

	private:
		int m_ImageHandle = -1;
		std::string m_ImageFile = {};
	};
}