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

	//Public helper functions
	void Activate();
private:
	//Component functions
	void Initialize() override;
	void Update() override;

	//Components
	Horizon::TransformComponent* m_pTransformComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_OriginalPos;

	float m_ElapsedTime;
	bool m_IsActive;
};

