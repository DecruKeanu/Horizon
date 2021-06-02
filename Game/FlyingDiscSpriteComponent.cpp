#include "GamePCH.h"
#include "FlyingDiscSpriteComponent.h"
#include <SpriteComponent.h>
#include <TimedFunctionComponent.h>

FlyingDiscSpriteComponent::FlyingDiscSpriteComponent(Horizon::GameObject* pParent, const SDL_Rect& srcRect) : Component(pParent),
	m_SpriteTimer{},
	m_CurrentSpriteNumber{}
{
	//Component makes sprite because sprite is knowhere else used and this class defines the spritebehavior
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject, srcRect, 12);
	m_pGameObject->AddComponent(m_pSpriteComponent);

	ConstructTimedFunction();
}

void FlyingDiscSpriteComponent::ConstructTimedFunction()
{
	Horizon::TimedFunctionComponent* const pTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, true, 0.1f);
	pTimedFunction->SetTimerFunction([this, pTimedFunction]()
		{
			m_CurrentSpriteNumber++;
			m_pSpriteComponent->SetCurrentSprite(m_CurrentSpriteNumber % 4);
		});

	pTimedFunction->Activate();

	m_pGameObject->AddComponent(pTimedFunction);
}

