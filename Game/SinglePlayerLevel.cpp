#include "GamePCH.h"
#include "SinglePlayerLevel.h"
#include "MainMenuScene.h"
#include "CubeHandleComponent.h"
#include <ResourceManager.h>
#include <TextComponent.h>
#include <TransformComponent.h>
#include "LevelReader.h"
#include <GameObject.h>
#include "InputManager.h"
#include <TriggerManager.h>
#include "Command.h"
#include <TextureComponent.h>
#include <SpriteComponent.h>
#include <TimedFunctionComponent.h>
#include <HealthComponent.h>
#include <ScoreComponent.h>
#include <ScoreDisplayComponent.h>
#include <ScoreDisplayObserver.h>
#include <HealthDisplayComponent.h>
#include <HealthDisplayObserver.h>
#include <timer.h>
#include <SoundSystemServiceLocator.h>

using namespace Horizon;

SinglePlayerLevel::SinglePlayerLevel(int level, int playerScore, int playerLives) : Scene("SinglePlayerScene"),
m_Level{ level },
m_PlayerScore{ playerScore },
m_PlayerLives{ playerLives },
m_LevelCompleted{},
m_SwitchToNewLevel{}
{

}

void SinglePlayerLevel::Initialize()
{
	LevelReader levelReader{};
	const std::wstring fileName = L"SoloLevel" + std::to_wstring(m_Level) + L".json";
	levelReader.ParseLevel(fileName);

	for (GameObject* const pPrefab : levelReader.GetGameObjects())
	{
		Add(pPrefab);
	}

	const std::vector<GameObject*> pCubes = GetGameObjects("Cube");

	for (GameObject* const pCube : pCubes)
		m_pCubeHandles.push_back(pCube->GetComponent<CubeHandleComponent>());

	{
		GameObject* const pCubesSwitch = new GameObject();

		m_pTimedFunction = new TimedFunctionComponent(pCubesSwitch, true, 0.1f);

		m_pTimedFunction->SetTimerFunction([this](float totalTime)
			{
				for (CubeHandleComponent* const pCubeHandleComponent : m_pCubeHandles)
				{
					pCubeHandleComponent->SwitchSprite();
				}

				if (totalTime > 4.f)
					m_SwitchToNewLevel = true;
			});

		pCubesSwitch->AddComponent(m_pTimedFunction);
		Add(pCubesSwitch);
	}
}

void SinglePlayerLevel::PostInitialize()
{
	m_pPlayerScoreComponent = GetGameObject("Qbert")->GetComponent<ScoreComponent>();
	m_pPlayerScoreComponent->AddObserver(new ScoreDisplayObserver(GetGameObject("ScoreDisplayObject")->GetComponent<ScoreDisplayComponent>()));
	m_pPlayerScoreComponent->IncreaseScore(m_PlayerScore);

	m_pPlayerHealthComponent = GetGameObject("Qbert")->GetComponent<HealthComponent>();
	m_pPlayerHealthComponent->AddObserver(new HealthDisplayObserver(GetGameObject("HealthDisplayObject")->GetComponent<HealthDisplayComponent>()));
	m_pPlayerHealthComponent->SetCurrentLives(m_PlayerLives);

	auto& soundSystem = SoundSystemServiceLocator::GetSoundSystem();
	soundSystem.QueueEvent(0, 60);
}

void SinglePlayerLevel::Update()
{
	if (m_SwitchToNewLevel)
		NextLevel();

	if (m_LevelCompleted)
		return;

	if (m_pPlayerHealthComponent->GetCurrentLives() == 0)
	{
		BackToMainMenu();
	}
	else if (m_pPlayerHealthComponent->GetCurrentLives() < m_PlayerLives)
	{
		ResetLevel();
	}

	for (CubeHandleComponent* const pCubeHandle : m_pCubeHandles)
	{
		if (!pCubeHandle->GetisActivated())
			return;
	}
	m_LevelCompleted = true;
	m_pTimedFunction->Activate();

	InputManager::GetInstance().ClearInput();

	auto& soundSystem = SoundSystemServiceLocator::GetSoundSystem();
	soundSystem.QueueEvent(1, 80);
}

void SinglePlayerLevel::BackToMainMenu()
{
	InputManager::GetInstance().ClearInput();
	TriggerManager::GetInstance().ClearTriggerComponents();
	Horizon::SceneManager::GetInstance().AddActiveScene(new MainMenuScene());
}

void SinglePlayerLevel::ResetLevel()
{
	InputManager::GetInstance().ClearInput();
	TriggerManager::GetInstance().ClearTriggerComponents();
	m_PlayerScore = GetGameObject("Qbert")->GetComponent<ScoreComponent>()->GetScore();
	m_PlayerLives = m_pPlayerHealthComponent->GetCurrentLives();
	Horizon::SceneManager::GetInstance().AddActiveScene(new SinglePlayerLevel(m_Level, m_PlayerScore, m_PlayerLives));
}

void SinglePlayerLevel::NextLevel()
{
	TriggerManager::GetInstance().ClearTriggerComponents();

	(m_Level == 3) ? Horizon::SceneManager::GetInstance().AddActiveScene(new MainMenuScene()) : Horizon::SceneManager::GetInstance().AddActiveScene(new SinglePlayerLevel(++m_Level, m_PlayerScore, m_PlayerLives));
}
