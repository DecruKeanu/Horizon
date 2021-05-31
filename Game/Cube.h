#pragma once
#include "document.h"
#include "Prefab.h"

class Cube final : public Horizon::Prefab
{
public:
	Cube(const rapidjson::Value& jsonObject);
private:
	void Initialize();
	SDL_Rect LevelNumberToSrcRect(const int levelNumber);
	const rapidjson::Value& m_Value;
};

