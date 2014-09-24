#include "stdafx.h"
#include "windows.h"
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
	HPEN old_hpen = (HPEN)SelectObject(hdc, hpen);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdc, leftTop.x, leftTop.y,  rightButtom.x, rightButtom.y);
	SelectObject(hdc, old_hpen);
	DeleteObject(hpen);
}