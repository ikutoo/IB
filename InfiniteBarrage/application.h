#pragma once
#include "common.h"

class CTitleScene;

class CApplication
{
public:
	CApplication();
	~CApplication();

	static CApplication* getInstance()
	{
		static CApplication Instance;
		return &Instance;
	}

	int run();

private:
	void __init();
	int __processLoop();

	CTitleScene* m_pTitleScene = nullptr;
};