#pragma once
#include <vector>
#include "engine/scene.h"
#include "engine/label.h"
#include "common.h"

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

	int m_SelectedLabelIndex = 0;

	void __updateSelectedLabel();
};