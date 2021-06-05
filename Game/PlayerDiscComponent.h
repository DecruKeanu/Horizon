#pragma once
#include <Component.h>

namespace Horizon
{
	class Gameobject;
	class TransformComponent;
}

class MovementComponent;
class PlayerInputComponent;

class PlayerDiscComponent final : public Horizon::Component
{
public:
	PlayerDiscComponent(Horizon::GameObject* pGameObject);

	void PlayerOnDisc(Horizon::TransformComponent* pFlyingDiscTransformComponent);
private:
	void Initialize() override;
	void Update() override;

	void PlayerStandingOnDisc();
	void PlayerFallingOfDisc();

	Horizon::IPoint2 m_OriginalPoint;
	float m_ElapsedTime;
	bool m_IsPlayerOnFlyingDisc;
	bool m_IsFallingOfFlyingDisc;

	PlayerInputComponent* m_pPlayerInputComponent = nullptr;

	MovementComponent* m_pPlayerMovementComponent = nullptr;
	Horizon::TransformComponent* m_pPlayerTransformComponent = nullptr;
	Horizon::TransformComponent* m_pFlyingDiscTransformComponent = nullptr;
};

