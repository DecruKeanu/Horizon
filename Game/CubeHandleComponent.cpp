#include "GamePCH.h"
#include "CubeHandleComponent.h"
#include <SpriteComponent.h>

CubeHandleComponent::CubeHandleComponent(Horizon::GameObject* parent, const CubeType& cubeType) : Component(parent),
m_CubeType{ cubeType },
m_jumps{},
m_IsActivated{ false }
{

}

void CubeHandleComponent::Initialize()
{
	m_pSpriteComponent = m_pGameObject->GetComponent<Horizon::SpriteComponent>();
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
