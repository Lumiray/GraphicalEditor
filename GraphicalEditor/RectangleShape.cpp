#include "stdafx.h"
#include "RectangleShape.h"


RectangleShape::RectangleShape(COLORREF color, int width):Shape(color, width)
{
}

RectangleShape::~RectangleShape(void)
{
}

void RectangleShape::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hDC, hpen);
	HBRUSH old_hbrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	SelectObject(hDC,hpen);
	Rectangle(hDC, leftTop.x, leftTop.y,  rightBottom.x, rightBottom.y);
	SelectObject(hDC, old_hpen);
	SelectObject(hDC, old_hbrush);
	DeleteObject(hpen);
}
