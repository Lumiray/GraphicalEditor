#pragma once
#include "shape.h"
class Line :
	public Shape
{
public:
	Line(COLORREF color, int width);
	~Line(void);
	void Draw(HDC hDC, POINT dot1, LPARAM dot2);
};

