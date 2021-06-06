#include "GamePCH.h"
#include "Coily.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include <TimedFunctionComponent.h>
#include "MovementComponent.h"
#include "CoilyInputComponent.h"
#include "GameSpriteComponent.h"
#include "SpriteComponent.h"
#include "RespawnComponent.h"
#include <SceneManager.h>
#include <Scene.h>

using namespace Horizon;

Coily::Coily(const rapidjson::Value& jsonObject) :
	m_Value{jsonObject},
	m_SpawnPos{}
{
	Initialize();
}

Coily::Coily(const Horizon::IPoint2& spawnPos) : 
	m_Value{},
	m_SpawnPos{spawnPos}
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
	const float respawnTime = 10.f;

	if (m_SpawnPos == IPoint2{})
	{
		positionX += srcWidth;
		positionY -= srcHeight;

	}


	GameObject* const pGameObject = new GameObject("Coily", 4.f/*float(rand() % 10 + 6)*/);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 2, srcHeight },2);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	MovementComponent* const pMovementComponent = new MovementComponent(pGameObject, IPoint2{ positionX,positionY + fallHeight }, false);
	CoilyInputComponent* const pInputComponent = new CoilyInputComponent(pGameObject);
	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,14, int(scale * srcWidth), int(scale * srcHeight) - 14 });
	RespawnComponent* const pRespawnComponent = new RespawnComponent(pGameObject, { positionX,positionY }, respawnTime);

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);
	pGameObject->AddComponent(pRespawnComponent);

	m_pGameObject = pGameObject;
}
