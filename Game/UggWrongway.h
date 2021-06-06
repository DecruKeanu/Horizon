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
	Horizon::GameObject* GetGameObject() const;
private:
	void Initialize();

	const Horizon::IPoint2& m_SpawnPos;
	const std::string m_Type;
	float m_RespawnTime;
	const rapidjson::Value& m_Value;
	Horizon::GameObject* m_pGameObject = nullptr;
};

