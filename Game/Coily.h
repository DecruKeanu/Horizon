#pragma once
#include "document.h"

namespace Horizon
{
	class GameObject;
}

class Coily final 
{
public:
	Coily(const rapidjson::Value& jsonObject);
	Coily(const Horizon::IPoint2& spawnPos, float respawnTime, bool playerControlled);

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

	float m_RespawnTime;
	bool m_Respawn;
	bool m_IsPlayerControlled;
};

