#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TimedFunctionComponent;
	class TriggerComponent;
}

class MovementComponent;
class GameSpriteComponent;

class EnemyInputComponent final : public Horizon::Component
{
public:
	EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection);
private:
	void Initialize() override;
	void Update();

	int m_StepsTaken;
	float m_ElapsedTime;
	bool m_MinimumStepsReached;
	bool m_TilesEncountered;
	bool m_CanMoveBeUpdated;
	Horizon::IPoint2 m_MovementDirection;
	Horizon::IPoint2 m_Move;

	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::TimedFunctionComponent* m_pTimedFunction2 = nullptr;
};

