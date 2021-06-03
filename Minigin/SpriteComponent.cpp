#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "TextureComponent.h"

using namespace Horizon;

SpriteComponent::SpriteComponent(GameObject* parent,const std::string& fileName, const SDL_Rect& srcRect, int spriteAmount) : Component(parent),
m_CurrentSprite{ 0 },
m_SrcRect{ srcRect },
m_SpriteAmount{ spriteAmount }
{
	const float spriteWidthRounded = std::roundf(float(m_SrcRect.w) / m_SpriteAmount);

	m_SpriteWidth = int(spriteWidthRounded);

	//Component makes texture because sprite is dependent of a texture and texture should be knowhere else used
	m_pTextureComponent = new TextureComponent(m_pGameObject, fileName);
	m_pGameObject->AddComponent(m_pTextureComponent);
}

int SpriteComponent::GetCurrentSprite()
{
	return m_CurrentSprite;
}

void SpriteComponent::Initialize()
{
	m_pTextureComponent->SetSrcRect(m_SrcRect.x, m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void SpriteComponent::SetCurrentSprite(int spriteNumber)
{
	if (m_CurrentSprite == spriteNumber)
		return;
	if (m_CurrentSprite >= m_SpriteAmount)
	{
		Logger::LogWarning("SpriteComponent::SetCurrentSprite >> spriteNumber succeeds spriteAmount, call ignored");
		return;
	}

	m_CurrentSprite = spriteNumber;
	m_pTextureComponent->SetSrcRect(m_SrcRect.x + (m_SpriteWidth * m_CurrentSprite), m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void Horizon::SpriteComponent::NextSprite()
{
	(m_CurrentSprite == m_SpriteAmount - 1) ? m_CurrentSprite = 0 : m_CurrentSprite++;
	m_pTextureComponent->SetSrcRect(m_SrcRect.x + (m_SpriteWidth * m_CurrentSprite), m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void Horizon::SpriteComponent::PreviousSprite()
{
	(m_CurrentSprite == m_SpriteAmount - 1) ? m_CurrentSprite = 0 : m_CurrentSprite--;
	m_pTextureComponent->SetSrcRect(m_SrcRect.x + (m_SpriteWidth * m_CurrentSprite), m_SrcRect.y, m_SpriteWidth, m_SrcRect.h);
}

void Horizon::SpriteComponent::Scale(float scale)
{
	m_pTextureComponent->SetScale(scale);
}


