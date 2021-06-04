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

using namespace Horizon;

SinglePlayerLevel::SinglePlayerLevel(int level, const LevelType& levelType) : Scene("SinglePlayerScene"),
m_Level{ level },
m_LevelType{ levelType },
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

	const auto QBertFont = ResourceManager::GetInstance().LoadFont("QBert.ttf", 20);
	{
		GameObject* const pLevelTextObject = new GameObject();
		TextComponent* const pLevelText = new TextComponent(pLevelTextObject, "Level " + std::to_string(m_Level), QBertFont, { 1, 50, 32 });
		TransformComponent* const pLevelTextTransform = new TransformComponent(pLevelTextObject, 480, 20);
		pLevelTextObject->AddComponent(pLevelTextTransform);
		pLevelTextObject->AddComponent(pLevelText);
		Add(pLevelTextObject);
	}

	{
		GameObject* const pPlayerSpriteObject = new GameObject();
		SpriteComponent* const pPlayerSprite = new SpriteComponent(pPlayerSpriteObject, "QBertTextures.png", { 0,67,312,7 }, 6);
		pPlayerSprite->Scale(2.8f);
		TransformComponent* const pPlayerSpriteTransform = new TransformComponent(pPlayerSpriteObject, 20, 20);
		pPlayerSpriteObject->AddComponent(pPlayerSpriteTransform);
		pPlayerSpriteObject->AddComponent(pPlayerSprite);


		TimedFunctionComponent* const pTimedFunction = new TimedFunctionComponent(pPlayerSpriteObject,true, 0.1f);

		pTimedFunction->SetTimerFunction([pPlayerSprite](float)
			{
				pPlayerSprite->NextSprite();
			});
		pTimedFunction->Activate();
		pPlayerSpriteObject->AddComponent(pTimedFunction);

		Add(pPlayerSpriteObject);
	}

	{
		GameObject* const pPlayerNumberObject = new GameObject();
		SpriteComponent* const pPlayerNumberSprite = new SpriteComponent(pPlayerNumberObject, "QBertTextures.png", { 0,84,16,11 }, 2);
		pPlayerNumberSprite->Scale(2.8f);
		TransformComponent* const pPlayerNumberTransform = new TransformComponent(pPlayerNumberObject, 178, 14);
		pPlayerNumberObject->AddComponent(pPlayerNumberTransform);
		pPlayerNumberObject->AddComponent(pPlayerNumberSprite);
		Add(pPlayerNumberObject);
	}

	{
		GameObject* const pLeftArrowObject = new GameObject();
		SpriteComponent* const pLeftArrowTexture = new SpriteComponent(pLeftArrowObject, "QBertTextures.png", { 18,86,7,7 }, 1);
		pLeftArrowTexture->Scale(2.8f);
		TransformComponent* const pLeftArrowTransform = new TransformComponent(pLeftArrowObject, 20, 144);
		pLeftArrowObject->AddComponent(pLeftArrowTransform);
		pLeftArrowObject->AddComponent(pLeftArrowTexture);
		Add(pLeftArrowObject);
	}

	{
		GameObject* const pLeftArrowObject = new GameObject();
		SpriteComponent* const pLeftArrowTexture = new SpriteComponent(pLeftArrowObject, "QBertTextures.png", { 18,86,7,7 }, 1);
		pLeftArrowTexture->Scale(2.8f);
		TransformComponent* const pLeftArrowTransform = new TransformComponent(pLeftArrowObject, 48, 144);
		pLeftArrowObject->AddComponent(pLeftArrowTransform);
		pLeftArrowObject->AddComponent(pLeftArrowTexture);
		Add(pLeftArrowObject);
	}

	{
		GameObject* const pRightArrowObject = new GameObject();
		SpriteComponent* const pRightArrowTexture = new SpriteComponent(pRightArrowObject, "QBertTextures.png", { 27,86,7,7 }, 1);
		pRightArrowTexture->Scale(2.8f);
		TransformComponent* const pRightArrowTransform = new TransformComponent(pRightArrowObject, 136, 144);
		pRightArrowObject->AddComponent(pRightArrowTransform);
		pRightArrowObject->AddComponent(pRightArrowTexture);
		Add(pRightArrowObject);
	}

	{
		GameObject* const pRightArrowObject = new GameObject();
		SpriteComponent* const pRightArrowTexture = new SpriteComponent(pRightArrowObject, "QBertTextures.png", { 27,86,7,7 }, 1);
		pRightArrowTexture->Scale(2.8f);
		TransformComponent* const pRightArrowTransform = new TransformComponent(pRightArrowObject, 164, 144);
		pRightArrowObject->AddComponent(pRightArrowTransform);
		pRightArrowObject->AddComponent(pRightArrowTexture);
		Add(pRightArrowObject);
	}

	{
		GameObject* const pLeftArrowObject = new GameObject();
		SpriteComponent* const pLeftArrowTexture = new SpriteComponent(pLeftArrowObject, "QBertTextures.png", { 18,86,7,7 }, 1);
		pLeftArrowTexture->Scale(2.8f);
		TransformComponent* const pLeftArrowTransform = new TransformComponent(pLeftArrowObject, 48, 144);
		pLeftArrowObject->AddComponent(pLeftArrowTransform);
		pLeftArrowObject->AddComponent(pLeftArrowTexture);
		Add(pLeftArrowObject);
	}

	{
		GameObject* const pChangeToObject = new GameObject();
		TextComponent* const pChangeToText = new TextComponent(pChangeToObject, "Change to", QBertFont, { 255, 140, 0 });
		TransformComponent* const pChangeToTransform = new TransformComponent(pChangeToObject, 20, 100);
		pChangeToObject->AddComponent(pChangeToTransform);
		pChangeToObject->AddComponent(pChangeToText);
		Add(pChangeToObject);
	}

	{
		GameObject* const CubeObject = new GameObject();

		const int posX = (m_Level % 2 == 0) ? 128 : (32 + 80 * (m_Level - 1));
		const int posY = 164;
		const int width = 222;
		const int height = 32;

		SpriteComponent* pSpriteComponent = new SpriteComponent(CubeObject, "QBertTextures.png", { posX,posY,width,height }, 7);
		pSpriteComponent->Scale(1.6f);
		TransformComponent* const pDisplayCubeTransform = new TransformComponent(CubeObject, 75, 128);
		CubeObject->AddComponent(pSpriteComponent);
		CubeObject->AddComponent(pDisplayCubeTransform);
		Add(CubeObject);
	}

	const auto QBertFont24 = ResourceManager::GetInstance().LoadFont("QBert.ttf", 24);
	{
		GameObject* const QBertScoreDisplay = new GameObject();
		TransformComponent* const QBertScoreTransform = new TransformComponent(QBertScoreDisplay, 20, 50);


		TextComponent* const QBertScoreText = new TextComponent(QBertScoreDisplay, "", QBertFont24, { 255, 140, 0 });

		ScoreDisplayComponent* const QBertScoreDisplayComponent = new ScoreDisplayComponent(QBertScoreDisplay);


		QBertScoreDisplay->AddComponent(QBertScoreTransform);
		QBertScoreDisplay->AddComponent(QBertScoreText);
		QBertScoreDisplay->AddComponent(QBertScoreDisplayComponent);

		GetGameObject("Qbert")->GetComponent<ScoreComponent>()->AddObserver(new ScoreDisplayObserver(QBertScoreDisplayComponent));

		Add(QBertScoreDisplay);
	}
	{
		GameObject* const QBertHealthDisplay = new GameObject();
		TransformComponent* const QBertHealthTransform = new TransformComponent(QBertHealthDisplay, 20, 200);

		TextComponent* const QBertHealthText = new TextComponent(QBertHealthDisplay, "", QBertFont24, { 255, 140, 0 });

		HealthDisplayComponent* const QHealthScoreDisplayComponent = new HealthDisplayComponent(QBertHealthDisplay);


		QBertHealthDisplay->AddComponent(QBertHealthTransform);
		QBertHealthDisplay->AddComponent(QBertHealthText);
		QBertHealthDisplay->AddComponent(QHealthScoreDisplayComponent);

		GetGameObject("Qbert")->GetComponent<HealthComponent>()->AddObserver(new HealthDisplayObserver(QHealthScoreDisplayComponent));

		Add(QBertHealthDisplay);
	}

	{
		GameObject* const pCubesSwitch = new GameObject();

		m_pTimedFunction = new TimedFunctionComponent(pCubesSwitch,true, 0.1f);

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

		InputManager::GetInstance().ClearInput();
	}

	if (!m_SwitchToNewLevel)
		return;

	TriggerManager::GetInstance().ClearTriggerComponents();

	(m_Level == 3) ? Horizon::SceneManager::GetInstance().AddScene(new MainMenuScene()) : Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(m_Level + 1, LevelType::SinglePlayer));

	SceneManager::GetInstance().NextScene();
	SceneManager::GetInstance().RemoveScene(this);
}
