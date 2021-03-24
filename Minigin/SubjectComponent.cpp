#include "MiniginPCH.h"
#include "SubjectComponent.h"

dae::SubjectComponent::~SubjectComponent()
{
	for (size_t idx{}; idx < m_Observers.size(); idx++)
	{
		delete m_Observers[idx];
		m_Observers[idx] = nullptr;
	}
}

void dae::SubjectComponent::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void dae::SubjectComponent::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::find(m_Observers.begin(), m_Observers.end(), observer));
	m_Observers.shrink_to_fit();
}

void dae::SubjectComponent::Notify(const Event& event)
{
	for (size_t idx{}; idx < m_Observers.size(); idx++)
	{
		if (m_Observers[idx])
			m_Observers[idx]->OnNotify(event);
	}
}