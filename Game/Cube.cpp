#include "GamePCH.h"
#include "Cube.h"

#include "TriggerComponent.h"
#include "CubeHandleComponent.h"

#include <GameObject.h>
#include <ScoreComponent.h>
#include <SpriteComponent.h>
#include <TextureComponent.h>
#include <TransformComponent.h>

#include <Scene.h>
#include <SceneManager.h>
#include <SoundSystemServiceLocator.h>

Cube::Cube(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	InitializePrefab();
}

Horizon::GameObject* Cube::GetGameObject() const
{
	return m_pGameObject;
}

void Cube::InitializePrefab()
{
	const int level = m_Value["level"].GetInt();
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();

	const int srcPosX = (level % 2 == 0) ? 64 : (80 * (level - 1));
	const int srcPosY = 164;
	const int srcWidth = (level % 2 == 0) ? 96 : 64;
	const int srcHeight = 32;
	const SDL_Rect srcRect{ srcPosX,srcPosY,srcWidth,srcHeight };

	const int spriteAmount = (level % 2 == 0) ? 3 : 2;
	const float scale = 2.f;

	m_pGameObject = new Horizon::GameObject("Cube");
	CubeHandleComponent* const pHandleCubeComponent = new CubeHandleComponent(m_pGameObject, level);

	Horizon::TriggerComponent* const pTriggerComponent = new Horizon::TriggerComponent(m_pGameObject, { 22,6, 18, 10 });
	Horizon::TransformComponent* const pCubeTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::SpriteComponent* const pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, "QBertTextures.png", srcRect, spriteAmount);

	pTriggerComponent->SetOnTriggerCallBack([pHandleCubeComponent](Horizon::GameObject*, Horizon::GameObject* pOverlappedGameObject, Horizon::TriggerComponent::TriggerAction triggerAction, const std::string& overlappedTriggerIdentifier)
		{
			if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter &&  overlappedTriggerIdentifier == "FeetTrigger")
			{
				if (pHandleCubeComponent->GetisActivated() == false)
					pOverlappedGameObject->GetComponent<Horizon::ScoreComponent>()->IncreaseScore(25);

				pHandleCubeComponent->ActivateCube();

				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(2, 48);
			}
			else if (triggerAction == Horizon::TriggerComponent::TriggerAction::Enter && pOverlappedGameObject->GetIdentifier() == "SlickSam")
			{
				pHandleCubeComponent->DeactivateCube();
			}
		});

	pSpriteComponent->Scale(scale);
	m_pGameObject->AddComponent(pHandleCubeComponent);
	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(pCubeTransform);
	m_pGameObject->AddComponent(pTriggerComponent);
}



