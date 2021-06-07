#include "GamePCH.h"
#include "RespawnComponent.h"

#include <TimedFunctionComponent.h>

#include "Coily.h"
#include "SlickSam.h"
#include "UggWrongway.h"

#include <Scene.h>
#include <SceneManager.h>

RespawnComponent::RespawnComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime, bool PlayerControlled) : Component(pParent),
m_RespawnStarted{},
m_ObjectActivated{}
{
	m_pRespawnTimedFunction = new Horizon::TimedFunctionComponent(pParent, false, true, respawnTime);
	m_pRespawnTimedFunction->SetTimerFunction([this, spawnPos, respawnTime, type, PlayerControlled](float)
		{
			if (m_pGameObject->GetIdentifier() == "Coily")
			{
				const Coily coilyPrefab = Coily(spawnPos, respawnTime, PlayerControlled);
				Horizon::SceneManager::GetInstance().GetActiveScene()->Add(coilyPrefab.GetGameObject());
			}
			else if (m_pGameObject->GetIdentifier() == "SlickSam")
			{
				const SlickSam slickSam = SlickSam(spawnPos, type, respawnTime);
				Horizon::SceneManager::GetInstance().GetActiveScene()->Add(slickSam.GetGameObject());
			}
			else if (m_pGameObject->GetIdentifier() == "UggWrongway")
			{
				const UggWrongway uggWrongway = UggWrongway(spawnPos, type, respawnTime);
				Horizon::SceneManager::GetInstance().GetActiveScene()->Add(uggWrongway.GetGameObject());
			}
			m_RespawnStarted = false;
			m_ObjectActivated = false;
			m_pRespawnTimedFunction->Deactivate();
		});
	m_pGameObject->AddComponent(m_pRespawnTimedFunction);
}

void RespawnComponent::PersistentUpdate()
{
	if (m_pGameObject->GetIsActive())
	{
		if (m_ObjectActivated == false)
			m_ObjectActivated = true;
	}
	else
	{
		if (m_ObjectActivated && m_RespawnStarted == false)
		{
			m_RespawnStarted = true;
			m_pRespawnTimedFunction->Activate();
		}
	}
}
