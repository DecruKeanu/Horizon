#include "GamePCH.h"
#include "MainMenuScene.h"
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Cube.h"
#include "LevelReader.h"

using namespace Horizon;

MainMenuScene::MainMenuScene() : Scene("MainMenuScene")
{

}

void MainMenuScene::Initialize()
{
	//Logo
	{
		GameObject* const Logo = new GameObject();
		TextureComponent* const logoTexture = new TextureComponent(Logo, "QBertTextures.png");
		logoTexture->SetSrcRect(128, 33, 92, 14);
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
}
