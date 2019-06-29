#pragma once
#include "node.h"

namespace DxEngine
{
	class CImageLabel : public CNode
	{
	public:
		CImageLabel(const std::string& vImageFile);
		~CImageLabel();

		void drawV() override;

		vec2i getSize() const { return m_Size; }
		void setSize(int vWidth, int vHeight) { m_Size.x = vWidth; m_Size.y = vHeight; }

		void setImageFile(const std::string& vImageFile);

	private:
		vec2i m_Size = {};
		int m_ImageHandle = -1;
		std::string m_ImageFile = {};
	};

	class CTextLabel : public CNode
	{
	public:
		CTextLabel(const std::string& vText = "", int vFontSize = 20, int vFontType = 0, int vFontColor = 0xffffff, int vEdgeColor = 0xffffff);
		~CTextLabel() = default;

		void setText(const std::string& vText) { m_Text = vText; }
		void setFontSize(int vFontSize) { m_FontSize = vFontSize; }
		void setFontType(int vFontType) { m_FontType = vFontType; }
		void setFontColor(int vFontColor) { m_FontColor = vFontColor; }
		void setEdgeColoe(int vEdgeColor) { m_EdgeColor = vEdgeColor; }

		void drawV() override;

	private:
		std::string m_Text = {};
		int	m_FontSize = 0;
		int m_FontColor = 0;
		int m_EdgeColor = 0;
		int m_FontType = 0;
	};
}