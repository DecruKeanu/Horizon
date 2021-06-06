#include "GamePCH.h"
#include "Coily.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include <TimedFunctionComponent.h>
#include "MovementComponent.h"
#include "CoilyInputAIComponent.h"
#include "CoilyInputPlayerComponent.h"
#include "GameSpriteComponent.h"
#include "SpriteComponent.h"
#include "RespawnComponent.h"
#include <SceneManager.h>
#include <Scene.h>

using namespace Horizon;

Coily::Coily(const rapidjson::Value& jsonObject) :
	m_Value{jsonObject},
	m_SpawnPos{},
	m_RespawnTime{},
	m_IsPlayerControlled{},
	m_Respawn{}
{
	Initialize();
}

Coily::Coily(const Horizon::IPoint2& spawnPos, float respawnTime, bool playerControlled) : 
	m_Value{},
	m_SpawnPos{spawnPos},
	m_RespawnTime{respawnTime},
	m_IsPlayerControlled{playerControlled}
{
	Initialize();
}

Horizon::GameObject* Coily::GetGameObject() const
{
	return m_pGameObject;
}

void Coily::Initialize()
{
	const int fallHeight = 140;
	int positionX = (m_SpawnPos.x == 0) ? m_Value["positionX"].GetInt() : m_SpawnPos.x;
	int positionY = (m_SpawnPos.y == 0) ? m_Value["positionY"].GetInt() - fallHeight : m_SpawnPos.y;
	const int srcPosX = 0;
	const int srcPosY = 18;
	const int srcWidth = 16;
	const int srcHeight = 13;
	const float scale = 2.f; 
	const float spawnTime = (m_SpawnPos == IPoint2{ 0, 0 }) ? m_Value["spawnTime"].GetInt() : 0.f; 
	const bool isPlayerControlled = (m_Value.IsObject()) ? m_Value["isPlayerControlled"].GetBool() : m_IsPlayerControlled;
	m_RespawnTime = (m_RespawnTime == 0.f) ? m_Value["respawnTime"].GetFloat() : m_RespawnTime;

	if (m_SpawnPos == IPoint2{})
	{
		positionX += srcWidth;
		positionY -= srcHeight;
	}

	GameObject* const pGameObject = new GameObject("Coily", spawnTime);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 2, srcHeight },2);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	MovementComponent* const pMovementComponent = new MovementComponent(pGameObject, IPoint2{ positionX,positionY + fallHeight }, false);
	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,14, int(scale * srcWidth), int(scale * srcHeight) - 14 });
	RespawnComponent* const pRespawnComponent = new RespawnComponent(pGameObject, { positionX,positionY }, {}, m_RespawnTime,isPlayerControlled);

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);

	pGameObject->AddComponent(pTriggerBodyComponent);
	pGameObject->AddComponent(pRespawnComponent);

	if (isPlayerControlled)
	{
		CoilyInputPlayerComponent* const pInputComponent = new CoilyInputPlayerComponent(pGameObject);
		pGameObject->AddComponent(pInputComponent);
	}
	else
	{
		CoilyInputAIComponent* const pInputComponent = new CoilyInputAIComponent(pGameObject);
		pGameObject->AddComponent(pInputComponent);
	}

	m_pGameObject = pGameObject;
}
