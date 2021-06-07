#pragma once
#include <Scene.h>

class CubeHandleComponent;

namespace Horizon
{
	class TimedFunctionComponent;
	class HealthComponent;
	class ScoreComponent;
}

class VersusLevel final : public Horizon::Scene
{
public:
	VersusLevel(int level, int playerScore, int playerLives);
private:
	//Scene functions
	void Initialize() override;
	void PostInitialize() override;
	void Update() override;

	//Helper functions
	void BackToMainMenu();
	void ResetLevel();
	void NextLevel();

	//Components
	std::vector<CubeHandleComponent*> m_pCubeHandles;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::ScoreComponent* m_pPlayerScoreComponent = nullptr;
	Horizon::HealthComponent* m_pPlayerHealthComponent = nullptr;

	int m_Level;
	int m_PlayerScore;
	int m_PlayerLives;

	bool m_LevelCompleted;
	bool m_SwitchToNewLevel;
};

