#pragma once
#include <set>
#include <map>
#include <string>
#include "common.h"

namespace DxEngine
{
	enum class EResourceType : char
	{
		UNDEFINED = 0,
		IMAGE,
		SOUND
	};

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

		int loadResource(const std::string& vFilePath, EResourceType vResType);
		void deleteResource(const std::string& vFilePath, EResourceType vResType);

		int loadImage(const std::string& vFilePath) { return loadResource(vFilePath, EResourceType::IMAGE); }
		void deleteImage(const std::string& vFilePath) { deleteResource(vFilePath, EResourceType::IMAGE); }

		int loadSoundMem(const std::string& vFilePath) { return loadResource(vFilePath, EResourceType::SOUND); }
		void deleteSoundMem(const std::string& vFilePath) { deleteResource(vFilePath, EResourceType::SOUND); }

		std::string locateFile(const std::string& vFileName);

	private:
		CResourceManager();
		~CResourceManager();

		std::set<std::string> m_FileSearchPathSet;

		std::map<std::string, SResDesc> m_ResMap;
	};
}