#include "MiniginPCH.h"
#include "TimedFunctionComponent.h"
#include "Timer.h"

Horizon::TimedFunctionComponent::TimedFunctionComponent(GameObject* pParent, bool isLooping, float maxTime) : Component(pParent),
	m_IsLooping{isLooping},
	m_MaxTime{maxTime},
	m_ElapsedTime{},
	m_IsActive{false}
{
	m_TimerFunction = []() {};
}

void Horizon::TimedFunctionComponent::SetTimerFunction(const TimerFunction& timerFunction)
{
	m_TimerFunction = timerFunction;
}

void Horizon::TimedFunctionComponent::Activate()
{
	m_ElapsedTime = 0.f;
	m_IsActive = true;
}

void Horizon::TimedFunctionComponent::Deactivate()
{
	m_IsActive = false;
	m_ElapsedTime = 0.f;
}

void Horizon::TimedFunctionComponent::Update()
{
	if (m_IsActive == false)
		return;

	m_ElapsedTime += Timer::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= m_MaxTime)
	{
		m_TimerFunction();

		if (m_IsLooping)
			Activate();
		else
			Deactivate();
	}

}
