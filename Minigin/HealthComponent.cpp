#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "SubjectComponent.h"

dae::HealthComponent::HealthComponent(GameObject* parent) : ObjectComponent(parent),
    m_CurrentLives{3},
    m_pSubject{new SubjectComponent}
{

}

dae::HealthComponent::HealthComponent(GameObject* parent, int lives) : ObjectComponent(parent),
m_CurrentLives{ lives },
m_pSubject{ new SubjectComponent } 
{

}

dae::HealthComponent::~HealthComponent()
{
    SafeDelete<dae::SubjectComponent>(m_pSubject);
}

void dae::HealthComponent::DecreaseLive()
{
    if (m_CurrentLives > 0)
    {
        m_CurrentLives--;
        m_CurrentLives == 0 ? m_pSubject->Notify(PossibleEvent::GameOver) : m_pSubject->Notify(Event(PossibleEvent::PlayerDied, m_CurrentLives));
    }
}

void dae::HealthComponent::AddObserver(Observer* observer)
{
    m_pSubject->AddObserver(observer);
}

int dae::HealthComponent::GetCurrentLives() const
{
    return m_CurrentLives;
}