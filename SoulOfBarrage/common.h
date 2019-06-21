#pragma once
#include <string>

#define SINGLETION(T) static T* getInstance() { static T Instance; return &Instance; }

#define DISALLOW_COPY_AND_ASSIGN(T)	\
    T(const T&) = delete;			\
    T& operator=(const T&) = delete;

#define SAFE_DELETE(p) if (p) { delete p; p = nullptr;}

#define CHECK_RESULT(call) if (0 != call) assert(false);

#define WIDTH 1920
#define HEIGHT 1080

#define TITLE_SCENE		0
#define GAME_SCENE		1
#define HELP_SCENE		2
#define GAME_OVER_SCENE 3

const std::string RES_IMG_ROOT = "../Resource/images/";
#define LOCATE_IMAGE(file) (RES_IMG_ROOT + file).c_str()

struct SLabel
{
	const TCHAR* pText = nullptr;
	int x = 0;
	int y = 0;
	int fontSize = 10;
	int fontThickness = 6;
	unsigned int color = 0;
	unsigned int edgeColor = 0;
};

struct SImageLabel
{
	int x = 0;
	int y = 0;
	int image = -1;
};