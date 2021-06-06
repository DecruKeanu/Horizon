#include "GamePCH.h"
#include <Horizon.h>
#include <SceneManager.h>
#include <ResourceManager.h>
#include "MainMenuScene.h"
#include "SinglePlayerlevel.h"
#include "CooperativeLevel.h"
#include "VersusLevel.h"
#include <SoundSystemServiceLocator.h>
#include <SDLSoundSystem.h>

void InitializeGame()
{
	srand(unsigned int(time(NULL)));

	// tell the resource manager where he can find the game data
	Horizon::ResourceManager::GetInstance().Init("../Game/Resources/");

	Horizon::SceneManager::GetInstance().AddScene(new MainMenuScene());
	//Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(3,0,3));
	//Horizon::SoundSystemServiceLocator::RegisterSoundSystem(new Horizon::SDLSoundSystem());
	//auto& soundSystem = Horizon::SoundSystemServiceLocator::GetSoundSystem();
	//soundSystem.AddAudio("../Data/sounds/LevelIntro.wav"); //0
	//soundSystem.AddAudio("../Data/sounds/QbertJump.wav"); //1
	//soundSystem.AddAudio("../Data/sounds/CoilyJump.wav"); //2
}

int main(int,char*[])
{
	InitializeGame();

	Horizon::Horizon engine;
	engine.Run();
	return 0;
}
