#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
}

class Cube final
{
public:
	Cube(const rapidjson::Value& jsonObject);

	//Getters
	Horizon::GameObject* GetGameObject() const;
private:
	//Helper functions
	void InitializePrefab();

	//GameObject
	Horizon::GameObject* m_pGameObject = nullptr;

	//Variables
	const rapidjson::Value& m_Value;
};

