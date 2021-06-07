#pragma once
#include <Component.h>

class MovementComponent;
class PlayerInputComponent;

namespace Horizon
{
	class Gameobject;
	class TransformComponent;
}

class PlayerDiscComponent final : public Horizon::Component
{
public:
	PlayerDiscComponent(Horizon::GameObject* pGameObject);

	//Public helper functions
	void PlayerOnDisc(Horizon::TransformComponent* pFlyingDiscTransformComponent);

	//Getters
	bool PlayerOnDisc() const;
private:
	//Component functions
	void Initialize() override;
	void Update() override;

	//Helper functions
	void PlayerStandingOnDisc();
	void PlayerFallingOfDisc();

	//Components
	PlayerInputComponent* m_pPlayerInputComponent = nullptr;
	MovementComponent* m_pPlayerMovementComponent = nullptr;
	Horizon::TransformComponent* m_pPlayerTransformComponent = nullptr;
	Horizon::TransformComponent* m_pFlyingDiscTransformComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_OriginalPoint;

	float m_ElapsedTime;
	bool m_IsPlayerOnFlyingDisc;
	bool m_IsFallingOfFlyingDisc;
};

