#include "GamePCH.h"
#include "SpriteObject.h"
#include <GameObject.h>
#include <TransformComponent.h>
#include <SpriteComponent.h>
#include <TimedFunctionComponent.h>

using namespace Horizon;

SpriteObject::SpriteObject(const rapidjson::Value& jsonObject) : 
	m_Value{jsonObject}
{
	Initialize();
}

Horizon::GameObject* SpriteObject::GetGameObject() const
{
	return m_pGameObject;
}

void SpriteObject::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const float scale = m_Value["scale"].GetFloat();
	const int srcPosX = m_Value["srcPosX"].GetInt();
	const int srcPosY = m_Value["srcPosY"].GetInt();
	const int srcWidth = m_Value["srcWidth"].GetInt();
	const int srcHeight = m_Value["srcHeight"].GetInt();
	const int spriteAmount = m_Value["spriteAmount"].GetInt();
	const float spriteLenght = m_Value["spriteLength"].GetFloat();

	m_pGameObject = new GameObject();
	TransformComponent* const pSpriteTransform = new TransformComponent(m_pGameObject, positionX, positionY);
	SpriteComponent* const pSpriteComponent = new SpriteComponent(m_pGameObject, "QBertTextures.png", { srcPosX,srcPosY,srcWidth,srcHeight }, spriteAmount);
	TimedFunctionComponent* const pTimedFunction = new TimedFunctionComponent(m_pGameObject, true, spriteLenght);
	pTimedFunction->SetTimerFunction([pSpriteComponent](float) {pSpriteComponent->NextSprite(); });
	pTimedFunction->Activate(),

	pSpriteComponent->Scale(scale);
	m_pGameObject->AddComponent(pSpriteTransform);
	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(pTimedFunction);
}
