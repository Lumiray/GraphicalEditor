#include "stdafx.h"
#include "windows.h"
#include "EllipseShape.h"


EllipseShape::EllipseShape(COLORREF color, int width):Shape(color, width)
{
}


EllipseShape::~EllipseShape(void)
{
}

void EllipseShape::Draw(HDC hdc, POINT dot1, LPARAM dot2)
{
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hdc, hpen);
	SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hdc, leftTop.x, leftTop.y,  rightBottom.x, rightBottom.y);
	SelectObject(hdc, old_hpen);
	DeleteObject(hpen);
}