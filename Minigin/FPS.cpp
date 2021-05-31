#include "MiniginPCH.h"
#include "FPS.h"
#include "TextComponent.h"
#include "Timer.h"

Horizon::FPS::FPS(GameObject* parent) : Component(parent) 
{

}

void Horizon::FPS::Initialize()
{
	m_pTextComponent = m_pGameObject->GetComponent<TextComponent>();
}

void Horizon::FPS::Update()
{
	if (m_pTextComponent)
		m_pTextComponent->SetText(std::to_string(Timer::GetInstance().GetFPS()) + " FPS");
}

