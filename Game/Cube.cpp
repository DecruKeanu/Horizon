#include "GamePCH.h"
#include "Cube.h"
#include "Cube.h"
#include "SceneManager.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <SpriteComponent.h>
#include "CubeHandleComponent.h"
#include "TriggerComponent.h"
#include <Scene.h>

using namespace Horizon;

Cube::Cube(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

GameObject* Cube::GetGameObject() const
{
	return m_pGameObject;
}

void Cube::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const int level = m_Value["level"].GetInt();
	const int spriteAmount = (level % 2 == 0) ? 3 : 2;
	const float scale = 2.f;

	const int posX = (level % 2 == 0) ? 64 : (80 * (level - 1));
	const int posY = 164;
	const int width = (level % 2 == 0) ? 96 : 64;
	const int height = 32;
	const SDL_Rect srcRect{ posX,posY,width,height };

	GameObject* const pGameObject = new GameObject("Cube");
	CubeHandleComponent* const pHandleCubeComponent = new CubeHandleComponent(pGameObject, level);
	SpriteComponent* const pSpriteComponent = new SpriteComponent(pGameObject,"QBertTextures.png", srcRect, spriteAmount);
	pSpriteComponent->Scale(scale);
	TransformComponent* const blockTransform = new TransformComponent(pGameObject, positionX, positionY, 0);
	TriggerComponent* const pTriggerComponent = new TriggerComponent(pGameObject, { 20,10, 20, int(srcRect.w / 8) });

	pTriggerComponent->SetOnTriggerCallBack([pHandleCubeComponent](GameObject*, GameObject*, TriggerComponent::TriggerAction triggerAction, const std::string& overlappedTriggerIdentifier)
		{
			if (triggerAction == TriggerComponent::TriggerAction::Enter && overlappedTriggerIdentifier == "FeetTrigger")
			{
				pHandleCubeComponent->ActivateCube();
			}
		});

	pGameObject->AddComponent(pHandleCubeComponent);
	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(blockTransform);
	pGameObject->AddComponent(pTriggerComponent);

	m_pGameObject = pGameObject;
}



