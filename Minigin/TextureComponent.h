#pragma once
#include "Component.h"

namespace dae
{
	class Texture2D;
	class TransformComponent;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* parent, const std::string textureFile);
		void Initialize() override;
		void Render() const;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		TransformComponent* m_pTransformComponent = nullptr;
	};
}