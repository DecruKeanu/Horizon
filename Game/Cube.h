#pragma once
#include "document.h"
#include "Prefab.h"

namespace Horizon
{
	class GameObject;
}


class Cube final
{
public:
	Cube(const rapidjson::Value& jsonObject);
	Horizon::GameObject* GetGameObject() const;
private:
	void Initialize();
	SDL_Rect LevelNumberToSrcRect(const int levelNumber);
	const rapidjson::Value& m_Value;

	Horizon::GameObject* m_pGameObject;
};

