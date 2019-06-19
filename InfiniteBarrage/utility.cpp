#include "stdafx.h"
#include "utility.h"

//*********************************************************************
//FUNCTION:
void utility::drawLabel(const SLabel& vLabel)
{
	ASSERT_SUCCESS(SetFontSize(vLabel.fontSize));
	ASSERT_SUCCESS(SetFontThickness(vLabel.fontThickness));
	ASSERT_SUCCESS(DrawString(vLabel.x, vLabel.y, vLabel.pText, vLabel.color, vLabel.edgeColor));
}