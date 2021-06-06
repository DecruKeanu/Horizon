#include "GamePCH.h"
#include "CoilyInputPlayerComponent.h"

#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include <TriggerComponent.h>
#include <TransformComponent.h>
#include <TimedFunctionComponent.h>
#include <SceneManager.h>
#include <Scene.h>

#include <InputManager.h>
#include "GameCommands.h"
#include <TimedFunctionComponent.h>
#include <SoundSystemServiceLocator.h>

CoilyInputPlayerComponent::CoilyInputPlayerComponent(Horizon::GameObject* pParent) : Component(pParent),
m_Move{},
m_StepsTaken{},
m_CanMoveBeUpdated{},
m_CanInputBeRecieved{},
m_IsCoilyTransformed{}
{

}

CoilyInputPlayerComponent::~CoilyInputPlayerComponent()
{
	Horizon::Logger::LogInfo("Coily deleted");
}

void CoilyInputPlayerComponent::Initialize()
{
	using namespace Horizon;

	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_DOWN, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_LEFT, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_UP, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_RIGHT, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRecieved));
}

void CoilyInputPlayerComponent::PostInitialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pCoilyTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pQbertMovementComponent = Horizon::SceneManager::GetInstance().GetActiveScene()->GetGameObject("Qbert")->GetComponent<MovementComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	Horizon::TimedFunctionComponent* const pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	pTimedFunction->SetTimerFunction([this](float)
		{
			if (m_IsCoilyTransformed)
				return;

			if (m_StepsTaken >= 6 && m_IsCoilyTransformed == false)
			{
				m_IsCoilyTransformed = true;
				m_pSpriteComponent->SetSrcRect({ 0,32,128,32 });
				m_pSpriteComponent->SetSpriteAmount(8);
				m_pSpriteComponent->SetSpriteOffset({ 0,-24 });

				m_CanInputBeRecieved = true;
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

			m_pMovementComponent->SetMove(m_Move);
			m_pSpriteComponent->SetMove(m_Move);
		});

	pTimedFunction->Activate();
	m_pGameObject->AddComponent(pTimedFunction);

	m_pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, false, 1.02f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			ResetInput();
			m_pMovementComponent->SetMove(m_Move);

			if (m_pTriggerComponent->GetOverlappingActorsSize() == 0)
				m_pGameObject->Deactivate();
		});
	m_pGameObject->AddComponent(m_pTimedFunction);
}

void CoilyInputPlayerComponent::Update()
{
	if (!m_IsCoilyTransformed)
		return;

	m_pSpriteComponent->SetMove(m_Move);

	if (!m_CanInputBeRecieved)
		return;

	m_pMovementComponent->SetMove(m_Move);

	if (m_Move != Horizon::IPoint2{ 0, 0 })
	{
		m_pSpriteComponent->SetMove(m_Move);
		m_pMovementComponent->SetMove(m_Move);
		m_CanInputBeRecieved = false;
		m_pTimedFunction->Activate();

		auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
		soundSystem.QueueEvent(3, 60);
	}
}

void CoilyInputPlayerComponent::ResetInput()
{
	m_CanInputBeRecieved = true;
	m_Move = {};
}
