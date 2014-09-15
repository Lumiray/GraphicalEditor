#pragma once
#include "figure.h"
class Rectangle :
	public Figure
{
public:
	Rectangle(COLORREF color, int width);
	~Rectangle(void);
	void drawOnLeftButtomUp(HDC hdc);
	POINT drawOnMouseMove(HDC hdc);
};

