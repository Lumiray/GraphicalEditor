#pragma once
#include "Figure.h"
class Line :
	public Figure
{
public:
	Line(COLORREF color, int width);
	~Line(void);
	void drawOnLeftButtomUp(HDC hdc);
	POINT drawOnMouseMove(HDC hdc);
};

