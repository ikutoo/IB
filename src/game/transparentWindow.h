#pragma once

class CTransparentWindow
{
public:
	CTransparentWindow(HINSTANCE hInstance = NULL);
	~CTransparentWindow();

private:
	HWND m_hWnd = nullptr;
	ULONG_PTR m_gdiplusToken = {};

	void __createWindow(HINSTANCE hInstance = NULL);
	void __destroyWindow();
};