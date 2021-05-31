#include "GamePCH.h"
#include "CubeHandleComponent.h"
#include <TransformComponent.h>
#include <SpriteComponent.h>

CubeHandleComponent::CubeHandleComponent(Horizon::GameObject* parent) : Component(parent),
	m_IsActivated{false}
{

}

void CubeHandleComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject->GetComponent<Horizon::SpriteComponent>();
	m_pTransformComponent = m_pGameObject->GetComponent<Horizon::TransformComponent>();
	if (m_pSpriteComponent == nullptr)
	{
		Horizon::Logger::LogWarning("QBertMovementComponent::Initialize >> QBert does not have spriteComponent");
		return;
	}
	if (m_pTransformComponent == nullptr)
	{
		Horizon::Logger::LogWarning("QBertMovementComponent::Initialize >> QBert does not have transformComponent");
		return;
	}
}

void CubeHandleComponent::ActivateCube(const Horizon::IPoint2 playerPos)
{
	if (m_IsActivated)
		return;

	const Horizon::IPoint2 cubePos = { m_pTransformComponent->GetPosition().x,m_pTransformComponent->GetPosition().y };

	if (cubePos.x == playerPos.x - 15 && cubePos.y == playerPos.y + 15)
	{
		m_IsActivated = true;
		m_pSpriteComponent->SetCurrentSprite(m_pSpriteComponent->GetCurrentSprite() + 1);
	}

}
