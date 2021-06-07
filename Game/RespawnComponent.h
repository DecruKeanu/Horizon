#pragma once
#include <Component.h>

namespace Horizon
{
	class Gameobject;
	class TimedFunctionComponent;
}

class RespawnComponent final : public Horizon::Component
{
public:
	RespawnComponent(Horizon::GameObject* pParent, const Horizon::IPoint2& spawnPos, const std::string& type, float respawnTime, bool PlayerControlled = false);
private:
	//Component functions
	void PersistentUpdate() override;

	//Components
	Horizon::TimedFunctionComponent* m_pRespawnTimedFunction = nullptr;

	//Variables
	bool m_RespawnStarted;
	bool m_ObjectActivated;
};

