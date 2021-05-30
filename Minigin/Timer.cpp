#include "MiniginPCH.h"
#include "Timer.h"

using namespace std::chrono;

void dae::Timer::UpdateLastTime()
{
	m_LastTime = high_resolution_clock::now();
}

void dae::Timer::UpdateGameLoop()
{
	m_CurrentTime = high_resolution_clock::now();
	m_DeltaTime = duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;
}

void dae::Timer::CalculateFPS()
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

std::chrono::steady_clock::time_point dae::Timer::getCurrentTime() const
{
	return m_CurrentTime;
}

float dae::Timer::GetDeltaTime() const
{
	return m_DeltaTime;
}

float dae::Timer::GetFixedFrameTime() const
{
	return m_FixedSecPerFrame;
}

int dae::Timer::GetFPS() const
{
	return m_FPS;
}

