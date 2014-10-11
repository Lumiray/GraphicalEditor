#include "stdafx.h"
#include "PolylineShape.h"


PolylineShape::PolylineShape(COLORREF color, int width):Line(color, width)
{
	isFinished = FALSE;
	startPoint.x = - 1;
}


PolylineShape::~PolylineShape(void)
{
}

void PolylineShape::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	if (startPoint.x != -1)
	{
		dot1 = startPoint;
	}
	setPoints(dot1, dot2);
	HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
	HPEN old_hpen = (HPEN)SelectObject(hDC, hpen);
	HBRUSH old_hbrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
	MoveToEx(hDC, leftTop.x, leftTop.y, NULL);
	LineTo(hDC, rightBottom.x, rightBottom.y);
	SelectObject(hDC, old_hpen);
	SelectObject(hDC, old_hbrush);
	DeleteObject(hpen);
	startPoint.x = LOWORD(dot2); 
	startPoint.y = HIWORD(dot2); 
}