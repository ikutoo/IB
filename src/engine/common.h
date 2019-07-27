#pragma once
#include <string>
#include "math.h"

#define SINGLETION(T) static T* getInstance() { static T Instance; return &Instance; } \
    T(const T&) = delete;			\
    T& operator=(const T&) = delete;

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr;}

#define CHECK_RESULT(call) if (0 != call) _ASSERTE(false);

#define LOCATE_FILE(file) (CResourceManager::getInstance()->locateFile(file)).c_str()

#define LOG(msg)	std::cout << msg << std::endl;

namespace DxEngine
{
	struct SDisplayInfo
	{
		vec2i WindowSize = {};
		vec2i WindowPosition = {};
		vec2i ScreenSize = {};
		std::string WindowTitle = "";
		bool IsFullscreen = false;
	};
}