#include "stdafx.h"
#include "windows.h"
#include "EllipseShape.h"


EllipseShape::EllipseShape(COLORREF color, int width):Shape(color, width)
{
}


EllipseShape::~EllipseShape(void)
{
}

void EllipseShape::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hDC, hpen);
	HBRUSH old_hbrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	Ellipse(hDC, leftTop.x, leftTop.y,  rightBottom.x, rightBottom.y);
	SelectObject(hDC, old_hpen);
	SelectObject(hDC, old_hbrush);
	DeleteObject(hpen);
}