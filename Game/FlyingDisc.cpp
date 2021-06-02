#include "GamePCH.h"
#include "FlyingDisc.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <TriggerComponent.h>

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
	const float scale = 2.f;
	const SDL_Rect srcRect = LevelNumberToSrcRect(m_Value["level"].GetInt());
	const int srcWidth = srcRect.w / 8;
	const int srcHeight = srcRect.h / 2;

	GameObject* const pGameObject = new GameObject("FlyingDisc");
	TextureComponent* const pDiscTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	pDiscTexture->SetScale(scale);
	FlyingDiscSpriteComponent* const pSpriteComponent = new FlyingDiscSpriteComponent(pGameObject, srcRect);
	TransformComponent* const pFlyingDiscTransform = new TransformComponent(pGameObject, positionX, positionY, 0);
	TriggerComponent* const pTriggerComponent = new TriggerComponent(pGameObject, { int(srcWidth/2), srcHeight, int(srcWidth / 2), srcHeight });

	//pTriggerComponent->SetOnTriggerCallBack([](GameObject*, GameObject* pOverlappedGameObject, TriggerComponent::TriggerAction triggerAction)
	//	{

	//	});


	pGameObject->AddComponent(pDiscTexture);
	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(pFlyingDiscTransform);
	pGameObject->AddComponent(pTriggerComponent);

	m_pGameObject = pGameObject;
}

SDL_Rect FlyingDisc::LevelNumberToSrcRect(const int levelNumber)
{

	int posX = 0;
	const int posY = 205;
	const int width = 190;
	const int height = 10;

	switch (levelNumber)
	{
	case 1:
		posX = 0;
		break;
	case 2:
		posX = 64;
		break;
	case 3:
		posX = 128;
		break;
	default:
		Logger::LogWarning("LevelNumberToSrcRect >> invalid levelNumber. Default value is used, 1");
		break;
	}

	return SDL_Rect{ posX,posY,width,height };


}
