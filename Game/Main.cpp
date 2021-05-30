#include "GamePCH.h"
#include <iostream>
#include <Minigin.h>
#include <SDL_mixer.h>
#include "SceneManager.h"
#include <ResourceManager.h>
#include "DemoScene.h"
#include "MainMenuScene.h"
#include "SoloLevel1Scene.h"

void InitializeGame()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Game/Resources/");

	dae::SceneManager::GetInstance().AddScene(new SoloLevel1Scene());
}

int main(int,char*[])
{
	InitializeGame();

	dae::Minigin engine;
	engine.Run();
	return 0;
}
