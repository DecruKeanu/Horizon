#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TimedFunction;
}

class EnemyInputComponent final : public Horizon::Component
{
public:
	EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection);
	~EnemyInputComponent();

	const Horizon::IPoint2& GetMove();

	void DisableMovement();
	void EnableMovement();
private:
	void Initialize() override;

	int m_Moves;
	bool m_CanMoveBeUpdated;
	Horizon::IPoint2 m_MovementDirection;
	Horizon::IPoint2 m_Move;
	Horizon::TimedFunction* m_pTimedFunction = nullptr;
};

