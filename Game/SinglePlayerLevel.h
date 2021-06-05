#pragma once
#include <Scene.h>
#include "LevelType.h"

namespace Horizon
{
	class TimedFunctionComponent;
}


class CubeHandleComponent;

class SinglePlayerLevel final : public Horizon::Scene
{
public:
	SinglePlayerLevel(int level, const LevelType& levelType, int playerScore, int playerLives);
private:
	void Initialize() override;
	void Update() override;
	int m_Level;
	const LevelType m_LevelType;
	std::vector<CubeHandleComponent*> m_pCubeHandles;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;

	int m_PlayerScore;
	int m_PlayerLives;

	bool m_LevelCompleted;
	bool m_SwitchToNewLevel;
};

