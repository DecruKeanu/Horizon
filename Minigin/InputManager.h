#pragma once
#include <map>
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
#include "Singleton.h"
#include "SDLK.h"



namespace Horizon
{
	class Command;

	enum class ControllerButton : WORD
	{
		ButtonA = VK_PAD_A,
		ButtonB = VK_PAD_B,
		ButtonX = VK_PAD_X,
		ButtonY = VK_PAD_Y,
		DPadUp = VK_PAD_DPAD_UP,
		DPadLeft = VK_PAD_DPAD_LEFT,
		DPadRight = VK_PAD_DPAD_RIGHT,
		DPadDown = VK_PAD_DPAD_DOWN,
		Start = VK_PAD_START,
		Select = VK_PAD_BACK,
		LeftThumbStick = VK_PAD_LTHUMB_PRESS,
		RightThumbStick = VK_PAD_RTHUMB_PRESS,
		LeftShoulder = VK_PAD_LSHOULDER,
		RightShoulder = VK_PAD_RSHOULDER,
		LeftTrigger = VK_PAD_LTRIGGER,
		RightTrigger = VK_PAD_RTRIGGER
	};

	enum class ControllerButtonState : WORD
	{
		ButtonDown = XINPUT_KEYSTROKE_KEYDOWN,
		ButtonUp = XINPUT_KEYSTROKE_KEYUP
	};
	enum class KeyboardButtonState : Uint32
	{
		KeyDown = 768,
		KeyUp = 769
	};

	using Controllerkey = std::pair<ControllerButtonState, ControllerButton>;
	using ControllerCommandsMap = std::map<Controllerkey, std::unique_ptr<Command>>;
	using ControllerButtonPair = std::pair<Controllerkey, std::unique_ptr<Command>>;

	using Keyboardkey = std::pair<KeyboardButtonState, SDLK>;
	using KeyboardCommandsMap = std::map<Keyboardkey, std::unique_ptr<Command>>;
	using KeyboardButtonPair = std::pair<Keyboardkey, std::unique_ptr<Command>>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void AddControllerInput(ControllerButton button, ControllerButtonState buttonState, std::unique_ptr<Command> action);
		void AddKeyboardInput(SDLK key, KeyboardButtonState keyState, std::unique_ptr<Command> action);
		bool IsControllerInputPressed(const ControllerButton& button);
		bool IsKeyboardInputPressed(const SDLK& key);
		void ClearInput();
		bool ProcessInput();
	private:
		void ExecuteControllerInput(const std::pair<const Controllerkey, std::unique_ptr<Command>>& it) const;
		void ExecuteKeyboardInput(const std::pair<const Keyboardkey, std::unique_ptr<Command>>& it) const;
		void HandleControllerInput(const std::pair<const Controllerkey, std::unique_ptr<Command>>& it) const;
		void HandleKeyboardInput(const std::pair<const Keyboardkey, std::unique_ptr<Command>>& it) const;
		SDL_Keycode m_SDLKeyCode{};
		Uint32 m_KeyboardInput{};
		XINPUT_KEYSTROKE m_InputKeyStroke{};
		int m_MaxAmountOfControllers{ XUSER_MAX_COUNT };
		XINPUT_STATE m_InputState{};
		ControllerCommandsMap m_ControllerCommands{};
		KeyboardCommandsMap m_KeyboardCommands{};
	};
}
