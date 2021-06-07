#include "GamePCH.h"
#include "CoilyInputAIComponent.h"

#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include <ScoreComponent.h>
#include <TriggerComponent.h>
#include <TransformComponent.h>
#include <TimedFunctionComponent.h>

#include <Scene.h>
#include <SceneManager.h>
#include <TriggerManager.h>
#include <SoundSystemServiceLocator.h>

CoilyInputAIComponent::CoilyInputAIComponent(Horizon::GameObject* pParent) : Component(pParent),
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{},
m_IsCoilyTransformed{}
{

}

void CoilyInputAIComponent::Initialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pCoilyTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pQbertScoreComponent = Horizon::SceneManager::GetInstance().GetActiveScene()->GetGameObject("Qbert")->GetComponent<Horizon::ScoreComponent>();
	m_pQbertMovementComponent = Horizon::SceneManager::GetInstance().GetActiveScene()->GetGameObject("Qbert")->GetComponent<MovementComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	InitializeControllerTimedFunction();
}

void CoilyInputAIComponent::InitializeControllerTimedFunction()
{
	Horizon::TimedFunctionComponent* const pControllerTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	pControllerTimedFunction->SetTimerFunction([this](float)
		{
			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (m_IsCoilyTransformed == false && m_StepsTaken >= 6)
			{
				m_IsCoilyTransformed = true;
				m_pSpriteComponent->SetSrcRect({ 0,32,128,32 });
				m_pSpriteComponent->SetSpriteOffset({ 0,-24 });
			}

			if (m_CanMoveBeUpdated)
			{
				m_StepsTaken++;
				const int randomMove = (rand() % 2) ? 1 : -1;

				if (m_IsCoilyTransformed)
				{
					const Horizon::IPoint2& CoilyPos = m_pCoilyTransformComponent->GetPosition();
					const Horizon::IPoint2& QbertPos = m_pQbertMovementComponent->GetOriginalPos();

					m_Move.x = (QbertPos.x > CoilyPos.x) ? 1 : -1;
					m_Move.y = (QbertPos.y > CoilyPos.y) ? 1 : -1;

					auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
					soundSystem.QueueEvent(3, 48);
				}
				else
				{
					m_Move.x = randomMove;
					m_Move.y = 1;
				}

				m_pMovementComponent->SetMove(m_Move);
				m_pSpriteComponent->SetMove(m_Move);
			}
			else
			{
				m_Move = { 0,0 };
				m_pMovementComponent->SetMove(m_Move);
				m_pSpriteComponent->SetMove(m_Move);
			}

			if (m_pTriggerComponent->GetOverlappingActorsSize() == 0 && Horizon::TriggerManager::GetInstance().GetTriggersSize() != 0)
			{
				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(9, 50);

				m_pQbertScoreComponent->IncreaseScore(500);
				m_pGameObject->Deactivate();
			}
		});

	pControllerTimedFunction->Activate();
	m_pGameObject->AddComponent(pControllerTimedFunction);
}
