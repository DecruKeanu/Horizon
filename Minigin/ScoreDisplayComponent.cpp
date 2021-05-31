#include "MiniginPCH.h"
#include "ScoreDisplayComponent.h"
#include "TextComponent.h"

Horizon::ScoreDisplayComponent::ScoreDisplayComponent(GameObject* parent) : Component(parent),
	m_StartText{}
{

}

void Horizon::ScoreDisplayComponent::Initialize()
{
	m_pParentTextComponent = m_pGameObject->GetComponent<TextComponent>();

	m_StartText = m_pParentTextComponent->GetText();
	m_pParentTextComponent->SetText(m_StartText + std::to_string(0));
}

void Horizon::ScoreDisplayComponent::ScoreIncreased(int score) const
{
	m_pParentTextComponent->SetText(m_StartText + std::to_string(score));
}

