#pragma once
#include <map>
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib,"XInput.lib")
#include "Singleton.h"

class Command;
namespace dae
{
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
		KeyDown = XINPUT_KEYSTROKE_KEYDOWN,
		KeyUp = XINPUT_KEYSTROKE_KEYUP
	};

	using Controllerkey = std::pair<ControllerButtonState, ControllerButton>;
	using ControllerCommandsMap = std::map<Controllerkey, std::unique_ptr<Command>>;
	using ControllerButtonPair = std::pair <Controllerkey, std::unique_ptr<Command>>;

	class InputManager final : public Singleton<InputManager>
	{
	public:
		void AddInput(ControllerButton button, ControllerButtonState, std::unique_ptr<Command> action);
		bool ProcessInput();
	private:
		void ExecuteInput(const std::pair<const dae::Controllerkey, std::unique_ptr<Command>>& it) const;
		void HandleInput(const std::pair<const dae::Controllerkey, std::unique_ptr<Command>>& it) const;
		XINPUT_KEYSTROKE m_InputKeyStroke{};
		int m_MaxAmountOfControllers{ XUSER_MAX_COUNT };
		XINPUT_STATE m_InputState{};
		ControllerCommandsMap m_ConsoleCommands{};
	};
}

//#pragma once
//#include <XInput.h>
//#include "Singleton.h"
//
//namespace dae
//{
//	enum class ControllerButton
//	{
//		ButtonA,
//		ButtonB,
//		ButtonX,
//		ButtonY
//	};
//
//	class InputManager final : public Singleton<InputManager>
//	{
//	public:
//		bool ProcessInput();
//		bool IsPressed(ControllerButton button) const;
//	private:
//		XINPUT_STATE m_CurrentState{};
//	};
//
//}