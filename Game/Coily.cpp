#include "GamePCH.h"
#include "Coily.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "EnemyMovementComponent.h"
#include "CoilyInputComponent.h"
#include "GameSpriteComponent.h"
#include "SpriteComponent.h"
#include <SceneManager.h>
#include <Scene.h>

using namespace Horizon;

Coily::Coily(const rapidjson::Value& jsonObject) :
	m_Value{jsonObject}
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
	int positionX = m_Value["positionX"].GetInt();
	int positionY = m_Value["positionY"].GetInt() - fallHeight;
	const int srcPosX = 0;
	const int srcPosY = 18;
	const int srcWidth = 16;
	const int srcHeight = 13;
	const float scale = 2.f;

	positionX += srcWidth;
	positionY -= srcHeight;


	GameObject* const pGameObject = new GameObject("Coily", 1.f/*float(rand() % 10 + 20)*/);

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth * 2, srcHeight },2);
	TransformComponent* const pSlickSamTransform = new TransformComponent(pGameObject, positionX, positionY);
	EnemyMovementComponent* const pMovementComponent = new EnemyMovementComponent(pGameObject, IPoint2{ positionX,positionY + fallHeight }, false);
	CoilyInputComponent* const pInputComponent = new CoilyInputComponent(pGameObject);

	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, { 0 ,14, int(scale * srcWidth), int(scale * srcHeight) - 14 });

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pSlickSamTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);

	m_pGameObject = pGameObject;
}
