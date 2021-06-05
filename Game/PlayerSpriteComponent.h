#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}

class PlayerInputComponent;

class PlayerSpriteComponent final : public Horizon::Component
{
public:
	PlayerSpriteComponent(Horizon::GameObject* pParent, const std::string& fileName, const SDL_Rect& srcRect);
private:
	void Initialize() override;
	void Update() override;

	int m_CurrentSpriteNumber;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
	PlayerInputComponent* m_pInputComponent = nullptr;
};
