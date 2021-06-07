#include "GamePCH.h"
#include "ScoreDisplayObject.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <ScoreComponent.h>
#include <TransformComponent.h>
#include <ScoreDisplayComponent.h>

#include <ResourceManager.h>

ScoreDisplayObject::ScoreDisplayObject(const rapidjson::Value& jsonObject) : 
	m_Value{jsonObject}
{
	InitializePrefab();
}

Horizon::GameObject* ScoreDisplayObject::GetGameObject() const
{
	return m_pGameObject;
}

void ScoreDisplayObject::InitializePrefab()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const int fontSize = m_Value["fontSize"].GetInt();
	const unsigned int R = m_Value["R"].GetUint();
	const unsigned int G = m_Value["G"].GetUint();
	const unsigned int B = m_Value["B"].GetUint();
	const auto font = Horizon::ResourceManager::GetInstance().LoadFont("QBert.ttf", fontSize);

	m_pGameObject = new Horizon::GameObject("ScoreDisplayObject");
	Horizon::TransformComponent* const pTextTransform = new Horizon::TransformComponent(m_pGameObject, positionX, positionY);
	Horizon::TextComponent* const pTextComponent = new Horizon::TextComponent(m_pGameObject, "", font, { UINT8(R),UINT8(G),UINT8(B) });
	Horizon::ScoreDisplayComponent* const pScoreDisplayComponent = new Horizon::ScoreDisplayComponent(m_pGameObject);

	m_pGameObject->AddComponent(pTextTransform);
	m_pGameObject->AddComponent(pTextComponent);
	m_pGameObject->AddComponent(pScoreDisplayComponent);
}
