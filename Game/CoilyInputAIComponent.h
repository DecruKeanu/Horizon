#pragma once
#include <Component.h>

class MovementComponent;
class GameSpriteComponent;

namespace Horizon
{
	class GameObject;
	class ScoreComponent;
	class TransformComponent;
	class TriggerComponent;
}

class CoilyInputAIComponent final : public Horizon::Component
{
public:
	CoilyInputAIComponent(Horizon::GameObject* pParent);
private:
	//Component functions
	void Initialize() override;

	//Helper functions
	void InitializeControllerTimedFunction();

	//Components
	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;
	MovementComponent* m_pQbertMovementComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	Horizon::ScoreComponent* m_pQbertScoreComponent = nullptr;
	Horizon::TransformComponent* m_pCoilyTransformComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_Move;

	int m_StepsTaken;
	bool m_CanMoveBeUpdated;
	bool m_IsCoilyTransformed;
};

