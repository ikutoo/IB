#pragma once
#include "common.h"

class CEngine
{
public:
	SINGLETION(CEngine);
	DISALLOW_COPY_AND_ASSIGN(CEngine);

	int run();

private:
	CEngine() = default;
	~CEngine() = default;

	bool __init();
	void __destroy();

	void __update();
	void __render();
};