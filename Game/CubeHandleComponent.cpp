#include "GamePCH.h"
#include "CubeHandleComponent.h"
#include <SpriteComponent.h>

CubeHandleComponent::CubeHandleComponent(Horizon::GameObject* parent, int level) : Component(parent),
m_Level{ level },
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
	if (m_IsActivated && m_Level != 3)
		return;

	m_jumps++;

	if (m_Level == 1)
	{
		m_pSpriteComponent->NextSprite();
		m_IsActivated = true;
	}
	else if (m_Level == 2)
	{
		m_IsActivated = (m_jumps == 2);
		m_pSpriteComponent->SetCurrentSprite(m_jumps);
	}
	else if (m_Level == 3)
	{
		m_pSpriteComponent->NextSprite();
		m_IsActivated = (m_jumps % 2);
	}
}

void CubeHandleComponent::DeactivateCube()
{
	m_jumps--;

	if (m_jumps < 0)
	{
		m_jumps = 0;
		return;
	}


	if (m_Level == 1 && m_IsActivated)
	{
		m_IsActivated = false;

		m_pSpriteComponent->PreviousSprite();
	}
	else if (m_Level == 2 && m_jumps >= 0)
	{
		m_IsActivated = false;
		Horizon::Logger::LogInfo("cube reverted");
		m_pSpriteComponent->SetCurrentSprite(m_jumps);
	}
	else if (m_Level == 3 && m_IsActivated)
	{
		m_IsActivated = (m_jumps % 2);
		m_pSpriteComponent->PreviousSprite();
	}
}

bool CubeHandleComponent::GetisActivated() const
{
	return m_IsActivated;
}

void CubeHandleComponent::SwitchSprite()
{
	m_pSpriteComponent->NextSprite();
}
