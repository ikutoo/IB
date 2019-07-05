#pragma once
#include "engine/math.h"

using namespace DxEngine;

namespace Gdiplus
{
	class Image;
}

class CTransparentWindow
{
public:
	CTransparentWindow(HINSTANCE hInstance = NULL);
	~CTransparentWindow();

	void update(double vDeltaTime);

private:
	HWND m_hWnd = nullptr;
	HDC	 m_DC = nullptr;

	ULONG_PTR m_GdiToken = {};

	Gdiplus::Image* m_pDollImage = nullptr;
	vec2f m_DollPos = {};
	float m_DollSpeed = 0.05f;

	HWND __createWindow(HINSTANCE hInstance = NULL);

	void __onPaint(HWND hWnd, HDC hdc);
};