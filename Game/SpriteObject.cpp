#include "GamePCH.h"
#include "SpriteObject.h"

#include <GameObject.h>
#include <SpriteComponent.h>
#include <TransformComponent.h>
#include <TimedFunctionComponent.h>

SpriteObject::SpriteObject(const rapidjson::Value& jsonObject) : 
	m_Value{jsonObject}
{
	InitializePrefab();
}

Horizon::GameObject* SpriteObject::GetGameObject() const
{
	return m_pGameObject;
}

void SpriteObject::InitializePrefab()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();

	const int srcPosX = m_Value["srcPosX"].GetInt();
	const int srcPosY = m_Value["srcPosY"].GetInt();
	const int srcWidth = m_Value["srcWidth"].GetInt();
	const int srcHeight = m_Value["srcHeight"].GetInt();

	const int spriteAmount = m_Value["spriteAmount"].GetInt();
	const float spriteLenght = m_Value["spriteLength"].GetFloat();

	const float scale = m_Value["scale"].GetFloat();

	m_pGameObject = new Horizon::GameObject();
	Horizon::TransformComponent* const pSpriteTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TimedFunctionComponent* const pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, spriteLenght);
	Horizon::SpriteComponent* const pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, "QBertTextures.png", { srcPosX,srcPosY,srcWidth,srcHeight }, spriteAmount);

	pTimedFunction->SetTimerFunction([pSpriteComponent](float) {pSpriteComponent->NextSprite(); });
	pTimedFunction->Activate();
	pSpriteComponent->Scale(scale);

	m_pGameObject->AddComponent(pSpriteTransform);
	m_pGameObject->AddComponent(pSpriteComponent);
	m_pGameObject->AddComponent(pTimedFunction);
}
