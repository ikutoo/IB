#include "stdafx.h"
#include <objidl.h>
#include <gdiplus.h>
#include "engine/resourceManager.h"
#include "transparentWindow.h"
#include "common.h"

#pragma comment (lib,"Gdiplus.lib")

const WCHAR* DOLL_IMAGE_PATH = L"../../res/images/shanghai.png";
const float HIDDEN_DISTANCE = 400.0;

//*********************************************************************
//FUNCTION:
CTransparentWindow::CTransparentWindow(HINSTANCE hInstance)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&m_GdiToken, &gdiplusStartupInput, nullptr);

	m_hWnd = __createWindow(hInstance);
	m_DC = GetDC(m_hWnd);
	m_pDollImage = new Gdiplus::Image(DOLL_IMAGE_PATH);
	m_DollPos = { -HIDDEN_DISTANCE, 0 };
}

//*********************************************************************
//FUNCTION:
CTransparentWindow::~CTransparentWindow()
{
	SAFE_DELETE(m_pDollImage);
	Gdiplus::GdiplusShutdown(m_GdiToken);
	DestroyWindow(m_hWnd);
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::update(double vDeltaTime)
{
	m_DollPos.x += vDeltaTime * m_DollSpeed;

	int ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	if (m_DollPos.x < -HIDDEN_DISTANCE || m_DollPos.x > ScreenWidth + HIDDEN_DISTANCE)
	{
		m_DollPos.x = m_DollPos.x < -HIDDEN_DISTANCE ? -HIDDEN_DISTANCE : ScreenWidth + HIDDEN_DISTANCE;
		m_pDollImage->RotateFlip(Gdiplus::RotateFlipType::RotateNoneFlipX);
		m_DollSpeed = -m_DollSpeed;
	}

	__onPaint(m_hWnd, m_DC);
}

//*********************************************************************
//FUNCTION:
void CTransparentWindow::__onPaint(HWND hWnd, HDC hdc)
{
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
LRESULT CALLBACK __windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}

//*********************************************************************
//FUNCTION:
HWND CTransparentWindow::__createWindow(HINSTANCE hInstance)
{
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

	auto hWnd = CreateWindowEx(NULL,
		wc.lpszClassName,    // name of the window class
		nullptr,
		WS_POPUP | WS_CHILD,    // window style
		0,    // x-position
		100,    // y-position
		GetSystemMetrics(SM_CXSCREEN),    // width
		200,    // height
		DxLib::GetMainWindowHandle(),
		nullptr,
		hInstance,
		nullptr);

	SetWindowLong(hWnd, GWL_EXSTYLE, GetWindowLong(hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	::SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 255, LWA_COLORKEY);

	ShowWindow(hWnd, 10); //TODO

	return hWnd;
}