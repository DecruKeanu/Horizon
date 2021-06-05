#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}

class EnemyInputComponent;


class EnemySpriteComponent final : public Horizon::Component
{
public:
	EnemySpriteComponent(Horizon::GameObject* pParent, const std::string& fileName, const SDL_Rect& srcRect, int spriteAmount);

	void SetMove(const Horizon::IPoint2& input);
	void SetSrcRect(const SDL_Rect& srcRect);
	void SetSpriteAmount(const int spriteAmount);
	void SetSpriteOffset(const Horizon::IPoint2& offset);
private:
	void Initialize() override;
	void Update() override;

	int m_SpriteAmount;
	int m_CurrentSpriteNumber;
	Horizon::IPoint2 m_Move;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
	EnemyInputComponent* m_pInputComponent = nullptr;
};

