#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPS.h"

dae::GameObject::~GameObject()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		SafeDelete<ObjectComponent>(m_pObjectComponents[idx]);
}

void dae::GameObject::BeginPlay()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->BeginPlay();
}

void dae::GameObject::FixedUpdate()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->FixedUpdate();
}

void dae::GameObject::Update()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->Update();
}

void dae::GameObject::LateUpdate()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->LateUpdate();
}

void dae::GameObject::Render() const
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->Render();
}

void dae::GameObject::AddComponent(ObjectComponent* component)
{
	m_pObjectComponents.push_back(component);
}
