#pragma once
#include <set>
#include <map>
#include <string>
#include "common.h"

namespace DxEngine
{
	struct SResDesc
	{
		int ResHandle = -1;
		int RefCount = 0;
	};

	class CResourceManager
	{
	public:
		SINGLETION(CResourceManager);

		void addFileSearchPath(const std::string& vPath) { m_FileSearchPathSet.insert(vPath); }

		int loadImage(const std::string& vImageFile);
		void deleteImage(const std::string& vImageFile);

	private:
		CResourceManager();
		~CResourceManager();

		std::set<std::string> m_FileSearchPathSet;

		std::map<std::string, SResDesc> m_ImageResMap;
	};
}