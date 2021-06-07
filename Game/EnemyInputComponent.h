#pragma once
#include <Component.h>

class MovementComponent;
class GameSpriteComponent;


namespace Horizon
{
	class GameObject;
	class TriggerComponent;
}

class EnemyInputComponent final : public Horizon::Component
{
public:
	EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection);
private:
	//Component functions
	void Initialize() override;

	//Helper functions
	void InitializeMovementTimedFunction();
	void InitializeTilesEncounteredTimedFunction();

	//Components
	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_MovementDirection;
	Horizon::IPoint2 m_Move;

	int m_StepsTaken;
	bool m_CanMoveBeUpdated;
	bool m_TilesEncountered;
};

