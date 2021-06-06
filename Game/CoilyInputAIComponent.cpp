#include "GamePCH.h"
#include "CoilyInputAIComponent.h"
#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include <TriggerComponent.h>
#include <TransformComponent.h>
#include <TimedFunctionComponent.h>
#include <SceneManager.h>
#include <Scene.h>
#include <SoundSystemServiceLocator.h>

CoilyInputAIComponent::CoilyInputAIComponent(Horizon::GameObject* pParent) : Component(pParent),
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{},
m_IsCoilyTransformed{}
{

}

CoilyInputAIComponent::~CoilyInputAIComponent()
{
	Horizon::Logger::LogInfo("Coily deleted");
}

void CoilyInputAIComponent::Initialize()
{
	
}

void CoilyInputAIComponent::PostInitialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pCoilyTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pQbertMovementComponent = Horizon::SceneManager::GetInstance().GetActiveScene()->GetGameObject("Qbert")->GetComponent<MovementComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	Horizon::TimedFunctionComponent* const pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	pTimedFunction->SetTimerFunction([this](float)
		{
			if (m_StepsTaken >= 6 && m_IsCoilyTransformed == false)
			{
				m_IsCoilyTransformed = true;
				m_pSpriteComponent->SetSrcRect({ 0,32,128,32 });
				m_pSpriteComponent->SetSpriteAmount(8);
				m_pSpriteComponent->SetSpriteOffset({ 0,-24 });
			}

			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (m_pTriggerComponent->GetOverlappingActorsSize() == 0)
			{
				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(9, 50);

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

			if (m_IsCoilyTransformed == false)
			{
				m_Move.x = randomMove;
				m_Move.y = 1;
			}
			else
			{
				const Horizon::IPoint2& CoilyPos = m_pCoilyTransformComponent->GetPosition();
				const Horizon::IPoint2& QbertPos = m_pQbertMovementComponent->GetOriginalPos();

				Horizon::Logger::LogInfo("CurrentPos: (" + std::to_string(QbertPos.x) + " , " + std::to_string(QbertPos.y) + ")");

				m_Move.x = (QbertPos.x > CoilyPos.x) ? 1 : -1;
				m_Move.y = (QbertPos.y > CoilyPos.y) ? 1 : -1;

				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(3, 60);
			}

			m_pMovementComponent->SetMove(m_Move);
			m_pSpriteComponent->SetMove(m_Move);
		});

	pTimedFunction->Activate();
	m_pGameObject->AddComponent(pTimedFunction);
}
