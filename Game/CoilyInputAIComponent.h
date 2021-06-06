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

class CoilyInputAIComponent final : public Horizon::Component
{
public:
	CoilyInputAIComponent(Horizon::GameObject* pParent);
	~CoilyInputAIComponent();
private:
	void Initialize() override;
	void PostInitialize() override;

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

