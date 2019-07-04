#include "resourceManager.h"
#include <filesystem>
#include <DXLib/DxLib.h>

using namespace DxEngine;

DxEngine::CResourceManager::CResourceManager()
{
}

DxEngine::CResourceManager::~CResourceManager()
{
	_ASSERTE(m_ImageResMap.empty());
}

//***********************************************************************************************
//FUNCTION:
int CResourceManager::loadImage(const std::string& vImageFile)
{
	if (m_ImageResMap.find(vImageFile) != m_ImageResMap.end())
	{
		m_ImageResMap[vImageFile].RefCount++;
		return m_ImageResMap[vImageFile].ResHandle;
	}
	else
	{
		auto ImageHandle = DxLib::LoadGraph(locateFile(vImageFile.c_str()).c_str());
		_ASSERTE(ImageHandle != -1);
		m_ImageResMap[vImageFile] = SResDesc{ ImageHandle, 1 };
		return ImageHandle;
	}
}

//*********************************************************************
//FUNCTION:
void DxEngine::CResourceManager::deleteImage(const std::string& vImageFile)
{
	if (m_ImageResMap.find(vImageFile) == m_ImageResMap.end()) return;

	_ASSERTE(m_ImageResMap[vImageFile].RefCount > 0);
	m_ImageResMap[vImageFile].RefCount--;

	if (m_ImageResMap[vImageFile].RefCount == 0)
	{
		CHECK_RESULT(DxLib::DeleteGraph(m_ImageResMap[vImageFile].ResHandle));
		m_ImageResMap.erase(vImageFile);
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