#include "MiniginPCH.h"
#include "ScoreDisplayObserver.h"
#include "ScoreDisplayComponent.h"
#include "Events.h"
dae::ScoreDisplayObserver::ScoreDisplayObserver(ScoreDisplayComponent* scoreDisplayComponent) :
	m_pScoreDisplayComponent{scoreDisplayComponent}
{

}

void dae::ScoreDisplayObserver::OnNotify(const Event& event)
{
	switch (event.event)
	{
	case PossibleEvent::ColorChange:
		m_pScoreDisplayComponent->ScoreIncreased(event.GetData<int>());
		break;
	case PossibleEvent::RemainingDisc:
		m_pScoreDisplayComponent->ScoreIncreased(event.GetData<int>());
		break;
	case PossibleEvent::CatchingSamOrSlick:
		m_pScoreDisplayComponent->ScoreIncreased(event.GetData<int>());
		break;
	case PossibleEvent::DefeatCoily:
		m_pScoreDisplayComponent->ScoreIncreased(event.GetData<int>());
		break;
	}
}