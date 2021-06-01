#include "GamePCH.h"
#include "CubeHandleComponent.h"
#include <TransformComponent.h>
#include <SpriteComponent.h>

CubeHandleComponent::CubeHandleComponent(Horizon::GameObject* parent, const CubeType& cubeType) : Component(parent),
m_CubeType{ cubeType },
m_jumps{},
m_IsActivated{ false }
{

}

bool CubeHandleComponent::playerOnCube(const Horizon::IPoint2 playerPos)
{
	const Horizon::IPoint2 cubePos = { m_pTransformComponent->GetPosition().x,m_pTransformComponent->GetPosition().y };
	const Horizon::IPoint2 playerOffset = { 15,15 };

	if (cubePos.x == playerPos.x - playerOffset.x && cubePos.y == playerPos.y + playerOffset.y)
		return true;

	return false;
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

void CubeHandleComponent::ActivateCube()
{
	if (m_IsActivated && m_CubeType != CubeType::loopjumps)
		return;

	m_jumps++;
	switch (m_CubeType)
	{
	case CubeType::oneJump:
		m_IsActivated = true;
		m_pSpriteComponent->NextSprite();
		break;
	case CubeType::twoJumps:
		m_IsActivated = (m_jumps == 2);
		m_pSpriteComponent->NextSprite();
		break;
	case CubeType::loopjumps:
		m_IsActivated = m_jumps % 2;
		if (!m_IsActivated)
			m_pSpriteComponent->PreviousSprite();
		else
			m_pSpriteComponent->NextSprite();
		break;
	}
}

bool CubeHandleComponent::GetisActivated() const
{
	return m_IsActivated;
}
