#pragma once

#include "resource.h"

#define WIDTH 1920
#define HEIGHT 1080

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