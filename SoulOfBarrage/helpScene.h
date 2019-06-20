#pragma once
#include "scene.h"

class CHelpScene : public CScene
{
public:
	CHelpScene();
	~CHelpScene();

	virtual void updateV(double vDeltaTime) override;
};