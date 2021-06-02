#pragma once
#include "Component.h"
#include <functional>

namespace Horizon
{
	class GameObject;

	using TimerFunction = std::function<void()>;

	class TimedFunctionComponent final : public Component
	{
	public:
		TimedFunctionComponent(GameObject* pParent, bool isLooping, float maxTime);
		void SetTimerFunction(const TimerFunction& timerFunction);

		void Activate();
		void Deactivate();
	private:
		void Update() override;

		TimerFunction m_TimerFunction;

		float m_ElapsedTime;
		float m_MaxTime;
		bool m_IsLooping;
		bool m_IsActive;
	};

}

