#include "MiniginPCH.h"
#include "Prefab.h"

using namespace dae;

GameObject* Prefab::GetGameObject() const
{
	return m_pGameObject;
}

void Prefab::SetGameObject(GameObject* pGameObject)
{
	m_pGameObject = pGameObject;
}
