#include "resourceManager.h"
#include <DXLib/DxLib.h>

using namespace DxEngine;

//***********************************************************************************************
//FUNCTION:
int CResourceManager::loadImage(const std::string& vImageFile)
{
	if (m_ImageFile2HandleMap.find(vImageFile) != m_ImageFile2HandleMap.end())
	{
		return m_ImageFile2HandleMap[vImageFile];
	}
	else
	{
		auto ImageHandle = DxLib::LoadGraph(vImageFile.c_str());
		_ASSERTE(ImageHandle != -1);
		m_ImageFile2HandleMap[vImageFile] = ImageHandle;
	}
}