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
	EnemyMovementComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& fallPoint, const Horizon::IPoint2 blockOffset, bool hopping);
private:
	void Initialize() override;
	void Update() override;
	void LetEnemyFall();

	bool m_IsEnemyOnFloor;
	bool m_TilesEncountered;
	bool m_Hopping;
	float m_ElapsedTime;


	Horizon::IPoint2 m_OriginalPoint;
	Horizon::IPoint2 m_FallPoint;
	Horizon::IPoint2 m_BlockOffset;


	EnemyInputComponent* m_pMovementComponent = nullptr;
	Horizon::TransformComponent* m_pTransformComponent = nullptr;
	Horizon::TriggerComponent* m_pTriggerComponent = nullptr;
};

