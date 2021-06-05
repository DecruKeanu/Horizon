#include "GamePCH.h"
#include "UggWrongway.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "EnemyMovementComponent.h"
#include "EnemyInputComponent.h"
#include "GameSpriteComponent.h"
#include "SpriteComponent.h"

using namespace Horizon;

UggWrongway::UggWrongway(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

Horizon::GameObject* UggWrongway::GetGameObject() const
{
	return m_pGameObject;
}

void UggWrongway::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	int positionY = m_Value["positionY"].GetInt();
	const std::string type = m_Value["type"].GetString();
	const int srcPosX = 0;
	const int srcPosY = (type == "Ugg") ? 96 : 112;
	const int srcWidth = 128;
	const int srcHeight = 16;
	const float scale = 2.f;
	const int fallHeight = (type == "Ugg") ? 200 : -200;
	const int movementDirectionX = (type == "Ugg") ? -1 : 1;

	GameObject* const pGameObject = new GameObject("UggWrongway", 6.f/*float(rand() % 10 + 20)*/);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth, srcHeight },8);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX + fallHeight, positionY);
	EnemyMovementComponent* const pMovementComponent = new EnemyMovementComponent(pGameObject, IPoint2{ positionX,positionY }, true);
	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(pGameObject, IPoint2{ movementDirectionX,0 });
	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,0, int(scale * 128 / 8), int(scale * srcHeight) });

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);

	m_pGameObject = pGameObject;
}
