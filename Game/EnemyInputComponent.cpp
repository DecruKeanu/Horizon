#include "GamePCH.h"
#include "EnemyInputComponent.h"
#include <TimedFunction.h>
#include <Timer.h>

EnemyInputComponent::EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection) : Component(pParent),
m_MovementDirection{ movementDirection },
m_Move{},
m_Moves{},
m_CanMoveBeUpdated{}
{

}

EnemyInputComponent::~EnemyInputComponent()
{
	Horizon::Timer::GetInstance().RemoveTimedFunction(m_pTimedFunction);
	SafeDelete(m_pTimedFunction);
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

void EnemyInputComponent::Initialize()
{
	m_pTimedFunction = new Horizon::TimedFunction(true, 1.f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			m_Moves++;

			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (!m_CanMoveBeUpdated)
			{
				m_Move = { 0,0 };
				return;
			}

			const int randomMove = (rand() % 2) ? 1 : -1;
			m_Move.x = (m_MovementDirection.x == 0) ? randomMove : m_MovementDirection.x;
			m_Move.y = (m_MovementDirection.y == 0) ? randomMove : m_MovementDirection.y;

			if (m_MovementDirection.x != 0)
				m_MovementDirection.y = (m_MovementDirection.y != 0 && m_Moves > 3) ? 0 : m_MovementDirection.y;
		});
	EnableMovement();
	Horizon::Timer::GetInstance().AddTimedFunction(m_pTimedFunction);
}

