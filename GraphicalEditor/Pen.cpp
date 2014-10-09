#include "stdafx.h"
#include "Pen.h"


Pen::Pen(COLORREF color, int width):Shape(color, width)
{
	isContinuous = TRUE;
}


Pen::~Pen(void)
{
}

void Pen::setPoints(POINT dot1, LPARAM dot2)
{
	if (leftTop.x == -842150451 && leftTop.y == -842150451) // if is not initialised
		leftTop = dot1;
	rightBottom.x = LOWORD(dot2); 
	rightBottom.y = HIWORD(dot2);
}

void Pen::Draw(HDC hDC, POINT dot1, LPARAM dot2)
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