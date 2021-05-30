#include "Cube.h"
#include "GamePCH.h"
#include "Cube.h"
#include "SceneManager.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <Scene.h>

using namespace dae;

Cube::Cube(const rapidjson::Value& jsonObject) :
	m_Value{ jsonObject },
	m_InitCubeColor{},
	m_SrcPositions{ IPoint2{240,224},{240,192}, {0,160},{0,192},{0,224},{80,192},{80,160} }
{
	Initialize();
}

void Cube::Initialize()
{
	const int srcWidth = 32;
	const int srcHeight = 32;
	const int positionX = m_Value["positionX"].GetInt();
	const int positionY = m_Value["positionY"].GetInt();
	SetInitCubeColor(m_Value["color"].GetString());
	const IPoint2 leftBottomSrcPos = m_SrcPositions[static_cast<int>(m_InitCubeColor)];

	GameObject* const pGameObject = new GameObject();

	TextureComponent* const blockTexture = new TextureComponent(pGameObject, "QBertTextures.png");
	blockTexture->SetSrcRect(leftBottomSrcPos.x, leftBottomSrcPos.y, srcWidth, srcHeight);
	blockTexture->SetScale(2.f);
	TransformComponent* const blockTransform = new TransformComponent(pGameObject, positionX, positionY, 0);

	pGameObject->AddComponent(blockTexture);
	pGameObject->AddComponent(blockTransform);

	SetGameObject(pGameObject);
}

void Cube::SetInitCubeColor(const std::string& color)
{
	if (color == "level1Purple")
		m_InitCubeColor = CubeColor::level1Purple;
	else if (color == "level1Blue")
		m_InitCubeColor = CubeColor::level1Blue;
	else if (color == "level2Pink")
		m_InitCubeColor = CubeColor::level2Pink;
	else if (color == "level2Yellow")
		m_InitCubeColor = CubeColor::level2Yellow;
	else if (color == "level2Blue")
		m_InitCubeColor = CubeColor::level2Blue;
	else if (color == "level3Mellow")
		m_InitCubeColor = CubeColor::level3Mellow;
	else if (color == "level3Blue")
		m_InitCubeColor = CubeColor::level3Blue;
	else
		Logger::LogWarning("Cube::SetInitCubeColor: m_CurrentColor could not be set, invalid string. Default value is used, level1Purple");
}



