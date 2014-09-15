#pragma once
class Figure
{
protected:
	POINT leftTop;
	POINT rightButtom;
	COLORREF penColor;
	int penWidth;
public:
	Figure(COLORREF color, int width);
	~Figure(void);
	void setPoints(POINT dot1, LPARAM dot2);
	void setPenColor(COLORREF color);
	void setPenWidth(int width);
	virtual void drawOnLeftButtomUp(HDC hdc);
	virtual POINT drawOnMouseMove(HDC hdc);
};

