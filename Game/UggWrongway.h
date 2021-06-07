#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
}

class UggWrongway final
{
public:
	UggWrongway(const rapidjson::Value& jsonObject);
	UggWrongway(const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime);

	//Getters
	Horizon::GameObject* GetGameObject() const;
private:
	//Helper functions
	void InitializePrefab();

	//GameObject
	Horizon::GameObject* m_pGameObject = nullptr;

	//Variables
	const rapidjson::Value& m_Value;
	const Horizon::IPoint2& m_SpawnPos;
	const std::string m_Type;

	float m_RespawnTime;
};

