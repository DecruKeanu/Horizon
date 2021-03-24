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
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN) {

		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {

		}
	}

	//Xinput for controllers
	for (int idx{}; idx < m_MaxAmountOfControllers; idx++)
	{
		auto check = XInputGetState(idx, &m_InputState);

		if (check != ERROR_SUCCESS)
			continue;

		XInputGetKeystroke(idx, 0, &m_InputKeyStroke);
		
			for (const auto& pair : m_ConsoleCommands)
			{
				if (m_InputKeyStroke.Flags == WORD(pair.first.first))
					HandleInput(pair);
			}
	}
	return true;
}

void dae::InputManager::ExecuteInput(const std::pair<const dae::Controllerkey,std::unique_ptr<Command>>& it) const
{
		it.second->Execute();
}

void dae::InputManager::HandleInput(const std::pair<const dae::Controllerkey, std::unique_ptr<Command>>& it) const
{
	if (m_InputKeyStroke.VirtualKey == WORD(it.first.second))
		ExecuteInput(it);
}

void dae::InputManager::AddInput(ControllerButton button, ControllerButtonState buttonState, std::unique_ptr<Command> action)
{
	m_ConsoleCommands.insert({ Controllerkey(buttonState, button),std::move(action) });
}

//#include "MiniginPCH.h"
//#include "InputManager.h"
//#include <SDL.h>
//
//
//bool dae::InputManager::ProcessInput()
//{
//	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
//	XInputGetState(0, &m_CurrentState);
//
//	SDL_Event e;
//	while (SDL_PollEvent(&e)) {
//		if (e.type == SDL_QUIT) {
//			return false;
//		}
//		if (e.type == SDL_KEYDOWN) {
//
//		}
//		if (e.type == SDL_MOUSEBUTTONDOWN) {
//
//		}
//	}
//
//	return true;
//}
//
//bool dae::InputManager::IsPressed(ControllerButton button) const
//{
//	switch (button)
//	{
//	case ControllerButton::ButtonA:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
//	case ControllerButton::ButtonB:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
//	case ControllerButton::ButtonX:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
//	case ControllerButton::ButtonY:
//		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
//	default: return false;
//	}
//}