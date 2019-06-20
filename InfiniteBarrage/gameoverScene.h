#pragma once
#include "scene.h"
#include "common.h"

class CGameoverScene : public CScene
{
public:
	CGameoverScene();
	~CGameoverScene();

	virtual void updateV(double vDeltaTime) override;

private:
	SLabel m_TitleLabel;
};