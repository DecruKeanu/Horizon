#include "GamePCH.h"
#include "SlickSam.h"

#include "RespawnComponent.h"
#include "MovementComponent.h"
#include "EnemyInputComponent.h"
#include "GameSpriteComponent.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <TextureComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>

SlickSam::SlickSam(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject },
	m_Type{},
	m_SpawnPos{},
	m_RespawnTime{}
{
	InitializePrefab();
}

SlickSam::SlickSam(const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime) :
	m_Value{},
	m_Type{type},
	m_SpawnPos{ spawnPos },
	m_RespawnTime{ respawnTime }
{
	InitializePrefab();
}

Horizon::GameObject* SlickSam::GetGameObject() const
{
	return m_pGameObject;
}

void SlickSam::InitializePrefab()
{
	const int fallHeight = 140;

	int positionX = (m_SpawnPos.x == 0) ? m_Value["positionX"].GetInt() : m_SpawnPos.x;
	int positionY = (m_SpawnPos.y == 0) ? m_Value["positionY"].GetInt() - fallHeight : m_SpawnPos.y;
	const std::string type = (m_Type.empty()) ? m_Value["type"].GetString() : m_Type;

	const int srcPosX = 0;
	const int srcPosY = (type == "Slick") ? 128 : 144;
	const int srcWidth = 12;
	const int srcHeight = 16;

	const float scale = 2.f;

	const float spawnTime = (m_SpawnPos == Horizon::IPoint2{ 0, 0 }) ? m_Value["spawnTime"].GetInt() : 0.f;
	m_RespawnTime = (m_RespawnTime == 0.f) ? m_Value["respawnTime"].GetInt() : m_RespawnTime;

	if (m_SpawnPos == Horizon::IPoint2{})
	{
		positionX += srcWidth;
		positionY -= srcHeight;
	}

	m_pGameObject = new Horizon::GameObject("SlickSam", spawnTime);

	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(m_pGameObject, { 0,1 });
	RespawnComponent* const pRespawnComponent = new RespawnComponent(m_pGameObject, { positionX,positionY }, type, m_RespawnTime);
	MovementComponent* const pMovementComponent = new MovementComponent(m_pGameObject, Horizon::IPoint2{ positionX,positionY + fallHeight }, false);
	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(m_pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 8, srcHeight },8);

	Horizon::TransformComponent* const pSlickSamTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TriggerComponent* const pTriggerBodyComponent = new Horizon::TriggerComponent(m_pGameObject, { 10 ,14, int(scale * srcWidth) - 12, int(scale * srcHeight) - 14 });

	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(pSlickSamTransform);
	m_pGameObject->AddComponent(pMovementComponent);
	m_pGameObject->AddComponent(pInputComponent);
	m_pGameObject->AddComponent(pTriggerBodyComponent);
	m_pGameObject->AddComponent(pRespawnComponent);
}
