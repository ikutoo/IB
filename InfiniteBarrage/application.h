#pragma once
#include "common.h"

class CApplication
{
public:
	SINGLETION(CApplication);
	DISALLOW_COPY_AND_ASSIGN(CApplication);

	int run();

private:
	CApplication() = default;
	~CApplication() = default;

	bool __init();
	int __processLoop();
	void __destroy();
};