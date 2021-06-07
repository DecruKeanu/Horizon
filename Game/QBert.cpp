#include "GamePCH.h"
#include "QBert.h"

#include "MovementComponent.h"
#include "PlayerDiscComponent.h"
#include "GameSpriteComponent.h"
#include "PlayerInputComponent.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <ScoreComponent.h>
#include <SpriteComponent.h>
#include <HealthComponent.h>
#include <TextureComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>
#include <ScoreDisplayComponent.h>
#include <HealthDisplayComponent.h>

#include <Scene.h>
#include <SoundSystemServiceLocator.h>

QBert::QBert(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	InitializePrefab();
}

Horizon::GameObject* QBert::GetGameObject() const
{
	return m_pGameObject;
}

void QBert::InitializePrefab()
{
	const int fallOffset = 50;
	int positionX = m_Value["positionX"].GetInt();
	int positionY = m_Value["positionY"].GetInt() - fallOffset;
	const bool isFirstPlayer = m_Value["IsFirstQbert"].GetBool();
	const int srcPosX = isFirstPlayer ? 0 : 126;
	const int srcPosY = 0;
	const int srcWidth = 120;
	const int srcHeight = 16;
	const float scale = 2.f;

	positionX += srcWidth / 8;
	positionY -= srcHeight;

	const std::string objectName = isFirstPlayer ? "Qbert" : "SecondQbert";
	m_pGameObject = new Horizon::GameObject(objectName);

	PlayerDiscComponent* const pPlayerDiscComponent = new PlayerDiscComponent(m_pGameObject);
	PlayerInputComponent* const pInputComponent = new PlayerInputComponent(m_pGameObject, isFirstPlayer);
	MovementComponent* const pMovementComponent = new MovementComponent(m_pGameObject, { positionX,positionY + fallOffset }, false);
	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(m_pGameObject, "QBertTextures.png", SDL_Rect{ srcPosX, srcPosY, srcWidth, srcHeight }, 8);

	Horizon::ScoreComponent* const pScoreComponent = new Horizon::ScoreComponent(m_pGameObject);
	Horizon::HealthComponent* const pHealthComponent = new Horizon::HealthComponent(m_pGameObject);
	Horizon::TransformComponent* const QBertTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TriggerComponent* const pTriggerBodyComponent = new Horizon::TriggerComponent(m_pGameObject, "BodyTrigger", { 4 ,10, int(scale * 15) - 8, int(scale * srcHeight) - 10 });
	Horizon::TriggerComponent* const pTriggerFeetComponent = new Horizon::TriggerComponent(m_pGameObject, "FeetTrigger", { int(15 * 0.5f) ,int(srcHeight * 1.8f), int(15), int(srcHeight * 0.2) });

	pTriggerFeetComponent->SetOnTriggerCallBack([pPlayerDiscComponent, pInputComponent](Horizon::GameObject*, Horizon::GameObject* pOverlappedGameObject, Horizon::TriggerComponent::TriggerAction triggerAction, const std::string&)
		{
			if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "FlyingDisc")
			{
				pPlayerDiscComponent->PlayerOnDisc(pOverlappedGameObject->GetComponent<Horizon::TransformComponent>());
				pInputComponent->DeactivateInput();
			}
			else if (triggerAction == Horizon::TriggerComponent::TriggerAction::Exit && pOverlappedGameObject->GetIdentifier() == "FlyingDisc")
			{
				pInputComponent->ActivateInput();
			}
		});

	pTriggerBodyComponent->SetOnTriggerCallBack([pScoreComponent, pHealthComponent, pPlayerDiscComponent](Horizon::GameObject*, Horizon::GameObject* pOverlappedGameObject, Horizon::TriggerComponent::TriggerAction triggerAction, const std::string&)
		{
			if (pPlayerDiscComponent->PlayerOnDisc())
				return;

			if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "SlickSam")
			{
				pScoreComponent->IncreaseScore(300);
				pOverlappedGameObject->Deactivate();
			}
			else if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "UggWrongway")
			{
				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(7, 36);
				pHealthComponent->DecreaseLive();
			}
			else if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "Coily")
			{
				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(7, 36);
				pHealthComponent->DecreaseLive();
			}
		});


	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(QBertTransform);
	m_pGameObject->AddComponent(pMovementComponent);
	m_pGameObject->AddComponent(pInputComponent);
	m_pGameObject->AddComponent(pTriggerBodyComponent);
	m_pGameObject->AddComponent(pTriggerFeetComponent);
	m_pGameObject->AddComponent(pScoreComponent);
	m_pGameObject->AddComponent(pHealthComponent);
	m_pGameObject->AddComponent(pPlayerDiscComponent);
}
