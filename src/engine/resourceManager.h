#pragma once
#include <set>
#include <map>
#include <string>
#include "common.h"

namespace DxEngine
{
	class CResourceManager
	{
	public:
		SINGLETION(CResourceManager);

		void addFileSearchPath(const std::string& vPath) { m_FileSearchPathSet.insert(vPath); }

		int loadImage(const std::string& vImageFile);
		int getImageHandle(const std::string& vImageFile) const { return m_ImageFile2HandleMap.at(vImageFile); }

	private:
		CResourceManager() = default;
		~CResourceManager() = default;

		std::set<std::string> m_FileSearchPathSet;

		std::map<std::string, int> m_ImageFile2HandleMap;
	};
}