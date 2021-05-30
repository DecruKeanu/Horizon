#include "GamePCH.h"
#include "QBert.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
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
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();

	GameObject* const pGameObject = new GameObject();

	TextureComponent* const QBertTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	QBertTexture->SetSrcRect(0, 0, srcWidth, srcHeight);
	QBertTexture->SetScale(2.f);
	TransformComponent* const QBertTransform = new TransformComponent(pGameObject, positionX, positionY, 0);

	pGameObject->AddComponent(QBertTexture);
	pGameObject->AddComponent(QBertTransform);

	SetGameObject(pGameObject);
}
