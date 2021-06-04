#include "GamePCH.h"
#include "PlayerSpriteComponent.h"
#include <GameObject.h>
#include <SpriteComponent.h>
#include "PlayerInputComponent.h"

PlayerSpriteComponent::PlayerSpriteComponent(Horizon::GameObject* pParent,const std::string& fileName, const SDL_Rect& srcRect) : Component(pParent),
m_CurrentSpriteNumber{ 5 }
{
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject,fileName, srcRect, 8);
	m_pGameObject->AddComponent(m_pSpriteComponent);
}

void PlayerSpriteComponent::Initialize()
{
	m_pInputComponent = m_pGameObject->GetComponent<PlayerInputComponent>();
	m_pSpriteComponent->Scale(2.f);
}

void PlayerSpriteComponent::Update()
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

	(move.x == 0 && move.y == 0) ? m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber - 1) : m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber);
}
