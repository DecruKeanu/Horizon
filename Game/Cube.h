#pragma once
#include <array>
#include "document.h"
#include "Prefab.h"

namespace dae
{
	class GameObject;
	class TextureComponent;
	class TransformComponent;
}


class Cube final : public dae::Prefab
{
public:
	Cube(const rapidjson::Value& jsonObject);

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
private:
	void Initialize();
	void SetInitCubeColor(const std::string& color);
	const rapidjson::Value& m_Value;
	CubeColor m_InitCubeColor;

	dae::TextureComponent* m_pTextureComponent = nullptr;
	dae::TransformComponent* m_pTransformComponent = nullptr;

	const std::array<IPoint2, int(CubeColor::enumSize)> m_SrcPositions;
};

