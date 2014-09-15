#include "stdafx.h"
#include "EllipceFigure.h"


EllipceFigure::EllipceFigure(COLORREF color, int width):Figure(color, width)
{
}


EllipceFigure::~EllipceFigure(void)
{
}

void EllipceFigure::drawOnLeftButtomUp(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	SelectObject(hdc,hpen);
	Ellipse(hdc, leftTop.x, leftTop.y,  rightButtom.x, rightButtom.y);
}