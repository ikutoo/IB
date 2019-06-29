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

		void setImageFile(const std::string& vImageFile);
		vec2i getSize() const { return m_Size; }

		void flip() { m_IsFliped = !m_IsFliped; }

	private:
		int m_ImageHandle = -1;
		std::string m_ImageFile = {};
		vec2i m_Size = {};

		bool m_IsFliped = false;
	};
}