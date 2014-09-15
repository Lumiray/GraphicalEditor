#pragma once
#include "figure.h"
class RectangleFigure :
	public Figure
{
public:
	RectangleFigure(COLORREF color, int width);
	~RectangleFigure(void);
	void drawOnLeftButtomUp(HDC hdc);
};

