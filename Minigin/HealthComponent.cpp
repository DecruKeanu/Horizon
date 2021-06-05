#include "MiniginPCH.h"
#include "HealthComponent.h"
#include "SubjectComponent.h"

Horizon::HealthComponent::HealthComponent(GameObject* parent) : Component(parent),
    m_CurrentLives{3},
    m_pSubject{new SubjectComponent}
{

}

Horizon::HealthComponent::HealthComponent(GameObject* parent, int lives) : Component(parent),
m_CurrentLives{ lives },
m_pSubject{ new SubjectComponent } 
{

}

Horizon::HealthComponent::~HealthComponent()
{
    SafeDelete<SubjectComponent>(m_pSubject);
}

void Horizon::HealthComponent::DecreaseLive()
{
    if (m_CurrentLives > 0)
    {
        m_CurrentLives--;
        m_CurrentLives == 0 ? m_pSubject->Notify(PossibleEvent::GameOver) : m_pSubject->Notify(Event(PossibleEvent::PlayerDied, m_CurrentLives));
    }
}

void Horizon::HealthComponent::AddObserver(Observer* observer)
{
    m_pSubject->AddObserver(observer);
}

int Horizon::HealthComponent::GetCurrentLives() const
{
    return m_CurrentLives;
}

void Horizon::HealthComponent::SetCurrentLives(int currentLives)
{
    m_CurrentLives = currentLives;

    m_pSubject->Notify(Event(PossibleEvent::PreviousLevelData,m_CurrentLives));
}
