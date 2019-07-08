#include "utility.h"
#include <fstream>
#include <sstream>
#include <windows.h> 

using namespace DxEngine;

//*********************************************************************
//FUNCTION:
std::string Utility::readFileToString(const std::string& vFilePath)
{
	_ASSERTE(!vFilePath.empty());
	std::ifstream fin(vFilePath);
	_ASSERTE(fin.is_open());
	std::string fileContent;

	std::ostringstream oss;
	oss << fin.rdbuf();
	fileContent = oss.str();
	fin.close();

	return fileContent;
}

//*********************************************************************
//FUNCTION:
std::vector<std::string> Utility::splitString(const std::string& vStr, const std::string& vSeparator)
{
	int cutAt;
	std::string str = vStr;
	std::vector<std::string> results;
	while ((cutAt = str.find(vSeparator)) != str.npos)
	{
		if (cutAt > 0)
			results.push_back(str.substr(0, cutAt));
		str = str.substr(cutAt + vSeparator.length());
	}
	if (str.length() > 0)
		results.push_back(str);
	return results;
}

//*********************************************************************
//FUNCTION:
std::string Utility::gbkToUtf8(const std::string& vStrGBK)
{
	std::string strOutUTF8;
	int n = MultiByteToWideChar(CP_ACP, 0, vStrGBK.c_str(), -1, nullptr, 0);
	auto pStr1 = new WCHAR[n];
	MultiByteToWideChar(CP_ACP, 0, vStrGBK.c_str(), -1, pStr1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, pStr1, -1, nullptr, 0, nullptr, nullptr);
	auto pStr2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, pStr1, -1, pStr2, n, nullptr, nullptr);
	strOutUTF8 = pStr2;
	delete[] pStr1;
	pStr1 = nullptr;
	delete[] pStr2;
	pStr2 = nullptr;
	return strOutUTF8;
}

//*********************************************************************
//FUNCTION:
void Utility::writeStringToFile(const std::string& vFilePath, const std::string& vContent)
{
	std::ofstream ofs(vFilePath);
	_ASSERTE(ofs.is_open());
	ofs << vContent;
}