#include "MiniginPCH.h"
#include "DemoScene.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "SoundSystemServiceLocator.h"
#include "SDLSoundSystem.h"
#include "MutedSoundSystem.h"
#include "GameObject.h"
#include "Scene.h"
#include "Timer.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "HealthDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "FPS.h"
#include "ScoreDisplayObserver.h"
#include "HealthDisplayObserver.h"
#include "Structs.h"
#include "Command.h"
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace dae;

DemoScene::DemoScene() : Scene("DemoScene")
{

}


void DemoScene::Initialize()
{

	//BackGround
	GameObject* const backGround = new GameObject();

	TextureComponent* const backGroundTexture = new dae::TextureComponent(backGround, "background.jpg");

	backGround->AddComponent(backGroundTexture);
	Add(backGround);

	//Logo
	GameObject* const Logo = new GameObject();
	TextureComponent* const logoTexture = new dae::TextureComponent(Logo, "logo.png");
	TransformComponent* const logoTransform = new dae::TransformComponent(Logo, 216, 80, 0);

	Logo->AddComponent(logoTexture);
	Logo->AddComponent(logoTransform);
	Add(Logo);

	//Text
	GameObject* const textObject = new GameObject();

	const auto Lingua36Font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	dae::TextComponent* const text = new dae::TextComponent(textObject, "Programming 4 Assignment", Lingua36Font);
	dae::TransformComponent* const textTransform = new dae::TransformComponent(Logo, 80, 20, 0);

	textObject->AddComponent(text);
	textObject->AddComponent(textTransform);
	Add(textObject);

	//FpsCounter
	GameObject* const fpsCounter = new GameObject();

	const auto Lingua20Font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	dae::TextComponent* const fpsText = new dae::TextComponent(fpsCounter, "test", Lingua20Font, Color{ 255,255,0 });
	dae::FPS* const fps = new dae::FPS(fpsCounter);
	dae::TransformComponent* const fpsTransform = new dae::TransformComponent(fpsCounter, 10, 10, 0);

	fpsCounter->AddComponent(fpsText);
	fpsCounter->AddComponent(fps);
	fpsCounter->AddComponent(fpsTransform);
	Add(fpsCounter);

	//QBert (player1)
	GameObject* const QBert = new GameObject();
	HealthComponent* const QBertHealth = new dae::HealthComponent(QBert);
	QBert->AddComponent(QBertHealth);
	ScoreComponent* const QBertScore = new dae::ScoreComponent(QBert);
	QBert->AddComponent(QBertScore);

	//QBert healthDisplay
	GameObject* const QBertHealthDisplay = new GameObject();
	dae::TransformComponent* const QBertHealthTransform = new dae::TransformComponent(QBertHealthDisplay, 80, 200, 0);
	QBertHealthDisplay->AddComponent(QBertHealthTransform);
	dae::TextComponent* const QBertHealthText = new dae::TextComponent(QBertHealthDisplay, "Qbert remaining lives: ", Lingua36Font);
	QBertHealthDisplay->AddComponent(QBertHealthText);
	dae::HealthDisplayComponent* const QBertHealthDisplayComponent = new dae::HealthDisplayComponent(QBertHealthDisplay);
	QBertHealthDisplay->AddComponent(QBertHealthDisplayComponent);

	//Qbert scoreDisplay
	GameObject* const QBertScoreDisplay = new GameObject();
	dae::TransformComponent* const QBertScoreTransform = new dae::TransformComponent(QBertScoreDisplay, 80, 250, 0);
	QBertScoreDisplay->AddComponent(QBertScoreTransform);
	dae::TextComponent* const QBertScoreText = new dae::TextComponent(QBertScoreDisplay, "Qbert current score: ", Lingua36Font);
	QBertScoreDisplay->AddComponent(QBertScoreText);
	dae::ScoreDisplayComponent* const QBertScoreDisplayComponent = new dae::ScoreDisplayComponent(QBertScoreDisplay);
	QBertScoreDisplay->AddComponent(QBertScoreDisplayComponent);

	//Add objects to scene
	Add(QBert);
	Add(QBertHealthDisplay);
	Add(QBertScoreDisplay);

	//Qbert observers
	QBertScore->AddObserver(new ScoreDisplayObserver(QBertScoreDisplayComponent));
	QBertHealth->AddObserver(new HealthDisplayObserver(QBertHealthDisplayComponent));

	//Qbert input
	InputManager::GetInstance().AddInput(ControllerButton::ButtonA, ControllerButtonState::KeyDown, std::make_unique<ColorChangeCommand>(QBertScore));
	InputManager::GetInstance().AddInput(ControllerButton::ButtonX, ControllerButtonState::KeyDown, std::make_unique<RemainingDiscCommand>(QBertScore));
	InputManager::GetInstance().AddInput(ControllerButton::ButtonY, ControllerButtonState::KeyDown, std::make_unique<CatchingSamOrSlickCommand>(QBertScore));
	InputManager::GetInstance().AddInput(ControllerButton::ButtonB, ControllerButtonState::KeyDown, std::make_unique<DefeatCoilyCommand>(QBertScore));
	InputManager::GetInstance().AddInput(ControllerButton::RightTrigger, ControllerButtonState::KeyDown, std::make_unique<LifeLostCommand>(QBertHealth));

	//Coily (player2)
	GameObject* const Coily = new GameObject();
	HealthComponent* const CoilyHealth = new dae::HealthComponent(Coily);
	Coily->AddComponent(CoilyHealth);
	ScoreComponent* const CoilyScore = new dae::ScoreComponent(Coily);
	Coily->AddComponent(CoilyScore);

	//Coily healthDisplay
	GameObject* const CoilyHealthDisplay = new GameObject();
	dae::TransformComponent* const CoilyHealthTransform = new dae::TransformComponent(CoilyHealthDisplay, 80, 350, 0);
	CoilyHealthDisplay->AddComponent(CoilyHealthTransform);
	dae::TextComponent* const CoilyHealthText = new dae::TextComponent(CoilyHealthDisplay, "Coily remaining lives: ", Lingua36Font);
	CoilyHealthDisplay->AddComponent(CoilyHealthText);
	dae::HealthDisplayComponent* const CoilyHealthDisplayComponent = new dae::HealthDisplayComponent(CoilyHealthDisplay);
	CoilyHealthDisplay->AddComponent(CoilyHealthDisplayComponent);

	//Coily scoreDisplay
	GameObject* const CoilyScoreDisplay = new GameObject();
	dae::TransformComponent* const CoilyScoreTransform = new dae::TransformComponent(CoilyScoreDisplay, 80, 400, 0);
	CoilyScoreDisplay->AddComponent(CoilyScoreTransform);
	dae::TextComponent* const CoilyScoreText = new dae::TextComponent(CoilyScoreDisplay, "Coily current score: ", Lingua36Font);
	CoilyScoreDisplay->AddComponent(CoilyScoreText);
	dae::ScoreDisplayComponent* const CoilyScoreDisplayComponent = new dae::ScoreDisplayComponent(CoilyScoreDisplay);
	CoilyScoreDisplay->AddComponent(CoilyScoreDisplayComponent);

	//Add objects to scene
	Add(Coily);
	Add(CoilyHealthDisplay);
	Add(CoilyScoreDisplay);

	//Coily observers
	CoilyScore->AddObserver(new ScoreDisplayObserver(CoilyScoreDisplayComponent));
	CoilyHealth->AddObserver(new HealthDisplayObserver(CoilyHealthDisplayComponent));

	//Coily input
	InputManager::GetInstance().AddInput(ControllerButton::DPadDown, ControllerButtonState::KeyDown, std::make_unique<ColorChangeCommand>(CoilyScore));
	InputManager::GetInstance().AddInput(ControllerButton::DPadLeft, ControllerButtonState::KeyDown, std::make_unique<RemainingDiscCommand>(CoilyScore));
	InputManager::GetInstance().AddInput(ControllerButton::DPadUp, ControllerButtonState::KeyDown, std::make_unique<CatchingSamOrSlickCommand>(CoilyScore));
	InputManager::GetInstance().AddInput(ControllerButton::DPadRight, ControllerButtonState::KeyDown, std::make_unique<DefeatCoilyCommand>(CoilyScore));
	InputManager::GetInstance().AddInput(ControllerButton::LeftTrigger, ControllerButtonState::KeyDown, std::make_unique<LifeLostCommand>(CoilyHealth));


	//auto& soundSystem = SoundSystemServiceLocator::GetSoundSystem();
	//soundSystem.AddAudio("../Data/sounds/bell.wav");
	//soundSystem.QueueEvent(0, 128);


}
