#include "Cube.h"
#include "SceneManager.h"
#include <GameObject.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <Scene.h>

using namespace dae;

Cube::Cube(CubeColor color):
	m_CurrentCubeColor{color}
{
	const int srcWidth = 32;
	const int srcHeight = 32;
	const glm::vec2 leftBottomSrcPos = m_SrcPositions[static_cast<int>(m_CurrentCubeColor)];

	m_pGameObject = new dae::GameObject();
	TextureComponent* const blockTexture = new dae::TextureComponent(m_pGameObject, "QBertTextures.png");
	blockTexture->SetSrcRect(int(leftBottomSrcPos.x), int(leftBottomSrcPos.y), srcWidth, srcHeight);
	blockTexture->SetScale(4.f);
	TransformComponent* const blockTransform = new dae::TransformComponent(m_pGameObject, 230 - 128 / 2, 80, 0);

	m_pGameObject->AddComponent(blockTexture);
	m_pGameObject->AddComponent(blockTransform);
}

GameObject* Cube::GetGameObject()
{
	return m_pGameObject;
}
