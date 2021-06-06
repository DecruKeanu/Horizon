#include "GamePCH.h"
#include "TextObject.h"
#include <GameObject.h>

#include <ResourceManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <TimedFunctionComponent.h>

using namespace Horizon;

TextObject::TextObject(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

Horizon::GameObject* TextObject::GetGameObject() const
{
	return m_pGameObject;
}

void TextObject::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const std::string text = m_Value["text"].GetString();
	const int fontSize = m_Value["fontSize"].GetInt();
	const unsigned int R = m_Value["R"].GetUint();
	const unsigned int G = m_Value["G"].GetUint();
	const unsigned int B = m_Value["B"].GetUint();
	const auto font = ResourceManager::GetInstance().LoadFont("QBert.ttf", fontSize);

	m_pGameObject = new GameObject();
	TransformComponent* const pTextTransform = new TransformComponent(m_pGameObject, positionX, positionY);
	TextComponent* const pTextComponent = new TextComponent(m_pGameObject, text, font, {UINT8(R),UINT8(G),UINT8(B)});
	m_pGameObject->AddComponent(pTextTransform);
	m_pGameObject->AddComponent(pTextComponent);
}
