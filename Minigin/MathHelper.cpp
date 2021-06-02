#include "MiniginPCH.h"
#include "MathHelper.h"

bool Horizon::MathHelper::AreRectsOverlapping(const IRect& firstRect, const IRect& secondRect)
{
	const int firstRectRight = firstRect.x + firstRect.width;
	const int secondRectRight = secondRect.x + secondRect.width;

	const int firstRectBottom = firstRect.y + firstRect.height;
	const int secondRectBottom = secondRect.y + secondRect.height;

	//check if first rectangle is right of second rect 
	if (firstRect.x > secondRectRight)
		return false;

	//check if first rectangle is left of second rect 
	if (firstRectRight < secondRect.x)
		return false;

	//check if first rectangle is below second rect 
	if (firstRect.y > secondRectBottom)
		return false;

	//check if first rectangle is above second rect 
	if (firstRectBottom < secondRect.y)
		return false;

	return true;
}

int Horizon::MathHelper::ILerp(const int startValue, const int endValue, float lerpValue)
{
	//returns a value between startValue and endValue at the hand of the lerpValue
	return int(startValue + (endValue - startValue) * lerpValue);
}
