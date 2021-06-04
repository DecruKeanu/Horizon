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

	m_pParentTextComponent->SetText(std::to_string(0));
}

void Horizon::ScoreDisplayComponent::ScoreIncreased(int score) const
{
	if (m_pParentTextComponent == nullptr)
		return;

	m_pParentTextComponent->SetText(std::to_string(score));
}

