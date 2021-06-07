#include "GamePCH.h"
#include "Coily.h"

#include "SpriteComponent.h"
#include "RespawnComponent.h"
#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include "CoilyInputAIComponent.h"
#include "CoilyInputPlayerComponent.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>
#include <TimedFunctionComponent.h>

#include <Scene.h>
#include <SceneManager.h>

Coily::Coily(const rapidjson::Value& jsonObject) :
	m_Value{jsonObject},
	m_SpawnPos{},
	m_RespawnTime{},
	m_IsPlayerControlled{},
	m_Respawn{}
{
	InitializePrefab();
}

Coily::Coily(const Horizon::IPoint2& spawnPos, float respawnTime, bool playerControlled) : 
	m_Value{},
	m_SpawnPos{spawnPos},
	m_RespawnTime{respawnTime},
	m_IsPlayerControlled{playerControlled}
{
	InitializePrefab();
}

Horizon::GameObject* Coily::GetGameObject() const
{
	return m_pGameObject;
}

void Coily::InitializePrefab()
{
	const int fallHeight = 140;
	int positionX = (m_SpawnPos.x == 0) ? m_Value["positionX"].GetInt() : m_SpawnPos.x;
	int positionY = (m_SpawnPos.y == 0) ? m_Value["positionY"].GetInt() - fallHeight : m_SpawnPos.y;
	const float spawnTime = (m_SpawnPos == Horizon::IPoint2{ 0, 0 }) ? m_Value["spawnTime"].GetInt() : 0.f;
	const bool isPlayerControlled = (m_Value.IsObject()) ? m_Value["isPlayerControlled"].GetBool() : m_IsPlayerControlled;

	const int srcPosX = 0;
	const int srcPosY = 18;
	const int srcWidth = 16;
	const int srcHeight = 13;
	const float scale = 2.f; 

	m_RespawnTime = (m_RespawnTime == 0.f) ? m_Value["respawnTime"].GetFloat() : m_RespawnTime;

	if (m_SpawnPos == Horizon::IPoint2{})
	{
		positionX += srcWidth;
		positionY -= srcHeight;
	}

	m_pGameObject = new Horizon::GameObject("Coily", spawnTime);

	RespawnComponent* const pRespawnComponent = new RespawnComponent(m_pGameObject, { positionX,positionY }, {}, m_RespawnTime, isPlayerControlled);
	MovementComponent* const pMovementComponent = new MovementComponent(m_pGameObject, Horizon::IPoint2{ positionX,positionY + fallHeight }, false);
	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(m_pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 8, srcHeight },8);

	Horizon::TransformComponent* const pCoilyTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TriggerComponent* const pTriggerBodyComponent = new Horizon::TriggerComponent(m_pGameObject, { 0 ,14, int(scale * srcWidth), int(scale * srcHeight) - 14 });

	m_pGameObject->AddComponent(pRespawnComponent);
	m_pGameObject->AddComponent(pMovementComponent);
	m_pGameObject->AddComponent(pSpriteComponent);

	m_pGameObject->AddComponent(pCoilyTransform);
	m_pGameObject->AddComponent(pTriggerBodyComponent);


	if (isPlayerControlled)
	{
		CoilyInputPlayerComponent* const pInputComponent = new CoilyInputPlayerComponent(m_pGameObject);
		m_pGameObject->AddComponent(pInputComponent);
	}
	else
	{
		CoilyInputAIComponent* const pInputComponent = new CoilyInputAIComponent(m_pGameObject);
		m_pGameObject->AddComponent(pInputComponent);
	}
}
