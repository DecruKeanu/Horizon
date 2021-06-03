#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "TriggerManager.h"
#include "Renderer.h"

#include "TextureComponent.h"
#include "TriggerComponent.h"
#include "TextComponent.h"
#include "FPS.h"

size_t Horizon::GameObject::m_LastId{};

Horizon::GameObject::GameObject() : 
	m_Identifier{ "NoIdentifier" },
	m_Id{m_LastId++},
	m_IsActive{true}
{

}

Horizon::GameObject::GameObject(const std::string& identifier):
	m_Identifier{identifier},
	m_Id{ m_LastId++ },
	m_IsActive{true}
{

}

Horizon::GameObject::~GameObject()
{
	for (Component* const pComponent : m_pObjectComponents)
		SafeDelete<Component>(pComponent);
}

void Horizon::GameObject::Initialize()
{
	for (Component* const pComponent : m_pObjectComponents)
		pComponent->Initialize();
}

void Horizon::GameObject::FixedUpdate()
{
	if (!m_IsActive)
		return;

	for (Component* const pComponent : m_pObjectComponents)
		pComponent->FixedUpdate();
}

void Horizon::GameObject::Update()
{
	if (!m_IsActive)
		return;

	for (Component* const pComponent : m_pObjectComponents)
		pComponent->Update();
}

void Horizon::GameObject::LateUpdate()
{
	if (!m_IsActive)
		return;

	for (Component* const pComponent : m_pObjectComponents)
		pComponent->LateUpdate();
}

void Horizon::GameObject::Render() const
{
	if (!m_IsActive)
		return;

	for (const Component* const pComponent : m_pObjectComponents)
		pComponent->Render();
}

void Horizon::GameObject::AddComponent(Component* component)
{
	m_pObjectComponents.push_back(component);
}

const std::string& Horizon::GameObject::GetIdentifier()
{
	return m_Identifier;
}

bool Horizon::GameObject::Equals(GameObject* pOther) const
{
	return (m_Id == pOther->m_Id);
}

bool Horizon::GameObject::GetIsActive() const
{
	return m_IsActive;
}

void Horizon::GameObject::Deactivate()
{
	m_IsActive = false;
}
