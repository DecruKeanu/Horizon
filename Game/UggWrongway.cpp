#include "GamePCH.h"
#include "UggWrongway.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "MovementComponent.h"
#include "EnemyInputComponent.h"
#include "GameSpriteComponent.h"
#include "SpriteComponent.h"
#include "RespawnComponent.h"

using namespace Horizon;

UggWrongway::UggWrongway(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject },
	m_Type{},
	m_SpawnPos{},
	m_RespawnTime{}
{
	Initialize();
}

UggWrongway::UggWrongway(const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime) : 
	m_Value{},
	m_Type{ type },
	m_SpawnPos{ spawnPos },
	m_RespawnTime{ respawnTime }
{
	Initialize();
}

Horizon::GameObject* UggWrongway::GetGameObject() const
{
	return m_pGameObject;
}

void UggWrongway::Initialize()
{
	const std::string type = (m_Type.empty()) ? m_Value["type"].GetString() : m_Type;
	const int fallHeight = (type == "Ugg") ? 200 : -200;
	int positionX = (m_SpawnPos.x == 0) ? m_Value["positionX"].GetInt() + fallHeight : m_SpawnPos.x;
	int positionY = (m_SpawnPos.y == 0) ? m_Value["positionY"].GetInt()  : m_SpawnPos.y;
	const int srcPosX = 0;
	const int srcPosY = (type == "Ugg") ? 96 : 112;
	const int srcWidth = 128;
	const int srcHeight = 16;
	const float scale = 2.f;
	const float spawnTime = (m_SpawnPos == IPoint2{ 0, 0 }) ? m_Value["spawnTime"].GetInt() : 0.f;
	m_RespawnTime = (m_RespawnTime == 0.f) ? m_Value["respawnTime"].GetInt() : m_RespawnTime;

	const int movementDirectionX = (type == "Ugg") ? -1 : 1;

	GameObject* const pGameObject = new GameObject("UggWrongway", spawnTime);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth, srcHeight },8);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	MovementComponent* const pMovementComponent = new MovementComponent(pGameObject, IPoint2{ positionX - fallHeight,positionY }, true);
	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(pGameObject, IPoint2{ movementDirectionX,0 });
	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,0, int(scale * 128 / 8), int(scale * srcHeight) });
	RespawnComponent* const pRespawnComponent = new RespawnComponent(pGameObject, { positionX,positionY }, type, m_RespawnTime);

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);
	pGameObject->AddComponent(pRespawnComponent);

	m_pGameObject = pGameObject;
}
