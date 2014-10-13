#include "stdafx.h"
#include "PolylineShape.h"


PolylineShape::PolylineShape(COLORREF color, int width):Line(color, width)
{
	isFinished = FALSE;
	PolylineLastPoint.x = - 1;
	ChangeCoords = 0;
}


PolylineShape::~PolylineShape(void)
{
}

void PolylineShape::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	if (PolylineLastPoint.x != -1)
	{
		dot1 = PolylineLastPoint;
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
	if (ChangeCoords == 1)
	{
		PolylineLastPoint.x = LOWORD(dot2); 
		PolylineLastPoint.y = HIWORD(dot2); 
		ChangeCoords = 0;
	} else
	{
		ChangeCoords++;
	}
}