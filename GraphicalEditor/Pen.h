#pragma once
#include "Shape.h"
class Pen :
	public Shape
{
protected:
	void setPoints(POINT dot1, LPARAM dot2);
public:
	Pen(COLORREF color, int width);
	~Pen(void);
	void Draw(HDC hDC, POINT dot1, LPARAM dot2);
};
