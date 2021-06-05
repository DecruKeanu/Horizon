#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <SDL.h>
namespace Horizon
{
	class Texture2D;
	class TransformComponent;
	class TextureComponent final : public Component
	{
	public:
		TextureComponent(GameObject* parent, const std::string textureFile);
		void Initialize() override;
		void Render() const;

		void SetSrcRect(int x, int y, int width, int height);
		void SetScale(float scale);

		void SetTextureOffset(const IPoint2& offset);
	private:
		std::shared_ptr<Texture2D> m_pTexture;
		TransformComponent* m_pTransformComponent = nullptr;
		SDL_Rect m_SrcRect;
		float m_Scale;

		IPoint2 m_TextureOffset;
	};
}