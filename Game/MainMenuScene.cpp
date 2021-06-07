#include "GamePCH.h"
#include "MainMenuScene.h"

#include <TextComponent.h>
#include <TextureComponent.h>
#include <TransformComponent.h>
#include <ResourceManager.h>

#include "Cube.h"
#include "LevelReader.h"
#include <InputManager.h>
#include "InputCommands.h"
#include <SoundSystemServiceLocator.h>

#include "SinglePlayerLevel.h"
#include "CooperativeLevel.h"
#include "VersusLevel.h"

MainMenuScene::MainMenuScene() : Scene("MainMenuScene"),
m_CurrentModeSelected{ ModeSelected::singlePlayer },
m_InputPressed{}
{

}

void MainMenuScene::Initialize()
{
	using namespace Horizon;

	//Logo
	{
		GameObject* const Logo = new GameObject();
		TextureComponent* const logoTexture = new TextureComponent(Logo, "QBertTextures.png");
		logoTexture->SetSrcRect(202, 45, 92, 14);
		logoTexture->SetScale(4.f);
		TransformComponent* const logoTransform = new TransformComponent(Logo, 230 - 128 / 2, 80);

		Logo->AddComponent(logoTexture);
		Logo->AddComponent(logoTransform);
		Add(Logo);
	}

	//Text
	const auto QBertFont = ResourceManager::GetInstance().LoadFont("QBert.ttf", 30);
	{
		GameObject* const singlePlayerObject = new GameObject();
		TextComponent* const singlePlayerText = new TextComponent(singlePlayerObject, "Single player", QBertFont, { 255, 140, 0 });
		TransformComponent* const singlePlayerTransform = new TransformComponent(singlePlayerObject, 140, 200);
		singlePlayerObject->AddComponent(singlePlayerText);
		singlePlayerObject->AddComponent(singlePlayerTransform);
		Add(singlePlayerObject);
	}

	{
		GameObject* const CoOpObject = new GameObject();
		TextComponent* const CoOpText = new TextComponent(CoOpObject, "cooperative", QBertFont, { 255, 140, 0 });
		TransformComponent* const CoOpTransform = new TransformComponent(CoOpObject, 140, 280);
		CoOpObject->AddComponent(CoOpText);
		CoOpObject->AddComponent(CoOpTransform);
		Add(CoOpObject);
	}

	{
		GameObject* const versusObject = new GameObject();
		TextComponent* const versusText = new TextComponent(versusObject, "versus", QBertFont, { 255, 140, 0 });
		TransformComponent* const versusTransform = new TransformComponent(versusObject, 140, 360);
		versusObject->AddComponent(versusText);
		versusObject->AddComponent(versusTransform);
		Add(versusObject);
	}

	{
		GameObject* const pArrowObject = new GameObject();
		TextureComponent* const pArrowTexture = new TextureComponent(pArrowObject, "QBertTextures.png");
		pArrowTexture->SetSrcRect(18, 86, 7, 7);
		pArrowTexture->SetScale(4.f);
		m_pArrowTransformComponent = new TransformComponent(pArrowObject, 100, 200);

		pArrowObject->AddComponent(pArrowTexture);
		pArrowObject->AddComponent(m_pArrowTransformComponent);
		Add(pArrowObject);
	}

	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_z, KeyboardButtonState::KeyDown, std::make_unique<ArrowUpCommand>(m_CurrentModeSelected, m_pArrowTransformComponent));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_s, KeyboardButtonState::KeyDown, std::make_unique<ArrowDownCommand>(m_CurrentModeSelected, m_pArrowTransformComponent));
	InputManager::GetInstance().AddKeyboardInput(SDLK::SDLK_RETURN, KeyboardButtonState::KeyDown, std::make_unique<InputPressedCommand>(m_InputPressed));

	InputManager::GetInstance().AddControllerInput(ControllerButton::DPadUp, ControllerButtonState::ButtonDown, std::make_unique<ArrowUpCommand>(m_CurrentModeSelected, m_pArrowTransformComponent));
	InputManager::GetInstance().AddControllerInput(ControllerButton::DPadDown, ControllerButtonState::ButtonDown, std::make_unique<ArrowDownCommand>(m_CurrentModeSelected, m_pArrowTransformComponent));
	InputManager::GetInstance().AddControllerInput(ControllerButton::ButtonA, ControllerButtonState::ButtonDown, std::make_unique<InputPressedCommand>(m_InputPressed));
}

void MainMenuScene::Update()
{
	if (m_InputPressed)
	{
		Horizon::InputManager::GetInstance().ClearInput();

		m_InputPressed = false;
		switch (m_CurrentModeSelected)
		{
		case ModeSelected::singlePlayer:
			Horizon::SceneManager::GetInstance().AddActiveScene(new SinglePlayerLevel(1, 0, 3));
			break;
		case ModeSelected::Cooperative:
			Horizon::SceneManager::GetInstance().AddActiveScene(new CooperativeLevel(1, 0, 3, 0, 3));
			break;
		case ModeSelected::versus:
			Horizon::SceneManager::GetInstance().AddActiveScene(new VersusLevel(1, 0, 3));
			break;
		}
	}
}
