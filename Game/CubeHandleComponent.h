#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class SpriteComponent;
}


class CubeHandleComponent : public Horizon::Component
{
public:
	CubeHandleComponent(Horizon::GameObject* parent);
	void ActivateCube(const Horizon::IPoint2 playerPos);
private:
	void Initialize() override;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::SpriteComponent* m_pSpriteComponent = nullptr;

	bool m_IsActivated;
};

