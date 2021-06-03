#include "MiniginPCH.h"
#include "IPoint2Operators.h"

Horizon::IPoint2 Horizon::operator+(Horizon::IPoint2 lhs, const Horizon::IPoint2& rhs)
{
	return (lhs += rhs);
}

Horizon::IPoint2 Horizon::operator+(Horizon::IPoint2 lhs, const int value)
{
	return lhs += Horizon::IPoint2{ value, value };
}

Horizon::IPoint2& Horizon::operator+=(Horizon::IPoint2& lhs, const Horizon::IPoint2& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;

	return lhs;
}

Horizon::IPoint2 Horizon::operator-(Horizon::IPoint2 lhs, const Horizon::IPoint2& rhs)
{
	return (lhs -= rhs);
}

Horizon::IPoint2 Horizon::operator-(Horizon::IPoint2 lhs, const int value)
{
	return lhs -= Horizon::IPoint2{ value, value };
}

Horizon::IPoint2& Horizon::operator-=(Horizon::IPoint2& lhs, const Horizon::IPoint2& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;

	return lhs;
}

Horizon::IPoint2 Horizon::operator*(Horizon::IPoint2 lhs, const Horizon::IPoint2& rhs)
{
	return (lhs *= rhs);
}

Horizon::IPoint2 Horizon::operator*(Horizon::IPoint2 lhs, const int value)
{
	return lhs *= Horizon::IPoint2{ value, value };
}

Horizon::IPoint2& Horizon::operator*=(Horizon::IPoint2& lhs, const Horizon::IPoint2& rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;

	return lhs;
}

Horizon::IPoint2 Horizon::operator/(Horizon::IPoint2 lhs, const Horizon::IPoint2& rhs)
{
	return (lhs /= rhs);
}

Horizon::IPoint2 Horizon::operator/(Horizon::IPoint2 lhs, const int value)
{
	return lhs /= Horizon::IPoint2{ value, value };
}

Horizon::IPoint2& Horizon::operator/=(Horizon::IPoint2& lhs, const Horizon::IPoint2& rhs)
{
	lhs.x /= rhs.x;
	lhs.y /= rhs.y;

	return lhs;
}

bool Horizon::operator==(const Horizon::IPoint2& lhs, const Horizon::IPoint2& rhs)
{
	return (lhs.x == rhs.x && rhs.y == rhs.y);
}

bool Horizon::operator!=(const Horizon::IPoint2& lhs, const Horizon::IPoint2& rhs)
{
	return !(lhs.x == rhs.x && rhs.y == rhs.y);
}
