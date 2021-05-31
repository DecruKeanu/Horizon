#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

#include "TextureComponent.h"
#include "TextComponent.h"
#include "FPS.h"

Horizon::GameObject::~GameObject()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		SafeDelete<Component>(m_pObjectComponents[idx]);
}

void Horizon::GameObject::Initialize()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->Initialize();
}

void Horizon::GameObject::FixedUpdate()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->FixedUpdate();
}

void Horizon::GameObject::Update()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->Update();
}

void Horizon::GameObject::LateUpdate()
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->LateUpdate();
}

void Horizon::GameObject::Render() const
{
	for (size_t idx{}; idx < m_pObjectComponents.size(); idx++)
		m_pObjectComponents[idx]->Render();
}

void Horizon::GameObject::AddComponent(Component* component)
{
	m_pObjectComponents.push_back(component);
}
