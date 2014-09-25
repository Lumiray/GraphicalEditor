#include "stdafx.h"
#include "Pen.h"


Pen::Pen(COLORREF color, int width):Shape(color, width)
{
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

void Pen::Draw(HDC hdc, POINT dot1, LPARAM dot2)
{
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	SelectObject(hdc,hpen);
	MoveToEx(hdc, leftTop.x, leftTop.y, NULL); 
	LineTo(hdc, rightBottom.x, rightBottom.y);
	leftTop = rightBottom;
}