#include "GamePCH.h"
#include "CubeHandleComponent.h"
#include <SpriteComponent.h>

CubeHandleComponent::CubeHandleComponent(Horizon::GameObject* parent) : Component(parent),
	m_IsActivated{false}
{

}

void CubeHandleComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject->GetComponent<Horizon::SpriteComponent>();

	if (m_pSpriteComponent == nullptr)
	{
		Horizon::Logger::LogWarning("QBertMovementComponent::Initialize >> QBert does not have spriteComponent");
		return;
	}
}

void CubeHandleComponent::ActivateCube()
{
	m_IsActivated = true;
	m_pSpriteComponent->SetCurrentSprite(m_pSpriteComponent->GetCurrentSprite() + 1);
}
