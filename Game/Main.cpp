#include <iostream>
#include <Minigin.h>
#include <SDL_mixer.h>
#include "SceneManager.h"
#include <ResourceManager.h>
#include "DemoScene.h"
#include "MainMenuScene.h"

void InitializeGame()
{
	// tell the resource manager where he can find the game data
	dae::ResourceManager::GetInstance().Init("../Game/Resources/");

	dae::SceneManager::GetInstance().AddScene(new MainMenuScene());
}

int main()
{
	InitializeGame();

	dae::Minigin engine;
	engine.Run();
	return 0;
}
