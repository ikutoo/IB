#pragma once
#include <vector>
#include "scene.h"
#include "common.h"

class CLevelScene : public  DxEngine::CScene
{
public:
	bool initV() override;
	void updateV(double vDeltaTime) override;
	void destroyV() override;
};