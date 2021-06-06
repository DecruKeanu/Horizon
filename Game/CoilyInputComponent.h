#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class TriggerComponent;
}

class MovementComponent;
class GameSpriteComponent;

class CoilyInputComponent final : public Horizon::Component
{
public:
	CoilyInputComponent(Horizon::GameObject* pParent);
private:
	void Initialize() override;

	int m_StepsTaken;
	bool m_CanMoveBeUpdated;
	bool m_IsCoilyTransformed;
	Horizon::IPoint2 m_Move;

	MovementComponent* m_pMovementComponent = nullptr;
	GameSpriteComponent* m_pSpriteComponent = nullptr;

	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
	Horizon::TransformComponent* m_pCoilyTransformComponent = nullptr;
	MovementComponent* m_pQbertMovementComponent = nullptr;
};

