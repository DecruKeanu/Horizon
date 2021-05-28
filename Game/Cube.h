#pragma once
#pragma warning (disable:4201)
#include <array>
#include <glm/vec2.hpp>

namespace dae
{
	class GameObject;
	class TextureComponent;
	class TransformComponent;
}


class Cube final
{
public:
	enum class CubeColor : int
	{
		level1Purple,
		level1Blue,
		level2Pink,
		level2Yellow,
		level2Blue,
		level3Mellow,
		level3Blue,
		enumSize
	};

	Cube(CubeColor color);
	dae::GameObject* GetGameObject();
private:
	CubeColor m_CurrentCubeColor;

	dae::GameObject* m_pGameObject = nullptr;
	dae::TextureComponent* m_pTextureComponent = nullptr;
	dae::TransformComponent* m_pTransformComponent = nullptr;

	const std::array<glm::vec2, int(CubeColor::enumSize)> m_SrcPositions{ glm::vec2{240,224},glm::vec2{240,192}, glm::vec2{0,160},glm::vec2{0,192},glm::vec2{0,224},glm::vec2{80,192},glm::vec2{80,160} };
};

