#pragma once
#include "Shape.h"

class EllipseShape :
	public Shape
{
public:
	EllipseShape(COLORREF color, int width);
	~EllipseShape(void);
	void Draw(HDC hdc, POINT dot1, LPARAM dot2);
};

