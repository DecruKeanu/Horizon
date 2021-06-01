#include "GamePCH.h"
#include <iostream>
#include <Minigin.h>
#include <SDL_mixer.h>
#include "SceneManager.h"
#include <ResourceManager.h>
#include "DemoScene.h"
#include "MainMenuScene.h"
#include "SoloLevel1Scene.h"
#include "SoloLevel2Scene.h"
#include "SoloLevel3Scene.h"

void InitializeGame()
{
	// tell the resource manager where he can find the game data
	Horizon::ResourceManager::GetInstance().Init("../Game/Resources/");

	Horizon::SceneManager::GetInstance().AddScene(new SoloLevel1Scene());
	//Horizon::SceneManager::GetInstance().AddScene(new SoloLevel2Scene());
	//Horizon::SceneManager::GetInstance().AddScene(new SoloLevel3Scene());
}

int main(int,char*[])
{
	InitializeGame();

	Horizon::Minigin engine;
	engine.Run();
	return 0;
}
