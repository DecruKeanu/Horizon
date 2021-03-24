#pragma once
using SoundId = unsigned short;

struct Color
{
	UINT8 r;
	UINT8 g;
	UINT8 b;
};

struct AudioData
{
	SoundId id;
	int volume;
};