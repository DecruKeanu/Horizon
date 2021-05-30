#pragma once
#include "Component.h"

namespace dae
{
	class GameObject;
	class TextureComponent;


	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(GameObject* parent, SDL_Rect srcRect, int spriteAmount);
		int GetCurrentSprite();
		void SetCurrentSprite(int spriteNumber);
	private:
		void Initialize() override;

		dae::TextureComponent* m_pTextureComponent = nullptr;
		SDL_Rect m_SrcRect;
		int m_CurrentSprite;
		int m_SpriteAmount;
		int m_SpriteWidth;

	};
}

