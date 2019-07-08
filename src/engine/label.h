#pragma once
#include "node.h"

namespace DxEngine
{
	class CTextLabel : public CNode
	{
	public:
		CTextLabel(const std::string& vText = "", int vFontSize = 20, int vFontType = 0, int vFontColor = 0xffffff, int vEdgeColor = 0xffffff, int vFontThickness = 6);
		~CTextLabel();

		void setText(const std::string& vText) { if (vText != m_Text) { m_Text = vText;  m_IsChanged = true; } }
		void setFontSize(int vFontSize) { if (vFontSize != m_FontSize) { m_FontSize = vFontSize; m_IsChanged = true; } }
		void setFontType(int vFontType) { if (vFontType != m_FontType) { m_FontType = vFontType; m_IsChanged = true; } }
		void setFontColor(int vFontColor) { if (vFontColor != m_FontColor) { m_FontColor = vFontColor; m_IsChanged = true; } }
		void setEdgeColor(int vEdgeColor) { if (vEdgeColor != m_EdgeColor) { m_EdgeColor = vEdgeColor; m_IsChanged = true; } }

		void setBrightness(vec3i vColor) { if (_BrightnessColor != vColor) { CNode::setBrightness(vColor); m_IsChanged = true; } }

		void drawV() override;

	private:
		std::string m_Text = {};

		int	m_FontSize = 0;
		int m_FontColor = 0;
		int m_EdgeColor = 0;
		int m_FontType = 0;
		int m_FontThickness = 0;

		bool m_IsChanged = true;

		int m_TextGraphHandle = -1;
	};
}