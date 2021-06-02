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
#include "Command.h"

using namespace Horizon;

SinglePlayerLevel::SinglePlayerLevel(int level, const LevelType& levelType) : Scene("SinglePlayerScene"),
m_Level{ level },
m_LevelType{ levelType }
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
}

void SinglePlayerLevel::Update()
{
	for (CubeHandleComponent* const pCubeHandle : m_pCubeHandles)
	{
		if (!pCubeHandle->GetisActivated())
			return;
	}

	InputManager::GetInstance().ClearInput();

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

	Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(2, LevelType::SinglePlayer));
	SceneManager::GetInstance().NextScene();
	SceneManager::GetInstance().RemoveScene(this);
}
