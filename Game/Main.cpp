#include "GamePCH.h"
#include <Horizon.h>


#include "SinglePlayerlevel.h"
#include "CooperativeLevel.h"
#include "VersusLevel.h"
#include "MainMenuScene.h"

#include <SceneManager.h>
#include <ResourceManager.h>

void InitializeGame()
{
	srand(unsigned int(time(NULL)));

	// tell the resource manager where he can find the game data
	Horizon::ResourceManager::GetInstance().Init("../Game/Resources/");

	Horizon::SceneManager::GetInstance().AddScene(new MainMenuScene());
	//Horizon::SceneManager::GetInstance().AddScene(new SinglePlayerLevel(2,0,3));

	std::cout << "INPUT:\n";
	std::cout << "MAIN MENU\n";
	std::cout << "Controller:\n";
	std::cout << "Move up : D-pad Up\n";
	std::cout << "Move down : D-pad down\n";
	std::cout << "Enter: A\n";
	std::cout << "-----------\n";
	std::cout << "Keyboard & Mouse:\n";
	std::cout << "Move up : Arrow up\n";
	std::cout << "Move down :Arrow down\n";
	std::cout << "Enter: Enter/Return\n";
	std::cout << "-----------\n";
	std::cout << "GAME\n";
	std::cout << "Controller (Player 1):\n";
	std::cout << "Moving : D-pad\n";
	std::cout << "Controller (Player 2):\n";
	std::cout << "Moving : AXYB (buttons)\n";
	std::cout << "-----------\n";
	std::cout << "Keyboard & Mouse (Player 1):\n";
	std::cout << "Moving : WASD\n";
	std::cout << "Keyboard & Mouse (Player 2):\n";
	std::cout << "Moving : Arrow keys\n";
	std::cout << "-----------\n";
}

int main(int,char*[])
{
	InitializeGame();

	Horizon::Horizon engine;
	engine.Run();
	return 0;
}
