#pragma once
#include "scene.h"
#include "common.h"

class CGameoverScene : public DxEngine::CScene
{
public:
	CGameoverScene();
	~CGameoverScene();

	virtual void updateV(double vDeltaTime) override;
};