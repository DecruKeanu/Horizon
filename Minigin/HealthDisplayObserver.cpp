#include "MiniginPCH.h"
#include "HealthDisplayObserver.h"
#include "HealthDisplayComponent.h"
#include "Events.h"

Horizon::HealthDisplayObserver::HealthDisplayObserver(HealthDisplayComponent* healthDisplayComponent) :
	m_pHealthDisplayComponent{healthDisplayComponent}
{

}

void Horizon::HealthDisplayObserver::OnNotify(const Event& event)
{
	switch (event.event)
	{
	case PossibleEvent::PlayerDied:
		m_pHealthDisplayComponent->LifeLost(event.GetData<int>());
			break;
	case PossibleEvent::GameOver:
		m_pHealthDisplayComponent->GameOver();
		break;
	}
}
