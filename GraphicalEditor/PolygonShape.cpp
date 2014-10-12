#include "stdafx.h"
#include "PolygonShape.h"


PolygonShape::PolygonShape(COLORREF color, int width):PolylineShape(color, width)
{
	isFinished = FALSE;
	PolylineLastPoint.x = - 1;
	PolylineFirstPoint.x = - 1;
	ChangeCoords = 0;
}


PolygonShape::~PolygonShape(void)
{
}

void PolygonShape::Draw(HDC hDC, POINT dot1, LPARAM dot2)
{
	if ((PolylineLastPoint.x != -1) && (PolylineFirstPoint.x != -1) && (PolylineFirstPoint.x != PolylineLastPoint.x) 
		&& (PolylineFirstPoint.y != PolylineLastPoint.y) && (isFinished))
	{
		HPEN hpen = CreatePen(PS_SOLID,penWidth,penColor);
		HPEN old_hpen = (HPEN)SelectObject(hDC, hpen);
		HBRUSH old_hbrush = (HBRUSH)SelectObject(hDC, GetStockObject(HOLLOW_BRUSH));
		MoveToEx(hDC, PolylineLastPoint.x, PolylineLastPoint.y, NULL);
		LineTo(hDC, PolylineFirstPoint.x, PolylineFirstPoint.y);
		SelectObject(hDC, old_hpen);
		SelectObject(hDC, old_hbrush);
		DeleteObject(hpen);
		if (ChangeCoords == 1)
		{
			PolylineFirstPoint.x = -1;
			ChangeCoords = 0;
			isFinished = FALSE;
		} else
		{
			ChangeCoords++;
		}
		return;
	}
  	if (PolylineLastPoint.x != -1)
	{
		dot1 = PolylineLastPoint;
	} else
	{
		PolylineFirstPoint = dot1;
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
	if (ChangeCoords == 0)
	{
		PolylineLastPoint.x = LOWORD(dot2); 
		PolylineLastPoint.y = HIWORD(dot2); 
	} else
	{
		ChangeCoords++;
	}
}