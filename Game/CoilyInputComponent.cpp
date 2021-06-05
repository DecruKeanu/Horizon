#include "GamePCH.h"
#include "CoilyInputComponent.h"
#include "EnemyMovementComponent.h"
#include "GameSpriteComponent.h"
#include <TransformComponent.h>
#include <TimedFunctionComponent.h>
#include <SceneManager.h>
#include <Scene.h>

CoilyInputComponent::CoilyInputComponent(Horizon::GameObject* pParent) : Component(pParent),
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{},
m_IsCoilyTransformed{}
{

}

void CoilyInputComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pCoilyTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pQbertTransformComponent = Horizon::SceneManager::GetInstance().GetActiveScene()->GetGameObject("Qbert")->GetComponent<Horizon::TransformComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<EnemyMovementComponent>();

	m_pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			if (m_StepsTaken >= 6 && m_IsCoilyTransformed == false)
			{
				m_IsCoilyTransformed = true;
				m_pSpriteComponent->SetSrcRect({ 0,32,128,32 });
				m_pSpriteComponent->SetSpriteAmount(8);
				m_pSpriteComponent->SetSpriteOffset({ 0,-24 });
			}
			//m_IsCoilyTransformed = (m_StepsTaken >= 6);

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

			if (m_IsCoilyTransformed == false)
			{
				m_Move.x = randomMove;
				m_Move.y = 1;
			}
			else
			{
				const Horizon::IPoint2& CoilyPos = m_pCoilyTransformComponent->GetPosition();
				const Horizon::IPoint2& QbertPos = m_pQbertTransformComponent->GetPosition();

				m_Move.x = (QbertPos.x > CoilyPos.x) ? 1 : -1;
				m_Move.y = (QbertPos.y > CoilyPos.y) ? 1 : -1;
			}

			m_pMovementComponent->SetMove(m_Move);
			m_pSpriteComponent->SetMove(m_Move);
		});

	m_pTimedFunction->Activate();
	m_pGameObject->AddComponent(m_pTimedFunction);
}
