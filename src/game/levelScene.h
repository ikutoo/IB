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
	void destroyV() override;

private:
	std::vector<DxEngine::CTextLabel*> m_MenuLabels;
	DxEngine::CImageLabel* m_pFlagLabel = nullptr;

	DxEngine::CImageLabel* m_pImageLabel = nullptr;
	DxEngine::CTextLabel* m_pDescLabel = nullptr;

	CTransparentWindow* m_pTransWindow = nullptr;

	int m_SelectedLabelIndex = 0;

	bool __initUI();

	void __updateSelectedLabel();
};