#include "Rectangle.h"

Rect::Rect()
{
	//create a rectangle with all zero values
	left = 0.0f;
	top = 0.0f;
	width = 0.0f;
	height = 0.0f;
}

Rect::Rect(float nLeft, float nTop, float nWidth, float nHeight)
{
	//create a rectangle with specified values
	left = nLeft;
	top = nTop;
	width = nWidth;
	height = nHeight;
}

Rect::~Rect()
{
}

//get left edge x value
float Rect::GetLeft()
{
	return left;
}

//get right edge x value
float Rect::GetRight()
{
	return left + width;
}

//get top edge y value
float Rect::GetTop()
{
	return top;
}

//get bottom edge y value
float Rect::GetBottom()
{
	return top + height;
}

//get rectangle width
float Rect::GetWidth()
{
	return width;
}

//get rectangle height
float Rect::GetHeight()
{
	return height;
}