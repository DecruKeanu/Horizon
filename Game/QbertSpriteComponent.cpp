#include "GamePCH.h"
#include "QbertSpriteComponent.h"
#include <GameObject.h>
#include <SpriteComponent.h>
#include "PlayerInputComponent.h"

QbertSpriteComponent::QbertSpriteComponent(Horizon::GameObject* pParent, const SDL_Rect& srcRect) : Component(pParent),
m_CurrentSpriteNumber{ 5 }
{
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, srcRect, 8);
	m_pGameObject->AddComponent(m_pSpriteComponent);
}

void QbertSpriteComponent::Initialize()
{
	m_pInputComponent = m_pGameObject->GetComponent<PlayerInputComponent>();
}

void QbertSpriteComponent::Update()
{
	const Horizon::IPoint2& move = m_pInputComponent->GetMove();

	if (move.x == -1 && move.y == -1)
		m_CurrentSpriteNumber = 3;
	else if (move.x == -1 && move.y == 1)
		m_CurrentSpriteNumber = 7;
	else if (move.x == 1 && move.y == 1)
		m_CurrentSpriteNumber = 5;
	else if (move.x == 1 && move.y == -1)
		m_CurrentSpriteNumber = 1;

	if (move.x == 0 && move.y == 0)
		m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber - 1);
	else
		m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber);
}
