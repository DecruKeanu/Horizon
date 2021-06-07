#include "GamePCH.h"
#include "UggWrongway.h"

#include "RespawnComponent.h"
#include "MovementComponent.h"
#include "EnemyInputComponent.h"
#include "GameSpriteComponent.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <TextureComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>

UggWrongway::UggWrongway(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject },
	m_Type{},
	m_SpawnPos{},
	m_RespawnTime{}
{
	InitializePrefab();
}

UggWrongway::UggWrongway(const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime) : 
	m_Value{},
	m_Type{ type },
	m_SpawnPos{ spawnPos },
	m_RespawnTime{ respawnTime }
{
	InitializePrefab();
}

Horizon::GameObject* UggWrongway::GetGameObject() const
{
	return m_pGameObject;
}

void UggWrongway::InitializePrefab()
{
	const std::string type = (m_Type.empty()) ? m_Value["type"].GetString() : m_Type;

	const int fallHeight = (type == "Ugg") ? 200 : -200;
	const int movementDirectionX = (type == "Ugg") ? -1 : 1;

	int positionX = (m_SpawnPos.x == 0) ? m_Value["positionX"].GetInt() + fallHeight : m_SpawnPos.x;
	int positionY = (m_SpawnPos.y == 0) ? m_Value["positionY"].GetInt()  : m_SpawnPos.y;

	const int srcPosX = 0;
	const int srcPosY = (type == "Ugg") ? 96 : 112;
	const int srcWidth = 128;
	const int srcHeight = 16;

	const float scale = 2.f;

	const float spawnTime = (m_SpawnPos == Horizon::IPoint2{ 0, 0 }) ? m_Value["spawnTime"].GetInt() : 0.f;
	m_RespawnTime = (m_RespawnTime == 0.f) ? m_Value["respawnTime"].GetInt() : m_RespawnTime;

	m_pGameObject = new Horizon::GameObject("UggWrongway", spawnTime);

	RespawnComponent* const pRespawnComponent = new RespawnComponent(m_pGameObject, { positionX,positionY }, type, m_RespawnTime);
	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(m_pGameObject, Horizon::IPoint2{ movementDirectionX,0 });
	MovementComponent* const pMovementComponent = new MovementComponent(m_pGameObject, Horizon::IPoint2{ positionX - fallHeight,positionY }, true);
	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(m_pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth, srcHeight },8);

	Horizon::TransformComponent* const pSlickSamTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TriggerComponent* const pTriggerBodyComponent = new Horizon::TriggerComponent(m_pGameObject, { 0 ,0, int(scale * 128 / 8), int(scale * srcHeight) });

	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(pSlickSamTransform);
	m_pGameObject->AddComponent(pMovementComponent);
	m_pGameObject->AddComponent(pInputComponent);
	m_pGameObject->AddComponent(pTriggerBodyComponent);
	m_pGameObject->AddComponent(pRespawnComponent);
}
