#pragma once
#include <Scene.h>
#include "LevelType.h"

namespace Horizon
{
	class TimedFunctionComponent;
	class HealthComponent;
	class ScoreComponent;
}

class CubeHandleComponent;

class CooperativeLevel final : public Horizon::Scene
{
public:
	CooperativeLevel(int level, int player1Score, int player1Lives, int player2Score, int player2Lives);
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

	Horizon::HealthComponent* m_pPlayer1HealthComponent = nullptr;
	Horizon::ScoreComponent* m_pPlayer1ScoreComponent = nullptr;

	Horizon::HealthComponent* m_pPlayer2HealthComponent = nullptr;
	Horizon::ScoreComponent* m_pPlayer2ScoreComponent = nullptr;

	int m_Player1Score;
	int m_Player1Lives;

	int m_Player2Score;
	int m_Player2Lives;

	bool m_LevelCompleted;
	bool m_SwitchToNewLevel;
};

