#include "GamePCH.h"
#include "RespawnComponent.h"
#include <TimedFunctionComponent.h>
#include <Scene.h>
#include <SceneManager.h>
#include "Coily.h"

RespawnComponent::RespawnComponent(Horizon::GameObject* pParent, const Horizon::IPoint2 spawnPos, float respawnTime) : Component(pParent),
m_respawnTime{ respawnTime },
m_Activated{}
{
	m_pRespawnTimedFunction = new Horizon::TimedFunctionComponent(pParent, false, true, 0.1f);
	m_pRespawnTimedFunction->SetTimerFunction([this, spawnPos](float)
		{

			std::cout << "its working2";
			if (m_pGameObject->GetIdentifier() == "Coily")
			{
				std::cout << "its working3";
				Coily* const pCoilyPrefab = new Coily(spawnPos);
				Horizon::SceneManager::GetInstance().GetActiveScene()->Add(pCoilyPrefab->GetGameObject());
			}
			m_Activated = false;
			m_ObjectActivated = false;
			m_pRespawnTimedFunction->Deactivate();
		});
	m_pGameObject->AddComponent(m_pRespawnTimedFunction);
}

void RespawnComponent::Initialize()
{
	//m_pRespawnTimedFunction = new Horizon::TimedFunctionComponent(m_pGameObject, false, true, 10.f);
	//m_pRespawnTimedFunction->SetTimerFunction([this](float)
	//	{
	//		if (m_pGameObject->GetIdentifier() == "Coily")
	//		{
	//			std::cout << "wut";
	//		}
	//		m_Activated = false;
	//		m_pRespawnTimedFunction->Deactivate();
	//	});
}

void RespawnComponent::PersistentUpdate()
{
	if (m_ObjectActivated == false && m_pGameObject->GetIsActive() == true)
		m_ObjectActivated = true;

	if (m_pGameObject->GetIsActive() == false && m_ObjectActivated && m_Activated == false)
	{
		m_Activated = true;
		std::cout << "its working1";
		m_pRespawnTimedFunction->Activate();
	}


}
