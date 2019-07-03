#pragma once
#include <vector>
#include "engine/scene.h"
#include "engine/label.h"
#include "engine/sprite.h"

struct SParticle
{
	DxEngine::CSprite* pSprite = nullptr;
	float SpeedX = 0.0;
	float SpeedY = 0.0;
};

class CTitleScene : public  DxEngine::CScene
{
public:
	virtual bool initV() override;
	virtual void updateV(double vDeltaTime) override;
	virtual void destroyV() override;

private:
	DxEngine::CImageLabel* m_pFlagLabel = nullptr;
	std::vector<DxEngine::CTextLabel*> m_MenuLabels;

	std::vector<SParticle> m_Particles;

	int m_SelectedLabelIndex = 0;

	void __initPartices();
	void __updateParticles();
};