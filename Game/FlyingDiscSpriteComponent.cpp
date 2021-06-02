#include "GamePCH.h"
#include "FlyingDiscSpriteComponent.h"
#include <SpriteComponent.h>
#include <Timer.h>
#include <TimedFunction.h>

FlyingDiscSpriteComponent::FlyingDiscSpriteComponent(Horizon::GameObject* pParent, const SDL_Rect& srcRect) : Component(pParent),
	m_SpriteTimer{},
	m_CurrentSpriteNumber{}
{
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, srcRect, 12);
	m_pGameObject->AddComponent(m_pSpriteComponent);

	ConstructTimedFunction();
}

void FlyingDiscSpriteComponent::ConstructTimedFunction()
{
	m_pTimedFunction = new Horizon::TimedFunction(m_pGameObject, true, 0.1f);
	m_pTimedFunction->SetTimerFunction([this]()
		{
			m_CurrentSpriteNumber++;
			m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber % 4);
		});

	m_pTimedFunction->Activate();
	m_pGameObject->AddComponent(m_pTimedFunction);
}

