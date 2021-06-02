#pragma once
#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

bool Horizon::InputManager::ProcessInput()
{
	RtlZeroMemory(&m_InputKeyStroke, sizeof(XINPUT_KEYSTROKE));
	RtlZeroMemory(&m_InputState, sizeof(XINPUT_STATE));

	//SDL for mouse and keyboard
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		for (const auto& pair : m_KeyboardCommands)
		{
			if (e.type == Uint32(pair.first.first))
			{
				m_SDLKeyCode = e.key.keysym.sym;
				m_KeyboardInput = Uint32(KeyboardButtonState::KeyDown);
				HandleKeyboardInput(pair);
			}
		}
	}

	//Xinput for controllers
	for (int idx{}; idx < m_MaxAmountOfControllers; idx++)
	{
		auto check = XInputGetState(idx, &m_InputState);

		if (check != ERROR_SUCCESS)
			continue;

		XInputGetKeystroke(idx, 0, &m_InputKeyStroke);

		for (const auto& pair : m_ControllerCommands)
		{
			if (m_InputKeyStroke.Flags == WORD(pair.first.first))
				HandleControllerInput(pair);
		}
	}
	return true;
}

void Horizon::InputManager::ExecuteControllerInput(const std::pair<const Controllerkey, std::unique_ptr<Command>>& it) const
{
	if (it.second)
		it.second->Execute();
}

void Horizon::InputManager::ExecuteKeyboardInput(const std::pair<const Keyboardkey, std::unique_ptr<Command>>& it) const
{
	if (it.second)
		it.second->Execute();
}

void Horizon::InputManager::HandleControllerInput(const std::pair<const Controllerkey, std::unique_ptr<Command>>& it) const
{
	if (m_InputKeyStroke.VirtualKey == WORD(it.first.second))
		ExecuteControllerInput(it);
}

void Horizon::InputManager::HandleKeyboardInput(const std::pair<const Keyboardkey, std::unique_ptr<Command>>& it) const
{
	if (m_SDLKeyCode == int(it.first.second))
		ExecuteKeyboardInput(it);
}

void Horizon::InputManager::AddControllerInput(ControllerButton button, ControllerButtonState buttonState, std::unique_ptr<Command> action)
{
	m_ControllerCommands.insert({ Controllerkey(buttonState, button),std::move(action) });
}

void Horizon::InputManager::AddKeyboardInput(SDLK key, KeyboardButtonState keyState, std::unique_ptr<Command> action)
{
	m_KeyboardCommands.insert({ Keyboardkey(keyState,key),std::move(action) });
}

bool Horizon::InputManager::IsControllerInputPressed(const ControllerButton& button)
{
	if (m_InputKeyStroke.Flags != WORD(ControllerButtonState::ButtonDown))
		return false;

	if (m_InputKeyStroke.VirtualKey == WORD(button))
		return true;

	return false;
}

bool Horizon::InputManager::IsKeyboardInputPressed(const SDLK& key)
{
	if (m_KeyboardInput != Uint32(KeyboardButtonState::KeyDown))
		return false;

	if (m_SDLKeyCode == int(key))
	{
		m_KeyboardInput = 0;
		return true;
	}


	return false;
}

void Horizon::InputManager::ClearInput()
{
	m_ControllerCommands.clear();
	m_KeyboardCommands.clear();
}
