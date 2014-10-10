#include "stdafx.h"
#include "Line.h"


Line::Line(COLORREF color, int width):Shape(color, width)
{
}


Line::~Line(void)
{
}


void Line::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hDC, hpen);
	HBRUSH old_hbrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	MoveToEx(hDC, leftTop.x, leftTop.y, NULL);
	LineTo(hDC, rightBottom.x, rightBottom.y);
	SelectObject(hDC, old_hpen);
	SelectObject(hDC, old_hbrush);
	DeleteObject(hpen);
}