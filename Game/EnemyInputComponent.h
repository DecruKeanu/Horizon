#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
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

	//Helper functions
	void InitializeMovementTimedFunction();
	void InitializeTilesEncounteredTimedFunction();

	//Components
	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;

	//Movement
	Horizon::IPoint2 m_MovementDirection;
	Horizon::IPoint2 m_Move;
	bool m_CanMoveBeUpdated;
	
	//Tiles
	int m_StepsTaken;
	bool m_TilesEncountered;
};

