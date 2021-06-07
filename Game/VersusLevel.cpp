#include "GamePCH.h"
#include "VersusLevel.h"


#include "CubeHandleComponent.h"

#include <GameObject.h>
#include <TextComponent.h>
#include <ScoreComponent.h>
#include <HealthComponent.h>
#include <SpriteComponent.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <ScoreDisplayObserver.h>
#include <HealthDisplayObserver.h>
#include <ScoreDisplayComponent.h>
#include <TimedFunctionComponent.h>
#include <HealthDisplayComponent.h>

#include "LevelReader.h"
#include "MainMenuScene.h"
#include <ResourceManager.h>

#include <timer.h>
#include <Command.h>
#include <InputManager.h>
#include <TriggerManager.h>
#include <SoundSystemServiceLocator.h>

VersusLevel::VersusLevel(int level, int playerScore, int playerLives) : Scene("VersusScene"),
m_Level{ level },
m_PlayerScore{ playerScore },
m_PlayerLives{ playerLives },
m_LevelCompleted{},
m_SwitchToNewLevel{}
{

}

void VersusLevel::Initialize()
{
	LevelReader levelReader{};
	const std::wstring fileName = L"VersusLevel" + std::to_wstring(m_Level) + L".json";
	levelReader.ParseLevel(fileName);

	for (Horizon::GameObject* const pPrefab : levelReader.GetGameObjects())
	{
		Add(pPrefab);
	}

	const std::vector<Horizon::GameObject*> pCubes = GetGameObjects("Cube");

	for (Horizon::GameObject* const pCube : pCubes)
		m_pCubeHandles.push_back(pCube->GetComponent<CubeHandleComponent>());

	{
		Horizon::GameObject* const pCubesSwitch = new Horizon::GameObject();

		m_pTimedFunction = new Horizon::TimedFunctionComponent(pCubesSwitch, true, 0.1f);

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

void VersusLevel::PostInitialize()
{
	m_pPlayerScoreComponent = GetGameObject("Qbert")->GetComponent<Horizon::ScoreComponent>();
	m_pPlayerScoreComponent->AddObserver(new Horizon::ScoreDisplayObserver(GetGameObject("ScoreDisplayObject")->GetComponent<Horizon::ScoreDisplayComponent>()));
	m_pPlayerScoreComponent->IncreaseScore(m_PlayerScore);

	m_pPlayerHealthComponent = GetGameObject("Qbert")->GetComponent<Horizon::HealthComponent>();
	m_pPlayerHealthComponent->AddObserver(new Horizon::HealthDisplayObserver(GetGameObject("HealthDisplayObject")->GetComponent<Horizon::HealthDisplayComponent>()));
	m_pPlayerHealthComponent->SetCurrentLives(m_PlayerLives);

	auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
	//soundSystem.AddAudio("../Data/sounds/LevelIntro.wav");
	soundSystem.QueueEvent(0, 20);
}

void VersusLevel::Update()
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

	Horizon::InputManager::GetInstance().ClearInput();

	auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
	soundSystem.QueueEvent(1, 20);

	Horizon::TriggerManager::GetInstance().ClearTriggerComponents();
}

void VersusLevel::BackToMainMenu()
{
	Horizon::InputManager::GetInstance().ClearInput();
	Horizon::TriggerManager::GetInstance().ClearTriggerComponents();
	Horizon::SceneManager::GetInstance().AddActiveScene(new MainMenuScene());
}

void VersusLevel::ResetLevel()
{
	Horizon::InputManager::GetInstance().ClearInput();
	Horizon::TriggerManager::GetInstance().ClearTriggerComponents();
	m_PlayerScore = m_pPlayerScoreComponent->GetScore();
	m_PlayerLives = m_pPlayerHealthComponent->GetCurrentLives();
	Horizon::SceneManager::GetInstance().AddActiveScene(new VersusLevel(m_Level, m_PlayerScore, m_PlayerLives));
}

void VersusLevel::NextLevel()
{
	m_PlayerScore = m_pPlayerScoreComponent->GetScore();
	m_PlayerLives = m_pPlayerHealthComponent->GetCurrentLives() + 1;

	(m_Level == 3) ? Horizon::SceneManager::GetInstance().AddActiveScene(new MainMenuScene()) : Horizon::SceneManager::GetInstance().AddActiveScene(new VersusLevel(++m_Level, m_PlayerScore, m_PlayerLives));
}
