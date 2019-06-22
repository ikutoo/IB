#pragma once
#include "common.h"

class CApplication
{
public:
	SINGLETION(CApplication);

	int run();

private:
	CApplication() = default;
	~CApplication() = default;

	bool __init();
	int __processLoop();
	void __destroy();
};