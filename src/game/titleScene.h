#pragma once
#include <vector>
#include "engine/scene.h"
#include "engine/label.h"
#include "engine/sprite.h"
#include "particles.h"

class CTitleScene : public  DxEngine::CScene
{
public:
	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

private:
	DxEngine::CImageLabel* m_pFlagLabel = nullptr;
	std::vector<DxEngine::CTextLabel*> m_MenuLabels;

	CParticle01* m_pParticles = nullptr;

	int m_SelectedLabelIndex = 0;
};