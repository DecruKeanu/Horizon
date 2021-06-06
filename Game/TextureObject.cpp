#include "GamePCH.h"
#include "TextureObject.h"
#include <GameObject.h>
#include <TransformComponent.h>
#include <TextureComponent.h>
#include <TimedFunctionComponent.h>

using namespace Horizon;

TextureObject::TextureObject(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

Horizon::GameObject* TextureObject::GetGameObject() const
{
	return m_pGameObject;
}

void TextureObject::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const float scale = m_Value["scale"].GetFloat();
	const int srcPosX = m_Value["srcPosX"].GetInt();
	const int srcPosY = m_Value["srcPosY"].GetInt();
	const int srcWidth = m_Value["srcWidth"].GetInt();
	const int srcHeight = m_Value["srcHeight"].GetInt();


	m_pGameObject = new GameObject();
	TransformComponent* const pTextureTransform = new TransformComponent(m_pGameObject, positionX, positionY);
	TextureComponent* const pTextureComponent = new TextureComponent(m_pGameObject, "QBertTextures.png");

	pTextureComponent->SetScale(scale);
	pTextureComponent->SetSrcRect(srcPosX, srcPosY, srcWidth, srcHeight);
	m_pGameObject->AddComponent(pTextureTransform);
	m_pGameObject->AddComponent(pTextureComponent);
}
