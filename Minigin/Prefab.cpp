#include "MiniginPCH.h"
#include "Prefab.h"


Horizon::GameObject* Horizon::Prefab::GetGameObject() const
{
	return m_pGameObject;
}

void Horizon::Prefab::SetGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}
