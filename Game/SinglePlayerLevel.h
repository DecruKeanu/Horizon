#pragma once
#include <Scene.h>

class CubeHandleComponent;

namespace Horizon
{
	class ScoreComponent;
	class HealthComponent;
	class TimedFunctionComponent;
}

class SinglePlayerLevel final : public Horizon::Scene
{
public:
	SinglePlayerLevel(int level,int playerScore, int playerLives);
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
	Horizon::ScoreComponent* m_pPlayerScoreComponent = nullptr;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::HealthComponent* m_pPlayerHealthComponent = nullptr;

	//Variables
	int m_Level;
	int m_PlayerScore;
	int m_PlayerLives;
	bool m_LevelCompleted;
	bool m_SwitchToNewLevel;
};