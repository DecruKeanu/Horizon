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
	m_Name{ "NoIdentifier" },
	m_Id{m_LastId++}
{

}

Horizon::GameObject::GameObject(const std::string& identifier):
	m_Name{identifier},
	m_Id{ m_LastId++ }
{

}

Horizon::GameObject::~GameObject()
{
	TriggerManager::GetInstance().RemoveTriggerComponent(GetComponent<TriggerComponent>());

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
	for (Component* const pComponent : m_pObjectComponents)
		pComponent->FixedUpdate();
}

void Horizon::GameObject::Update()
{
	for (Component* const pComponent : m_pObjectComponents)
		pComponent->Update();
}

void Horizon::GameObject::LateUpdate()
{
	for (Component* const pComponent : m_pObjectComponents)
		pComponent->LateUpdate();
}

void Horizon::GameObject::Render() const
{
	for (const Component* const pComponent : m_pObjectComponents)
		pComponent->Render();
}

void Horizon::GameObject::AddComponent(Component* component)
{
	m_pObjectComponents.push_back(component);
}

const std::string& Horizon::GameObject::GetName()
{
	return m_Name;
}

bool Horizon::GameObject::Equals(GameObject* pOther) const
{
	return (m_Id == pOther->m_Id);
}
