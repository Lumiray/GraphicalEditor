#pragma once
#include "line.h"
class PolylineShape :
	public Line
{
public:
	PolylineShape(COLORREF color, int width);
	~PolylineShape(void);
	void Draw(HDC hDC, POINT dot1, LPARAM dot2);
	int ChangeCoords;
};

