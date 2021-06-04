#include "GamePCH.h"
#include "EnemyInputComponent.h"
#include <TimedFunctionComponent.h>
#include <Timer.h>

EnemyInputComponent::EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection) : Component(pParent),
m_MovementDirection{ movementDirection },
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{}
{

}

const Horizon::IPoint2& EnemyInputComponent::GetMove()
{
	return m_Move;
}

void EnemyInputComponent::DisableMovement()
{
	m_pTimedFunction->Deactivate();
}

void EnemyInputComponent::EnableMovement()
{
	m_pTimedFunction->Activate();
}

int EnemyInputComponent::GetStepsTaken() const
{
	return m_StepsTaken;
}

void EnemyInputComponent::Initialize()
{
	m_pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject,true, 1.f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (!m_CanMoveBeUpdated)
			{
				m_Move = { 0,0 };
				return;
			}

			m_StepsTaken++;
			const int randomMove = (rand() % 2) ? 1 : -1;
			m_Move.x = (m_MovementDirection.x == 0) ? randomMove : m_MovementDirection.x;
			m_Move.y = (m_MovementDirection.y == 0) ? randomMove : m_MovementDirection.y;
		});

	EnableMovement();
	m_pGameObject->AddComponent(m_pTimedFunction);
}

