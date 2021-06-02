#include "MiniginPCH.h"
#include "Timer.h"
#include "TimedFunction.h"
using namespace std::chrono;

void Horizon::Timer::UpdateLastTime()
{
	m_LastTime = high_resolution_clock::now();
}

void Horizon::Timer::Update()
{
	m_CurrentTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;
}

void Horizon::Timer::CalculateFPS()
{
	m_FPSTimer += m_DeltaTime;
	m_FPSCount++;

	if (m_FPSTimer >= 1.0f)
	{
		m_FPS = m_FPSCount;
		m_FPSCount = 0;
		m_FPSTimer -= 1.0f;
	}
}

std::chrono::steady_clock::time_point Horizon::Timer::getCurrentTime() const
{
	return m_CurrentTime;
}

float Horizon::Timer::GetDeltaTime() const
{
	return m_DeltaTime;
}

float Horizon::Timer::GetFixedFrameTime() const
{
	return m_FixedSecPerFrame;
}

int Horizon::Timer::GetFPS() const
{
	return m_FPS;
}
