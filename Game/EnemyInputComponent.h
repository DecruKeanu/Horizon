#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TimedFunctionComponent;
}

class EnemyMovementComponent;
class GameSpriteComponent;

class EnemyInputComponent final : public Horizon::Component
{
public:
	EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection);
private:
	void Initialize() override;

	int m_StepsTaken;
	bool m_CanMoveBeUpdated;
	Horizon::IPoint2 m_MovementDirection;
	Horizon::IPoint2 m_Move;

	EnemyMovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
};

