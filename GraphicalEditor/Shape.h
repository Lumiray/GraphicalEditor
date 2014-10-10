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
	BOOL isContinuous;
	void SetPenColor(COLORREF color);
	void SetPenWidth(int width);
	virtual void Draw(HDC hDC, POINT dot1, LPARAM dot2);
	void SetStartPoint(POINT startPoint);
	void CancelLastAction(void);
	POINT GetStartPoint(void);
};

