#pragma once
#include "figure.h"
class EllipceFigure :
	public Figure
{
public:
	EllipceFigure(COLORREF color, int width);
	~EllipceFigure(void);
	void drawOnLeftButtomUp(HDC hdc);
};

