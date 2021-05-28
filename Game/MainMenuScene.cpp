#include "MiniginPCH.h"
#include "MainMenuScene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Cube.h"
using namespace dae;

MainMenuScene::MainMenuScene() : Scene("MainMenuScene")
{

}

void MainMenuScene::Initialize()
{
	//GameObject* const Logo = new GameObject();
	//TextureComponent* const logoTexture = new dae::TextureComponent(Logo, "QBertTextures.png");
	//logoTexture->SetSrcRect(128, 33, 92, 14);
	//logoTexture->SetScale(4.f);
	//TransformComponent* const logoTransform = new dae::TransformComponent(Logo, 230 - 128/2, 80, 0);

	//Logo->AddComponent(logoTexture);
	//Logo->AddComponent(logoTransform);
	//Add(Logo);

	//cube test
	Cube* cube = new Cube(Cube::CubeColor::level3Mellow);
	Add(cube->GetGameObject());

	//Text
	const auto QBertFont = ResourceManager::GetInstance().LoadFont("QBert.ttf", 30);

	{
		GameObject* const singlePlayerObject = new GameObject();
		dae::TextComponent* const singlePlayerText = new dae::TextComponent(singlePlayerObject, "Single player", QBertFont, { 255, 140, 0 });
		dae::TransformComponent* const singlePlayerTransform = new dae::TransformComponent(singlePlayerObject, 140, 200, 0);
		singlePlayerObject->AddComponent(singlePlayerText);
		singlePlayerObject->AddComponent(singlePlayerTransform);
		Add(singlePlayerObject);
	}

	{
		GameObject* const CoOpObject = new GameObject();
		dae::TextComponent* const CoOpText = new dae::TextComponent(CoOpObject, "cooperative", QBertFont, { 255, 140, 0 });
		dae::TransformComponent* const CoOpTransform = new dae::TransformComponent(CoOpObject, 140, 280, 0);
		CoOpObject->AddComponent(CoOpText);
		CoOpObject->AddComponent(CoOpTransform);
		Add(CoOpObject);
	}

	{
		GameObject* const versusObject = new GameObject();
		dae::TextComponent* const versusText = new dae::TextComponent(versusObject, "versus", QBertFont, { 255, 140, 0 });
		dae::TransformComponent* const versusTransform = new dae::TransformComponent(versusObject, 140, 360, 0);
		versusObject->AddComponent(versusText);
		versusObject->AddComponent(versusTransform);
		Add(versusObject);
	}
}
