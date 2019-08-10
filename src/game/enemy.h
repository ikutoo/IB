#pragma once
#include <string>
#include "engine/sprite.h"

using namespace DxEngine;

class CEnemy : public CSprite
{
public:
	CEnemy(const std::string& vImageFile, const recti& vRect = {}) : CSprite(vImageFile, vRect) {}
	~CEnemy() = default;
};