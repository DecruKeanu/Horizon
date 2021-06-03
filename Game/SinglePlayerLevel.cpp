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
#include <TimedFunction.h>
#include "PlayerInputComponent.h"
#include <timer.h>

using namespace Horizon;

SinglePlayerLevel::SinglePlayerLevel(int level, const LevelType& levelType) : Scene("SinglePlayerScene"),
m_Level{ level },
m_LevelType{ levelType },
m_LevelCompleted{},
m_SwitchToNewLevel{}
{

}

SinglePlayerLevel::~SinglePlayerLevel()
{
	Horizon::Timer::GetInstance().RemoveTimedFunction(m_pTimedFunction);
	SafeDelete(m_pTimedFunction);
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

	std::vector<GameObject*> pCubes = GetGameObjects("Cube");

	for (GameObject* const pCube : pCubes)
		m_pCubeHandles.push_back(pCube->GetComponent<CubeHandleComponent>());

	const auto QBertFont = ResourceManager::GetInstance().LoadFont("QBert.ttf", 20);
	{
		GameObject* const singlePlayerObject = new GameObject();
		TextComponent* const singlePlayerText = new TextComponent(singlePlayerObject, "Level " + std::to_string(m_Level), QBertFont, { 255, 140, 0 });
		TransformComponent* const singlePlayerTransform = new TransformComponent(singlePlayerObject, 20, 20, 0);
		singlePlayerObject->AddComponent(singlePlayerTransform);
		singlePlayerObject->AddComponent(singlePlayerText);
		Add(singlePlayerObject);
	}

	{
		GameObject* const singlePlayerObject = new GameObject();
		TextComponent* const singlePlayerText = new TextComponent(singlePlayerObject, "Change to" , QBertFont, { 255, 140, 0 });
		TransformComponent* const singlePlayerTransform = new TransformComponent(singlePlayerObject, 20, 60, 0);
		singlePlayerObject->AddComponent(singlePlayerTransform);
		singlePlayerObject->AddComponent(singlePlayerText);
		Add(singlePlayerObject);
	}

	{
		GameObject* const CubeObject = new GameObject();
		//TextureComponent* pTextureComponent = new TextureComponent(CubeObject, "QBertTextures.png");
		//pTextureComponent->SetScale(1.6f);

		const int posY = 164;
		const int width = 222;
		const int height = 32;
		int posX = 0;

		switch (m_Level)
		{
		case 1:
			posX = 32;
			break;
		case 2:
			posX = 128;
			break;
		case 3:
			posX = 192;
			break;
		}


		SpriteComponent* pSpriteComponent = new SpriteComponent(CubeObject,"QBertTextures.png", { posX,posY,width,height }, 7);
		pSpriteComponent->Scale(1.6f);
		TransformComponent* const singlePlayerTransform = new TransformComponent(CubeObject, 75, 88, 0);
		//CubeObject->AddComponent(pTextureComponent);
		CubeObject->AddComponent(pSpriteComponent);
		CubeObject->AddComponent(singlePlayerTransform);
		Add(CubeObject);
	}

	{
		m_pTimedFunction = new TimedFunction(true, 0.1f);

		m_pTimedFunction->SetTimerFunction([this](float totalTime)
			{
				for (CubeHandleComponent* const pCubeHandleComponent : m_pCubeHandles)
				{
					pCubeHandleComponent->SwitchSprite();
				}

				if (totalTime > 4.f)
					m_SwitchToNewLevel = true;
			});

		Timer::GetInstance().AddTimedFunction(m_pTimedFunction);
	}
}

void SinglePlayerLevel::Update()
{
	if (m_LevelCompleted == false)
	{
		for (CubeHandleComponent* const pCubeHandle : m_pCubeHandles)
		{
			if (!pCubeHandle->GetisActivated())
				return;
		}
		m_LevelCompleted = true;
		m_pTimedFunction->Activate();

		GetGameObject("Qbert")->GetComponent<PlayerInputComponent>()->DeactivateInput();
	}


	if (!m_SwitchToNewLevel)
		return;

	InputManager::GetInstance().ClearInput();
	TriggerManager::GetInstance().ClearTriggerComponents();


	switch (m_Level)
	{
	case 1:
		Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(2, LevelType::SinglePlayer));
		break;
	case 2:
		Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(3, LevelType::SinglePlayer));
		break;
	case 3:
		Horizon::SceneManager::GetInstance().AddScene(new MainMenuScene());
		break;
	}

	SceneManager::GetInstance().NextScene();
	SceneManager::GetInstance().RemoveScene(this);
}
