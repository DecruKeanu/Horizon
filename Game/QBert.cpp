#include "GamePCH.h"
#include "QBert.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include "QBertMovementComponent.h"
#include <Scene.h>

using namespace dae;

QBert::QBert(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

void QBert::Initialize()
{
	const int srcWidth = 16;
	const int srcHeight = 16;
	const int positionX = m_Value["positionX"].GetInt() + srcWidth;
	const int positionY = m_Value["positionY"].GetInt() - srcHeight;

	GameObject* const pGameObject = new GameObject();

	TextureComponent* const QBertTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	QBertTexture->SetSrcRect(0, 0, srcWidth, srcHeight);
	QBertTexture->SetScale(2.f);
	TransformComponent* const QBertTransform = new TransformComponent(pGameObject, positionX, positionY, 0);

	QBertMovementComponent* const pMovementComponent = new QBertMovementComponent(pGameObject);

	pGameObject->AddComponent(QBertTexture);
	pGameObject->AddComponent(QBertTransform);
	pGameObject->AddComponent(pMovementComponent);

	SetGameObject(pGameObject);
}
