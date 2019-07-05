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

	static Gdiplus::Image* m_pDollImage;
	static vec2f m_DollPos;

	void __createWindow(HINSTANCE hInstance = NULL);
	void __destroyWindow();

	static void __onPaint(HDC hdc);
	static LRESULT CALLBACK __windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};