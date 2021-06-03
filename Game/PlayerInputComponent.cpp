#include "GamePCH.h"
#include "PlayerInputComponent.h"
#include "InputManager.h"
#include <Command.h>
#include "GameCommands.h"
#include <TimedFunction.h>
#include <Timer.h>
using namespace Horizon;

PlayerInputComponent::PlayerInputComponent(Horizon::GameObject* parent) : Component(parent),
m_CanInputBeRegistered{ true }
{

}

PlayerInputComponent::~PlayerInputComponent()
{
	Horizon::Timer::GetInstance().RemoveTimedFunction(m_pTimedFunction);
	SafeDelete(m_pTimedFunction);
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
}

const IPoint2& PlayerInputComponent::GetMove()
{
	return m_Move;
}

void PlayerInputComponent::Initialize()
{
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_s, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(m_Move,m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_q, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_z, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_d, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRegistered));

	m_pTimedFunction = new Horizon::TimedFunction(false, 1.f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			ResetInput();
		});

	Horizon::Timer::GetInstance().AddTimedFunction(m_pTimedFunction);
}

void PlayerInputComponent::Update()
{
	if (m_CanInputBeRegistered)
	{
		if (m_Move != IPoint2{0, 0})
		{
			m_CanInputBeRegistered = false;
			m_pTimedFunction->Activate();
		}
	}
}
