#include "MiniginPCH.h"
#include "SubjectComponent.h"

Horizon::SubjectComponent::~SubjectComponent()
{
	for (size_t idx{}; idx < m_Observers.size(); idx++)
	{
		delete m_Observers[idx];
		m_Observers[idx] = nullptr;
	}
	m_Observers.clear();
}

void Horizon::SubjectComponent::AddObserver(Observer* observer)
{
	m_Observers.push_back(observer);
}

void Horizon::SubjectComponent::RemoveObserver(Observer* observer)
{
	m_Observers.erase(std::find(m_Observers.begin(), m_Observers.end(), observer));
	m_Observers.shrink_to_fit();
}

void Horizon::SubjectComponent::Notify(const Event& event)
{
	for (size_t idx{}; idx < m_Observers.size(); idx++)
	{
		if (m_Observers[idx])
			m_Observers[idx]->OnNotify(event);
	}
}