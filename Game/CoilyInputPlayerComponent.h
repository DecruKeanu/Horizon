#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class TriggerComponent;
	class TimedFunctionComponent;
}

class MovementComponent;
class GameSpriteComponent;

class CoilyInputPlayerComponent final : public Horizon::Component
{
public:
	CoilyInputPlayerComponent(Horizon::GameObject* pParent);
	~CoilyInputPlayerComponent();
private:
	void Initialize() override;
	void PostInitialize() override;
	void Update();

	void ResetInput();

	int m_StepsTaken;
	bool m_CanInputBeRecieved;
	bool m_CanMoveBeUpdated;
	bool m_IsCoilyTransformed;
	Horizon::IPoint2 m_Move;

	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;

	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	Horizon::TransformComponent* m_pCoilyTransformComponent = nullptr;
	MovementComponent* m_pQbertMovementComponent = nullptr;
};

