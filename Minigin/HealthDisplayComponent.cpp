#include "MiniginPCH.h"
#include "HealthDisplayComponent.h"
#include "TextComponent.h"

Horizon::HealthDisplayComponent::HealthDisplayComponent(GameObject* parent) : Component(parent),
	m_StartText{}
{

}

void Horizon::HealthDisplayComponent::Initialize()
{
	m_pParentTextComponent = m_pGameObject->GetComponent<TextComponent>();

	m_StartText = m_pParentTextComponent->GetText();
	m_pParentTextComponent->SetText(m_StartText + std::to_string(3));
}

void Horizon::HealthDisplayComponent::LifeLost(int currentLives) const
{
	m_pParentTextComponent->SetText(m_StartText + std::to_string(currentLives));
}

void Horizon::HealthDisplayComponent::GameOver() const
{
	m_pParentTextComponent->SetText(m_StartText + "Game Over");
}

