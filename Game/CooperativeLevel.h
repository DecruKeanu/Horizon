#pragma once
#include <Scene.h>

class CubeHandleComponent;

namespace Horizon
{
	class TimedFunctionComponent;
	class HealthComponent;
	class ScoreComponent;
}

class CooperativeLevel final : public Horizon::Scene
{
public:
	CooperativeLevel(int level, int player1Score, int player1Lives, int player2Score, int player2Lives);
private:
	//Scene Functions
	void Initialize() override;
	void PostInitialize() override;
	void Update() override;

	//Helper Functions
	void BackToMainMenu();
	void ResetLevel();
	void NextLevel();

	//Components
	std::vector<CubeHandleComponent*> m_pCubeHandles;
	Horizon::TimedFunctionComponent* m_pTimedFunction = nullptr;
	Horizon::ScoreComponent* m_pPlayer1ScoreComponent = nullptr;
	Horizon::ScoreComponent* m_pPlayer2ScoreComponent = nullptr;
	Horizon::HealthComponent* m_pPlayer1HealthComponent = nullptr;
	Horizon::HealthComponent* m_pPlayer2HealthComponent = nullptr;

	int m_Level;
	int m_Player1Score;
	int m_Player1Lives;
	int m_Player2Score;
	int m_Player2Lives;
	bool m_LevelCompleted;
	bool m_SwitchToNewLevel;
};