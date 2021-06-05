#pragma once
#include <Component.h>
namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class TriggerComponent;
}

class EnemyMovementComponent final : public Horizon::Component
{
public:
	EnemyMovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, bool IsMovementSideways);

	void SetMove(const Horizon::IPoint2& input);
private:
	void Initialize() override;
	void Update() override;
	void LetEnemyFall();

	int m_StepsTaken;
	bool m_IsMovementSideways;
	bool m_IsEnemyOnFloor;
	bool m_TilesEncountered;
	float m_ElapsedTime;

	Horizon::IPoint2 m_FallPoint;
	Horizon::IPoint2 m_Move;
	Horizon::IPoint2 m_OriginalPoint;

	Horizon::IPoint2 m_BlockOffset;

	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
};

