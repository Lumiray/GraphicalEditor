#pragma once
#include "PolylineShape.h"
class PolygonShape :
	public PolylineShape
{
public:
	PolygonShape(COLORREF color, int width);
	~PolygonShape(void);
	void Draw(HDC hDC, POINT dot1, LPARAM dot2);
	int ChangeCoords;
};