#pragma once

namespace Horizon
{
	IPoint2 operator+(IPoint2 lhs, const IPoint2& rhs);
	IPoint2 operator+(IPoint2 lhs, const int value);
	IPoint2& operator+=(IPoint2& lhs, const IPoint2& rhs);

	IPoint2 operator-(IPoint2 lhs, const IPoint2& rhs);
	IPoint2 operator-(IPoint2 lhs, const int value);
	IPoint2& operator-=(IPoint2& lhs, const IPoint2& rhs);

	IPoint2 operator*(IPoint2 lhs, const IPoint2& rhs);
	IPoint2 operator*(IPoint2 lhs, const int value);
	IPoint2& operator*=(IPoint2& lhs, const IPoint2& rhs);

	IPoint2 operator/(IPoint2 lhs, const IPoint2& rhs);
	IPoint2 operator/(IPoint2 lhs, const int value);
	IPoint2& operator/=(IPoint2& lhs, const IPoint2& rhs);

	bool operator==(const IPoint2& lhs, const IPoint2& rhs);
	bool operator!=(const IPoint2& lhs, const IPoint2& rhs);
}
