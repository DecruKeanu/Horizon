#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

Horizon::GameObject* Horizon::Component::GetParent() const
{
	return m_pGameObject;
}

Horizon::Component::Component(GameObject* parent) :
	m_pGameObject{ parent }
{

}