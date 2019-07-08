#pragma once
#include <vector>
#include "engine/scene.h"
#include "engine/label.h"
#include "engine/sprite.h"
#include "particles.h"

using namespace DxEngine;

class CTitleScene : public CScene
{
public:
	virtual bool _initV() override;
	virtual void _updateV(double vDeltaTime) override;
	virtual void _destroyV() override;

private:
	CSprite* m_pFlagSprite = nullptr;
	std::vector<CTextLabel*> m_MenuLabels;

	CParticle01* m_pParticles = nullptr;

	int m_SelectedLabelIndex = 0;
};