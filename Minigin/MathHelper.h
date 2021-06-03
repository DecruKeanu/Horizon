#pragma once
#include "Structs.h"

namespace Horizon
{
	namespace MathHelper
	{
		bool AreRectsOverlapping(const IRect& firstRect, const IRect& secondRect);
		int ILerp(const int startValue, const int endValue, float lerpValue);
		IPoint2 IPoint2Lerp(const IPoint2& startValue, const IPoint2& endValue, float lerpValue);
	}
}

