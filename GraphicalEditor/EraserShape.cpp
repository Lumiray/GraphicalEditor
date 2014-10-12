#include "stdafx.h"
#include "EraserShape.h"


EraserShape::EraserShape(COLORREF color, int width):Pen(color, width)
{
}


EraserShape::~EraserShape(void)
{
}

void EraserShape::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hDC, hpen);
	MoveToEx(hDC, leftTop.x, leftTop.y, NULL); 
	LineTo(hDC, rightBottom.x, rightBottom.y);
	SelectObject(hDC, old_hpen);
	DeleteObject(hpen);
	leftTop = rightBottom;
}