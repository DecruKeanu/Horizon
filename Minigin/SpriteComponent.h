#pragma once
#include "Component.h"

namespace Horizon
{
	class GameObject;
	class TextureComponent;


	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(GameObject* parent, SDL_Rect srcRect, int spriteAmount);
		int GetCurrentSprite();
		void SetCurrentSprite(int spriteNumber);
		void NextSprite();
		void PreviousSprite();
	private:
		void Initialize() override;

		TextureComponent* m_pTextureComponent = nullptr;
		SDL_Rect m_SrcRect;
		int m_CurrentSprite;
		int m_SpriteAmount;
		int m_SpriteWidth;

	};
}

