#include "MiniginPCH.h"
#include "HealthDisplayObserver.h"
#include "HealthDisplayComponent.h"
#include "Events.h"

Horizon::HealthDisplayObserver::HealthDisplayObserver(HealthDisplayComponent* healthDisplayComponent) :
	m_pHealthDisplayComponent{ healthDisplayComponent }
{

}

void Horizon::HealthDisplayObserver::OnNotify(const Event& event)
{
	switch (event.event)
	{
	case PossibleEvent::PreviousLevelData:
		m_pHealthDisplayComponent->SetHealthText(event.GetData<int>());
		break;
	case PossibleEvent::PlayerDied:
		m_pHealthDisplayComponent->SetHealthText(event.GetData<int>());
		break;
	case PossibleEvent::GameOver:
		m_pHealthDisplayComponent->GameOver();
		break;
	}
}
