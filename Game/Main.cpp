#include "GamePCH.h"
#include <iostream>
#include <Minigin.h>
#include <SDL_mixer.h>
#include "SceneManager.h"
#include <ResourceManager.h>
#include "DemoScene.h"
#include "MainMenuScene.h"
#include "SinglePlayerlevel.h"

void InitializeGame()
{
	// tell the resource manager where he can find the game data
	Horizon::ResourceManager::GetInstance().Init("../Game/Resources/");

	Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(1,LevelType::SinglePlayer));
}

int main(int,char*[])
{
	InitializeGame();

	Horizon::Minigin engine;
	engine.Run();
	return 0;
}
