#pragma once
#include "Component.h"

namespace Horizon
{
	class GameObject;
	class TextureComponent;


	class SpriteComponent final : public Component
	{
	public:
		SpriteComponent(GameObject* parent, const std::string& fileName, const SDL_Rect& srcRect, int spriteAmount);
		int GetCurrentSprite();
		void SetCurrentSprite(int spriteNumber);
		void NextSprite();
		void PreviousSprite();

		void Scale(float scale);
		void SetSrcRect(const SDL_Rect& srcRect);
		void SetSpriteAmount(const int spirteAmount);
		void SetSpriteOffset(const IPoint2 offset);
	private:
		void Initialize() override;

		TextureComponent* m_pTextureComponent = nullptr;
		SDL_Rect m_SrcRect;
		int m_CurrentSprite;
		int m_SpriteAmount;
		int m_SpriteWidth;
	};
}

