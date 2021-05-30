#pragma once
#include "Prefab.h"
#include "document.h"

namespace dae
{
	class GameObject;
	class TextureComponent;
	class TransformComponent;
}

class QBert final : public dae::Prefab
{
public:
	QBert(const rapidjson::Value& jsonObject);
private:
	void Initialize();

	const rapidjson::Value& m_Value;
	dae::TextureComponent* m_pTextureComponent = nullptr;
	dae::TransformComponent* m_pTransformComponent = nullptr;
};

