#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
	class TimedFunction;
}


class FlyingDiscSpriteComponent final : public Horizon::Component
{
public:
	FlyingDiscSpriteComponent(Horizon::GameObject* pParent,const std::string& textureName, const SDL_Rect& srcRect);
	~FlyingDiscSpriteComponent();
private:
	void Initialize() override;

	float m_SpriteTimer;
	int m_CurrentSpriteNumber;

	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
	Horizon::TimedFunction* m_pTimedFunction = nullptr;
};

