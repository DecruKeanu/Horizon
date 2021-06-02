#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"

using namespace Horizon;

SpriteComponent::SpriteComponent(GameObject* parent, SDL_Rect srcRect, int spriteAmount) : Component(parent),
	m_CurrentSprite{0},
	m_SrcRect{srcRect},
	m_SpriteAmount{spriteAmount}
{
	const float spriteWidthRounded = std::roundf(float(m_SrcRect.w) / m_SpriteAmount);

	m_SpriteWidth = int(spriteWidthRounded);
}

int SpriteComponent::GetCurrentSprite()
{
	return m_CurrentSprite;
}

void SpriteComponent::Initialize()
{
	m_pTextureComponent = m_pGameObject->GetComponent<TextureComponent>();
	m_pTextureComponent->SetSrcRect(m_SrcRect.x, m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void SpriteComponent::SetCurrentSprite(int spriteNumber)
{
	if (m_CurrentSprite == spriteNumber)
		return;

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


