#pragma once
#include <Component.h>

namespace Horizon
{
	class GameObject;
	class TransformComponent;
}

class EnemyMovementComponent;
class EnemySpriteComponent;

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

	EnemyMovementComponent* m_pMovementComponent = nullptr;
	EnemySpriteComponent* m_pSpriteComponent = nullptr;

	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::TransformComponent* m_pCoilyTransformComponent = nullptr;
	Horizon::TransformComponent* m_pQbertTransformComponent = nullptr;
};

