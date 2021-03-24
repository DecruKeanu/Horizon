#include "MiniginPCH.h"
#include "ObjectComponent.h"
#include "GameObject.h"

dae::ObjectComponent::ObjectComponent(GameObject* parent) :
	m_pGameObject{ parent }
{

}