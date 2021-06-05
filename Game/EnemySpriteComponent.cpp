#include "GamePCH.h"
#include "EnemySpriteComponent.h"
#include <GameObject.h>
#include <SpriteComponent.h>
#include "EnemyInputComponent.h"

EnemySpriteComponent::EnemySpriteComponent(Horizon::GameObject* pParent, const std::string& fileName, const SDL_Rect& srcRect, int spriteAmount) : Component(pParent),
m_CurrentSpriteNumber{ 5 },
m_SpriteAmount{spriteAmount},
m_Move{}
{
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, fileName, srcRect, spriteAmount);
	m_pGameObject->AddComponent(m_pSpriteComponent);
}

void EnemySpriteComponent::SetMove(const Horizon::IPoint2& input)
{
	m_Move = input;
}

void EnemySpriteComponent::SetSrcRect(const SDL_Rect& srcRect)
{
	m_pSpriteComponent->SetSrcRect(srcRect);
}

void EnemySpriteComponent::SetSpriteAmount(const int spriteAmount)
{
	m_SpriteAmount = spriteAmount;
	m_pSpriteComponent->SetSpriteAmount(spriteAmount);
}

void EnemySpriteComponent::SetSpriteOffset(const Horizon::IPoint2& offset)
{
	m_pSpriteComponent->SetSpriteOffset(offset);
}

void EnemySpriteComponent::Initialize()
{
	m_pInputComponent = m_pGameObject->GetComponent<EnemyInputComponent>();
	m_pSpriteComponent->Scale(2.f);
}

void EnemySpriteComponent::Update()
{
	if (m_SpriteAmount == 2)
	{
		(m_Move.x == 0 && m_Move.y == 0) ? m_pSpriteComponent->SetCurrentSprite(0) : m_pSpriteComponent->SetCurrentSprite(1);
	}
	else
	{
		if (m_Move.x == 1 && m_Move.y == -1)
			m_CurrentSpriteNumber = 1;
		if (m_Move.x == -1 && m_Move.y == -1)
			m_CurrentSpriteNumber = 3;
		else if (m_Move.x == 1 && m_Move.y == 1)
			m_CurrentSpriteNumber = 5;
		else if (m_Move.x == -1 && m_Move.y == 1)
			m_CurrentSpriteNumber = 7;

		(m_Move.x == 0 && m_Move.y == 0) ? m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber - 1) : m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber);
	}
}
