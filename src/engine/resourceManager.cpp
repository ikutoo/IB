#include "resourceManager.h"
#include <filesystem>
#include <DXLib/DxLib.h>

using namespace DxEngine;

DxEngine::CResourceManager::CResourceManager()
{
}

DxEngine::CResourceManager::~CResourceManager()
{
	_ASSERTE(m_ResMap.empty());
}

//*********************************************************************
//FUNCTION:
int CResourceManager::loadResource(const std::string& vFilePath, EResourceType vResType)
{
	auto LoadResource = [&]()
	{
		switch (vResType)
		{
		case DxEngine::EResourceType::IMAGE:
			return  DxLib::LoadGraph(locateFile(vFilePath).c_str());
			break;
		case DxEngine::EResourceType::SOUND:
			return DxLib::LoadSoundMem(locateFile(vFilePath).c_str());
			break;
		default:
			_ASSERTE(false);
			break;
		}
	};

	if (m_ResMap.find(vFilePath) != m_ResMap.end())
	{
		m_ResMap[vFilePath].RefCount++;
		return m_ResMap[vFilePath].ResHandle;
	}
	else
	{
		auto ResHandle = LoadResource();
		_ASSERTE(ResHandle != -1);
		m_ResMap[vFilePath] = SResDesc{ ResHandle, 1 };
		return ResHandle;
	}
}

//*********************************************************************
//FUNCTION:
void DxEngine::CResourceManager::deleteResource(const std::string& vFilePath, EResourceType vResType)
{
	if (m_ResMap.find(vFilePath) == m_ResMap.end()) return;

	auto DeleteResource = [&]()
	{
		switch (vResType)
		{
		case DxEngine::EResourceType::IMAGE:
			CHECK_RESULT(DxLib::DeleteGraph(m_ResMap[vFilePath].ResHandle));
			break;
		case DxEngine::EResourceType::SOUND:
			CHECK_RESULT(DxLib::DeleteSoundMem(m_ResMap[vFilePath].ResHandle));
			break;
		default:
			_ASSERTE(false);
			break;
		}
	};

	_ASSERTE(m_ResMap[vFilePath].RefCount > 0);
	m_ResMap[vFilePath].RefCount--;

	if (m_ResMap[vFilePath].RefCount == 0)
	{
		DeleteResource();
		m_ResMap.erase(vFilePath);
	}
}

//***********************************************************************************************
//FUNCTION:
std::string DxEngine::CResourceManager::locateFile(const std::string& vFileName)
{
	for (auto& SearchPath : m_FileSearchPathSet)
	{
		auto FullPath = SearchPath + "/" + vFileName;
		if (std::filesystem::exists(FullPath)) return FullPath;
	}

	return "";
}