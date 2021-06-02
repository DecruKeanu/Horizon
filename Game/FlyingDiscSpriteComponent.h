#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}


class FlyingDiscSpriteComponent final : public Horizon::Component
{
public:
	FlyingDiscSpriteComponent(Horizon::GameObject* pParent, const SDL_Rect& srcRect);
private:
	void ConstructTimedFunction();

	float m_SpriteTimer;
	int m_CurrentSpriteNumber;

	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
};

