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
#include <TriggerManager.h>
#include "InputCommands.h"
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

void CoilyInputPlayerComponent::Initialize()
{
	using namespace Horizon;

	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_DOWN, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_LEFT, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_UP, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_RIGHT, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRecieved));

	InputManager::GetInstance().AddControllerInput(ControllerButton::ButtonA, ControllerButtonState::ButtonDown, std::make_unique<MoveDownCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddControllerInput(ControllerButton::ButtonX, ControllerButtonState::ButtonDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddControllerInput(ControllerButton::ButtonY, ControllerButtonState::ButtonDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRecieved));
	InputManager::GetInstance().AddControllerInput(ControllerButton::ButtonB, ControllerButtonState::ButtonDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRecieved));
}

void CoilyInputPlayerComponent::PostInitialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();
	m_pSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pCoilyTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	m_pQbertMovementComponent = Horizon::SceneManager::GetInstance().GetActiveScene()->GetGameObject("Qbert")->GetComponent<MovementComponent>();
	m_pMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	InitializeControllerTimedFunction();
	InitializeResetControllerTimedFunction();
}

void CoilyInputPlayerComponent::Update()
{
	if (!m_IsCoilyTransformed)
		return;

	m_pSpriteComponent->SetMove(m_Move);

	if (m_CanInputBeRecieved)
	{
		m_pMovementComponent->SetMove(m_Move);

		if (m_Move != Horizon::IPoint2{ 0, 0 })
		{
			m_pSpriteComponent->SetMove(m_Move);
			m_pMovementComponent->SetMove(m_Move);
			m_CanInputBeRecieved = false;
			m_pTimedFunction->Activate();

			auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
			soundSystem.QueueEvent(3, 48);
		}
	}
}

void CoilyInputPlayerComponent::InitializeControllerTimedFunction()
{
	Horizon::TimedFunctionComponent* const pControllerTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 1.f);
	pControllerTimedFunction->SetTimerFunction([this](float)
		{
			if (m_IsCoilyTransformed)
				return;

			if (m_StepsTaken >= 6 && m_IsCoilyTransformed == false)
			{
				m_IsCoilyTransformed = true;
				m_pSpriteComponent->SetSrcRect({ 0,32,128,32 });
				m_pSpriteComponent->SetSpriteOffset({ 0,-24 });

				m_CanInputBeRecieved = true;
			}

			m_CanMoveBeUpdated = !m_CanMoveBeUpdated;

			if (m_pTriggerComponent->GetOverlappingActorsSize() == 0 && Horizon::TriggerManager::GetInstance().GetTriggersSize() != 0)
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

	pControllerTimedFunction->Activate();
	m_pGameObject->AddComponent(pControllerTimedFunction);
}

void CoilyInputPlayerComponent::InitializeResetControllerTimedFunction()
{
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

void CoilyInputPlayerComponent::ResetInput()
{
	m_CanInputBeRecieved = true;
	m_Move = {};
}
