#include "GamePCH.h"
#include "QBert.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "PlayerMovementComponent.h"
#include "PlayerInputComponent.h"
#include "GameSpriteComponent.h"
#include "SpriteComponent.h"
#include <HealthComponent.h>
#include <ScoreComponent.h>
#include <TextComponent.h>
#include <ScoreDisplayComponent.h>
#include <ScoreDisplayObserver.h>
#include <HealthDisplayComponent.h>
#include <HealthDisplayObserver.h>
#include <ResourceManager.h>
#include <Scene.h>

using namespace Horizon;

QBert::QBert(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

GameObject* QBert::GetGameObject() const
{
	return m_pGameObject;
}

void QBert::Initialize()
{
	int positionX = m_Value["positionX"].GetInt();
	int positionY = m_Value["positionY"].GetInt();
	const int srcWidth = 15;
	const int srcHeight = 16;
	const float scale = 2.f;

	positionX += srcWidth;
	positionY -= srcHeight;

	GameObject* const pGameObject = new GameObject("Qbert");

	GameSpriteComponent* const pSpriteComponent = new GameSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ 0, 0, srcWidth * 8, srcHeight },8);
	TransformComponent* const QBertTransform = new TransformComponent(pGameObject, positionX, positionY);
	PlayerMovementComponent* const pMovementComponent = new PlayerMovementComponent(pGameObject);
	PlayerInputComponent* const pInputComponent = new PlayerInputComponent(pGameObject);

	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, "BodyTrigger", { 0 ,2, int(scale * srcWidth), int(scale * srcHeight) - 2 });
	TriggerComponent* const pTriggerFeetComponent = new TriggerComponent(pGameObject, "FeetTrigger", { int(srcWidth * 0.5f) ,int(srcHeight * 1.8f), int(srcWidth), int(srcHeight * 0.2) });
	ScoreComponent* const pScoreComponent = new ScoreComponent(pGameObject);
	HealthComponent* const pHealthComponent = new HealthComponent(pGameObject);

	pTriggerFeetComponent->SetOnTriggerCallBack([pScoreComponent,pMovementComponent, pInputComponent](GameObject*, GameObject* pOverlappedGameObject, TriggerComponent::TriggerAction triggerAction, const std::string&)
		{
			//if (triggerAction == TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "Cube")
			//{
			//	pScoreComponent->IncreaseScore(25);
			//}

			if (triggerAction == TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "FlyingDisc")
			{
				pMovementComponent->PlayerOnFlyingDisc(pOverlappedGameObject->GetComponent<TransformComponent>());
				pInputComponent->DeactivateInput();
			}
			else if (triggerAction == TriggerComponent::TriggerAction::Exit && pOverlappedGameObject->GetIdentifier() == "FlyingDisc")
			{
				pInputComponent->ResetInput();
			}
		});
	pTriggerBodyComponent->SetOnTriggerCallBack([pScoreComponent](GameObject*, GameObject* pOverlappedGameObject, TriggerComponent::TriggerAction triggerAction, const std::string&)
		{
			if (triggerAction == TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "SlickSam")
			{
				pScoreComponent->IncreaseScore(300);
				pOverlappedGameObject->Deactivate();
			}
			else if (triggerAction == TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "UggWrongway")
			{
				Logger::LogInfo("player should die");
			}
			else if (triggerAction == TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "Coily")
			{
				Logger::LogInfo("player should die");
			}
		});


	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(QBertTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pInputComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);
	pGameObject->AddComponent(pTriggerFeetComponent);
	pGameObject->AddComponent(pScoreComponent);
	pGameObject->AddComponent(pHealthComponent);

	//InitializeScoreDisplay(pScoreComponent);
	//InitializeHealthDisplay(pHealthComponent);

	m_pGameObject = pGameObject;
}

//void QBert::InitializeScoreDisplay(ScoreComponent* const pQbertScore)
//{
//	GameObject* const QBertScoreDisplay = new GameObject();
//	TransformComponent* const QBertScoreTransform = new TransformComponent(QBertScoreDisplay, 20, 50);
//
//	const auto QBertFont = ResourceManager::GetInstance().LoadFont("QBert.ttf", 24);
//	TextComponent* const QBertScoreText = new TextComponent(QBertScoreDisplay, "", QBertFont, { 255, 140, 0 });
//
//	ScoreDisplayComponent* const QBertScoreDisplayComponent = new ScoreDisplayComponent(QBertScoreDisplay);
//
//
//	QBertScoreDisplay->AddComponent(QBertScoreTransform);
//	QBertScoreDisplay->AddComponent(QBertScoreText);
//	QBertScoreDisplay->AddComponent(QBertScoreDisplayComponent);
//
//	pQbertScore->AddObserver(new ScoreDisplayObserver(QBertScoreDisplayComponent));
//
//	SceneManager::GetInstance().GetActiveScene()->Add(QBertScoreDisplay);
//}

//void QBert::InitializeHealthDisplay(Horizon::HealthComponent* const)
//{
//	GameObject* const QBertHealthDisplay = new GameObject();
//	TransformComponent* const QBertHealthTransform = new TransformComponent(QBertHealthDisplay, 20, 200);
//
//	const auto QBertFont = ResourceManager::GetInstance().LoadFont("QBert.ttf", 24);
//	TextComponent* const QBertHealthText = new TextComponent(QBertHealthDisplay, "", QBertFont, { 255, 140, 0 });
//
//	HealthDisplayComponent* const QHealthScoreDisplayComponent = new HealthDisplayComponent(QBertHealthDisplay);
//
//
//	QBertHealthDisplay->AddComponent(QBertHealthTransform);
//	QBertHealthDisplay->AddComponent(QBertHealthText);
//	QBertHealthDisplay->AddComponent(QHealthScoreDisplayComponent);
//
//	pQbertHealth->AddObserver(new HealthDisplayObserver(QHealthScoreDisplayComponent));
//
//	SceneManager::GetInstance().GetActiveScene()->Add(QBertHealthDisplay);
//}

