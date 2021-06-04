#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TimedFunctionComponent;
}

class EnemyInputComponent final : public Horizon::Component
{
public:
	EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection);

	const Horizon::IPoint2& GetMove();

	void DisableMovement();
	void EnableMovement();

	int GetStepsTaken() const;
private:
	void Initialize() override;

	int m_StepsTaken;
	bool m_CanMoveBeUpdated;
	Horizon::IPoint2 m_MovementDirection;
	Horizon::IPoint2 m_Move;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
};

