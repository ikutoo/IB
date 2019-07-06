#pragma once
#include "node.h"
#include "math.h"

namespace DxEngine
{
	class CBox2D : public CNode
	{
	public:
		CBox2D(recti vRect, int vColor = 0, bool vFill = true) : m_Rect(vRect), m_Color(vColor), m_Fill(vFill) {}

		virtual	void drawV() override;

	private:
		recti	m_Rect = {};
		int		m_Color = 0;
		bool	m_Fill = true;
	};
}