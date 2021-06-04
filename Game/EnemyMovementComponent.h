#pragma once
#include <Component.h>
namespace Horizon
{
	class GameObject;
	class TransformComponent;
	class TriggerComponent;
}

class EnemyInputComponent;

class EnemyMovementComponent final : public Horizon::Component
{
public:
	EnemyMovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, bool IsMovementSideways);
private:
	void Initialize() override;
	void Update() override;
	void LetEnemyFall();


	bool m_IsMovementSideways;
	bool m_IsEnemyOnFloor;
	bool m_TilesEncountered;
	float m_ElapsedTime;


	Horizon::IPoint2 m_OriginalPoint;
	Horizon::IPoint2 m_FallPoint;
	Horizon::IPoint2 m_BlockOffset;


	EnemyInputComponent* m_pMovementComponent = nullptr;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
};

