#include "GamePCH.h"
#include "ScoreDisplayObject.h"
#include <GameObject.h>

#include <SceneManager.h>
#include <Scene.h>
#include <ResourceManager.h>
#include <TransformComponent.h>
#include <TextComponent.h>
#include <TimedFunctionComponent.h>

#include <ScoreDisplayComponent.h>
#include <ScoreDisplayObserver.h>
#include <ScoreComponent.h>

using namespace Horizon;

ScoreDisplayObject::ScoreDisplayObject(const rapidjson::Value& jsonObject) : 
	m_Value{jsonObject}
{
	Initialize();
}

Horizon::GameObject* ScoreDisplayObject::GetGameObject() const
{
	return m_pGameObject;
}

void ScoreDisplayObject::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const int fontSize = m_Value["fontSize"].GetInt();
	const unsigned int R = m_Value["R"].GetUint();
	const unsigned int G = m_Value["G"].GetUint();
	const unsigned int B = m_Value["B"].GetUint();
	const auto font = ResourceManager::GetInstance().LoadFont("QBert.ttf", fontSize);

	m_pGameObject = new GameObject("ScoreDisplayObject");
	TransformComponent* const pTextTransform = new TransformComponent(m_pGameObject, positionX, positionY);
	TextComponent* const pTextComponent = new TextComponent(m_pGameObject, "", font, { UINT8(R),UINT8(G),UINT8(B) });
	ScoreDisplayComponent* const pScoreDisplayComponent = new ScoreDisplayComponent(m_pGameObject);


	m_pGameObject->AddComponent(pTextTransform);
	m_pGameObject->AddComponent(pTextComponent);
	m_pGameObject->AddComponent(pScoreDisplayComponent);

	//SceneManager::GetInstance().GetActiveScene()->GetGameObject(parent)->GetComponent<ScoreComponent>()->AddObserver(new ScoreDisplayObserver(pScoreDisplayComponent));

	//const auto QBertFont24 = ResourceManager::GetInstance().LoadFont("QBert.ttf", 24);
	//{
	//	GameObject* const QBertScoreDisplay = new GameObject();
	//	TransformComponent* const QBertScoreTransform = new TransformComponent(QBertScoreDisplay, 20, 50);


	//	TextComponent* const QBertScoreText = new TextComponent(QBertScoreDisplay, "", QBertFont24, { 255, 140, 0 });

	//	ScoreDisplayComponent* const QBertScoreDisplayComponent = new ScoreDisplayComponent(QBertScoreDisplay);


	//	QBertScoreDisplay->AddComponent(QBertScoreTransform);
	//	QBertScoreDisplay->AddComponent(QBertScoreText);
	//	QBertScoreDisplay->AddComponent(QBertScoreDisplayComponent);

	//	GetGameObject("Qbert")->GetComponent<ScoreComponent>()->AddObserver(new ScoreDisplayObserver(QBertScoreDisplayComponent));
	//	Add(QBertScoreDisplay);

	//	GetGameObject("Qbert")->GetComponent<ScoreComponent>()->IncreaseScore(m_PlayerScore);
	//}
}
