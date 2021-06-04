#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

size_t Horizon::Component::m_LastId{};

Horizon::GameObject* Horizon::Component::GetParent() const
{
	return m_pGameObject;
}

const std::string& Horizon::Component::GetIdentifier() const
{
	return m_Identifier;
}

Horizon::Component::Component(GameObject* parent) :
	m_pGameObject{ parent },
	m_Identifier{"NoIdentifier"},
	m_Id{ m_LastId++ }
{

}

Horizon::Component::Component(GameObject* parent, const std::string& identifier) : 
	m_pGameObject{ parent },
	m_Identifier{ identifier },
	m_Id{ m_LastId++ }
{

}

bool Horizon::Component::Equals(Component* pOther) const
{
	return (m_Id == pOther->m_Id);
}
