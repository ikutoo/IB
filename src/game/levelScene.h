#pragma once
#include <vector>
#include "engine/scene.h"
#include "common.h"

namespace DxEngine
{
	class CImageLabel;
	class CTextLabel;
	class CSprite;
}

class CTransparentWindow;

class CLevelScene : public  DxEngine::CScene
{
public:
	bool initV() override;
	void updateV(double vDeltaTime) override;
	void drawV() override;
	void destroyV() override;

private:
	std::vector<DxEngine::CTextLabel*> m_MenuLabels;
	DxEngine::CImageLabel* m_pFlagLabel = nullptr;

	DxEngine::CImageLabel* m_pImageLabel = nullptr;
	DxEngine::CTextLabel* m_pDescLabel = nullptr;

	DxEngine::CSprite* m_pDoll = nullptr;

	CTransparentWindow* m_pWindow = nullptr;

	int m_SelectedLabelIndex = 0;
	float m_DollSpeed = 0.1;

	bool __initUI();

	void __updateSelectedLabel();
	void __updateDollPosition(double vDeltaTime);
};