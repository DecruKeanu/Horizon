#include "MiniginPCH.h"
#include "FPS.h"
#include "TextComponent.h"
#include "Timer.h"

dae::FPS::FPS(GameObject* parent) : Component(parent) 
{

}

void dae::FPS::Initialize()
{
	m_pTextComponent = m_pGameObject->GetComponent<dae::TextComponent>();
}

void dae::FPS::Update()
{
	if (m_pTextComponent)
		m_pTextComponent->SetText(std::to_string(Timer::GetInstance().GetFPS()) + " FPS");
}

