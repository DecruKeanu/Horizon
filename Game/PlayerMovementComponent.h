#pragma once
#include "Component.h"
namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class TriggerComponent;
}
class PlayerInputComponent;

class PlayerMovementComponent final : public Horizon::Component
{
public:
	PlayerMovementComponent(Horizon::GameObject* parent);
private:
	void Initialize() override;
	void Update() override;

	float m_ElapsedTime;
	Horizon::IPoint2 m_OriginalPoint;

	PlayerInputComponent* m_pQBertInputComponent = nullptr;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
};

