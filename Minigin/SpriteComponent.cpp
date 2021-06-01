#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"

using namespace Horizon;

SpriteComponent::SpriteComponent(GameObject* parent, SDL_Rect srcRect, int spriteAmount) : Component(parent),
	m_CurrentSprite{0},
	m_SrcRect{srcRect},
	m_SpriteAmount{spriteAmount}
{
	m_SpriteWidth = m_SrcRect.w / m_SpriteAmount;
}

int SpriteComponent::GetCurrentSprite()
{
	return m_CurrentSprite;
}

void SpriteComponent::Initialize()
{
	m_pTextureComponent = m_pGameObject->GetComponent<TextureComponent>();

	if (m_pTextureComponent == nullptr)
	{
		Logger::LogWarning("SpriteComponent::Initialize() >> GameObject does not have transformComponent");
		return;
	}

	m_pTextureComponent->SetSrcRect(m_SrcRect.x, m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void SpriteComponent::SetCurrentSprite(int spriteNumber)
{
	m_CurrentSprite = spriteNumber;
	m_pTextureComponent->SetSrcRect(m_SrcRect.x + (m_SpriteWidth * m_CurrentSprite), m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void Horizon::SpriteComponent::NextSprite()
{
	m_CurrentSprite++;
	m_pTextureComponent->SetSrcRect(m_SrcRect.x + (m_SpriteWidth * m_CurrentSprite), m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void Horizon::SpriteComponent::PreviousSprite()
{
	m_CurrentSprite--;
	m_pTextureComponent->SetSrcRect(m_SrcRect.x + (m_SpriteWidth * m_CurrentSprite), m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}


