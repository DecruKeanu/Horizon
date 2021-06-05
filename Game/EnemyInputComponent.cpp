#include "GamePCH.h"
#include "EnemyInputComponent.h"
#include <TimedFunctionComponent.h>
#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include "TriggerComponent.h"
#include <Timer.h>

EnemyInputComponent::EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection) : Component(pParent),
m_MovementDirection{ movementDirection },
m_Move{},
m_StepsTaken{},
m_ElapsedTime{},
m_CanMoveBeUpdated{},
m_MinimumStepsReached{},
m_TilesEncountered{}
{

}

void EnemyInputComponent::Initialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	m_pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (m_MinimumStepsReached)
			{
				if (m_TilesEncountered)
					m_TilesEncountered = false;
				else
					m_pGameObject->Deactivate();
			}

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


			m_MinimumStepsReached = (m_StepsTaken >= 6) ? true : false;
		});



	m_pTimedFunction->Activate();
	m_pGameObject->AddComponent(m_pTimedFunction);
}

void EnemyInputComponent::Update()
{
	if (!m_MinimumStepsReached)
		return;

	m_ElapsedTime += Horizon::Timer::GetInstance().GetDeltaTime();
	
	if (m_TilesEncountered == false && m_pTriggerComponent->GetOverlappingActorsSize() > 0 && m_ElapsedTime > 0.8f)
	{
		m_ElapsedTime = 0.f;
		m_TilesEncountered = true;
	}
}

