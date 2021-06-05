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

	void PlayerOnFlyingDisc(Horizon::TransformComponent* pFlyingDiscTransformComponent);
private:
	void Initialize() override;
	void Update() override;
	void PlayerOnFlyingDisc();
	void FallingOfFlyingDisc();

	float m_ElapsedTime;
	Horizon::IPoint2 m_OriginalPoint;

	bool m_IsPlayerOnFlyingDisc;
	bool m_IsFallingOfFlyingDisc;

	PlayerInputComponent* m_pMovementComponent = nullptr;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;

	Horizon::TransformComponent* m_pFlyingDiscTransformComponent = nullptr;
};

