#include "stdafx.h"
#include "RectangleFigure.h"


RectangleFigure::RectangleFigure(COLORREF color, int width):Figure(color, width)
{
}

RectangleFigure::~RectangleFigure(void)
{
}

void RectangleFigure::drawOnLeftButtomUp(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hdc, hpen);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	SelectObject(hdc,hpen);
	Rectangle(hdc, leftTop.x, leftTop.y,  rightButtom.x, rightButtom.y);
	SelectObject(hdc, old_hpen);
	DeleteObject(hpen);
}
