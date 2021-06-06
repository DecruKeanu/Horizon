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

using namespace Horizon;

SlickSam::SlickSam(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
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
	int positionX = m_Value["positionX"].GetInt();
	int positionY = m_Value["positionY"].GetInt() - fallHeight;
	const std::string type = m_Value["type"].GetString();
	const int srcPosX = 0;
	const int srcPosY = (type == "Slick") ? 128 : 144;
	const int srcWidth = 12;
	const int srcHeight = 16;
	const float scale = 2.f;

	positionX += srcWidth;
	positionY -= srcHeight;

	 
	GameObject* const pGameObject = new GameObject("SlickSam", 120/*float(rand() % 20 + 20)*/);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 8, srcHeight },8);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	MovementComponent* const pMovementComponent = new MovementComponent(pGameObject, IPoint2{ positionX,positionY + fallHeight }, false);
	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(pGameObject, {0,1});

	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,14, int(scale * srcWidth), int(scale * srcHeight) - 14 });

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);

	m_pGameObject = pGameObject;
}
