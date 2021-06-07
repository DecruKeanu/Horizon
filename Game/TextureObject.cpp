#include "GamePCH.h"
#include "TextureObject.h"

#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>

TextureObject::TextureObject(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	InitializePrefab();
}

Horizon::GameObject* TextureObject::GetGameObject() const
{
	return m_pGameObject;
}

void TextureObject::InitializePrefab()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();

	const int srcPosX = m_Value["srcPosX"].GetInt();
	const int srcPosY = m_Value["srcPosY"].GetInt();
	const int srcWidth = m_Value["srcWidth"].GetInt();
	const int srcHeight = m_Value["srcHeight"].GetInt();

	const float scale = m_Value["scale"].GetFloat();

	m_pGameObject = new Horizon::GameObject();
	Horizon::TransformComponent* const pTextureTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TextureComponent* const pTextureComponent = new Horizon::TextureComponent(m_pGameObject, "QBertTextures.png");

	pTextureComponent->SetScale(scale);
	pTextureComponent->SetSrcRect(srcPosX, srcPosY, srcWidth, srcHeight);

	m_pGameObject->AddComponent(pTextureTransform);
	m_pGameObject->AddComponent(pTextureComponent);
}
