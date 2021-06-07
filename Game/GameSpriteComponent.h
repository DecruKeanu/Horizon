#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}

class GameSpriteComponent final : public Horizon::Component
{
public:
	GameSpriteComponent(Horizon::GameObject* pParent, const std::string& fileName, const SDL_Rect& srcRect, int spriteAmount);

	//Setters
	void SetMove(const Horizon::IPoint2& input);
	void SetSrcRect(const SDL_Rect& srcRect);
	void SetSpriteOffset(const Horizon::IPoint2& offset);
private:
	//Component functions
	void Initialize() override;
	void Update() override;

	//Components
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_Move;

	int m_SpriteAmount;
	int m_CurrentSpriteNumber;
};