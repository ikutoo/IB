#pragma once
#include <map>
#include "node.h"

namespace DxEngine
{
	class CSprite : public CNode
	{
	public:
		CSprite(const std::string& vImageFile = "");
		virtual ~CSprite() = default;

		void drawV() override;

	private:
		int m_ImageHandle = -1;

		static std::map<std::string, int> m_ImageFile2HandleMap;
	};
}