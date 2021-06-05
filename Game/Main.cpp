#include "GamePCH.h"
#include <Horizon.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include "DemoScene.h"
#include "MainMenuScene.h"
#include "SinglePlayerlevel.h"

void InitializeGame()
{
	srand(unsigned int(time(NULL)));

	// tell the resource manager where he can find the game data
	Horizon::ResourceManager::GetInstance().Init("../Game/Resources/");

	Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(1,LevelType::SinglePlayer,0,3));
}

int main(int,char*[])
{
	InitializeGame();

	Horizon::Horizon engine;
	engine.Run();
	return 0;
}
