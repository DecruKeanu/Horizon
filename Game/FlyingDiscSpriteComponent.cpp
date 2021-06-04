#include "GamePCH.h"
#include "FlyingDiscSpriteComponent.h"
#include <SpriteComponent.h>
#include <Timer.h>
#include <TimedFunction.h>

FlyingDiscSpriteComponent::FlyingDiscSpriteComponent(Horizon::GameObject* pParent, const std::string& textureName, const SDL_Rect& srcRect) : Component(pParent)
{
	//Component makes sprite because sprite is knowhere else used and this class defines the spritebehaviour
	m_pSpriteComponent = new Horizon::SpriteComponent(m_pGameObject,textureName, srcRect, 4);
	m_pSpriteComponent->Scale(2.f);
	m_pGameObject->AddComponent(m_pSpriteComponent);
}

FlyingDiscSpriteComponent::~FlyingDiscSpriteComponent()
{
	//Horizon::Timer::GetInstance().RemoveTimedFunction(m_pTimedFunction);
	//SafeDelete(m_pTimedFunction);
}

void FlyingDiscSpriteComponent::Initialize()
{
	m_pTimedFunction = new Horizon::TimedFunction(true, 0.1f);
	m_pTimedFunction->SetTimerFunction([this](float)
		{
			m_pSpriteComponent->NextSprite();
		});

	m_pTimedFunction->Activate();
	Horizon::Timer::GetInstance().AddTimedFunction(m_pTimedFunction);
}

