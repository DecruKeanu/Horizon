#include "GamePCH.h"
#include "EnemyInputComponent.h"

#include <ScoreComponent.h>
#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include <TriggerComponent.h>
#include <TimedFunctionComponent.h>

#include <Scene.h>
#include <SceneManager.h>


EnemyInputComponent::EnemyInputComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& movementDirection) : Component(pParent),
m_MovementDirection{ movementDirection },
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{},
m_TilesEncountered{}
{

}

void EnemyInputComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();

	InitializeMovementTimedFunction();
	InitializeTilesEncounteredTimedFunction();
}

void EnemyInputComponent::InitializeMovementTimedFunction()
{
	Horizon::TimedFunctionComponent* const pMovementTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	pMovementTimedFunction->SetTimerFunction([this](float)
		{
			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if ((m_StepsTaken >= 6) && !m_TilesEncountered)
				m_pGameObject->Deactivate();


			if (m_CanMoveBeUpdated)
			{
				m_StepsTaken++;

				const int randomMove = (rand() % 2) ? 1 : -1;
				m_Move.x = (m_MovementDirection.x == 0) ? randomMove : m_MovementDirection.x;
				m_Move.y = (m_MovementDirection.y == 0) ? randomMove : m_MovementDirection.y;

				m_pMovementComponent->SetMove(m_Move);
				m_pSpriteComponent->SetMove(m_Move);
			}
			else
			{
				m_Move = { 0,0 };
				m_pMovementComponent->SetMove(m_Move);
				m_pSpriteComponent->SetMove(m_Move);
			}
		});
	pMovementTimedFunction->Activate();
	m_pGameObject->AddComponent(pMovementTimedFunction);
}

void EnemyInputComponent::InitializeTilesEncounteredTimedFunction()
{
	Horizon::TimedFunctionComponent* const pTilesEncounteredTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 0.4f);
	pTilesEncounteredTimedFunction->SetTimerFunction([this](float) { m_TilesEncountered = (m_pTriggerComponent->GetOverlappingActorsSize() > 0); });
	pTilesEncounteredTimedFunction->Activate();

	m_pGameObject->AddComponent(pTilesEncounteredTimedFunction);
}
