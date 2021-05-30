#pragma once
#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Command.h"

bool dae::InputManager::ProcessInput()
{
	RtlZeroMemory(&m_InputKeyStroke, sizeof(XINPUT_KEYSTROKE));
	RtlZeroMemory(&m_InputState, sizeof(XINPUT_STATE));

	//SDL for mouse and keyboard
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		m_SDLKeyCode = e.key.keysym.sym;
		if (e.type == SDL_QUIT)
		{
			return false;
		}
		for (const auto& pair : m_KeyboardCommands)
		{
			if (e.type == Uint32(pair.first.first))
				HandleKeyboardInput(pair);
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

void dae::InputManager::ExecuteControllerInput(const std::pair<const dae::Controllerkey, std::unique_ptr<Command>>& it) const
{
	it.second->Execute();
}

void dae::InputManager::ExecuteKeyboardInput(const std::pair<const dae::Keyboardkey, std::unique_ptr<Command>>& it) const
{
	it.second->Execute();
}

void dae::InputManager::HandleControllerInput(const std::pair<const dae::Controllerkey, std::unique_ptr<Command>>& it) const
{
	if (m_InputKeyStroke.VirtualKey == WORD(it.first.second))
		ExecuteControllerInput(it);
}

void dae::InputManager::HandleKeyboardInput(const std::pair<const dae::Keyboardkey, std::unique_ptr<Command>>& it) const
{
	if (m_SDLKeyCode == int(it.first.second))
		ExecuteKeyboardInput(it);
}

void dae::InputManager::AddControllerInput(ControllerButton button, ControllerButtonState buttonState, std::unique_ptr<Command> action)
{
	m_ControllerCommands.insert({ Controllerkey(buttonState, button),std::move(action) });
}

void dae::InputManager::AddKeyboardInput(SDLK key, KeyboardButtonState keyState, std::unique_ptr<Command> action)
{
	m_KeyboardCommands.insert({ Keyboardkey(keyState,key),std::move(action) });
}
