#pragma once
#include "Component.h"
#include <functional>

namespace Horizon
{
	class GameObject;

	using TimerFunction = std::function<void(float)>;

	class TimedFunction final
	{
	public:
		TimedFunction(bool isLooping, float maxTime);
		void SetTimerFunction(const TimerFunction& timerFunction);

		void Activate();
		void Deactivate();
		void Update();
	private:
		TimerFunction m_TimerFunction;

		float m_ElapsedTime;
		float m_TotalTime;
		float m_MaxTime;
		bool m_IsLooping;
		bool m_IsActive;
	};

}

