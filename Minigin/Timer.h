#pragma once
#include "Singleton.h"
#include "SDL.h"
#include <chrono>

namespace Horizon
{
	class TimedFunction;

	class Timer final : public Singleton<Timer>
	{
	public:
		void UpdateLastTime();
		void Update();
		void CalculateFPS();
		std::chrono::steady_clock::time_point getCurrentTime() const;
		float GetDeltaTime() const;
		float GetFixedFrameTime() const;
		int GetFPS() const;

		void AddTimedFunction(TimedFunction* pTimedFunction);
		void RemoveTimedFunction(TimedFunction* pTimedFunction);
	private:
		std::chrono::steady_clock::time_point m_CurrentTime{};
		std::chrono::steady_clock::time_point m_LastTime{};
		float m_FPSTimer{};
		const float m_FixedSecPerFrame = 1/144.f; 
		float m_DeltaTime{};
		int m_FPS{};
		int m_FPSCount{};

		std::vector<TimedFunction*> m_pTimedFunctions;
	};
}
