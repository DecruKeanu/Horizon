#include "GamePCH.h"
#include "Cube.h"
#include "Cube.h"
#include "SceneManager.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <SpriteComponent.h>
#include <Scene.h>

using namespace Horizon;

Cube::Cube(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject }
{
	Initialize();
}

void Cube::Initialize()
{
	const int srcWidth = 32;
	const int srcHeight = 32;
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	const SDL_Rect srcRect = LevelNumberToSrcRect(m_Value["level"].GetInt());

	GameObject* const pGameObject = new GameObject();

	TextureComponent* const blockTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	//blockTexture->SetSrcRect(leftBottomSrcPos.x, leftBottomSrcPos.y, srcWidth, srcHeight);
	blockTexture->SetScale(2.f);
	SpriteComponent* const pSpriteComponent = new SpriteComponent(pGameObject, srcRect, 7);

	TransformComponent* const blockTransform = new TransformComponent(pGameObject, positionX, positionY, 0);

	pGameObject->AddComponent(blockTexture);
	pGameObject->AddComponent(pSpriteComponent);
	pGameObject->AddComponent(blockTransform);

	SetGameObject(pGameObject);
}

SDL_Rect Cube::LevelNumberToSrcRect(const int levelNumber)
{
	int posX = 0;
	const int posY = 164;
	const int width = 221;
	const int height = 32;


	if (levelNumber == 1)
		posX = 0;
	else if (levelNumber == 2)
		posX = 64;
	else if (levelNumber == 3)
		posX = 160;
	else
		Logger::LogWarning("LevelNumberToSrcRect >> invalid levelNumber. Default value is used, 1");

	return SDL_Rect{ posX,posY,width,height };
}



