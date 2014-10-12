#pragma once
#include "pen.h"
class EraserShape :
	public Pen
{
public:
	EraserShape(COLORREF color, int width);
	~EraserShape(void);
	void Draw(HDC hDC, POINT dot1, LPARAM dot2);
};

