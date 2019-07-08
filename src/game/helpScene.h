#pragma once
#include "engine/scene.h"

class CHelpScene : public  DxEngine::CScene
{
public:
	CHelpScene();
	~CHelpScene();

	virtual void _updateV(double vDeltaTime) override;
};