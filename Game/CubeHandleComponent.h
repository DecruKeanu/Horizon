#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class SpriteComponent;
}


class CubeHandleComponent : public Horizon::Component
{
public:
	CubeHandleComponent(Horizon::GameObject* parent);
private:
	void Initialize() override;
	void ActivateCube();
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	bool m_IsActivated;
};

