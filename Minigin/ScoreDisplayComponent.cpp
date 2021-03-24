#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"
#include "TextComponent.h"

dae::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* parent) : ObjectComponent(parent),
	m_StartText{}
{

}

void dae::ScoreDisplayComponent::BeginPlay()
{
	m_pParentTextComponent = m_pGameObject->GetComponent<TextComponent>();

	m_StartText = m_pParentTextComponent->GetText();
	m_pParentTextComponent->SetText(m_StartText + std::to_string(0));
}

void dae::ScoreDisplayComponent::ScoreIncreased(int score) const
{
	m_pParentTextComponent->SetText(m_StartText + std::to_string(score));
}

