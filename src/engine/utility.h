#pragma once
#include <string>
#include <vector>
#include "common.h"

namespace DxEngine
{
	namespace Utility
	{
		std::string gbkToUtf8(const std::string& vStrGBK);

		std::string readFileToString(const std::string& vFilePath);
		void		writeStringToFile(const std::string& vFilePath, const std::string& vContent);

		std::vector<std::string> splitString(const std::string& vStr, const std::string& vSeparator);
	}
}