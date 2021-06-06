#include "GamePCH.h"
#include "HealthDisplayObject.h"
#include <GameObject.h>

#include <SceneManager.h>
#include <Scene.h>
#include <ResourceManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <TimedFunctionComponent.h>

#include <HealthDisplayComponent.h>
#include <HealthDisplayObserver.h>
#include <HealthComponent.h>

using namespace Horizon;

HealthDisplayObject::HealthDisplayObject(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

Horizon::GameObject* HealthDisplayObject::GetGameObject() const
{
	return m_pGameObject;
}

void HealthDisplayObject::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const int fontSize = m_Value["fontSize"].GetInt();
	const unsigned int R = m_Value["R"].GetUint();
	const unsigned int G = m_Value["G"].GetUint();
	const unsigned int B = m_Value["B"].GetUint();
	const auto font = ResourceManager::GetInstance().LoadFont("QBert.ttf", fontSize);

	m_pGameObject = new GameObject("HealthDisplayObject");
	TransformComponent* const pTextTransform = new TransformComponent(m_pGameObject, positionX, positionY);
	TextComponent* const pTextComponent = new TextComponent(m_pGameObject, "", font, { UINT8(R),UINT8(G),UINT8(B) });
	HealthDisplayComponent* const pScoreDisplayComponent = new HealthDisplayComponent(m_pGameObject, 0);

	m_pGameObject->AddComponent(pTextTransform);
	m_pGameObject->AddComponent(pTextComponent);
	m_pGameObject->AddComponent(pScoreDisplayComponent);
}
