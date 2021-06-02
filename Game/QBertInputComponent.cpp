#include "GamePCH.h"
#include "QBertInputComponent.h"
#include "InputManager.h"
#include <Command.h>
#include "GameCommands.h"
#include <Timer.h>
using namespace Horizon;

QBertInputComponent::QBertInputComponent(Horizon::GameObject* parent) : Component(parent),
m_Move{},
m_CurrentInput{},
m_InputTimer{},
m_CanInputBeRegistered{ true }
{

}

void QBertInputComponent::ResetInput()
{
	m_CanInputBeRegistered = true;
	m_Move = {};
}

bool QBertInputComponent::GetCanInputBeRegistered()
{
	return m_CanInputBeRegistered;
}

const Horizon::IPoint2& QBertInputComponent::GetMove() const
{
	return m_Move;
}

void QBertInputComponent::Initialize()
{
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_s, KeyboardButtonState::KeyDown, std::make_unique<MoveDownCommand>(m_Move,m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_q, KeyboardButtonState::KeyDown, std::make_unique<MoveLeftCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_z, KeyboardButtonState::KeyDown, std::make_unique<MoveUpCommand>(m_Move, m_CanInputBeRegistered));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_d, KeyboardButtonState::KeyDown, std::make_unique<MoveRightCommand>(m_Move, m_CanInputBeRegistered));
}

void QBertInputComponent::Update()
{
	if (m_CanInputBeRegistered)
	{
		if (m_Move.x != 0 || m_Move.y != 0)
			m_CanInputBeRegistered = false;
	}
}
