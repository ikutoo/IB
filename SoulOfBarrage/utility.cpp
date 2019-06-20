#include "stdafx.h"
#include "utility.h"

//*********************************************************************
//FUNCTION:
void utility::drawLabel(const SLabel& vLabel)
{
	CHECK_RESULT(SetFontSize(vLabel.fontSize));
	CHECK_RESULT(SetFontThickness(vLabel.fontThickness));
	CHECK_RESULT(DrawString(vLabel.x, vLabel.y, vLabel.pText, vLabel.color, vLabel.edgeColor));
}