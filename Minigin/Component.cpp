#include "MiniginPCH.h"
#include "Component.h"
#include "GameObject.h"

dae::Component::Component(GameObject* parent) :
	m_pGameObject{ parent }
{

}