#pragma once
class Shape
{
protected:
	POINT leftTop;
	POINT rightBottom;
	COLORREF penColor;
	int penWidth;	
	void setPoints(POINT dot1, LPARAM dot2);
public:
	Shape(COLORREF color, int width);
	~Shape(void);
	void SetPenColor(COLORREF color);
	void SetPenWidth(int width);
	virtual void Draw(HDC hdc, POINT dot1, LPARAM dot2);
};

