#pragma once
#include <vector>
#include "engine/scene.h"
#include "common.h"

using namespace DxEngine;

namespace DxEngine
{
	class CImageLabel;
	class CTextLabel;
	class CSprite;
}

class CTransparentWindow;

class CLevelScene : public  CScene
{
public:
	bool _initV() override;
	void _updateV(double vDeltaTime) override;
	void _destroyV() override;

private:
	std::vector<CTextLabel*> m_MenuLabels;
	CTextLabel* m_pDescLabel = nullptr;
	CSprite* m_pFlagSprite = nullptr;
	CSprite* m_pImageLabel = nullptr;

	CTransparentWindow* m_pTransWindow = nullptr;

	int m_SelectedLabelIndex = 0;

	bool __initUI();

	void __updateSelectedLabel();
};