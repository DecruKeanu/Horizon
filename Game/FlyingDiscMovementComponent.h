#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
}

class FlyingDiscMovementComponent final : public Horizon::Component
{
public:
	FlyingDiscMovementComponent(Horizon::GameObject* pParent);
	void Activate();
	void Deactivate();
private:
	void Initialize() override;
	void Update() override;

	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::IPoint2 m_OriginalPos;

	float m_ElapsedTime;
	int m_Turns;
	bool m_IsActive;
};

