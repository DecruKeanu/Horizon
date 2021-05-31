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
	const SDL_Rect srcRect = ColorToSrcRect(m_Value["color"].GetString());

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

SDL_Rect Cube::ColorToSrcRect(const std::string& color)
{
	int posX = 0;
	const int posY = 164;
	const int width = 221;
	const int height = 32;


	if (color == "level1Purple")
		posX = 0;
	//else if (color == "level1Blue")
	//	m_InitCubeColor = CubeColor::level1Blue;
	else if (color == "level2Pink")
		posX = 64;
	//else if (color == "level2Yellow")
	//	m_InitCubeColor = CubeColor::level2Yellow;
	//else if (color == "level2Blue")
	//	m_InitCubeColor = CubeColor::level2Blue;
	else if (color == "level3Mellow")
		posX = 160;
	//else if (color == "level3Blue")
	//	m_InitCubeColor = CubeColor::level3Blue;
	else
		Logger::LogWarning("ColorToSrcRect >> invalid string. Default value is used, level1Purple");

	return SDL_Rect{ posX,posY,width,height };
}



