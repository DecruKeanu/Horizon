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
	RespawnComponent(Horizon::GameObject* pParent, const Horizon::IPoint2 spawnPos, float respawnTime);

private:
	void Initialize() override;
	void PersistentUpdate() override;

	float m_respawnTime;
	bool m_Activated;
	bool m_ObjectActivated;
	Horizon::TimedFunctionComponent* m_pRespawnTimedFunction = nullptr;
};

