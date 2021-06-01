#include "GamePCH.h"
#include "Cube.h"
#include "Cube.h"
#include "SceneManager.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <SpriteComponent.h>
#include "CubeHandleComponent.h"
#include <Scene.h>

using namespace Horizon;

Cube::Cube(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	//SetPrefabName("Cube");
	Initialize();
}

GameObject* Cube::GetGameObject() const
{
	return m_pGameObject;
}

void Cube::Initialize()
{
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const SDL_Rect srcRect = LevelNumberToSrcRect(m_Value["level"].GetInt());

	GameObject* const pGameObject = new GameObject();

	CubeHandleComponent* const pHandleCubeComponent = new CubeHandleComponent(pGameObject);
	TextureComponent* const blockTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	blockTexture->SetScale(2.f);
	SpriteComponent* const pSpriteComponent = new SpriteComponent(pGameObject, srcRect, 7);
	TransformComponent* const blockTransform = new TransformComponent(pGameObject, positionX, positionY, 0);

	pGameObject->AddComponent(pHandleCubeComponent);
	pGameObject->AddComponent(blockTexture);
	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(blockTransform);

	//SetGameObject(pGameObject);
	m_pGameObject = pGameObject;
}

SDL_Rect Cube::LevelNumberToSrcRect(const int levelNumber)
{
	int posX = 0;
	const int posY = 164;
	const int width = 222;
	const int height = 32;

	switch (levelNumber)
	{
	case 1:
		posX = 0;
		break;
	case 2:
		posX = 64; 
		break;
	case 3:
		posX = 160;
		break;
	default:
		Logger::LogWarning("LevelNumberToSrcRect >> invalid levelNumber. Default value is used, 1"); 
		break;
	}

	return SDL_Rect{ posX,posY,width,height };
}



