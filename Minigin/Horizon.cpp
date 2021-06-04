#include "MiniginPCH.h"
#include "Horizon.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "SDLSoundSystem.h"
#include "SoundSystemServiceLocator.h"
#include "Timer.h"
#include "Command.h"
#include "TriggerManager.h"
#include <thread>

void Horizon::Horizon::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());

	m_pWindow = SDL_CreateWindow("Programming 4 assignment", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);

	if (m_pWindow == nullptr)
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());

	Renderer::GetInstance().Init(m_pWindow);

	//SDL_Mixer
	const int audio_rate = 44100;
	const Uint16 audio_format = MIX_DEFAULT_FORMAT;
	const int audio_channels = 1;
	const int audio_buffers = 4096;

	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) < 0)
	{
		Logger::LogError("Horizon::Initialize >> SDL_MIXER could not be initialized");
		exit(1);
	}

	if (Mix_Init(MIX_INIT_MOD) != MIX_INIT_MOD)
		Logger::LogError("Horizon::Initialize >> SDL_MIXER could not be initialized");

	SoundSystemServiceLocator::RegisterSoundSystem(new SDLSoundSystem());
}

void Horizon::Horizon::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	Mix_CloseAudio();
	Mix_Quit();
	SoundSystemServiceLocator::ReleaseServiceLocator();
	SDL_Quit();
}

void Horizon::Horizon::Run() //no fpsCap because vsync does it automatically
{
	Initialize();
	{
		auto& input = InputManager::GetInstance();
		const auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& soundSystem = SoundSystemServiceLocator::GetSoundSystem();
		sceneManager.Initialize();

		bool doContinue = true;
		Timer::GetInstance().UpdateLastTime();

		float lag = 0.0f;
		std::thread audioThread{ [&doContinue, &soundSystem]()
			{
			while (doContinue)
				soundSystem.Update();
			} };

		while (doContinue)
		{
			Timer::GetInstance().Update();
			lag += Timer::GetInstance().GetDeltaTime();

			doContinue = input.ProcessInput();

			while (lag >= Timer::GetInstance().GetFixedFrameTime())
			{
				sceneManager.FixedUpdate();
				lag -= Timer::GetInstance().GetFixedFrameTime();
			}
			
			sceneManager.Update();
			sceneManager.LateUpdate();
			renderer.Render(lag / Timer::GetInstance().GetFixedFrameTime());
			TriggerManager::GetInstance().Update();
			Timer::GetInstance().CalculateFPS();
		}
		audioThread.join();
	}

	Cleanup();
}
