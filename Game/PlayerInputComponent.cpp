#include "GamePCH.h"
#include "PlayerInputComponent.h"

#include "MovementComponent.h"
#include "GameSpriteComponent.h"
#include <HealthComponent.h>
#include <TriggerComponent.h>
#include <TimedFunctionComponent.h>

#include <InputManager.h>
#include "InputCommands.h"
#include <SoundSystemServiceLocator.h>
#include <TriggerManager.h>

using Input = std::pair<SDLK, Horizon::ControllerButton>;

PlayerInputComponent::PlayerInputComponent(Horizon::GameObject* parent, bool isFirstPlayer) : Component(parent),
m_IsFirstPlayer{isFirstPlayer},
m_CanInputBeRegistered{ true },
m_Move{}
{

}

void PlayerInputComponent::Initialize()
{
	m_pTriggerComponent = m_pGameObject->GetComponent<Horizon::TriggerComponent>();
	m_pGameSpriteComponent = m_pGameObject->GetComponent<GameSpriteComponent>();
	m_pPlayerMovementComponent = m_pGameObject->GetComponent<MovementComponent>();

	InitializeInput();
	InitializeInputTimedFunction();
	InitializeStartInputTimedFunction();

	DeactivateInput();
}

void PlayerInputComponent::Update()
{
	m_pGameSpriteComponent->SetMove(m_Move);

	if (m_CanInputBeRegistered && m_Move != Horizon::IPoint2{ 0, 0 })
	{
		m_CanInputBeRegistered = false;
		m_pInputTimedFunction->Activate();
		m_pPlayerMovementComponent->SetMove(m_Move);
	}
}

void PlayerInputComponent::InitializeInput()
{
	using namespace Horizon;

	//AZERTY for personal use
	const Input downInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_s,ControllerButton::DPadDown } : Input{ SDLK::SDLK_DOWN, ControllerButton::ButtonA };
	const Input leftInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_q,ControllerButton::DPadLeft } : Input{ SDLK::SDLK_LEFT, ControllerButton::ButtonX };
	const Input upInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_z,ControllerButton::DPadUp } : Input{ SDLK::SDLK_UP, ControllerButton::ButtonY };
	const Input rightInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_d,ControllerButton::DPadRight } : Input{ SDLK::SDLK_RIGHT, ControllerButton::ButtonB };

	//QWERTY for general use
	//const Input downInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_s,ControllerButton::DPadDown } : Input{ SDLK::SDLK_DOWN, ControllerButton::ButtonA };
	//const Input leftInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_a,ControllerButton::DPadLeft } : Input{ SDLK::SDLK_LEFT, ControllerButton::ButtonX };
	//const Input upInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_w,ControllerButton::DPadUp } : Input{ SDLK::SDLK_UP, ControllerButton::ButtonY };
	//const Input rightInput = m_IsFirstPlayer ? Input{ SDLK::SDLK_d,ControllerButton::DPadRight } : Input{ SDLK::SDLK_RIGHT, ControllerButton::ButtonB };

	InputManager::GetInstance().AddKeyboardInput(downInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(leftInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(upInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(rightInput.first, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRegistered));

	InputManager::GetInstance().AddControllerInput(downInput.second, ControllerButtonState::ButtonDown, std::make_unique<MoveDownCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddControllerInput(leftInput.second, ControllerButtonState::ButtonDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddControllerInput(upInput.second, ControllerButtonState::ButtonDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddControllerInput(rightInput.second, ControllerButtonState::ButtonDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRegistered));
}

void PlayerInputComponent::InitializeInputTimedFunction()
{
	m_pInputTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, false, 1.02f);
	m_pInputTimedFunction->SetTimerFunction([this](float)
		{
			ActivateInput();
			m_pPlayerMovementComponent->SetMove(m_Move);

			if (m_pTriggerComponent->GetOverlappingActorsSize() == 0 && Horizon::TriggerManager::GetInstance().GetTriggersSize() != 0)
			{
				auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
				soundSystem.QueueEvent(8, 36);

				m_pGameObject->GetComponent<Horizon::HealthComponent>()->DecreaseLive();
			}
		});

	m_pGameObject->AddComponent(m_pInputTimedFunction);
}

void PlayerInputComponent::InitializeStartInputTimedFunction()
{
	Horizon::TimedFunctionComponent* pStartInputTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, false, 1.f);
	pStartInputTimedFunction->SetTimerFunction([this](float) {ActivateInput(); });
	pStartInputTimedFunction->Activate();
	m_pGameObject->AddComponent(pStartInputTimedFunction);
}

void PlayerInputComponent::ActivateInput()
{
	m_CanInputBeRegistered = true;
	m_Move = {};
}

void PlayerInputComponent::DeactivateInput()
{
	m_CanInputBeRegistered = false;
	m_pInputTimedFunction->Deactivate();
	m_Move = {};
}

bool PlayerInputComponent::GetCanInputBeRegistered() const
{
	return m_CanInputBeRegistered;
}

const Horizon::IPoint2& PlayerInputComponent::GetMove() const
{
	return m_Move;
}