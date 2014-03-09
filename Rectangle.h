#ifndef Rect_H
#define Rect_H

class Rect
{
public:
	Rect();
	Rect(float, float, float, float);
	~Rect();

	float GetLeft();
	float GetRight();
	float GetTop();
	float GetBottom();
	float GetWidth();
	float GetHeight();

private:
	float left, top;
	float width, height;
};

#endif