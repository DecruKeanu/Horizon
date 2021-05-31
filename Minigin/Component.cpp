#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

Horizon::Component::Component(GameObject* parent) :
	m_pGameObject{ parent }
{

}