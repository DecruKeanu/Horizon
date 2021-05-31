#pragma once
#include <array>
#include "document.h"
#include "Prefab.h"

class Cube final : public Horizon::Prefab
{
public:
	Cube(const rapidjson::Value& jsonObject);

	//enum class CubeColor : int
	//{
	//	level1Purple,
	//	level1Blue,
	//	level2Pink,
	//	level2Yellow,
	//	level2Blue,
	//	level3Mellow,
	//	level3Blue,
	//	enumSize
	//};
private:
	void Initialize();
	SDL_Rect ColorToSrcRect(const std::string& color);
	const rapidjson::Value& m_Value;
	//CubeColor m_InitCubeColor;



	//const std::array<Horizon::IPoint2, int(CubeColor::enumSize)> m_SrcPositions;
};

