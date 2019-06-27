#pragma once
#include "node.h"

namespace DxEngine
{
	class CImageLabel : public CNode
	{
	public:
		CImageLabel(int vImageHandle, bool vDeleteImageOnDestroy = true);
		CImageLabel(const char* vImageFile, bool vDeleteImageOnDestroy = true);
		~CImageLabel();

		void drawV() override;

		vec2i getSize() const { return m_Size; }

	private:
		vec2i m_Size = {};
		int m_ImageHandle = -1;
		bool m_DeleteImageOnDestroy = false;
	};

	class CTextLabel : public CNode
	{
	};
}