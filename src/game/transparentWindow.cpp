#include "stdafx.h"
#include <objidl.h>
#include <gdiplus.h>
#include "engine/resourceManager.h"
#include "transparentWindow.h"
#include "common.h"

#pragma comment (lib,"Gdiplus.lib")

const WCHAR* DOLL_IMAGE_PATH = L"../../res/images/shanghai.png";

vec2f CTransparentWindow::m_DollPos = {};
Gdiplus::Image* CTransparentWindow::m_pDollImage = nullptr;

//*********************************************************************
//FUNCTION:
CTransparentWindow::CTransparentWindow(HINSTANCE hInstance)
{
	__createWindow(hInstance);
	m_DollPos = { -200, 100 };
	m_DC = GetDC(m_hWnd);
}

//*********************************************************************
//FUNCTION:
CTransparentWindow::~CTransparentWindow()
{
	__destroyWindow();
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::update(double vDeltaTime)
{
	//TODO: Ð§ÂÊµÍ
	const float MoveSpeed = 0.05;
	m_DollPos.x += vDeltaTime * MoveSpeed;

	__onPaint(m_hWnd, m_DC);
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::__onPaint(HWND hWnd, HDC hdc)
{
	if (!m_pDollImage)
	{
		m_pDollImage = new Gdiplus::Image(DOLL_IMAGE_PATH);
	}

	RECT rcClient;
	GetClientRect(hWnd, &rcClient);

	HDC hdcMem = CreateCompatibleDC(hdc);
	const int nMemDC = SaveDC(hdcMem);

	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);
	SelectObject(hdcMem, hBitmap);

	Gdiplus::Graphics graphics(hdcMem);
	graphics.Clear(Gdiplus::Color(255, 0, 0, 0));
	graphics.DrawImage(m_pDollImage, m_DollPos.x, m_DollPos.y);

	RECT rcClip;
	GetClipBox(hdc, &rcClip);
	BitBlt(hdc, rcClip.left, rcClip.top, rcClip.right - rcClip.left, rcClip.bottom - rcClip.top, hdcMem, rcClip.left, rcClip.top, SRCCOPY);

	RestoreDC(hdcMem, nMemDC);
	DeleteObject(hBitmap);
}

//*********************************************************************
//FUNCTION:
LRESULT CALLBACK CTransparentWindow::__windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
	{
		PAINTSTRUCT  ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		__onPaint(hWnd, hdc);
		EndPaint(hWnd, &ps);
		break;
	}
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
	Gdiplus::GdiplusStartup(&m_GdiToken, &gdiplusStartupInput, nullptr);

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
		0,    // x-position
		0,    // y-position
		GetSystemMetrics(SM_CXSCREEN),    // width
		GetSystemMetrics(SM_CYSCREEN),    // height
		DxLib::GetMainWindowHandle(),
		nullptr,
		hInstance,
		nullptr);

	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	::SetLayeredWindowAttributes(m_hWnd, RGB(0, 0, 0), 100, LWA_COLORKEY);

	ShowWindow(m_hWnd, 10); //TODO
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::__destroyWindow()
{
	SAFE_DELETE(m_pDollImage);
	Gdiplus::GdiplusShutdown(m_GdiToken);
	DestroyWindow(m_hWnd);
}