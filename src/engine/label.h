#pragma once
#include "node.h"

namespace DxEngine
{
	class CImageLabel : public CNode
	{
	public:
		CImageLabel(const char* vImageFile);
		~CImageLabel();

		void drawV() override;

		vec2i getSize() const { return m_Size; }

	private:
		vec2i m_Size = {};
		int m_ImageHandle = -1;
	};

	class CTextLabel : public CNode
	{
	};
}