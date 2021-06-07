#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
	class ScoreComponent;
	class HealthComponent;
}

class QBert final
{
public:
	QBert(const rapidjson::Value& jsonObject);

	//Getters
	Horizon::GameObject* GetGameObject() const;
private:
	//Helper functions
	void InitializePrefab();

	//GameObject
	Horizon::GameObject* m_pGameObject;

	//Variables
	const rapidjson::Value& m_Value;
};

