#include "GamePCH.h"
#include "FlyingDisc.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "FlyingDiscMovementComponent.h"
#include "FlyingDiscSpriteComponent.h"
#include <Scene.h>

using namespace Horizon;

FlyingDisc::FlyingDisc(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

Horizon::GameObject* FlyingDisc::GetGameObject() const
{
	return m_pGameObject;
}

void FlyingDisc::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const int level = m_Value["level"].GetInt();
	const float scale = 2.f;

	const int posX = 0 + 64 * (level - 1);
	const int posY = 205;
	const int width = 64;
	const int height = 10;
	const SDL_Rect srcRect{ posX,posY,width,height };

	GameObject* const pGameObject = new GameObject("FlyingDisc");
	TransformComponent* const pFlyingDiscTransform = new TransformComponent(pGameObject, positionX, positionY, 0);
	FlyingDiscSpriteComponent* const pSpriteComponent = new FlyingDiscSpriteComponent(pGameObject,"QBertTextures.png", srcRect);
	FlyingDiscMovementComponent* const pMovementComponent = new FlyingDiscMovementComponent(pGameObject);
	TriggerComponent* const pTriggerComponent = new TriggerComponent(pGameObject, { 8, 6, width/4, 6 });

	pTriggerComponent->SetOnTriggerCallBack([pMovementComponent](GameObject*, GameObject* pOverlappedGameObject, TriggerComponent::TriggerAction triggerAction, std::string overlappedTriggerIdentifier)
		{
			if (triggerAction == TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "Qbert" && overlappedTriggerIdentifier == "FeetTrigger")
			{
				pMovementComponent->Activate();
			}
		});

	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pFlyingDiscTransform);
	pGameObject->AddComponent(pTriggerComponent);
	pGameObject->AddComponent(pMovementComponent);

	m_pGameObject = pGameObject;
}
