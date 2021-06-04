#include "GamePCH.h"
#include "SlickSam.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "EnemyMovementComponent.h"
#include "EnemyInputComponent.h"
#include "EnemySpriteComponent.h"
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
	int positionX = m_Value["positionX"].GetInt();
	int positionY = m_Value["positionY"].GetInt() - 200;
	const std::string type = m_Value["type"].GetString();
	const int srcPosX = 0;
	const int srcPosY = (type == "Slick") ? 128 : 144;
	const int srcWidth = 12;
	const int srcHeight = 16;
	const float scale = 2.f;

	positionX += srcWidth;
	positionY -= srcHeight;

	 
	GameObject* const pGameObject = new GameObject("SlickSam", 1.f/*float(rand() % 10 + 20)*/);

	EnemySpriteComponent* const pSpriteComponent = new EnemySpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 8, srcHeight });
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	EnemyMovementComponent* const pMovementComponent = new EnemyMovementComponent(pGameObject, IPoint2{ positionX,positionY + 200 }, false);
	EnemyInputComponent* const pInputComponent = new EnemyInputComponent(pGameObject, {0,1});

	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,14, int(scale * srcWidth), int(scale * srcHeight) - 14 });

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);

	m_pGameObject = pGameObject;
}
