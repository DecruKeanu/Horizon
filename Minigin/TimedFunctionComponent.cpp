#include "MiniginPCH.h"
#include "TimedFunctionComponent.h"
#include "Timer.h"

Horizon::TimedFunctionComponent::TimedFunctionComponent(GameObject* pParent, bool isLooping, float maxTime) : TimedFunctionComponent(pParent, isLooping, false, maxTime)
{

}

Horizon::TimedFunctionComponent::TimedFunctionComponent(Horizon::GameObject* pParent, bool isLooping, bool isPersistent, float maxTime) : Component(pParent),
m_IsLooping{ isLooping },
m_IsPersistent{isPersistent},
m_MaxTime{ maxTime },
m_ElapsedTime{},
m_TotalTime{},
m_IsActive{ false }
{
	m_TimerFunction = [](float) {};
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

void Horizon::TimedFunctionComponent::UpdateTimedFunction()
{
	if (m_IsActive == false)
		return;

	m_ElapsedTime += Timer::GetInstance().GetDeltaTime();
	m_TotalTime += Timer::GetInstance().GetDeltaTime();

	if (m_ElapsedTime >= m_MaxTime)
	{
		m_TimerFunction(m_TotalTime);

		(m_IsLooping) ? Activate() : Deactivate();
	}
}

void Horizon::TimedFunctionComponent::Update()
{
	if (m_IsPersistent == false)
		UpdateTimedFunction();
}

void Horizon::TimedFunctionComponent::PersistentUpdate()
{
	if (m_IsPersistent == true)
		UpdateTimedFunction();
}
