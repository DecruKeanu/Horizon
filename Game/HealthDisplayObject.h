#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
}

class HealthDisplayObject final
{
public:
	HealthDisplayObject(const rapidjson::Value& jsonObject);

	//Getter
	Horizon::GameObject* GetGameObject() const;
private:
	//Helper functions
	void InitializePrefab();

	//GameObject
	Horizon::GameObject* m_pGameObject = nullptr;

	//Variables
	const rapidjson::Value& m_Value;
};

