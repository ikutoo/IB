#include "stdafx.h"
#include <objidl.h>
#include <gdiplus.h>
#include "transparentWindow.h"

#pragma comment (lib,"Gdiplus.lib")

//*********************************************************************
//FUNCTION:
CTransparentWindow::CTransparentWindow(HINSTANCE hInstance)
{
	__createWindow(hInstance);
}

//*********************************************************************
//FUNCTION:
CTransparentWindow::~CTransparentWindow()
{
	__destroyWindow();
}

//*********************************************************************
//FUNCTION:
void __onPaint(HDC hdc)
{
	Gdiplus::Graphics graphics(hdc);
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));
	Gdiplus::SolidBrush brush2(Gdiplus::Color(255, 255, 255, 0));

	Gdiplus::Rect rect;
	graphics.GetVisibleClipBounds(&rect);

	graphics.FillRectangle(&brush, rect);
	graphics.FillRectangle(&brush2, 100, 100, 200, 200);
}

//*********************************************************************
//FUNCTION:
LRESULT CALLBACK __windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC          hdc;
	PAINTSTRUCT  ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		__onPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::__createWindow(HINSTANCE hInstance)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, nullptr);

	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = __windowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "TransparentWindowClass1";
	RegisterClassEx(&wc);

	m_hWnd = CreateWindowEx(NULL,
		wc.lpszClassName,    // name of the window class
		nullptr,
		WS_POPUP | WS_CHILD,    // window style
		100,    // x-position
		100,    // y-position
		3240,    // width
		1240,    // height
		DxLib::GetMainWindowHandle(),
		nullptr,
		hInstance,
		nullptr);

	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	::SetLayeredWindowAttributes(m_hWnd, RGB(0, 255, 0), 100, LWA_COLORKEY);

	ShowWindow(m_hWnd, 10); //TODO
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::__destroyWindow()
{
	Gdiplus::GdiplusShutdown(m_gdiplusToken);
	DestroyWindow(m_hWnd);
}