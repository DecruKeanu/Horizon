#include "GamePCH.h"
#include "SlickSam.h"
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

SlickSam::SlickSam(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject },
	m_Type{},
	m_SpawnPos{},
	m_RespawnTime{}
{
	Initialize();
}

SlickSam::SlickSam(const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime) :
	m_Value{},
	m_Type{type},
	m_SpawnPos{ spawnPos },
	m_RespawnTime{ respawnTime }
{
	Initialize();
}

Horizon::GameObject* SlickSam::GetGameObject() const
{
	return m_pGameObject;
}

void SlickSam::Initialize()
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
	const float spawnTime = (m_SpawnPos == IPoint2{ 0, 0 }) ? m_Value["spawnTime"].GetInt() : 0.f;
	m_RespawnTime = (m_RespawnTime == 0.f) ? m_Value["respawnTime"].GetInt() : m_RespawnTime;

	if (m_SpawnPos == IPoint2{})
	{
		positionX += srcWidth;
		positionY -= srcHeight;
	}

	GameObject* const pGameObject = new GameObject("SlickSam", spawnTime);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 8, srcHeight },8);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	MovementComponent* const pMovementComponent = new MovementComponent(pGameObject, IPoint2{ positionX,positionY + fallHeight }, false);
	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(pGameObject, {0,1});
	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 10 ,14, int(scale * srcWidth) - 12, int(scale * srcHeight) - 14 });
	RespawnComponent* const pRespawnComponent = new RespawnComponent(pGameObject, { positionX,positionY },type, m_RespawnTime);

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);
	pGameObject->AddComponent(pRespawnComponent);

	m_pGameObject = pGameObject;
}
