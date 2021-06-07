#include "GamePCH.h"
#include "FlyingDisc.h"

#include "FlyingDiscSpriteComponent.h"
#include "FlyingDiscMovementComponent.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>

#include <Scene.h>

FlyingDisc::FlyingDisc(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	InitializePrefab();
}

Horizon::GameObject* FlyingDisc::GetGameObject() const
{
	return m_pGameObject;
}

void FlyingDisc::InitializePrefab()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const int level = m_Value["level"].GetInt();

	const int srcPosX = 0 + 64 * (level - 1);
	const int srcPosY = 205;
	const int srcWidth = 64;
	const int srcHeight = 10;
	const SDL_Rect srcRect{ srcPosX,srcPosY,srcWidth,srcHeight };

	const float scale = 2.f;

	m_pGameObject = new Horizon::GameObject("FlyingDisc");

	FlyingDiscMovementComponent* const pMovementComponent = new FlyingDiscMovementComponent(m_pGameObject);
	FlyingDiscSpriteComponent* const pSpriteComponent = new FlyingDiscSpriteComponent(m_pGameObject, "QBertTextures.png", srcRect);

	Horizon::TriggerComponent* const pTriggerComponent = new Horizon::TriggerComponent(m_pGameObject, { 8, 6, srcWidth / 4, 6 });
	Horizon::TransformComponent* const pFlyingDiscTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);

	pTriggerComponent->SetOnTriggerCallBack([pMovementComponent](Horizon::GameObject*, Horizon::GameObject*, Horizon::TriggerComponent::TriggerAction triggerAction, std::string overlappedTriggerIdentifier)
		{
			if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter && overlappedTriggerIdentifier == "FeetTrigger")
			{
				pMovementComponent->Activate();
			}
		});

	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(pFlyingDiscTransform);
	m_pGameObject->AddComponent(pTriggerComponent);
	m_pGameObject->AddComponent(pMovementComponent);
}