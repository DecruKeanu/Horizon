#include "GamePCH.h"
#include "QBert.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>
#include "QBertMovementComponent.h"
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

	TextureComponent* const QBertTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	SpriteComponent* const pSpriteComponent = new SpriteComponent(pGameObject, SDL_Rect{ 0, 0, srcWidth * 8, srcHeight}, 8);
	QBertTexture->SetScale(scale);
	TransformComponent* const QBertTransform = new TransformComponent(pGameObject, positionX, positionY, 0);
	QBertMovementComponent* const pMovementComponent = new QBertMovementComponent(pGameObject);

	TriggerComponent* const pTriggerComponent = new TriggerComponent(pGameObject, { positionX , positionY, int(scale * srcWidth), int(scale * srcHeight) });

	pTriggerComponent->SetOnTriggerCallBack([](GameObject*, GameObject*, TriggerComponent::TriggerAction triggerAction)
		{
			if (triggerAction == TriggerComponent::TriggerAction::Exit)
			{
				std::cout << "EXIT\n";
			}
			else
				std::cout << "ENTER\n";
		});


	pGameObject->AddComponent(QBertTexture);
	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(QBertTransform);
	pGameObject->AddComponent(pMovementComponent);
	pGameObject->AddComponent(pTriggerComponent);

	m_pGameObject = pGameObject;
}
