#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "SubjectComponent.h"

dae::ScoreComponent::ScoreComponent(GameObject* parent) : ObjectComponent(parent),
	m_CurrentScore{ 0 },
	m_pSubject{ new SubjectComponent() } 
{

}

dae::ScoreComponent::~ScoreComponent()
{
	SafeDelete<dae::SubjectComponent>(m_pSubject);
}

void dae::ScoreComponent::IncreaseScore(int scoreIncrease)
{
	m_CurrentScore += scoreIncrease;

	if (scoreIncrease == 25)
		m_pSubject->Notify(Event(PossibleEvent::ColorChange, m_CurrentScore));

	if (scoreIncrease == 50)
		m_pSubject->Notify(Event(PossibleEvent::RemainingDisc, m_CurrentScore));

	if (scoreIncrease == 300)
		m_pSubject->Notify(Event(PossibleEvent::CatchingSamOrSlick,m_CurrentScore));

	if (scoreIncrease == 500)
		m_pSubject->Notify(Event(PossibleEvent::DefeatCoily,m_CurrentScore));
}

void dae::ScoreComponent::AddObserver(Observer* observer)
{
	m_pSubject->AddObserver(observer);
}

