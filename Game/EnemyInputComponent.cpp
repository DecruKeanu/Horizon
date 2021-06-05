#include "GamePCH.h"
#include "EnemyInputComponent.h"
#include <TimedFunctionComponent.h>
#include "EnemyMovementComponent.h"
#include "EnemySpriteComponent.h"
#include <Timer.h>

EnemyInputComponent::EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection) : Component(pParent),
m_MovementDirection{ movementDirection },
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{}
{

}

void EnemyInputComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject->GetComponent<EnemySpriteComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<EnemyMovementComponent>();

	m_pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject,true, 1.f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (!m_CanMoveBeUpdated)
			{
				m_Move = { 0,0 };
				m_pMovementComponent->SetMove(m_Move);
				m_pSpriteComponent->SetMove(m_Move);
				return;
			}

			m_StepsTaken++;
			const int randomMove = (rand() % 2) ? 1 : -1;
			m_Move.x = (m_MovementDirection.x == 0) ? randomMove : m_MovementDirection.x;
			m_Move.y = (m_MovementDirection.y == 0) ? randomMove : m_MovementDirection.y;

			m_pMovementComponent->SetMove(m_Move);
			m_pSpriteComponent->SetMove(m_Move);
		});

	m_pTimedFunction->Activate();
	m_pGameObject->AddComponent(m_pTimedFunction);
}

