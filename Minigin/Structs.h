#pragma once
using SoundId = unsigned short;

struct IPoint2 final
{
	int x = 0, y = 0;
};

struct FPoint2 final
{
	float x = 0.f, y = 0.f;
};

struct IPoint3 final
{
	int x = 0, y = 0, z = 0;
};

struct FPoint3 final
{
	float x = 0.f, y = 0.f, z = 0.f;
};

struct Color final
{
	UINT8 r = 0;
	UINT8 g = 0;
	UINT8 b = 0;
};

struct AudioData final
{
	SoundId id = 0;
	int volume = 0;
};