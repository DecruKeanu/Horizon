#pragma once
#include <Scene.h>

namespace Horizon
{
	class TimedFunctionComponent;
	class HealthComponent;
	class ScoreComponent;
}

class CubeHandleComponent;

class VersusLevel final : public Horizon::Scene
{
public:
	VersusLevel(int level, int playerScore, int playerLives);
private:
	void Initialize() override;
	void PostInitialize() override;
	void Update() override;

	void BackToMainMenu();
	void ResetLevel();
	void NextLevel();

	int m_Level;
	std::vector<CubeHandleComponent*> m_pCubeHandles;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;

	Horizon::HealthComponent* m_pPlayerHealthComponent = nullptr;
	Horizon::ScoreComponent* m_pPlayerScoreComponent = nullptr;

	int m_PlayerScore;
	int m_PlayerLives;

	bool m_LevelCompleted;
	bool m_SwitchToNewLevel;


};

