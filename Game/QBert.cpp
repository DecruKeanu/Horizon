#include "GamePCH.h"
#include "QBert.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include "QBertMovementComponent.h"
#include "SpriteComponent.h"
#include <Scene.h>

using namespace Horizon;

QBert::QBert(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	//SetPrefabName("QBert");
	Initialize();
}

GameObject* QBert::GetGameObject() const
{
	return m_pGameObject;
}

void QBert::Initialize()
{
	const int srcWidth = 15;
	const int srcHeight = 15;
	const int positionX = m_Value["positionX"].GetInt() + srcWidth;
	const int positionY = m_Value["positionY"].GetInt() - srcHeight;

	GameObject* const pGameObject = new GameObject();

	TextureComponent* const QBertTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	SpriteComponent* const pSpriteComponent = new SpriteComponent(pGameObject, SDL_Rect{ 0, 0, srcWidth * 8, srcHeight}, 8);
	QBertTexture->SetScale(2.f);
	TransformComponent* const QBertTransform = new TransformComponent(pGameObject, positionX, positionY, 0);

	QBertMovementComponent* const pMovementComponent = new QBertMovementComponent(pGameObject);


	pGameObject->AddComponent(QBertTexture);
	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(QBertTransform);
	pGameObject->AddComponent(pMovementComponent);

	m_pGameObject = pGameObject;

	//SetGameObject(pGameObject);
}
