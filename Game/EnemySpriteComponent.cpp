#include "GamePCH.h"
#include "EnemySpriteComponent.h"
#include <GameObject.h>
#include <SpriteComponent.h>
#include "EnemyInputComponent.h"

EnemySpriteComponent::EnemySpriteComponent(Horizon::GameObject* pParent, const std::string& fileName, const SDL_Rect& srcRect) : Component(pParent),
m_CurrentSpriteNumber{ 5 }
{
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, fileName, srcRect, 8);
	m_pGameObject->AddComponent(m_pSpriteComponent);
}

void EnemySpriteComponent::Initialize()
{
	m_pInputComponent = m_pGameObject->GetComponent<EnemyInputComponent>();
	m_pSpriteComponent->Scale(2.f);
}

void EnemySpriteComponent::Update()
{
	if (m_pInputComponent == nullptr)
		return;

	const Horizon::IPoint2& move = m_pInputComponent->GetMove();

	if (move.x == 1)
		m_CurrentSpriteNumber = 5;
	else if (move.x == -1)
		m_CurrentSpriteNumber = 1;

	(move.x == 0 && move.y == 0) ? m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber - 1) : m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber);
}
