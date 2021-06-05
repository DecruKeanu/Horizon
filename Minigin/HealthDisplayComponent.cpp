#include "MiniginPCH.h"
#include "HealthDisplayComponent.h"
#include "TextComponent.h"

Horizon::HealthDisplayComponent::HealthDisplayComponent(GameObject* parent, int health) : Component(parent),
m_StartHealth{ health }
{

}

void Horizon::HealthDisplayComponent::Initialize()
{
	m_pParentTextComponent = m_pGameObject->GetComponent<TextComponent>();

	m_pParentTextComponent->SetText(std::to_string(m_StartHealth));
}

void Horizon::HealthDisplayComponent::SetHealthText(int currentLives) const
{
	if (m_pParentTextComponent)
		m_pParentTextComponent->SetText(std::to_string(currentLives));
}

void Horizon::HealthDisplayComponent::GameOver() const
{
	m_pParentTextComponent->SetText("Game Over");
}

