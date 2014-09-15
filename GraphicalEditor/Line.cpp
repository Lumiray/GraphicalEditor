#include "stdafx.h"
#include "Line.h"


Line::Line(COLORREF color, int width):Figure(color, width)
{
}


Line::~Line(void)
{
}

void Line::drawOnLeftButtomUp(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	SelectObject(hdc,hpen);
	MoveToEx(hdc, leftTop.x, leftTop.y, NULL); 
	LineTo(hdc, rightButtom.x, rightButtom.y);
}

POINT Line::drawOnMouseMove(HDC hdc)
{
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	SelectObject(hdc,hpen);
	MoveToEx(hdc, leftTop.x, leftTop.y, NULL); 
	LineTo(hdc, rightButtom.x, rightButtom.y);
	return rightButtom;
}