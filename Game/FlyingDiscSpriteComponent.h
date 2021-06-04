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
	FlyingDiscSpriteComponent(Horizon::GameObject* pParent,const std::string& textureName, const SDL_Rect& srcRect);
private:
	void InitializeTimedFunction();

	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;
};

