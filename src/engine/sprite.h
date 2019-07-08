#pragma once
#include <map>
#include "node.h"

namespace DxEngine
{
	class CSprite : public CNode
	{
	public:
		CSprite(const std::string& vImageFile = "", const recti& vRect = {});
		virtual ~CSprite();

		void drawV() override;

		void setImageFile(const std::string& vImageFile, const recti& vRect = {});
		void setRect(const recti& vRect) { m_Rect = vRect; m_Size = { vRect.w, vRect.h }; }

		vec2i getSize() const;

		void flip() { m_IsFliped = !m_IsFliped; }

	private:
		int m_ImageHandle = -1;
		std::string m_ImageFile = {};

		recti m_Rect = {};
		vec2i m_Size = {};
		vec2i m_Anchor = {};

		bool m_IsFliped = false;
	};
}