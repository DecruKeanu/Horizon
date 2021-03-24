#pragma once
#include "ObjectComponent.h"

namespace dae
{
	class Texture2D;
	class TransformComponent;
	class TextureComponent final : public ObjectComponent
	{
	public:
		TextureComponent(GameObject* parent, const std::string textureFile);
		void BeginPlay();
		void Render() const;
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		TransformComponent* m_pTransformComponent = nullptr;
	};
}