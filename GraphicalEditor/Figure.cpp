#include "stdafx.h"
#include "Figure.h"


Figure::Figure(COLORREF color, int width)
{
	penColor = color;
	penWidth = width;
}

Figure::~Figure(void)
{
}

void Figure::setPoints(POINT dot1, LPARAM dot2)
{
	leftTop = dot1;
	rightButtom.x = LOWORD(dot2); 
	rightButtom.y = HIWORD(dot2);
}

void Figure::setPenColor(COLORREF color)
{
	penColor = color;
}

void Figure::setPenWidth(int width)
{
	penWidth = width;
}

void Figure::drawOnLeftButtomUp(HDC hdc)
{
}

POINT Figure::drawOnMouseMove(HDC hdc)
{
	return leftTop;
}