#include "GamePCH.h"
#include "QBert.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "PlayerMovementComponent.h"
#include "PlayerInputComponent.h"
#include "QbertSpriteComponent.h"
#include "SpriteComponent.h"
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
	const int srcWidth = 15;
	const int srcHeight = 15;
	const float scale = 2.f;
	const int positionX = m_Value["positionX"].GetInt() + srcWidth;
	const int positionY = m_Value["positionY"].GetInt() - srcHeight;

	GameObject* const pGameObject = new GameObject("Qbert");

	QbertSpriteComponent* const pSpriteComponent = new QbertSpriteComponent(pGameObject, "QBertTextures.png", SDL_Rect{ 0, 0, srcWidth * 8, srcHeight});
	TransformComponent* const QBertTransform = new TransformComponent(pGameObject, positionX, positionY, 0);
	PlayerMovementComponent* const pMovementComponent = new PlayerMovementComponent(pGameObject);

	TriggerComponent* const pTriggerBodyComponent = new TriggerComponent(pGameObject, "BodyTrigger", { 0 ,0, int(scale * srcWidth), int(scale * srcHeight) });
	TriggerComponent* const pTriggerFeetComponent = new TriggerComponent(pGameObject, "FeetTrigger",{ int(srcWidth* 0.5f) ,int(srcHeight*1.8f), int(srcWidth), int(srcHeight *0.2) });
	PlayerInputComponent* const pInputComponent = new PlayerInputComponent(pGameObject);

	pTriggerFeetComponent->SetOnTriggerCallBack([pMovementComponent, pInputComponent](GameObject*, GameObject* pOverlappedGameObject, TriggerComponent::TriggerAction triggerAction,const std::string&)
		{
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


	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(QBertTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pTriggerBodyComponent);
	pGameObject->AddComponent(pTriggerFeetComponent);
	pGameObject->AddComponent(pInputComponent);

	m_pGameObject = pGameObject;
}

