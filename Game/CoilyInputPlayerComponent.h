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
	class TimedFunctionComponent;
}

class CoilyInputPlayerComponent final : public Horizon::Component
{
public:
	CoilyInputPlayerComponent(Horizon::GameObject* pParent);
private:
	//Component functions
	void Initialize() override;
	void PostInitialize() override;
	void Update();

	//Helper functions
	void InitializeControllerTimedFunction();
	void InitializeResetControllerTimedFunction();
	void ResetInput();

	//Components
	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;
	MovementComponent* m_pQbertMovementComponent = nullptr;

	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::TransformComponent* m_pCoilyTransformComponent = nullptr;

	//Variables
	Horizon::IPoint2 m_Move;

	int m_StepsTaken;
	bool m_CanInputBeRecieved;
	bool m_CanMoveBeUpdated;
	bool m_IsCoilyTransformed;
};

