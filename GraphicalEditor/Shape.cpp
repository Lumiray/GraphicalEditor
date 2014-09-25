#include "stdafx.h"
#include "Shape.h"


Shape::Shape(COLORREF color, int width)
{
	penColor = color;
	penWidth = width;
}

Shape::~Shape(void)
{
}

void Shape::setPoints(POINT dot1, LPARAM dot2)
{
	leftTop = dot1;
	rightBottom.x = LOWORD(dot2); 
	rightBottom.y = HIWORD(dot2);
}

void Shape::SetPenColor(COLORREF color)
{
	penColor = color;
}

void Shape::SetPenWidth(int width)
{
	penWidth = width;
}

void Shape::Draw(HDC hdc, POINT dot1, LPARAM dot2)
{
}