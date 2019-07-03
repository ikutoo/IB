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
		vec2i getSize() const { return vec2i{ (int)(m_Size.x * _Scale.x), (int)(m_Size.y * _Scale.y) }; }

		void flip() { m_IsFliped = !m_IsFliped; }

	private:
		int m_ImageHandle = -1;
		std::string m_ImageFile = {};
		vec2i m_Size = {};
		vec2i m_Anchor = {};

		bool m_IsFliped = false;
	};
}