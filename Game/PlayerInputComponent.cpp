#include "GamePCH.h"
#include "PlayerInputComponent.h"
#include "InputManager.h"
#include <Command.h>
#include "GameCommands.h"
#include <TimedFunctionComponent.h>
#include <TriggerComponent.h>
#include <HealthComponent.h>
#include "GameSpriteComponent.h"
#include "MovementComponent.h"
#include <Timer.h>
#include <SoundSystemServiceLocator.h>

using namespace Horizon;

using Input = std::pair<SDLK, ControllerButton>;

PlayerInputComponent::PlayerInputComponent(Horizon::GameObject* parent, bool isFirstPlayer) : Component(parent),
m_IsFirstPlayer{isFirstPlayer},
m_CanInputBeRegistered{ true },
m_Move{}
{

}

void PlayerInputComponent::ResetInput()
{
	m_CanInputBeRegistered = true;
	m_Move = {};
}

bool PlayerInputComponent::GetCanInputBeRegistered()
{
	return m_CanInputBeRegistered;
}

void PlayerInputComponent::DeactivateInput()
{
	m_CanInputBeRegistered = false;
	m_pTimedFunction->Deactivate();
	m_Move = {};
}

const IPoint2& PlayerInputComponent::GetMove()
{
	return m_Move;
}

void PlayerInputComponent::Initialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<TriggerComponent>();
	m_pGameSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pPlayerMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	const Input downInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_s,ControllerButton::DPadDown } : Input{ SDLK::SDLK_DOWN, ControllerButton::ButtonA };
	const Input leftInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_q,ControllerButton::DPadLeft } : Input{ SDLK::SDLK_LEFT, ControllerButton::ButtonX };
	const Input upInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_z,ControllerButton::DPadUp } : Input{ SDLK::SDLK_UP, ControllerButton::ButtonY };
	const Input rightInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_d,ControllerButton::DPadRight } : Input{ SDLK::SDLK_RIGHT, ControllerButton::ButtonB };


	InputManager::GetInstance().AddKeyboardInput(downInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(leftInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(upInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(rightInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRegistered));

	m_pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, false, 1.02f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			ResetInput();
			m_pPlayerMovementComponent->SetMove(m_Move);

			if (m_pTriggerComponent->GetOverlappingActorsSize() == 0)
			{
				auto& soundSystem = SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(8, 36);

				m_pGameObject->GetComponent<HealthComponent>()->DecreaseLive();
			}

		});

	m_pGameObject->AddComponent(m_pTimedFunction);

	DeactivateInput();

	Horizon::TimedFunctionComponent* pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, false, 1.f);
	pTimedFunction->SetTimerFunction([this](float){ResetInput();});
	pTimedFunction->Activate();
	m_pGameObject->AddComponent(pTimedFunction);
}

void PlayerInputComponent::Update()
{
	m_pGameSpriteComponent->SetMove(m_Move);

	if (!m_CanInputBeRegistered)
		return;

	if (m_Move != IPoint2{ 0, 0 })
	{
		m_pPlayerMovementComponent->SetMove(m_Move);
		m_CanInputBeRegistered = false;
		m_pTimedFunction->Activate();
	}
}
